#ifndef VECTOR_H
#define VECTOR_H

#include <glad/glad.h>

typedef struct
{
    GLfloat x;
    GLfloat y;
} Vector2;

typedef struct
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
} Vector3;

Vector2 vector2(GLfloat x, GLfloat y);
Vector3 vector3(GLfloat x, GLfloat y, GLfloat z);

#endif
