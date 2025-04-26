#include "dry/sdl_app.h"
#include <SDL3/SDL.h>

#define NUM_POINTS 66
static SDL_FPoint points[NUM_POINTS];

SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_Delay(60);

    points[50].y = 0.0f;
    points[50].x = 0.0f;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderPoints(renderer, points, SDL_arraysize(points));
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

