#include <stdio.h>
#include <math.h>

// Screen size
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 400

// Vector struct
typedef struct {
  double x, y, z;
} Vec3;

// Camera and scene globals
Vec3 vertices[8] = {
  {20, 20, 0}, {30, 20, 0}, {20, 30, 0}, {30, 30, 0},
  {20, 20, 10}, {30, 20, 10}, {20, 30, 10}, {30, 30, 10}
};

Vec3 view_point = {25, 0, 40};
Vec3 target_point = {25, 25, 0};

Vec3 camera_dir;
Vec3 up = {0, 0, 1};
Vec3 right;
Vec3 true_up;

double focal_length = 1.0;

// Vector math utilities
Vec3 subtract(Vec3 a, Vec3 b) {
  return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

Vec3 add(Vec3 a, Vec3 b) {
  return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

Vec3 scale(Vec3 v, double s) {
  return (Vec3){v.x * s, v.y * s, v.z * s};
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
void draw_point(double x, double y) {
  printf("Draw point at screen coordinates: (%d, %d)\n", (int)x, (int)y);
}

// Update camera orientation vectors
void update_camera_vectors() {
  camera_dir = normalize(subtract(target_point, view_point));
  right = normalize(cross(up, camera_dir));
  true_up = cross(camera_dir, right);
}

// Render function
void init_view() {
  update_camera_vectors();

  for (int i = 0; i < 8; i++) {
    Vec3 rel = subtract(vertices[i], view_point);

    double x_cam = dot(rel, right);
    double y_cam = dot(rel, true_up);
    double z_cam = dot(rel, camera_dir);

    if (z_cam > 0) {
      double proj_x = (x_cam / z_cam) * focal_length;
      double proj_y = (y_cam / z_cam) * focal_length;

      double screen_x = (proj_x + 1) * (SCREEN_WIDTH / 2.0);
      double screen_y = (1 - proj_y) * (SCREEN_HEIGHT / 2.0);

      draw_point(screen_x, screen_y);
    }
  }
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
}


// Move camera forward or backward along view direction
void move_forward_backward(double step) {
  Vec3 dir = normalize(subtract(target_point, view_point));
  Vec3 movement = scale(dir, step);
  view_point = add(view_point, movement);
  target_point = add(target_point, movement);
}

int main() {
  // Initial render
  init_view();

  // Move camera forward (positive step) or backward (negative step)
  printf("\nMoving forward by 6 units:\n");
  move_forward_backward(6.0);
  init_view();

  printf("\nRotating camera clockwise by 30 degrees:\n");
  rotate_camera_by_degree(30.0);
  init_view();

  printf("\nRotating camera clockwise by -30 degrees:\n");
  rotate_camera_by_degree(-30.0);
  init_view();

  printf("\nMoving forward by -6 units:\n");
  move_forward_backward(-6.0);
  init_view();

  return 0;
}

