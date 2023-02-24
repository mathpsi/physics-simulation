#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>

typedef struct
{
    GLuint *collide;
    GLuint collide_count;
} Collision;

typedef enum
{
    rectangle,
    circle /* Unavailable now */
} Shape_t;

typedef struct
{
    Shape_t shape;
    GLfloat width;
    GLfloat height;
    GLfloat radius;
} Shape;

typedef struct
{
    GLfloat x;
    GLfloat y;
    GLuint id;

    Shape *shape;
    Collision *collision;
} Object;

typedef struct
{
    GLuint object_count;
    GLuint vao;
    GLuint ebo;
    GLuint move;
    GLuint model;
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
