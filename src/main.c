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

    v2 click_pos;
    v2 mouse_pos;

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

v2 project_to_world(v2 pos)
{
    return v2_from_pos(pos.x, WIN_HEIGHT - pos.y);
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

        case SDL_MOUSEBUTTONDOWN:
            state.click_pos = v2_from_pos(event.button.x, event.button.y);
            break;
        
        case SDL_MOUSEMOTION:
            state.mouse_pos = v2_from_pos(event.button.x, event.button.y);
            break;

        case SDL_MOUSEBUTTONUP:
            if (state.click_pos.x != -1 && state.click_pos.y != -1)
            {
                add_rigidbody(world, create_rigidbody_v(project_to_world(state.click_pos),
                                                        sub_v2(project_to_world(state.mouse_pos), project_to_world(state.click_pos))));
                state.click_pos = v2_from_pos(-1, -1);
            }
            else add_rigidbody(world, create_rigidbody_at_pos(project_to_world(state.click_pos)));
            break;
        
        default:
            break;
    }
}

void render(World* world)
{
    SDL_SetRenderDrawColor(state.renderer, 255, 0, 0, 255);

    if (state.click_pos.x != -1 && state.click_pos.y != -1)
    {
        aa_draw_circle(state.renderer,
                       state.click_pos,
                       10);
        
        SDL_RenderDrawLineF(state.renderer,
                            state.click_pos.x, state.click_pos.y,
                            state.mouse_pos.x, state.mouse_pos.y);
    }

    for (unsigned int i = 0; i < world->size; i++)
    {
        RigidBody* object = &(world->rigidbodies[i]);

        aa_draw_circle(state.renderer,
                       project_to_world(object->pos),
                       10);
    }

    SDL_RenderPresent(state.renderer);

    SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
    SDL_RenderClear(state.renderer);
}


int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    ASSERT(!SDL_Init(SDL_INIT_VIDEO), "Cannot initialize SDL : %s\n", SDL_GetError());

    state.window = SDL_CreateWindow("physics",
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

    state.click_pos = v2_from_pos(-1, -1);
    state.mouse_pos = v2_from_pos(-1, -1);

    World* world = default_world();

    uint64_t last_update = SDL_GetPerformanceCounter();
    while(!state.quit)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event)) handle_event(world, event);

        uint64_t current = SDL_GetPerformanceCounter();
        float dt = (current - last_update) / (float) SDL_GetPerformanceFrequency();
        last_update = current;

        update(world, 1, dt);
        render(world);
    }

    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
