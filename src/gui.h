#ifndef GUI_H
#define GUI_H

#define GUI_BUTTON 0x0
#define GUI_TEXT 0x1

#include "vector.h"

#include <glad/glad.h>

typedef struct
{
    Vector2 position;
    Vector2 size;
} Gui_button;

typedef struct
{
    GLuint object_type;
    Gui_button *button;
} Gui_object;

typedef struct
{
    GLuint program_id;
    GLuint object_count;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLuint zoom;
    GLuint move;
    GLuint model;
    Gui_object **objects;
} Gui_renderer;


Gui_renderer *initialize_gui_renderer(GLuint program_id);
Gui_object *gui_button(Vector2 position, Vector2 size, Gui_renderer *renderer);

void gui_render(Gui_renderer *renderer);

int gui_collision(Gui_object *object, Vector2 cursor_position);

#endif
