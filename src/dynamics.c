#include "dynamics.h"

void update(World* world, float dt)
{
    for (size_t i = 0; i < world->size; i++)
    {
        RigidBody* object = &(world->objects[i]);

        object->velocity.y += 100*dt;
        if (object->pos.y + object->velocity.y*dt + 10 >= 600)
        {
            object->velocity.y *= -.8f;
        }
        object->pos.y += object->velocity.y*dt;
    }
}

void init_world(World *world)
{
    world->size = 0;
    world->capacity = 10;
    RigidBody* objects = malloc(world->capacity*sizeof(RigidBody));
    world->objects = objects;
}

void add_object(World* world, RigidBody object)
{
    if (world->size + 1 > world->capacity)
    {
        world->capacity *= 2;
        world->objects = realloc(world->objects, world->capacity*sizeof(RigidBody));
        world->objects[world->size++] = object;
    }
    else world->objects[world->size++] = object;

}

void add_objects(World *world, RigidBody *objects, uint32_t size)
{
    for (size_t i = 0; i < size; i++) add_object(world, objects[i]);
}
