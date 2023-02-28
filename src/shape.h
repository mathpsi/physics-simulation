#ifndef SHAPE_H
#define SHAPE_H

#define CIRCLE_QUALITY 32
#define PI 3.14159265f

#include <glad/glad.h>

extern GLfloat unit_square[12];
extern GLuint  indices_unit_square[6];

GLfloat *GenerateCircle(GLfloat radius, int quality);
GLuint  *GenerateCircleIndices(int quality);

#endif
