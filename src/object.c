#include "object.h"

#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

/* Coordinates of triangle */
GLfloat tri_vertices[] = {
    -.5f,  .0f, .0f,
     .5f,  .0f, .0f,
     .0f,  .5f, .0f 
};

/* Coordinates of square */
GLfloat sq_vertices[] = {
    -.05f,  .05f,  .0f,
    -.05f, -.05f,  .0f,
     .05f, -.05f,  .0f,

    -.05f,  .05f,  .0f,
     .05f,  .05f,  .0f,
     .05f, -.05f,  .0f
};

Object *InitializeObject(GLfloat x, GLfloat y, object_type object_type, Renderer *renderer) {
    Object *object = malloc(sizeof(Object));
    object->x = x; object->y = y; object->object_type = object_type;
    renderer->objects[renderer->object_count] = object; renderer->object_count++;
    return object;
}

Renderer *InitializeRenderer(GLuint program_id) {
    Renderer *renderer = malloc(sizeof(Renderer));
    renderer->objects = malloc(sizeof(renderer->objects) * 5); /* Max objects = 5 */
    GLuint move = glGetUniformLocation(program_id, "move");
    
    GLuint square_vao, triangle_vao, square_vbo, triangle_vbo;
    
    glGenVertexArrays(1, &square_vao);
    glGenVertexArrays(1, &triangle_vao);
    glGenBuffers(1, &square_vbo);
    glGenBuffers(1, &triangle_vbo);
    
    glBindVertexArray(square_vao);
    glBindBuffer(GL_ARRAY_BUFFER, square_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sq_vertices), sq_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(triangle_vao);
    glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tri_vertices), tri_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void*)0);
    glEnableVertexAttribArray(0);
    
    renderer->object_count = 0; renderer->square_vao = square_vao; renderer->triangle_vao = triangle_vao; renderer->move = move;
    
    return renderer;
}

void RenderObjects(Renderer *renderer, GLuint program_id) {
    /* Clear the screen */
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program_id);

    /* Draw objects */
    /* TODO: Draw objects without calling glBufferData for each frame */
    for (int i = 0; i < renderer->object_count; i++) {
      if (renderer->objects[i]->object_type == square) {
    	    glBindVertexArray(renderer->square_vao);
    	    glBufferData(GL_ARRAY_BUFFER, sizeof(sq_vertices), sq_vertices, GL_STATIC_DRAW);
      } else {
	    glBindVertexArray(renderer->triangle_vao);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(tri_vertices), tri_vertices, GL_STATIC_DRAW);
      }

      glUniform2f(renderer->move, renderer->objects[i]->x, renderer->objects[i]->y);
      glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}
