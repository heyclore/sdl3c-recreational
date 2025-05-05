#include <stdio.h>
#include <math.h>

#define PI 3.1415926f

typedef struct {
  float x, y, z;
} Point3D;

void rotateX(Point3D *v, float angle) {
  float new_y = v->y * cosf(angle) - v->z * sinf(angle);
  float new_z = v->y * sinf(angle) + v->z * cosf(angle);
  v->y = new_y;
  v->z = new_z;
}

void rotateY(Point3D *v, float angle) {
  float new_x = v->x * cosf(angle) + v->z * sinf(angle);
  float new_z = -v->x * sinf(angle) + v->z * cosf(angle);
  v->x = new_x;
  v->z = new_z;
}

void rotateZ(Point3D *v, float angle) {
  float new_x = v->x * cosf(angle) - v->y * sinf(angle);
  float new_y = v->x * sinf(angle) + v->y * cosf(angle);
  v->x = new_x;
  v->y = new_y;
}

void rotate_around_center(Point3D *v, Point3D center, float angle, char axis) {
  // Translate to origin
  v->x -= center.x;
  v->y -= center.y;
  v->z -= center.z;

  // Rotate on selected axis
  if (axis == 'x') {
    rotateX(v, angle);
  } else if (axis == 'y') {
    rotateY(v, angle);
  } else if (axis == 'z') {
    rotateZ(v, angle);
  }

  // Translate back
  v->x += center.x;
  v->y += center.y;
  v->z += center.z;
}

int main() {
  Point3D A = {10, 10, 0};
  Point3D B = {20, 10, 0};
  Point3D C = {10, 20, 0};
  Point3D D = {20, 20, 0};
  Point3D center = {15, 15, 0};

  float angle = PI / 6.0f; // 30 degrees

  printf("A: (%d, %d, %d)\n", (int)(A.x + 0.5f), (int)(A.y + 0.5f), (int)(A.z + 0.5f));
  printf("B: (%d, %d, %d)\n", (int)(B.x + 0.5f), (int)(B.y + 0.5f), (int)(B.z + 0.5f));
  printf("C: (%d, %d, %d)\n", (int)(C.x + 0.5f), (int)(C.y + 0.5f), (int)(C.z + 0.5f));
  printf("D: (%d, %d, %d)\n\n", (int)(D.x + 0.5f), (int)(D.y + 0.5f), (int)(D.z + 0.5f));
  for (int i = 0; i < 11; i++) {
    rotate_around_center(&A, center, angle, 'y');
    rotate_around_center(&B, center, angle, 'y');
    rotate_around_center(&C, center, angle, 'y');
    rotate_around_center(&D, center, angle, 'y');
    printf("A: (%d, %d, %d)\n", (int)(A.x + 0.5f), (int)(A.y + 0.5f), (int)(A.z + 0.5f));
    printf("B: (%d, %d, %d)\n", (int)(B.x + 0.5f), (int)(B.y + 0.5f), (int)(B.z + 0.5f));
    printf("C: (%d, %d, %d)\n", (int)(C.x + 0.5f), (int)(C.y + 0.5f), (int)(C.z + 0.5f));
    printf("D: (%d, %d, %d)\n", (int)(D.x + 0.5f), (int)(D.y + 0.5f), (int)(D.z + 0.5f));
  }

  return 0;
}

