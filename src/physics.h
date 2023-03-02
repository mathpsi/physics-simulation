#ifndef PHYSICS_H
#define PHYSICS_H

#include "object.h"

void ElasticCollision(Object *object_1, Object *object_2);
void SimulatePhysics(Renderer *renderer);

#endif
