#include <stdio.h>
#include <stdlib.h>

// 1. Plain variable
void printInt(int x) {
  printf("Value (int): %d\n", x);
}

// 2. Pointer to variable
void modifyInt(int *x) {
  *x += 10;
}

// 3. Double pointer
void allocateInt(int **ptr) {
  *ptr = (int *)malloc(sizeof(int));
  **ptr = 42;
}

// 4. Array (decays to pointer)
void printArray(int *arr, int size) {
  printf("Array: ");
  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

// 5. Struct by value
struct Point {
  int x, y;
};

void printPoint(struct Point p) {
  printf("Point by value: (%d, %d)\n", p.x, p.y);
}

// 6. Struct by pointer
void movePoint(struct Point *p) {
  p->x += 1;
  p->y += 1;
}

// 7. Void pointer
void printGeneric(void *ptr, char type) {
  switch (type) {
    case 'i': printf("Void pointer as int: %d\n", *(int *)ptr); break;
    case 'f': printf("Void pointer as float: %.2f\n", *(float *)ptr); break;
  }
}

// 8. Function pointer
void greet() {
  printf("Hello from function pointer!\n");
}

void callFunction(void (*fptr)()) {
  fptr();
}

int main() {
  int a = 5;
  printInt(a);        // 1. Plain variable
  modifyInt(&a);      // 2. Pointer to int
  printInt(a);        // Check modification

  int *b;
  allocateInt(&b);    // 3. Double pointer
  printInt(*b);
  free(b);

  int nums[] = {1, 2, 3};
  printArray(nums, 3); // 4. Array

  struct Point pt = {10, 20};
  printPoint(pt);     // 5. Struct by value
  movePoint(&pt);     // 6. Struct by pointer
  printPoint(pt);

  float f = 3.14f;
  printGeneric(&a, 'i'); // 7. Void pointer as int
  printGeneric(&f, 'f'); // 7. Void pointer as float

  callFunction(greet);   // 8. Function pointer

  return 0;
}

