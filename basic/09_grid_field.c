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
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define COLOR 0xFFFF0000

// Grid dimensions and cell size
#define GRID_SIZE 13
#define CELL_SIZE 13
#define GRID_CENTER GRID_SIZE * CELL_SIZE / 2
#define CELL_CENTER(i) ((i) * CELL_SIZE + CELL_SIZE / 2.0)

// Vector struct
typedef struct {
  double x, y, z;
} Vec3;

typedef struct {
  int x, y;
} Point;

typedef struct {
  Point* points;
  int count;
} PointRow;


// Camera and scene globals
Vec3 view_point = {GRID_CENTER, 0, 160};
Vec3 target_point = {GRID_CENTER, GRID_CENTER, 20};

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

// Update camera orientation vectors
void update_camera_vectors() {
  camera_dir = normalize(subtract(target_point, view_point));
  right = normalize(cross(up, camera_dir));
  true_up = cross(camera_dir, right);
}

bool is_edge_cell(int i, int j) {
  return (i == 0 || i == GRID_SIZE - 1 || j == 0 || j == GRID_SIZE - 1);
}

Point project_to_screen(Vec3 world_point) {
  Vec3 rel = subtract(world_point, view_point);
  double x_cam = dot(rel, right);
  double y_cam = dot(rel, true_up);
  double z_cam = dot(rel, camera_dir);

  Point screen_point = { -1, -1 };
  if (z_cam > 0) {
    double proj_x = (x_cam / z_cam) * focal_length;
    double proj_y = (y_cam / z_cam) * focal_length;

    screen_point.x = (int)((proj_x + 1) * (SCREEN_WIDTH / 2.0));
    screen_point.y = (int)((1 - proj_y) * (SCREEN_HEIGHT / 2.0));
  }
  return screen_point;
}

void draw_point(int x, int y) {
  if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
    ((uint32_t*)surface->pixels)[y * surface->w + x] = COLOR;
  }
}

void draw_line_updated(int x0, int y0, int x1, int y1) {
  bool steep = abs(y1 - y0) > abs(x1 - x0);

  if (steep) {
    int temp = x0; x0 = y0; y0 = temp;
    temp = x1; x1 = y1; y1 = temp;
  }

  if (x0 > x1) {
    int temp = x0; x0 = x1; x1 = temp;
    temp = y0; y0 = y1; y1 = temp;
  }

  int dx = x1 - x0;
  int dy = abs(y1 - y0);
  int err = dx / 2;
  int ystep = (y0 < y1) ? 1 : -1;
  int y = y0;

  for (int x = x0; x <= x1; x++) {
    if (steep) draw_point(y, x);
    else       draw_point(x, y);

    err -= dy;
    if (err < 0) {
      y += ystep;
      err += dx;
    }
  }
}

void init_view() {
  SDL_memset(surface->pixels, 0x00, surface->w * surface->h * 4);
  update_camera_vectors();

  PointRow edge_rows[GRID_SIZE];
  PointRow edge_cols[GRID_SIZE];

  for (int i = 0; i < GRID_SIZE; i++) {
    Point* row_points = NULL;
    Point* col_points = NULL;
    int row_index = 0;
    int col_index = 0;

    for (int j = 0; j < GRID_SIZE; j++) {
      if (!is_edge_cell(i, j)) continue;

      Point row = project_to_screen((Vec3){
          .x = CELL_CENTER(j),
          .y = CELL_CENTER(i),
          .z = 0
          });

      Point col = project_to_screen((Vec3){
          .x = CELL_CENTER(i),
          .y = CELL_CENTER(j),
          .z = 0
          });

      row_points = realloc(row_points, (row_index + 1) * sizeof(Point));
      col_points = realloc(col_points, (col_index + 1) * sizeof(Point));


      if (!row_points || !col_points) {
        // Handle allocation failure, e.g. cleanup and return
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
      }

        row_points[row_index++] = row;
        col_points[col_index++] = col;
    }

    edge_rows[i].points = row_points;
    edge_rows[i].count = row_index;
    edge_cols[i].points = col_points;
    edge_cols[i].count = col_index;
    for (int k = 0; k < row_index; k++) {
      edge_rows[i].points[k] = row_points[k];
    }
    for (int k = 0; k < col_index; k++) {
      edge_cols[i].points[k] = col_points[k];
    }
  }

  for (int i = 0; i < GRID_SIZE; i++) {
    if (edge_rows[i].count > 1) {
      draw_line_updated(edge_rows[i].points[0].x, edge_rows[i].points[0].y,
          edge_rows[i].points[edge_rows[i].count - 1].x,
          edge_rows[i].points[edge_rows[i].count - 1].y);
    }
    if (edge_cols[i].count > 1) {
      draw_line_updated(edge_cols[i].points[0].x, edge_cols[i].points[0].y,
          edge_cols[i].points[edge_cols[i].count - 1].x,
          edge_cols[i].points[edge_cols[i].count - 1].y);
    }
    free(edge_rows[i].points);
    free(edge_cols[i].points);
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
  init_view();
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
  init_view();
}

// Function to move the camera and target sideways (left or right)
void move_camera_sideways(int direction) {
  double move_amount = direction * CELL_SIZE;
  target_point.x += right.x * move_amount;
  target_point.y += right.y * move_amount;
  view_point.x += right.x * move_amount;
  view_point.y += right.y * move_amount;
  init_view();
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
      init_view();
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

