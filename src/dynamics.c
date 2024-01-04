#include "dynamics.h"

void update(World* world, float dt)
{
    for (size_t i = 0; i < world->size; i++)
    {
        RigidBody* object = &(world->rigidbodies[i]);

        object->velocity.y += 100*dt;
        if (object->pos.y + object->velocity.y*dt + 10 >= 600)
        {
            object->velocity.y *= -.8f;
        } else if (object->pos.x + object->velocity.x*dt + 10 >= 800 ||
                   object->pos.x + object->velocity.x*dt - 10 <= 0)
        {
            object->velocity.x *= -1;
        }
        
        object->pos.x += object->velocity.x*dt;
        object->pos.y += object->velocity.y*dt;
    }
}

void init_world(World *world)
{
    world->size = 0;
    world->capacity = 10;
    world->rigidbodies = malloc(world->capacity*sizeof(RigidBody));
}

void add_rigidbody(World* world, RigidBody object)
{
    if (world->size + 1 > world->capacity)
    {
        world->capacity *= 2;
        world->rigidbodies = realloc(world->rigidbodies, world->capacity*sizeof(RigidBody));
        world->rigidbodies[world->size++] = object;
    }
    else world->rigidbodies[world->size++] = object;

}

void add_rigibodies(World *world, RigidBody *rigidbodies, uint32_t size)
{
    for (size_t i = 0; i < size; i++) add_rigidbody(world, rigidbodies[i]);
}
