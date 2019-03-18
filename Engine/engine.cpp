#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

#include "parser.h"


float translate_x, translate_y, translate_z, rotate_y, rotate_x, scale = 1;
float px = 0, py = 0, pz = 10;
GLenum mode = GL_FILL;
GLenum face = GL_FRONT;

int startX, startY;
int alpha = 0, beta = 0;

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
    std::list<Group>::iterator it;

    for (it = g.begin(); it != g.end(); ++it) {
        glPushMatrix();
        std::vector<float> v = it->getVertices();

        for (int i = it->getNextTransf(); i != 0; i = it->getNextTransf()) {
            if(i == TRANSLATE) {
                float* translate = it->getTranslate();
                glTranslatef(translate[0], translate[1], translate[2]);
            }
            else if(i == ROTATE) {
                float* rotate = it->getRotate();
                glRotatef(rotate[0], rotate[1], rotate[2], rotate[3]);
            }
            else if(i == SCALE) {
                float * scale = it->getScale();
                glScalef(scale[0], scale[1], scale[2]);
            }
        }

        for (size_t i = 0; i + 9 <= v.size(); i += 9) {
            glBegin(GL_TRIANGLES);
            glVertex3f(v[i], v[i + 1], v[i + 2]);
            glVertex3f(v[i + 3], v[i + 4], v[i + 5]);
            glVertex3f(v[i + 6], v[i + 7], v[i + 8]);
            glEnd();
        }

        draw(it->getChildGroups());
        glPopMatrix();
    }
}

void renderScene() {
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
    draw(groups);

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
            if(scale > 0.1) scale -= 0.1;
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
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    std::string xml_name = "SistemaSolar.xml";
    if (argc == 2) xml_name = argv[1];
    xml(xml_name);

    // enter GLUT's main loop
    glutMainLoop();

    return 1;
}
