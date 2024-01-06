#include "dynamics.h"

v2 v2_from_pos(float x, float y)
{
    return (v2) {
        .x = x,
        .y = y,
    };
}

v2 add_v2(v2 u, v2 v)
{
    return (v2) {
        .x = u.x + v.x,
        .y = u.y + v.y,
    };
}

v2 sub_v2(v2 u, v2 v)
{
    return (v2) {
        .x = u.x - v.x,
        .y = u.y - v.y,
    };
}

v2 scale_v2(v2 u, float lambda)
{
    return (v2) {
        .x = u.x * lambda,
        .y = u.y * lambda,
    };
}


void check_collisions(World* world)
{
    for (unsigned int i = 0; i < world->size; i++)
    {
        RigidBody* object_1 = &world->rigidbodies[i];

        for (unsigned int j = i+1; j < world->size; j++)
        {
            RigidBody* object_2 = &world->rigidbodies[j];
            const v2 dir = sub_v2(object_1->pos, object_2->pos);
            const float dist_sq = dir.x * dir.x + dir.y * dir.y;
            
            if (dist_sq >= 20*20) continue;

            const float dist = sqrtf(dist_sq);
            const float delta = .5f * .75f * (dist - 20);

            translate_rigidbody(object_1, scale_v2(dir, -delta/(2*dist)));
            translate_rigidbody(object_2, scale_v2(dir, delta/(2*dist)));

            float vx = object_1->velocity.x;
            object_1->velocity.x = object_2->velocity.x;
            object_2->velocity.x = vx;
            float vy = object_1->velocity.y;
            object_1->velocity.y = object_2->velocity.y;
            object_2->velocity.y = vy;
        }
    }
}

void check_constraint(World* world)
{
    for (unsigned int i = 0; i < world->size; i++)
    {
        RigidBody* object = &(world->rigidbodies[i]);

        if (object->pos.y - 10 < 0)
        {
            object->pos.y = 10;
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

RigidBody create_rigidbody(v2 pos, v2 velocity, v2 acceleration)
{
    return (RigidBody) {pos, pos, velocity, acceleration};
}

RigidBody create_rigidbody_v(v2 pos, v2 velocity)
{
    return create_rigidbody(pos, velocity, v2NULL);
}

RigidBody create_rigidbody_at_pos(v2 pos)
{
    return create_rigidbody(pos, v2NULL, v2NULL);
}


void set_rigidbody_pos(RigidBody* rigidbody, v2 new_pos)
{
    rigidbody->pos = new_pos;
}

void translate_rigidbody(RigidBody* rigidbody, v2 v)
{
    rigidbody->pos = add_v2(rigidbody->pos, v);
}

void set_rigidbody_velocity(RigidBody* rigidbody, v2 new_speed)
{
    rigidbody->velocity = new_speed;
}

void add_rigidbody_velocity(RigidBody *rigidbody, v2 v)
{
    rigidbody->velocity = add_v2(rigidbody->velocity, v);
}

void set_rigidbody_acceleration(RigidBody *rigidbody, v2 new_acceleration)
{
    rigidbody->acceleration = new_acceleration;
}

void accelerate_rigidbody(RigidBody* rigidbody, v2 acceleration)
{
    rigidbody->acceleration = add_v2(rigidbody->acceleration, acceleration);
}


void update(World* world, float dt)
{
    check_constraint(world);
    check_collisions(world);

    for (unsigned int i = 0; i < world->size; i++)
    {
        RigidBody* object = &(world->rigidbodies[i]);

        // gravity
        object->velocity.y -= 100*dt;
        
        object->prev_pos = object->pos;
        translate_rigidbody(object, scale_v2(object->velocity, dt));
    }
}

void init_world(World* world)
{
    world->size = 0;
    world->capacity = 2;
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

void add_rigibodies(World* world, RigidBody* rigidbodies, unsigned int size)
{
    for (unsigned int i = 0; i < size; i++) add_rigidbody(world, rigidbodies[i]);
}
