#ifndef GUI_H
#define GUI_H

#include "vector.h"

#include <glad/glad.h>

typedef struct
{
    Vector2 position;
    Vector2 size;
} Gui_button;

typedef struct
{
    Gui_button button;
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

void render_gui(Gui_renderer *renderer);

#endif
