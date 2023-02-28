#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR2_NULL vector2(.0f, .0f)
#define VECTOR3_NULL vector3(.0f, .0f, .0f);

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

Vector2 vector2_sum(Vector2 vector_1, Vector2 vector_2);
Vector3 vector3_sum(Vector3 vector_1, Vector3 vector_2);
Vector2 vector2_sub(Vector2 vector_1, Vector2 vector_2);
Vector3 vector3_sub(Vector3 vector_1, Vector3 vector_2);
int vector2_comp(Vector2 vector_1, Vector2 vector_2);
int vector3_comp(Vector3 vector_1, Vector3 vector_2);

#endif
