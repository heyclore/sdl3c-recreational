#include "dry/sdl_app.h"
#include <stdio.h>

int q;

void initMessage() {
  printf("\n\n=== %s ===\n\n", "CLICK ON SCREEN TO DRAW A PIXEL!!!");
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
  //printf("%d\n", q);
  SDL_Delay(66);
  return SDL_APP_CONTINUE;
}

#include <stdio.h>
#include <math.h>

// Screen size
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 400
#define COLOR 0xFFFF0000

// Grid dimensions and cell size
#define GRID_SIZE 6
#define CELL_SIZE 8
#define GRID_CENTER GRID_SIZE * CELL_SIZE / 2

// Vector struct
typedef struct {
  double x, y, z;
} Vec3;

// Camera and scene globals
Vec3 view_point = {GRID_CENTER, 0, 40};
Vec3 target_point = {GRID_CENTER, GRID_CENTER, 0};

Vec3 camera_dir;
Vec3 up = {0, 0, 1};
Vec3 right;
Vec3 true_up;

double focal_length = 1.0;

// Vector math utilities
Vec3 subtract(Vec3 a, Vec3 b) {
  return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

double dot(Vec3 a, Vec3 b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 cross(Vec3 a, Vec3 b) {
  return (Vec3){
    a.y * b.z - a.z * b.y,
      a.z * b.x - a.x * b.z,
      a.x * b.y - a.y * b.x
  };
}

Vec3 normalize(Vec3 v) {
  double len = sqrt(dot(v, v));
  if (len == 0) return (Vec3){0, 0, 0};
  return (Vec3){v.x / len, v.y / len, v.z / len};
}

// Print point to simulate drawing
void draw_point(double x, double y, SDL_Surface *surface) {
  //printf("Draw point at screen coordinates: (%d, %d)\n", (int)x, (int)y);
  if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
    ((uint32_t*)surface->pixels)[(int)y * surface->w + (int)x] = COLOR;
  }
}

// Update camera orientation vectors
void update_camera_vectors() {
  camera_dir = normalize(subtract(target_point, view_point));
  right = normalize(cross(up, camera_dir));
  true_up = cross(camera_dir, right);
}

// Render function to draw the grid
void init_view(SDL_Surface *surface) {
  SDL_memset(surface->pixels, (0x000000 & 0xFF), surface->w * surface->h * 4);
  update_camera_vectors();

  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      // Calculate the center position of each grid cell in world space
      Vec3 grid_center = {
        j * CELL_SIZE + CELL_SIZE / 2.0,
        i * CELL_SIZE + CELL_SIZE / 2.0,
        0 // Assuming the grid is on the Z=0 plane
      };

      Vec3 rel = subtract(grid_center, view_point);

      double x_cam = dot(rel, right);
      double y_cam = dot(rel, true_up);
      double z_cam = dot(rel, camera_dir);

      if (z_cam > 0) {
        double proj_x = (x_cam / z_cam) * focal_length;
        double proj_y = (y_cam / z_cam) * focal_length;

        double screen_x = (proj_x + 1) * (SCREEN_WIDTH / 2.0);
        double screen_y = (1 - proj_y) * (SCREEN_HEIGHT / 2.0);

        draw_point(screen_x, screen_y, surface);
      }
    }
  }
  SDL_UpdateWindowSurface(window);
}

// Rotate camera around the target point (clockwise)
void rotate_camera_by_degree(double angle_degrees) {
  double theta = angle_degrees * (M_PI / 180.0); // degrees to radians

  // Get offset from target to camera
  double dx = view_point.x - target_point.x;
  double dy = view_point.y - target_point.y;

  // Rotate around Z axis
  double new_dx = dx * cos(theta) + dy * sin(theta);
  double new_dy = -dx * sin(theta) + dy * cos(theta);

  // Update view_point with new rotated position
  view_point.x = target_point.x + new_dx;
  view_point.y = target_point.y + new_dy;
  // Keep Z the same
  init_view(surface);
}

void check_facing_direction() {
  if (fabs(camera_dir.y) > fabs(camera_dir.x)) {
    printf("Camera is primarily facing the Y field.\n");
  } else if (fabs(camera_dir.x) > fabs(camera_dir.y)) {
    printf("Camera is primarily facing the X field.\n");
  } else {
    printf("Camera is facing diagonally between X and Y fields.\n");
  }
}

// Function to move the camera and target forward or backward
void move_camera_forward_backward(int direction) {
  double move_amount = direction * CELL_SIZE;
  target_point.x += camera_dir.x * move_amount;
  target_point.y += camera_dir.y * move_amount;
  view_point.x += camera_dir.x * move_amount;
  view_point.y += camera_dir.y * move_amount;
  init_view(surface);
}

// Function to move the camera and target sideways (left or right)
void move_camera_sideways(int direction) {
  double move_amount = direction * CELL_SIZE;
  target_point.x += right.x * move_amount;
  target_point.y += right.y * move_amount;
  view_point.x += right.x * move_amount;
  view_point.y += right.y * move_amount;
  init_view(surface);
}


SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
  float x,y;
  Uint32 buttons;
  buttons = SDL_GetMouseState(&x,&y);

  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }
  if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
  }
  if (event->type == SDL_EVENT_KEY_DOWN) {
    if(q==0){
      init_view(surface);
      q++;
    }
    SDL_Scancode key_code = event->key.scancode;
    //printf("%u\n", key_code);

    switch (key_code) {
      case 26:
        move_camera_forward_backward(1);
        break;
      case 4:
        move_camera_sideways(-1);
        break;
      case 22:
        move_camera_forward_backward(-1);
        break;
      case 7:
        move_camera_sideways(1);
        break;
      case 20:
        rotate_camera_by_degree(-30.0);
        break;
      case 8:
        rotate_camera_by_degree(30.0);
        break;
      default:
        break;
    }
  }
  return SDL_APP_CONTINUE;
}

