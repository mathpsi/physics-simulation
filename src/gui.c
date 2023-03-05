#include "gui.h"
#include "shape.h"

#include <glad/glad.h>
#include <stdlib.h>

Gui_renderer *initialize_gui_renderer(GLuint program_id) {
    Gui_renderer *renderer = malloc(sizeof(Gui_renderer));
    renderer->objects = malloc(sizeof(Gui_object**));

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

void render_gui(Gui_renderer *renderer) {
    glUseProgram(renderer->program_id);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);

    glBindVertexArray(renderer->vao);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_unit_square), indices_unit_square, GL_STATIC_DRAW); /* ebo */
    glBufferData(GL_ARRAY_BUFFER, sizeof(unit_square), unit_square, GL_STATIC_DRAW); /* vao */

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glUniform1f(renderer->zoom, 1.0f);
    glUniform2f(renderer->move, 0.0f, 0.0f);
    glUniform2f(renderer->model, 0.5f, 0.5f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}
