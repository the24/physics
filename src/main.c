#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "dynamics.h"
#include "graphics.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define ASSERT(_e, ...) if (!(_e)) { fprintf(stderr, __VA_ARGS__); exit(EXIT_FAILURE); }

struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool quit;
} state;

World* default_world()
{
    RigidBody rigidbodies[2] = {
        create_rigidbody_v(v2_from_pos(100, 200), v2_from_pos(50, -50)),
        create_rigidbody_v(v2_from_pos(200, 100), v2_from_pos(-50, 50)),
    };

    World* world = malloc(sizeof(World));
    init_world(world);
    add_rigibodies(world, rigidbodies, 2);

    return world;
}

void reset_world(World** world)
{
    *world = default_world();
}

void handle_event(World* world, SDL_Event event)
{
    switch(event.type)
    {
        case SDL_QUIT:
            state.quit = true;
            break;
        
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_r) reset_world(&world);
            break;

        case SDL_MOUSEBUTTONUP:
            add_rigidbody(world, create_rigidbody_at_pos(v2_from_pos(event.button.x,
                                                                     WIN_HEIGHT - event.button.y)));
            break;
        
        default:
            break;
    }
}

void render(World* world)
{
    SDL_SetRenderDrawColor(state.renderer, 255, 0, 0, 255);

    for (unsigned int i = 0; i < world->size; i++)
    {
        RigidBody* object = &(world->rigidbodies[i]);

        aa_draw_circle(state.renderer,
                       v2_from_pos(object->pos.x, WIN_HEIGHT - object->pos.y),
                       10);
    }

    SDL_RenderPresent(state.renderer);

    SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
    SDL_RenderClear(state.renderer);
}


int main(int argc, char **argv)
{
    ASSERT(!SDL_Init(SDL_INIT_VIDEO), "Cannot initialize SDL : %s\n", SDL_GetError());

    state.window = SDL_CreateWindow("Phisics",
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

    ASSERT(!SDL_SetRenderDrawBlendMode(state.renderer, SDL_BLENDMODE_BLEND), "Failed to set blend mode : %s\n", SDL_GetError());

    World* world = default_world();

    uint32_t last_update = SDL_GetTicks();
    while(!state.quit)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event)) handle_event(world, event);

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
