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
    GLuint object_type;  
} Object;

typedef struct
{
    GLuint object_count;
    GLuint square_vao;
    GLuint triangle_vao;
    Object **objects;
} Renderer;

Object *InitializeObject(GLfloat x, GLfloat y, object_type object_type, Renderer *renderer);

Renderer *InitializeRenderer();

void RenderObjects(Renderer *renderer, GLuint program_id);

#endif
