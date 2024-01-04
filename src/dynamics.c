#include "dynamics.h"

#define max(a,b) (((a) > (b)) ? (a) : (b))

void check_collisions(World* world)
{
    for (size_t i = 0; i < world->size; i++)
    {
        RigidBody* object_1 = &world->rigidbodies[i];

        for (size_t j = i+1; j < world->size; j++)
        {
            RigidBody* object_2 = &world->rigidbodies[j];
            const v2 dir = {object_1->pos.x - object_2->pos.x,
                            object_1->pos.y - object_2->pos.y};
            float dist_sq = dir.x * dir.x + dir.y * dir.y;
            
            if (dist_sq < 20*20)
            {
                const float dist = sqrtf(dist_sq);
                const float delta = .5f * .75f * (dist - 20);

                object_1->pos = (v2) {object_1->pos.x - (dir.x / dist) * .5f * delta,
                                      object_1->pos.y - (dir.y / dist) * .5f * delta};
                object_2->pos = (v2) {object_2->pos.x + (dir.x / dist) * .5f * delta,
                                      object_2->pos.y + (dir.y / dist) * .5f * delta};

                float vx = object_1->velocity.x;
                object_1->velocity.x = object_2->velocity.x;
                object_2->velocity.x = vx;
                float vy = object_1->velocity.y;
                object_1->velocity.y = object_2->velocity.y;
                object_2->velocity.y = vy;
            }
        }
    }
}

void check_constraint(World* world)
{
    for (size_t i = 0; i < world->size; i++)
    {
        RigidBody* object = &(world->rigidbodies[i]);

        if (object->pos.y + 10 > 600)
        {
            object->pos.y = 600 - 10;
            object->velocity.y *= -.75f;
        } else if (object->pos.x + 10 > 800)
        {
            object->pos.x = 800 - 10;
            object->velocity.x *= -.75f;
        } else if (object->pos.x - 10 < 0)
        {
            object->pos.x = 10;
            object->velocity.x *= -.75f;
        }
    }
}

void update(World* world, float dt)
{
    check_constraint(world);
    check_collisions(world);

    for (size_t i = 0; i < world->size; i++)
    {
        RigidBody* object = &(world->rigidbodies[i]);

        // gravity
        object->velocity.y += 100*dt;
        
        object->prev_pos = object->pos;
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
