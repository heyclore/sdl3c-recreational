#include "dry/sdl_app.h"

int q;

SDL_Surface* imga = NULL;

void initMessage() {
  printf("\n\n=== %s ===\n", "CLICK ON SCREEN & SEE THE IMPORTED IMAGE!!!");
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
  //printf("%d\n", q);
  //SDL_Delay(666);
  return SDL_APP_CONTINUE;
}

SDL_Surface* load_image(const char* file) {
  SDL_Surface* surface = IMG_Load(file);
  if (!surface) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load: %s\n", SDL_GetError());
  }
  return surface;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
  float x,y;
  Uint32 buttons;
  buttons = SDL_GetMouseState(&x,&y);

  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }
  if (event->type == SDL_EVENT_KEY_DOWN) {
  }
  if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    if(q == 0){
      imga = load_image("assets/eww.png");
      if(imga){
        addSurfaceToList(imga);
        const char *format_name = SDL_GetPixelFormatName(surface->format);
        printf("Surface window format: %s\n", format_name);
        const char *format = SDL_GetPixelFormatName(imga->format);
        printf("Surface imga format: %s\n", format);
        SDL_Rect destRect = {100, 100, 600, 400};
        if (SDL_BlitSurfaceScaled(imga, NULL, surface, NULL, SDL_SCALEMODE_LINEAR) != true) {
          SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_BlitSurfaceScaled Error: %s\n", SDL_GetError());
        }
        printf("\n\n=== %s ===\n", "CLICK ON SCREEN AGAIN FOR ZOOM IN!!!");
      }
    }
    if(q > 0 && q < 2){
      SDL_Rect destRect = {70, 269, surface->w *0.85, surface->h*0.85};
      if (SDL_BlitSurfaceScaled(imga, &destRect, surface, NULL, SDL_SCALEMODE_LINEAR) != true) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_BlitSurfaceScaled Error: %s\n", SDL_GetError());
      }
    }
    q++;
  }
  SDL_UpdateWindowSurface(window);
  return SDL_APP_CONTINUE;
}

