#include "physics.h"
#include "object.h"
#include "vector.h"
#include <stdio.h>

void ElasticCollision(Object *object_1, Object *object_2) {
    if (object_1->rigidbody.coll == 0 && object_2->rigidbody.coll == 0) {
        /* Final velocity = 2m1v1 + m1v1 - m2v1 / m2 + m1 */
        GLfloat m1 = object_1->rigidbody.mass; GLfloat m2 = object_2->rigidbody.mass;
	Vector2 v1 = object_1->rigidbody.velocity; Vector2 v2 = object_2->rigidbody.velocity;
	object_1->rigidbody.velocity = vector2_dnum(m2 + m1, vector2_sub(vector2_sum(vector2_mnum(2.0f, vector2_mnum(m2, v2)), vector2_mnum(m1, v1)), vector2_mnum(m2, v1)));
	object_2->rigidbody.velocity = vector2_dnum(m1 + m2, vector2_sub(vector2_sum(vector2_mnum(2.0f, vector2_mnum(m1, v1)), vector2_mnum(m2, v2)), vector2_mnum(m1, v2)));
	printf("velocity_1: (%f, %f); velocity_2: (%f, %f)\n", object_1->rigidbody.velocity.x, object_1->rigidbody.velocity.y, object_2->rigidbody.velocity.x, object_2->rigidbody.velocity.y);
	object_1->rigidbody.coll = 1; object_2->rigidbody.coll = 1;
    } else {
        object_1->rigidbody.coll = 0; object_2->rigidbody.coll = 0;
    }
}

void SimulatePhysics(Renderer *renderer) {
    for (int i = 0; i < renderer->object_count; i++) {
        Object *object = renderer->objects[i];
	
	object->rigidbody.velocity = vector2_sum(object->rigidbody.velocity, object->rigidbody.acceleration);
	object->position = vector2_sum(object->position, vector2_mnum(renderer->time_delta, object->rigidbody.velocity));
    }
}
