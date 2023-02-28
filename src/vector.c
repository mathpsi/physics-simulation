#include "vector.h"

#include <glad/glad.h>
#include <stdlib.h>

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

Vector2 vector2_sum(Vector2 vector_1, Vector2 vector_2) {
    Vector2 vector;
    vector.x = vector_1.x + vector_2.x;
    vector.y = vector_1.y + vector_2.y;

    return vector;
}

Vector3 vector3_sum(Vector3 vector_1, Vector3 vector_2) {
    Vector3 vector;
    vector.x = vector_1.x + vector_2.x;
    vector.y = vector_1.y + vector_2.y;
    vector.z = vector_1.z + vector_2.z;

    return vector;
}

Vector2 vector2_sub(Vector2 vector_1, Vector2 vector_2) {
    Vector2 vector;
    vector.x = vector_1.x - vector_2.x;
    vector.y = vector_1.y - vector_2.y;

    return vector;
}

Vector3 vector3_sub(Vector3 vector_1, Vector3 vector_2) {
    Vector3 vector;
    vector.x = vector_1.x - vector_2.x;
    vector.y = vector_1.y - vector_2.y;
    vector.z = vector_1.z - vector_2.z;

    return vector;
}

int vector2_comp(Vector2 vector_1, Vector2 vector_2) {
    return(vector_1.x == vector_2.x && vector_1.y == vector_2.y);
}

int vector3_comp(Vector3 vector_1, Vector3 vector_2) {
    return(vector_1.x == vector_2.x && vector_1.y == vector_2.y && vector_1.z == vector_2.z);
}
