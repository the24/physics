/**
 * \file graphics.h
 * 
 * Header for drawing functions.
*/

#ifndef _graphics_h
#define _graphics_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "SDL2/SDL.h"
#include "dynamics.h"

#define max(a,b) (((a) > (b)) ? (a) : (b))

void draw_circle(SDL_Renderer* renderer, v2 center, unsigned int radius);
/** An efficient antialiasing technique from Xiaolin Wu */
void aa_draw_circle(SDL_Renderer* renderer, v2 center, unsigned int radius);

#endif /* _graphics_h */