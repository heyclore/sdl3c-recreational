# Vector Math - Course 5: Coordinate Systems and Spaces

Understanding coordinate spaces is crucial when working with transformations, cameras, and rendering pipelines. This course explains the types of spaces commonly used in 2D and 3D environments and how vectors are transformed between them.

---

## Topics Covered

1. Local (Object) Space  
2. World Space  
3. View (Camera) Space  
4. Screen (Clip and NDC) Space  
5. Homogeneous Coordinates  
6. Basis Vectors and Orientation

---

## 1. Local (Object) Space

- The coordinates **relative to the object’s own origin**.
- All geometry is defined here initially.

### Example:
A vertex at `(1, 0)` on a square is 1 unit to the right of the square’s center — regardless of where the square is in the world.

---

## 2. World Space

- A global coordinate system shared by all objects.
- Object space is transformed into world space using a **model matrix**.

### Model Matrix:
Applies scale, rotation, and translation to place an object in the world.

---

## 3. View (Camera) Space

- Coordinates relative to the **camera’s position and orientation**.
- Transformed using the **view matrix** (usually the inverse of the camera’s transform).

### Use:
- Simulates the world from the camera’s point of view.

---

## 4. Screen Space (Clip & NDC)

### Clip Space:
- After multiplying by **projection matrix**, coordinates lie in a 4D space.

### NDC (Normalized Device Coordinates):
- Coordinates are divided by `w`, becoming 3D in range `[-1, 1]` for X, Y, Z.

### Screen Space:
- NDC is mapped to pixels based on resolution.

---

## 5. Homogeneous Coordinates

- Adds a 4th dimension (w) to enable translation in matrix math.
- Vectors: `[x, y, z, w]`
  - Points have `w = 1`
  - Directions have `w = 0` (they're not affected by translation)

---

## 6. Basis Vectors and Orientation

A coordinate space is defined by:
- An **origin** (position)
- Three **basis vectors**:
  - **Right** (X-axis)
  - **Up** (Y-axis)
  - **Forward** (Z-axis)

You can define a custom space by placing and rotating these vectors.

---

## Summary Table

| Space Type     | Description                             | Transformation Used     | Use Cases                   |
|----------------|-----------------------------------------|--------------------------|-----------------------------|
| Local Space    | Object-centered coordinates              | Model matrix             | Geometry definition         |
| World Space    | Global positioning of all objects        | Model matrix             | Scene layout                |
| View Space     | Camera-relative coordinates              | View matrix              | Camera effects              |
| Clip Space     | Transformed by projection matrix         | Projection matrix        | Visibility culling          |
| NDC            | Normalized screen-aligned [-1, 1] range  | Division by w            | Screen-space operations     |
| Screen Space   | Pixel space for rasterization            | Viewport mapping         | Rendering                   |

