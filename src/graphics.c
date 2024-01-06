#include "graphics.h"

void draw_circle_symetries(SDL_Renderer* renderer, v2 center, int x, int y)
{
    SDL_RenderDrawPointF(renderer, center.x + x, center.y - y);
    SDL_RenderDrawPointF(renderer, center.x + x, center.y + y);
    SDL_RenderDrawPointF(renderer, center.x - x, center.y - y);
    SDL_RenderDrawPointF(renderer, center.x - x, center.y + y);
    SDL_RenderDrawPointF(renderer, center.x + y, center.y - x);
    SDL_RenderDrawPointF(renderer, center.x + y, center.y + x);
    SDL_RenderDrawPointF(renderer, center.x - y, center.y - x);
    SDL_RenderDrawPointF(renderer, center.x - y, center.y + x);
}

void draw_circle(SDL_Renderer* renderer, v2 center, unsigned int radius)
{
    const int diameter = (radius * 2);

    int x = (radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    while (x >= y)
    {
        draw_circle_symetries(renderer, center, x, y);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void aa_draw_circle(SDL_Renderer* renderer, v2 center, unsigned int radius)
{
    int x = (radius - 1);
    int y = 0;
    float last_fade_amount = 0;
    float fade_amount = 0;

    uint8_t r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    const float MAX_OPAQUE = a;

    while (x >= y)
    {
        float height = sqrt(max(radius * radius - y * y, 0));
        fade_amount = MAX_OPAQUE * (ceilf(height) - height);

        if (fade_amount < last_fade_amount) x--;

        last_fade_amount = fade_amount;

        SDL_SetRenderDrawColor(renderer, r, g, b, (int) MAX_OPAQUE - fade_amount);
        draw_circle_symetries(renderer, center, x, y);
        SDL_SetRenderDrawColor(renderer, r, g, b, (int) fade_amount);
        draw_circle_symetries(renderer, center, x - 1, y);

        y++;
    }
    
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
