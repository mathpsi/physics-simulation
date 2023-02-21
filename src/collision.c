#include "collision.h"
#include "object.h"

#include <glad/glad.h>
#include <math.h>
#include <stdlib.h>

int CircularCollision(Object *object_1, Object *object_2) {
    /* Distance = sqrt((x1 - x2)^2 + (y1 - y2)^2) */
    GLfloat distance = sqrt(pow(object_1->x - object_2->x, 2) + pow(object_1->y - object_2->y, 2));

    if (object_1->radius + object_2->radius > distance) {
	object_1->collision->collide_count++; object_2->collision->collide_count++;
	object_1->collision->collide = realloc(object_1->collision->collide, sizeof(GLuint*) * object_1->collision->collide_count);
	object_2->collision->collide = realloc(object_2->collision->collide, sizeof(GLuint*) * object_2->collision->collide_count);
	object_1->collision->collide[object_1->collision->collide_count - 1] = object_2->id;
	object_2->collision->collide[object_2->collision->collide_count - 1] = object_1->id;
        return 1;
    } else if (object_1->radius + object_2->radius < distance) {
        if (object_1->collision->collide_count > 0 && object_2->collision->collide_count > 0) {
	    object_1->collision->collide_count--; object_2->collision->collide_count--;
	}
        return 0;
    } else {
        return -1; /* Error */
    }
}