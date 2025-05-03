# 🧮 Vector Math - Course 1: Vector Basics

## What Is a Vector?

A **vector** is a mathematical object that has both:

- **Magnitude** (length)
- **Direction**

It is different from a scalar (which has only magnitude).

---

## 📐 Notation

Vectors are often written in angle brackets:

- **2D Vector**: `v = ⟨x, y⟩`
- **3D Vector**: `v = ⟨x, y, z⟩`

Examples:

- `v = ⟨3, 4⟩` (2D)
- `w = ⟨1, 2, 2⟩` (3D)

---

## 📏 Magnitude (Length)

To find the length (or magnitude) of a vector:

### 2D: `|v| = √(x² + y²)`
### 3D: `|v| = √(x² + y² + z²)`

**Example**: `|v| = √(3² + 4²) = √(9 + 16) = √25 = 5`

---

## 📊 Visualization

Vectors are typically visualized as arrows from the origin `(0, 0)` or `(0, 0, 0)` to the point `(x, y)` or `(x, y, z)`.

They represent:
- A **position** in space
- A **direction** of movement

---

##  Vector in C

### Vector2 and Vector3 Structs

```c
typedef struct {
    float x;
    float y;
} Vector2;

typedef struct {
    float x;
    float y;
    float z;
} Vector3;
```
```c
#include <math.h>

// Function to compute magnitude of a 2D vector
float magnitude(Vector2 v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

// Function to normalize a 2D vector
Vector2 normalize(Vector2 v) {
    float mag = magnitude(v);
    Vector2 result = {v.x / mag, v.y / mag};
    return result;
}
```
## Common Uses in Programming

* **Representing 2D/3D positions:** Think of storing where an object is on a screen (x, y coordinates) or in a virtual world (x, y, z coordinates).
* **Storing movement direction:** Instead of just a speed, you can use a vector to define both speed and direction (e.g., moving forward and slightly to the left).
* **Calculating distances:** Vectors make it easy to calculate the straight-line distance between two points.
* **Describing normals in lighting:** In 3D graphics, normal vectors define the orientation of a surface, which is crucial for realistic lighting calculations.
* **Driving ray casting and camera orientation:** Vectors are fundamental for determining the path of rays in ray tracing and defining the direction a virtual camera is pointing.
