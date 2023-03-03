#ifndef PHYSICS_H
#define PHYSICS_H

#include "object.h"

void ElasticCollision(Object *object_1, Object *object_2);
void ApplyForce(Object *object, Vector2 force, GLfloat time, GLfloat time_now);
Vector2 AddForces(Object *object);
void SimulatePhysics(Renderer *renderer);

#endif
