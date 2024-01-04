/**
 * \file dynamics.h
 * 
 * 
*/

#ifndef _dynamics_h
#define _dynamics_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    float x;
    float y;
} v2;

#define v2NULL {.0f, .0f}

typedef struct {
    v2 pos;
    v2 velocity;
} RigidBody;

typedef struct {
    uint32_t   capacity;
    uint32_t   size;
    RigidBody* rigidbodies;
} World;

void update(World* world, float dt);
void init_world(World* world);
void add_rigidbody(World* world, RigidBody rigidbody);
void add_rigibodies(World* world, RigidBody* rigidbodies, uint32_t size);

#endif /* _dynamics_h */