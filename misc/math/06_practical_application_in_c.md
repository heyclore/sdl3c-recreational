# Vector Math - Course 6: Practical Application in C

This course demonstrates how to apply all previous vector and matrix knowledge into real-world usage using the C programming language. You'll implement a simple 2D/3D transformation pipeline, simulate motion, and construct a basic camera system without relying on external libraries.

---

## Topics Covered

1. Vector and Matrix Structs  
2. Transformation Functions (Scale, Rotate, Translate)  
3. Transformation Pipeline  
4. Simulating Movement and Physics  
5. Camera and View Matrix  
6. Manual Rendering (Text or Pixel Output)

---

## 1. Vector and Matrix Structs

### 2D Vector
```c
typedef struct {
    float x, y;
} Vec2;
```

### 3D Vector
```c
typedef struct {
    float x, y, z;
} Vec3;
```

### 4x4 Matrix
```c
typedef struct {
    float m[4][4];
} Mat4;
```

## 2. Transformation Functions

### Scaling (3D)
```c
Mat4 mat4_scale(float sx, float sy, float sz);
```

### Rotation (around Z-axis in 2D)
```c
Mat4 mat4_rotate_z(float radians);
```

### Translation (3D)
```c
Mat4 mat4_translate(float tx, float ty, float tz);
```

### Matrix Multiplication
```c
Mat4 mat4_mul(Mat4 a, Mat4 b);
Vec3 mat4_mul_vec3(Mat4 m, Vec3 v);
```

## 3. Transformation Pipeline
Apply model → view → projection transforms in order:
```c
Mat4 model = mat4_translate(0, 0, 0);
Mat4 view = mat4_look_at(camera_pos, target, up);
Mat4 proj = mat4_perspective(fov, aspect, near, far);

Mat4 mvp = mat4_mul(proj, mat4_mul(view, model));
Vec3 transformed = mat4_mul_vec3(mvp, vertex);
```

## 4. Simulating Movement and Physics

### Position Update
```c
Vec3 move(Vec3 position, Vec3 direction, float speed, float dt) {
    return (Vec3){
        position.x + direction.x * speed * dt,
        position.y + direction.y * speed * dt,
        position.z + direction.z * speed * dt
    };
}
```

### Gravity & Velocity
```c
velocity.y -= gravity * dt;
position.y += velocity.y * dt;
```
