/**
 * \file dynamics.h
 * 
 * Header for dynamics/physics struct and functions
*/

#ifndef _dynamics_h
#define _dynamics_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float x;
    float y;
} v2;

#define v2NULL (v2) {.0f, .0f}

v2 v2_from_pos(float x, float y);
v2 add_v2(v2 u, v2 v);
v2 sub_v2(v2 u, v2 v);
v2 scale_v2(v2 u, float lambda);


typedef struct {
    v2 pos;
    v2 prev_pos;
    v2 velocity;
    v2 acceleration;
} RigidBody;

RigidBody create_rigidbody(v2 pos, v2 velocity, v2 acceleration);
RigidBody create_rigidbody_v(v2 pos, v2 velocity);
RigidBody create_rigidbody_at_pos(v2 pos);

void set_rigidbody_pos(RigidBody* rigidbody, v2 new_pos);
void translate_rigidbody(RigidBody* rigidbody, v2 v);
void set_rigidbody_velocity(RigidBody* rigidbody, v2 new_speed);
void add_rigidbody_velocity(RigidBody* rigidbody, v2 v);
void set_rigidbody_acceleration(RigidBody* rigidbody, v2 new_acceleration);
void accelerate_rigidbody(RigidBody* rigidbody, v2 acceleration);


typedef struct {
    /* Dynamic array of rigidbody */
    unsigned int capacity;
    unsigned int size;
    RigidBody*   rigidbodies;
} World;

void update(World* world, float dt);
void init_world(World* world);

void add_rigidbody(World* world, RigidBody rigidbody);
void add_rigibodies(World* world, RigidBody* rigidbodies, unsigned int size);

#endif /* _dynamics_h */