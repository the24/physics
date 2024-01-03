/**
 * \file dynamics.h
 * 
 * 
*/

#ifndef _geometry_h
#define _geometry_h

#include <stdio.h>
#include <stdint.h>

typedef struct {
    float x;
    float y;
} v2;

typedef struct {
    v2 pos;
    v2 velocity;
} RigidBody;

typedef struct {
    uint32_t count;
    RigidBody* objects;
} World;

void update(World* world, float dt);

#endif /* _geometry_h */