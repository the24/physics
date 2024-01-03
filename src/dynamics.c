#include "dynamics.h"

void update(World* world, float dt)
{
    for (size_t i = 0; i < world->count; i++)
    {
	RigidBody* object = &(world->objects[i]);

	object->velocity.y += 100*dt;
	if (object->pos.y + object->velocity.y*dt + 10 >= 600)
	{
	    object->velocity.y *= -.5f;
	}
	object->pos.y += object->velocity.y*dt;
    }
}