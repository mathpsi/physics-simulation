#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>

typedef enum
{
    rectangle
} Shape_t;

typedef struct
{
    GLuint *collide;
    GLuint collide_count;
} Collision;

typedef struct
{
    Shape_t shape;
    GLfloat *vertices;
} Shape;

typedef struct
{
    GLfloat x;
    GLfloat y;
    GLfloat radius;
    GLuint id;

    Shape *shape;
    Collision *collision;
} Object;

typedef struct
{
    GLuint object_count;
    GLuint vao;
    GLuint move;
    GLfloat x;
    GLfloat y;
    GLfloat z;
    Object **objects;
} Renderer;

Object *InitializeObject(GLfloat x, GLfloat y, Shape_t object_type, GLfloat width, GLfloat height, GLfloat radius, Renderer *renderer);

Renderer *InitializeRenderer(GLuint program_id);

void RenderObjects(Renderer *renderer, GLuint program_id);

#include "collision.h"

#endif
