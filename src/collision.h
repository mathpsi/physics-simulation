#ifndef COLLISION_H
#define COLLISION_H

#include "object.h"

int is_colliding(Object *object_1, Object *object_2);
int CircularCollision(Object *object_1, Object *object_2);
int RectangularCollision(Object *object_1, Object *object_2);

#endif
