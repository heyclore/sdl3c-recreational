# Vector Math - Course 3: Vector Applications (2D & 3D)

In this course, we explore how to apply vectors to solve real-world and graphical problems.

## Topics Covered

1. Vector Magnitude and Normalization  
2. Vector Projection  
3. Reflection over a Normal  
4. Distance Between Points  
5. Interpolation (LERP)  
6. Movement and Direction

---

## 1. Vector Magnitude and Normalization

### Magnitude

The **magnitude** (or length) of a vector:

- **2D**: `|v| = sqrt(x² + y²)`
- **3D**: `|v| = sqrt(x² + y² + z²)`


### Normalization

To **normalize** a vector is to scale it to unit length (1): `normalized_v = v / |v|`

#### Use:
- Keep direction, remove scale.
- Useful in lighting and movement direction.

---

## 2. Vector Projection

Projects vector `v` onto vector `n` (often a unit vector):

### Formula: `proj_n(v) = (v · n) / |n|² * n`
If `n` is normalized: `proj_n(v) = (v · n) * n`

#### Use:
- Sliding objects along surfaces.
- Lighting angle effects.

---

## 3. Reflection over a Normal

Reflect a vector `v` over a surface with normal `n` (must be normalized):

### Formula: `r = v - 2 * (v · n) * n`

#### Use:
- Bounce effect.
- Light or ball reflection logic.

---

## 4. Distance Between Points

The distance between two points (vectors) `a` and `b`:

- **2D**: `dist = sqrt((ax - bx)² + (ay - by)²)`
- **3D**: `dist = sqrt((ax - bx)² + (ay - by)² + (az - bz)²)`

#### Use:
- Collision detection.
- Proximity checks.

---

## 5. Interpolation (LERP)

Linearly interpolate between two vectors `a` and `b` with factor `t` (0 ≤ t ≤ 1):

### Formula:

#### Use:
- Smooth transitions.
- Animation and motion blending.

---

## 6. Movement and Direction

To move an object in direction `d` at speed `s` over time `t`: `new_pos = pos + normalize(d) * s * t`

#### Use:
- Character or object movement.
- Simulating velocity.

---

## C Code Examples

```c
// Vector magnitude
float magnitude(Vector2 v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}

// Vector normalization
Vector2 normalize(Vector2 v) {
    float mag = magnitude(v);
    if (mag == 0) return (Vector2){0, 0};
    return (Vector2){v.x / mag, v.y / mag};
}

// Dot product reused from previous course
float dot(Vector2 a, Vector2 b) {
    return a.x * b.x + a.y * b.y;
}

// Projection
Vector2 project(Vector2 v, Vector2 n) {
    float dp = dot(v, n);
    float lenSq = dot(n, n);
    float scale = dp / lenSq;
    return (Vector2){n.x * scale, n.y * scale};
}

// Reflection
Vector2 reflect(Vector2 v, Vector2 n) {
    float dp = dot(v, n);
    return (Vector2){
        v.x - 2 * dp * n.x,
        v.y - 2 * dp * n.y
    };
}

// Distance between points
float distance(Vector2 a, Vector2 b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrtf(dx * dx + dy * dy);
}

// LERP
Vector2 lerp(Vector2 a, Vector2 b, float t) {
    return (Vector2){
        a.x * (1 - t) + b.x * t,
        a.y * (1 - t) + b.y * t
    };
}
```

## Summary Table

| Concept    | Description                                | Use Cases                   |
|------------|--------------------------------------------|-----------------------------|
| Magnitude  | Length of vector                           | Movement speed, distance    |
| Normalize  | Vector scaled to length 1                  | Directional control         |
| Projection | Part of vector in direction of another     | Sliding along surfaces      |
| Reflection | Mirror image over a normal                 | Bounce, lighting            |
| Distance   | Euclidean distance                         | Proximity detection         |
| LERP       | Blend between values                       | Animation, interpolation    |
| Movement   | Advance along direction by speed * time    | Physics, games              |

