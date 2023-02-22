#include "object.h"
#include "collision.h"
#include "shape.h"

#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

Object *InitializeObject(GLfloat x, GLfloat y, Shape_t shape, GLfloat width, GLfloat height, GLfloat radius, Renderer *renderer) {
    Object *object = malloc(sizeof(Object));
    object->collision = malloc(sizeof(Collision));
    object->shape = malloc(sizeof(Shape));
    object->shape->vertices = malloc(sizeof(GLfloat**));
    object->shape->shape = shape;
    
    if (shape == rectangle) {
        object->shape->vertices = GenerateRectangle(width, height);
    } else {
        fprintf(stderr, "ERR_INITIALIZE_OBJECT\n");
    }
    object->collision->collide = malloc(sizeof(GLuint*));
    renderer->objects = realloc(renderer->objects, sizeof(Object**) * (renderer->object_count + 1));
    object->x = x; object->y = y; object->shape->shape = shape;  object->id = renderer->object_count; object->shape->width = width; object->shape->height = height; object->shape->radius = radius;
    renderer->objects[renderer->object_count] = object; renderer->object_count++; object->collision->collide_count = 0;
    return object;
}

Renderer *InitializeRenderer(GLuint program_id) {
    Renderer *renderer = malloc(sizeof(Renderer));
    renderer->objects = malloc(sizeof(Object**)); 
    GLuint move = glGetUniformLocation(program_id, "move");
    
    GLuint vao, vbo;
    
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    renderer->object_count = 0; renderer->vao = vao; renderer->move = move;
    
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
        /* Collision detection but not works well */
        for (int j = i + 1; j < renderer->object_count; j++) {
	    if (renderer->objects[i]->shape->shape == rectangle && renderer->objects[j]->shape->shape == rectangle) {
                RectangularCollision(renderer->objects[i], renderer->objects[j]);
	    } else if (renderer->objects[i]->shape->shape == circle && renderer->objects[j]->shape->shape == circle) {
                RectangularCollision(renderer->objects[i], renderer->objects[j]);
	    } else {
	        fprintf(stderr, "ERR_NO_COLLISION_FOUND");
	    }
	    
	}
	
        /* Object shape */
        glBindVertexArray(renderer->vao);
	GLfloat  data[18]; /* For now 18 */
	GetData(&data, renderer->objects[i]->shape->vertices);
        glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	
	if (renderer->objects[i]->collision->collide_count > 0) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

        renderer->objects[i]->collision->collide_count = 0;
	memset(renderer->objects[i]->collision->collide, 0, sizeof(renderer->objects[i]->collision->collide));
	
	glUniform2f(renderer->move, renderer->objects[i]->x, renderer->objects[i]->y);
	glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}
