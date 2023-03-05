#ifndef OBJECT_H
#define OBJECT_H

#include "vector.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

extern GLfloat zoom_value;

typedef struct
{
    GLuint *collide;
    GLuint collide_count;
} Collision;

typedef struct
{
    Vector2 force;
    GLfloat time;
    GLfloat apply_time;
    GLuint applied;
} Force;

typedef struct
{
    GLfloat mass;
    Vector2 force_net;
    Force force[50]; /* Max forces for now 50 */
    GLuint force_count;
    Vector2 acceleration;
    Vector2 velocity;
    GLuint coll;
} Rigidbody;

typedef enum
{
    black,
    white,
    yellow,
    green,
    red,
    blue,
    cyan
} Color;

typedef enum
{
    rectangle,
    circle /* Unavailable now */
} Shape_t;

typedef struct
{
    Shape_t shape;
    Vector2 size; /* Width and height */
    GLfloat radius;
} Shape;

typedef struct
{
    Vector2 position;
    Color color;
    GLuint id;

    Shape *shape;
    Collision *collision;
    Rigidbody *rigidbody;
} Object;

typedef struct
{
    GLuint object_count;
    GLuint program_id;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLuint zoom;
    GLuint move;
    GLuint model;
    GLuint color;
    GLfloat time;
    GLfloat time_delta;
    GLuint *indices_circle;
    GLfloat *unit_circle;
    Object **objects;
} Renderer;

Object *InitializeObject(Vector2 position, Shape_t shape, Vector2 size, GLfloat radius, Color color, Renderer *renderer);

Renderer *InitializeRenderer(GLuint program_id);

void RenderObjects(Renderer *renderer);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

#include "collision.h"

#endif
