#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H

#include <string>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <GL/glew.h>
#include <GL/glut.h>

#endif

extern GLuint texIDSphere;

int loadTexture(std::string s);

#endif
