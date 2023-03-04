#include "physics.h"
#include "object.h"
#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

void ElasticCollision(Object *object_1, Object *object_2) {
    if (object_1->rigidbody->coll == 0 && object_2->rigidbody->coll == 0) {
        /* Final velocity = 2m1v1 + m1v1 - m2v1 / m2 + m1 */
        GLfloat m1 = object_1->rigidbody->mass; GLfloat m2 = object_2->rigidbody->mass;
	Vector2 v1 = object_1->rigidbody->velocity; Vector2 v2 = object_2->rigidbody->velocity;
	object_1->rigidbody->velocity = vector2_dnum(m2 + m1, vector2_sub(vector2_sum(vector2_mnum(2.0f, vector2_mnum(m2, v2)), vector2_mnum(m1, v1)), vector2_mnum(m2, v1)));
	object_2->rigidbody->velocity = vector2_dnum(m1 + m2, vector2_sub(vector2_sum(vector2_mnum(2.0f, vector2_mnum(m1, v1)), vector2_mnum(m2, v2)), vector2_mnum(m1, v2)));
	printf("velocity_1: (%f, %f); velocity_2: (%f, %f)\n", object_1->rigidbody->velocity.x, object_1->rigidbody->velocity.y, object_2->rigidbody->velocity.x, object_2->rigidbody->velocity.y);
	object_1->rigidbody->coll = 1; object_2->rigidbody->coll = 1;
    } else {
        object_1->rigidbody->coll = 0; object_2->rigidbody->coll = 0;
    }
}

void ApplyForce(Object *object, Vector2 force, GLfloat time, GLfloat time_now) {
    object->rigidbody->force_count++;
    //object->rigidbody->force = realloc(object->rigidbody->force, sizeof(Force) * object->rigidbody->force_count);
    object->rigidbody->force[object->rigidbody->force_count - 1].force = force;
    object->rigidbody->force[object->rigidbody->force_count - 1].time = time;
    object->rigidbody->force[object->rigidbody->force_count - 1].applied = 1;
    object->rigidbody->force[object->rigidbody->force_count - 1].apply_time = time_now;
}

Vector2 AddForces(Object *object) {
    Vector2 force_net = VECTOR2_NULL;
    for (int i = 0; i < object->rigidbody->force_count; i++) {
        if (object->rigidbody->force[i].applied) {
            force_net = vector2_sum(force_net, object->rigidbody->force[i].force);
	}
    }

    return force_net;
}

void SimulatePhysics(Renderer *renderer) {
    for (int i = 0; i < renderer->object_count; i++) {
        Object *object = renderer->objects[i];
	object->rigidbody->force_net = AddForces(object);
        for (int i = 0; i < object->rigidbody->force_count; i++) {
	    if (renderer->time - object->rigidbody->force[i].apply_time >= object->rigidbody->force[i].time && object->rigidbody->force[i].applied == 1) {
	        object->rigidbody->force[i].applied = 0;
		object->rigidbody->force_net = vector2_sub(object->rigidbody->force_net, object->rigidbody->force[i].force);
	    }
	}

	/* F=ma Thank you, Sir Isaac Newton */
	object->rigidbody->acceleration = vector2_dnum(object->rigidbody->mass, vector2_mnum(renderer->time_delta, object->rigidbody->force_net));
	object->rigidbody->velocity = vector2_sum(object->rigidbody->velocity, object->rigidbody->acceleration);
	object->position = vector2_sum(object->position, vector2_mnum(renderer->time_delta, object->rigidbody->velocity));
    }
}
