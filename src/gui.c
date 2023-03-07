#include "gui.h"
#include "shape.h"

#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>

Gui_renderer *initialize_gui_renderer(GLuint program_id) {
    Gui_renderer *renderer = malloc(sizeof(Gui_renderer));
    renderer->objects = malloc(sizeof(Gui_object**));
    renderer->object_count = 0;

    GLuint vao, vbo, ebo;

    GLuint zoom = glGetUniformLocation(program_id, "zoom");
    GLuint move = glGetUniformLocation(program_id, "move");
    GLuint model = glGetUniformLocation(program_id, "model_wh");
    
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    renderer->vao = vao; renderer->vbo = vbo; renderer->ebo = ebo; renderer->program_id = program_id; renderer->move = move; renderer->model = model; renderer->zoom = zoom;
    
    return renderer;    
}

Gui_object *gui_button(Vector2 position, Vector2 size, Gui_renderer *renderer) {
    Gui_object *button = malloc(sizeof(Gui_object));
    button->button = malloc(sizeof(Gui_button));
    renderer->objects = realloc(renderer->objects, sizeof(Gui_object**) * (renderer->object_count + 1));
    button->object_type = GUI_BUTTON; button->button->position = position; button->button->size = size;
    renderer->objects[renderer->object_count] = button; renderer->object_count++;
    return button;
}

void gui_render(Gui_renderer *renderer) {
    glUseProgram(renderer->program_id);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);

    glBindVertexArray(renderer->vao);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_unit_square), indices_unit_square, GL_STATIC_DRAW); /* ebo */
    glBufferData(GL_ARRAY_BUFFER, sizeof(unit_square), unit_square, GL_STATIC_DRAW); /* vao */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    for (int i = 0; i < renderer->object_count; i++) {
        Gui_object *object = renderer->objects[i];
	
        glUniform1f(renderer->zoom, 1.0f);
	
	switch (object->object_type)
	{
	    case GUI_BUTTON:
	    {        
	        glUniform2f(renderer->move, object->button->position.x, object->button->position.y);
	        glUniform2f(renderer->model, object->button->size.x, object->button->size.y);      
	    }
	}
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    }
}

int gui_collision(Gui_object *object, Vector2 cursor_position) {
    switch (object->object_type)
    {
        case GUI_BUTTON:
	{
         
	}
      
    } 
}
