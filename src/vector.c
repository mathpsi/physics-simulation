#include "vector.h"

#include <glad/glad.h>

Vector2 vector2(GLfloat x, GLfloat y) {
    Vector2 vector;
    vector.x = x; vector.y = y;
    return vector;
}

Vector3 vector3(GLfloat x, GLfloat y, GLfloat z) {
    Vector3 vector;
    vector.x = x; vector.y = y; vector.z = z;
    return vector;
}
