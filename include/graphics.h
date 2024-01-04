/**
 * \file graphics.h
 * 
 * 
*/

#ifndef _graphics_h
#define _graphics_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "SDL2/SDL.h"
#include "dynamics.h"

void DrawCircle(SDL_Renderer* renderer, v2 pos, uint32_t radius);

#endif /* _graphics_h */