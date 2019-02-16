#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glut.h>

#endif

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "parser.h"

std::vector<float> coord;

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

void saveVertices() {
    // nome dos ficheiros com as coordenadas está guardado em files_list
}

void draw() {

}

void renderScene() {
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0,
              0.0, 0.0, -1.0,
              0.0f, 1.0f, 0.0f);

    // put drawing instructions here
    draw();

    // End of frame
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    // put GLUT init here
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(200, 0);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Sistema Solar");

    // put callback registration here
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    std::string xml_name = "ss.xml";
    if(argc == 2) xml_name = argv[1];
    xml(xml_name);

    saveVertices();

    // enter GLUT's main loop
    glutMainLoop();

    return 1;
}
