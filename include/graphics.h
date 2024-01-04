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
#include <math.h>

#include "SDL2/SDL.h"
#include "dynamics.h"

#define max(a,b) (((a) > (b)) ? (a) : (b))

void draw_circle(SDL_Renderer* renderer, v2 pos, uint32_t radius);
/** An efficient antialiasing technique from Xiaolin Wu */
void aa_draw_circle(SDL_Renderer* renderer, v2 pos, uint32_t radius);

#endif /* _graphics_h */