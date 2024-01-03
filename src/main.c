#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "dynamics.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define ASSERT(_e, ...) if (!(_e)) { fprintf(stderr, __VA_ARGS__); exit(EXIT_FAILURE); }

struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool quit;
} state;

World* init_world()
{
    uint32_t count = 2;

    RigidBody* objects = malloc(count*sizeof(RigidBody));

    objects[0] = (RigidBody) {{10, 20}, {0, 0}};
    objects[1] = (RigidBody) {{40, 100}, {0, 0}};

    World* world = malloc(sizeof(RigidBody));
    world->count = count;
    world->objects = objects;

    return world;
}


void handle_event(World** world)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                state.quit = true;
                break;
            
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_r) *world = init_world();
                break;
            
            default:
                break;
        }
    }
}

void render(World* world)
{
    SDL_SetRenderDrawColor(state.renderer, 255, 0, 0, 255);

    for (size_t i = 0; i < world->count; i++)
    {
        RigidBody* object = &(world->objects[i]);

        SDL_Rect rect = {(int) object->pos.x, (int) object->pos.y, 10, 10};
        SDL_RenderDrawRect(state.renderer, &rect);
    }

    SDL_RenderPresent(state.renderer);

    SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
    SDL_RenderClear(state.renderer);
}


int main(int argc, char **argv)
{
    ASSERT(!SDL_Init(SDL_INIT_VIDEO), "Cannot initialize SDL : %s\n", SDL_GetError());

    state.window = SDL_CreateWindow("SDL Window",
                SDL_WINDOWPOS_CENTERED_DISPLAY(0),
                SDL_WINDOWPOS_CENTERED_DISPLAY(0),
                WIN_WIDTH,
                WIN_HEIGHT,
                SDL_WINDOW_SHOWN);

    ASSERT(state.window, "Failed to create window : %s\n", SDL_GetError());

    state.renderer = SDL_CreateRenderer(state.window,
                -1,
                SDL_RENDERER_ACCELERATED);

    ASSERT(state.renderer, "Failed to create renderer : %s\n", SDL_GetError());

    World* world = init_world();

    uint32_t last_update = SDL_GetTicks();
    while(!state.quit)
    {
        handle_event(&world);
        uint32_t current = SDL_GetTicks();
        float dt = (current - last_update) / 1000.f;
        last_update = current;
        update(world, dt);
        render(world);
    }

    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
