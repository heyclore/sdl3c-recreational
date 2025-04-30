#include "dry/sdl_app.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//static int BLOCK_SIZE = 10;
#define BLOCK_SIZE 10
int q;

void initMessage() {
  printf("\n\n=== %s ===\n", "CLICK ON SCREEN & SEE THE IMAGE!!!");
  printf("=== %s ===\n\n", "CLICK ANY KEY TO SCREEN RESET!!!");
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
  //printf("%d\n", q);
  //SDL_Delay(666);
  return SDL_APP_CONTINUE;
}

typedef struct {
  uint32_t color;  // Stores color value as a 32-bit unsigned integer (e.g., 0xFF00FFFF)
  int startIndex;  // Index where the pair sequence starts
  int numPairs;    // Number of pairs in the entry
} FooEntry;

const int foo[] = {
  //5, 5, 10, 10, 20, 20, 15, 15,
  3,0, 4,0, 5,0, 6,0, 7,0, 2,1, 3,1, 4,1, 5,1, 6,1, 7,1, 8,1, 9,1, 10,1, 2,7, 3,7, 5,7, 6,7, 7,7, 1,8, 2,8, 3,8, 5,8, 6,8, 8,8, 9,8, 10,8, 0,9, 1,9, 2,9, 3,9, 8,9, 9,9, 10,9, 11,9, 2,10, 9,10,
  2,2, 3,2, 4,2, 7,2, 1,3, 3,3, 7,3, 1,4, 3,4, 4,4, 8,4, 1,5, 2,5, 7,5, 8,5, 9,5, 10,5, 1,14, 2,14, 3,14, 8,14, 9,14, 10,14, 0,15, 1,15, 2,15, 3,15, 8,15, 9,15, 10,15, 11,15,
  5,2, 6,2, 8,2, 2,3, 4,3, 5,3, 6,3, 8,3, 9,3, 10,3, 2,4, 5,4, 6,4, 7,4, 9,4, 10,4, 11,4, 3,5, 4,5, 5,5, 6,5, 3,6, 4,6, 5,6, 6,6, 7,6, 8,6, 9,6, 0,10, 1,10, 4,10, 7,10, 10,10, 11,10, 0,11, 1,11, 2,11, 9,11, 10,11, 11,11, 0,12, 1,12, 10,12, 11,12,
  4,7, 4,8, 7,8, 4,9, 5,9, 6,9, 7,9, 3,10, 5,10, 6,10, 8,10, 3,11, 4,11, 5,11, 6,11, 7,11, 8,11, 2,12, 3,12, 4,12, 5,12, 6,12, 7,12, 8,12, 9,12, 2,13, 3,13, 4,13, 7,13, 8,13, 9,13,
  //0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,
};  // Or larger array as needed
    //
const FooEntry fooEntries[] = {
  { 0xFFFF0000, 0, 37 },  // First entry has 37 pairs, starts at index 0
  { 0xFF8B4513, 37, 31 },  // Second entry has 31 pairs, starts at index 37
  { 0xFFFFFF00, 68, 44 },   // Third entry has 5 pairs, starts at index 7
  { 0xFF0000FF, 112, 31 }   // Third entry has 5 pairs, starts at index 7
};

// Calculate the number of elements in fooEntries
const int numEntries = sizeof(fooEntries) / sizeof(fooEntries[0]);

void Memcpy(SDL_Surface *surface, int x, int y, uint32_t color, int pos_x, int pos_y) {
  if ((pos_x + x * BLOCK_SIZE + BLOCK_SIZE) > surface->w || (pos_y + y * BLOCK_SIZE + BLOCK_SIZE) > surface->h) {
    printf("Out of bounds! Skipping draw at (%d, %d)\n", x, y);
    return;
  }
  Uint32 *pixels = (Uint32 *)surface->pixels;
  Uint32 *targetPixels = &pixels[(pos_y + y  *BLOCK_SIZE) * surface->w + (pos_x + x * BLOCK_SIZE)];

  // Create a block of memory filled with the color
  Uint32 colorBlock[BLOCK_SIZE];
  for (int i = 0; i < BLOCK_SIZE; ++i) {
    colorBlock[i] = color;
  }

  // Copy the color block into the target region
  for (int i = 0; i < BLOCK_SIZE; ++i) {
    SDL_memcpy(&targetPixels[i * surface->w], colorBlock, BLOCK_SIZE * sizeof(Uint32));
  }
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
    SDL_memset(surface->pixels, (0x000000 & 0xFF), surface->w * surface->h * 4);
    SDL_UpdateWindowSurface(window);
  }
  if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    /*
       for (int i = 0; i < numEntries; i++) {
       printf("Entry %d (Color=0x%08X):\n", i, fooEntries[i].color);
       for (int j = 0; j < fooEntries[i].numPairs; j++) {
       int startIndex = fooEntries[i].startIndex;
    //int index = startIndex + 2 * j + startIndex;
    int index = startIndex * 2 + 2 * j;
    //printf("%d %d\n", foo[index], foo[index + 1]);
    Memcpy(surface, foo[index], foo[index + 1], fooEntries[i].color, (int)x, (int)y);
    }
    }
    */
    for (int i = 0; i < numEntries; ++i) {
      const FooEntry *entry = &fooEntries[i];
      const int *p = &foo[entry->startIndex * 2];
      printf("Entry %d (Color=0x%08X):\n", i, entry->color);

      for (int j = 0; j < entry->numPairs; ++j, p += 2) {
        Memcpy(surface, p[0], p[1], entry->color, (int)x, (int)y);
      }
    }


    SDL_UpdateWindowSurface(window);
  }
  return SDL_APP_CONTINUE;
}

