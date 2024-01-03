/**
 * \file dynamics.h
 * 
 * 
*/

#ifndef _geometry_h
#define _geometry_h

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
    RigidBody* objects;
} World;

void update(World* world, float dt);
void init_world(World* world);
void add_object(World* world, RigidBody object);
void add_objects(World* world, RigidBody* objects, uint32_t size);

#endif /* _geometry_h */