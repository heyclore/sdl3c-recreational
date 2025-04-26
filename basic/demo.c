#include "dry/sdl_app.h"
#include <SDL3/SDL.h>

#define NUM_POINTS 66
static SDL_FPoint points[NUM_POINTS];
int j;

SDL_AppResult SDL_AppIterate(void *appstate)
{
  SDL_Delay(60);
  SDL_FRect rect;

  /* as you can see from this, rendering draws over whatever was drawn before it. */
  SDL_SetRenderDrawColor(renderer, 33, 33, 33, SDL_ALPHA_OPAQUE);  /* dark gray, full alpha */
  SDL_RenderClear(renderer);  /* start with a blank canvas. */

  /* draw a filled rectangle in the middle of the canvas. */
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);  /* blue, full alpha */
  rect.x = rect.y = 100;
  rect.w = 440;
  rect.h = 280;
  SDL_RenderFillRect(renderer, &rect);

  /* draw some points across the canvas. */
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);  /* red, full alpha */
  SDL_RenderPoints(renderer, points, SDL_arraysize(points));

  /* draw a unfilled rectangle in-set a little bit. */
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);  /* green, full alpha */
  rect.x += 30;
  rect.y += 30;
  rect.w -= 60;
  rect.h -= 60;
  SDL_RenderRect(renderer, &rect);

  /* draw two lines in an X across the whole canvas. */
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);  /* yellow, full alpha */
  SDL_RenderLine(renderer, 0, 0, 640, 480);
  SDL_RenderLine(renderer, 0, 480, 640, 0);

  SDL_RenderPresent(renderer);  /* put it all on the screen! */
  return SDL_APP_CONTINUE;
}

