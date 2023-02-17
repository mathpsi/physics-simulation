#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>

typedef enum
{
  square,
  triangle
} object_type;

typedef struct
{
    GLfloat x;
    GLfloat y;
    GLfloat radius;
    GLuint object_type;
    GLuint id;
    GLuint *collide;
    GLuint collide_count;
} Object;

typedef struct
{
    GLuint object_count;
    GLuint square_vao;
    GLuint triangle_vao;
    GLuint move;
    GLfloat x;
    GLfloat y;
    GLfloat z;
    Object **objects;
} Renderer;

Object *InitializeObject(GLfloat x, GLfloat y, object_type object_type, Renderer *renderer);

Renderer *InitializeRenderer(GLuint program_id);

void RenderObjects(Renderer *renderer, GLuint program_id);

#endif
