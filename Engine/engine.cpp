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

GLuint *vertices_buffers;
int vertices_nIndB = 0;

GLuint *textures_buffers;
int textures_nIndB = 0;

GLuint *normals_buffers;

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

void draw(std::list<Group> g) {
    std::list<Group>::iterator it_g;

    for (it_g = g.begin(); it_g != g.end(); ++it_g) {
        glPushMatrix();

        for (int i = it_g->getNextTransf(); i != 0; i = it_g->getNextTransf()) {
            if (i == TRANSLATE) {
                if (it_g->isTransCatmull()) {
                    float pos[3], xD[3], yD[3] = {0, 1, 0}, zD[3];

                    std::map<int, float *> points = it_g->getPointsCatmull();

                    float t = glutGet(GLUT_ELAPSED_TIME) / (it_g->getTime() * 1000);

                    if (drawCatmull) {
                        glBindBuffer(GL_ARRAY_BUFFER, vertices_buffers[vertices_nIndB]);
                        glVertexPointer(3, GL_FLOAT, 0, nullptr);

                        glDrawArrays(GL_LINE_LOOP, 0, it_g->getCatmullCurve().size() / 3);
                    }
                    vertices_nIndB++;

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
                    float *translate = it_g->getTranslate();
                    glTranslatef(translate[0], translate[1], translate[2]);
                }
            } else if (i == ROTATE) {
                if (it_g->isRotateCatmull()) {
                    float *rotate = it_g->getRotate();
                    glRotatef((glutGet(GLUT_ELAPSED_TIME) * 360) / (rotate[0] * 1000), rotate[1], rotate[2], rotate[3]);
                } else {
                    float *rotate = it_g->getRotate();
                    glRotatef(rotate[0], rotate[1], rotate[2], rotate[3]);
                }
            } else if (i == SCALE) {
                float *scale = it_g->getScale();
                glScalef(scale[0], scale[1], scale[2]);
            }
        }

        std::list<Model> m = it_g->getModels();
        std::list<Model>::iterator it_m;

        for (it_m = m.begin(); it_m != m.end(); ++it_m) {
            std::vector<float> v = it_m->getVertices();

            glBindBuffer(GL_ARRAY_BUFFER, vertices_buffers[vertices_nIndB]);
            glVertexPointer(3, GL_FLOAT, 0, nullptr);

            if (it_m->hasTextures()) {
                glBindBuffer(GL_ARRAY_BUFFER, normals_buffers[vertices_nIndB]);
                glNormalPointer(GL_FLOAT, 0, nullptr);
                glBindBuffer(GL_ARRAY_BUFFER, textures_buffers[textures_nIndB++]);
                glTexCoordPointer(2, GL_FLOAT, 0, nullptr);
                glBindTexture(GL_TEXTURE_2D, it_m->getTextID());
            }

            vertices_nIndB++;
            glDrawArrays(GL_TRIANGLES, 0, v.size());

            glBindTexture(GL_TEXTURE_2D, 0);

            draw(it_g->getChildGroups());
            glPopMatrix();
        }
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
    vertices_nIndB = 0;
    textures_nIndB = 0;
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

void bindBuffers(std::list<Group> g) {
    std::list<Group>::iterator it_g;

    for (it_g = g.begin(); it_g != g.end(); ++it_g) {
        if (it_g->isTransCatmull()) {
            std::vector<float> curve = it_g->getCatmullCurve();

            glBindBuffer(GL_ARRAY_BUFFER, vertices_buffers[vertices_nIndB]);
            glBufferData(GL_ARRAY_BUFFER, curve.size() * sizeof(float), curve.data(), GL_STATIC_DRAW);
            vertices_nIndB++;
        }

        std::list<Model> m = it_g->getModels();
        std::list<Model>::iterator it_m;

        for (it_m = m.begin(); it_m != m.end(); ++it_m) {
            // vertices
            std::vector<float> vertices = it_m->getVertices();
            glBindBuffer(GL_ARRAY_BUFFER, vertices_buffers[vertices_nIndB]);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data() , GL_STATIC_DRAW);

            // normals
            std::vector<float> normals = it_m->getNormals();
            glBindBuffer(GL_ARRAY_BUFFER, normals_buffers[vertices_nIndB]);
            glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
            vertices_nIndB++;

            // textures
            std::vector<float> textures = it_m->getTextures();
            glBindBuffer(GL_ARRAY_BUFFER, textures_buffers[textures_nIndB++]);
            glBufferData(GL_ARRAY_BUFFER, textures.size() * sizeof(float), textures.data(), GL_STATIC_DRAW);
        }

        bindBuffers(it_g->getChildGroups());
    }
}

void initBuffers() {
    // Generate Buffer Object
    vertices_buffers = new GLuint[vert_nBuffers];
    glGenBuffers(vert_nBuffers, vertices_buffers);

    normals_buffers = new GLuint[vert_nBuffers];
    glGenBuffers(vert_nBuffers, normals_buffers);

    textures_buffers = new GLuint[text_nBuffers];
    glGenBuffers(text_nBuffers, textures_buffers);
}

void initGL() {
    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // Enable Buffers
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glClearColor(0, 0, 0, 0);

    glEnable(GL_TEXTURE_2D);
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

#ifndef __APPLE__
    glewInit();
#endif

    std::string xml_name = "SistemaSolar.xml";
    if (argc == 2) xml_name = argv[1];
    xml(xml_name);

    initGL();

    initBuffers();
    bindBuffers(groups);

    // enter GLUT's main loop
    glutMainLoop();

    return 1;
}