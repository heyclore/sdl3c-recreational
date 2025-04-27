#define SDL_MAIN_USE_CALLBACKS 1
#include "sdl_app.h"

SDL_Window *window = NULL;
SDL_Surface *surface;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  window = SDL_CreateWindow("ASUKABEH!", WINDOW_WIDTH, WINDOW_HEIGHT, 0);

  if (window == NULL) {
    SDL_Log("Window could not be created! SDL_Error: %s", SDL_GetError());
    SDL_Quit();
    return SDL_APP_FAILURE;
  }

  surface = SDL_GetWindowSurface(window);
  SDL_LockSurface(surface);
  SDL_memset(surface->pixels, 6, surface->h * surface->pitch);
  SDL_UnlockSurface(surface);
  SDL_UpdateWindowSurface(window);

  return SDL_APP_CONTINUE;
}


void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
  SDL_DestroyWindow(window);
}

