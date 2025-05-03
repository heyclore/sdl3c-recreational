# Vector Math - Course 4: Matrices and Transformations (2D & 3D)

This course covers how matrices are used to transform vectors in 2D and 3D space, enabling rotation, scaling, translation, and combinations of those.

---

## Topics Covered

1. Matrix Basics and Notation  
2. Matrix-Vector Multiplication  
3. 2D Transformations  
4. 3D Transformations  
5. Homogeneous Coordinates  
6. Combining Transformations (Matrix Composition)  
7. Inverse Transformations

---

## 1. Matrix Basics and Notation

A matrix is a rectangular array of numbers. Matrices are commonly used to transform vectors.

- A 2×2 matrix transforms a 2D vector.
- A 3×3 matrix transforms a 2D vector with homogeneous coordinates.
- A 4×4 matrix transforms a 3D vector with homogeneous coordinates.

Matrix notation (row-major or column-major) matters depending on convention.

---

## 2. Matrix-Vector Multiplication

### 2D (without translation):
```
| a b | * | x | = | ax + by |
| c d | | y | | cx + dy |
```


### General Rule:
- Rows of matrix multiply columns of vector.
- Result is a new transformed vector.

---

## 3. 2D Transformations

### Scaling
```
| sx 0 |
| 0 sy |
```

### Rotation (by angle θ)
```
| cosθ -sinθ |
| sinθ cosθ |
```

### Example in C:
```c
Vector2 rotate(Vector2 v, float angle_rad) {
    float c = cosf(angle_rad);
    float s = sinf(angle_rad);
    return (Vector2){
        v.x * c - v.y * s,
        v.x * s + v.y * c
    };
}
```

## 4. 3D Transformations
- Rotation uses 3 axes (X, Y, Z) and 3 separate rotation matrices.
- Matrices used are 3×3 (linear), or 4×4 if translation is included.

### Rotation Around Z-axis:
```
| cosθ -sinθ  0 |
| sinθ  cosθ  0 |
|  0     0    1 |
```

### Scaling:
```
| sx  0   0 |
| 0   sy  0 |
| 0   0   sz|
```

## 5. Homogeneous Coordinates
To perform translation using matrix multiplication, vectors are extended with an extra coordinate.

### 2D Homogeneous:
```
[x, y] → [x, y, 1]
```

### Translation Matrix (3×3):
```
| 1  0  tx |
| 0  1  ty |
| 0  0  1  |
```

### 3D Homogeneous:
```
[x, y, z] → [x, y, z, 1]
```

### Translation Matrix (4×4):
```
| 1  0  0  tx |
| 0  1  0  ty |
| 0  0  1  tz |
| 0  0  0  1  |
```

## 6. Combining Transformations
To apply multiple transformations (e.g., scale → rotate → translate), multiply matrices in reverse order of application:
```
M_total = T * R * S
```
Then apply:
```
v' = M_total * v
```

## 7. Inverse Transformations
To undo a transformation:
- Use the inverse matrix.
- Common in camera/view transformations (moving the world relative to the camera).


| Concept              | Description                             | Use Cases                         |
|----------------------|-----------------------------------------|------------------------------------|
| Scaling              | Increase/decrease size along axes       | Resize models, squash/stretch     |
| Rotation             | Turn around origin or axis              | Spin, orientation, camera         |
| Translation          | Move object by offset                   | Positioning, motion               |
| Homogeneous Coord.   | Add 1 to enable translation via matrix  | Combine scale/rotate/translate    |
| Matrix Composition   | Multiply matrices to combine effects    | Complex animation, transformations|
| Inverse Transform    | Reverse a transformation                | Camera, object reset              |

