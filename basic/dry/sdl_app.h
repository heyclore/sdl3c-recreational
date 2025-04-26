#ifndef SDL_APP_H
#define SDL_APP_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]);
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event);
void SDL_AppQuit(void *appstate, SDL_AppResult result);

extern SDL_Window *window;
extern SDL_Renderer *renderer;

#endif /* SDL_APP_H */

