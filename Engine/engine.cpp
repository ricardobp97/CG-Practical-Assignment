#ifdef __APPLE__
#include <GLUT/glew.h>
#include <GLUT/glut.h>
#else

#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>

#endif

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

#define _USE_MATH_DEFINES

#include <math.h>

#include "parser.h"
#include "catmull-rom.h"

float translate_x, translate_y, translate_z, rotate_y, rotate_x, scale = 1;
float px = 0, py = 0, pz = 10;
GLenum mode = GL_FILL;
GLenum face = GL_FRONT;
int timebase = 0, frame = 0;

int startX, startY;
int alpha = 0, beta = 0;
bool drawCatmull = false;

GLuint *buffers;
int nIndB = 0;

void changeSize(int w, int h) {
    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if (h == 0)
        h = 1;

    // compute window's aspect ratio
    auto ratio = static_cast<float>(w * 1.0 / h);

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);

    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void renderCatmullRomCurve(std::map<int, float *> p) {
// draw curve using line segments with GL_LINE_LOOP
    glBegin(GL_LINE_LOOP);
    for (float gt = 0; gt < 1; gt += 0.0001) {
        float pos[3];
        float deriv[3];

        getGlobalCatmullRomPoint(gt, pos, deriv, p);

        glVertex3f(pos[0], pos[1], pos[2]);
    }
    glEnd();
}

void draw(std::list<Group> g) {
    std::list<Group>::iterator it;

    for (it = g.begin(); it != g.end(); ++it) {
        glPushMatrix();
        std::vector<float> v = it->getVertices();

        for (int i = it->getNextTransf(); i != 0; i = it->getNextTransf()) {
            if (i == TRANSLATE) {
                if (it->isTransCatmull()) {
                    float pos[3], xD[3], yD[3] = {0, 1, 0}, zD[3];

                    std::map<int, float *> points = it->getPointsCatmull();

                    float t = glutGet(GLUT_ELAPSED_TIME) / (it->getTime() * 1000);

                    if (drawCatmull) renderCatmullRomCurve(points);
                    getGlobalCatmullRomPoint(t, pos, xD, points);

                    normalize(xD);
                    cross(xD, yD, zD);
                    normalize(zD);
                    cross(zD, xD, yD);

                    glTranslatef(pos[0], pos[1], pos[2]);

                    float m[16];
                    buildRotMatrix(xD, yD, zD, m);
                    glMultMatrixf(m);
                } else {
                    float *translate = it->getTranslate();
                    glTranslatef(translate[0], translate[1], translate[2]);
                }
            } else if (i == ROTATE) {
                if (it->isRotateCatmull()) {
                    float *rotate = it->getRotate();
                    glRotatef((glutGet(GLUT_ELAPSED_TIME) * 360) / (rotate[0] * 1000), rotate[1], rotate[2], rotate[3]);
                }
                else {
                    float *rotate = it->getRotate();
                    glRotatef(rotate[0], rotate[1], rotate[2], rotate[3]);
                }
            } else if (i == SCALE) {
                float *scale = it->getScale();
                glScalef(scale[0], scale[1], scale[2]);
            }
        }

        glBindBuffer(GL_ARRAY_BUFFER, buffers[nIndB]);
        glVertexPointer(3, GL_FLOAT, 0, nullptr);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(v.size()));
        nIndB++;

        draw(it->getChildGroups());
        glPopMatrix();
    }
}

void renderScene() {
    float fps;
    int time;
    char s[64];

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(px, py, pz,
              0.0, 0.0, 0.0,
              0.0f, 1.0f, 0.0f);

    // put the geometric transformations here
    glTranslatef(translate_x, translate_y, translate_z);
    glRotatef(rotate_y, 0, 1, 0);
    glRotatef(rotate_x, 1, 0, 0);
    glScalef(scale, scale, scale);
    glPolygonMode(face, mode);

    // put drawing instructions here
    nIndB = 0;
    draw(groups);

    frame++;
    time = glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000) {
        fps = frame * 1000.0 / (time - timebase);
        timebase = time;
        frame = 0;
        sprintf(s, "Engine | FPS: %f", fps);
        glutSetWindowTitle(s);
    }

    // End of frame
    glutSwapBuffers();
}

void processKeys(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            translate_x += 0.2;
            break;
        case 'd':
            translate_x -= 0.2;
            break;
        case 'w':
            translate_z += 0.2;
            break;
        case 's':
            translate_z -= 0.2;
            break;
        case 'q':
            translate_y += 0.2;
            break;
        case 'e':
            translate_y -= 0.2;
            break;
        case '-':
            if (scale > 0.1) scale -= 0.1;
            break;
        case '+':
            scale += 0.1;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void processSpecialKeys(int key_code, int x, int y) {
    // put code to process special keys in here
    switch (key_code) {
        case GLUT_KEY_UP:
            rotate_x -= 10;
            break;
        case GLUT_KEY_DOWN:
            rotate_x += 10;
            break;
        case GLUT_KEY_LEFT:
            rotate_y -= 10;
            break;
        case GLUT_KEY_RIGHT:
            rotate_y += 10;
            break;
        case GLUT_KEY_F2:
            if (mode == GL_FILL) mode = GL_LINE;
            else if (mode == GL_LINE) mode = GL_POINT;
            else mode = GL_FILL;
            break;
        case GLUT_KEY_F3:
            drawCatmull = !drawCatmull;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void processMouseButtons(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        startX = x;
        startY = y;
    } else if (state == GLUT_UP) {
        alpha += (startX - x);
        beta += (y - startY);
    }
}

void processMouseMotion(int x, int y) {
    int deltaX = startX - x;
    int deltaY = y - startY;

    int alphaAux = alpha + deltaX;
    int betaAux = beta + deltaY;

    if (betaAux > 90)
        betaAux = 90;
    else if (betaAux < -90)
        betaAux = -90;

    px = static_cast<float>(10 * sin(alphaAux * M_PI / 180) * cos(betaAux * M_PI / 180));
    py = static_cast<float>(10 * sin(betaAux * M_PI / 180));
    pz = static_cast<float>(10 * cos(alphaAux * M_PI / 180) * cos(betaAux * M_PI / 180));
}

void bufferInit(std::list<Group> g) {
    std::list<Group>::iterator it;

    for (it = g.begin(); it != g.end(); ++it) {
        std::vector<float> vertices = it->getVertices();
        glBindBuffer(GL_ARRAY_BUFFER, buffers[nIndB]);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        nIndB++;

        bufferInit(it->getChildGroups());
    }
}

int main(int argc, char **argv) {
    // put GLUT init here
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(200, 0);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Engine");

    // put callback registration here
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    // Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);
    glutMouseFunc(processMouseButtons);
    glutMotionFunc(processMouseMotion);

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    std::string xml_name = "SistemaSolar.xml";
    if (argc == 2) xml_name = argv[1];
    xml(xml_name);

#ifndef __APPLE__
    glewInit();
#endif

    // Enable Buffers
    glEnableClientState(GL_VERTEX_ARRAY);

    // Generate Buffer Object
    buffers = new GLuint[nBuffers];
    glGenBuffers(nBuffers, buffers);
    bufferInit(groups);

    // enter GLUT's main loop
    glutMainLoop();

    return 1;
}