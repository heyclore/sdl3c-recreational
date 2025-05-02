| Term                        | Description                                                                                         |
|----------------------------|-----------------------------------------------------------------------------------------------------|
| Projective Transformation  | A mathematical mapping from 3D space to a 2D plane. Used in cameras, rendering, and ray tracing.     |
| Perspective Projection     | A specific kind of projective transform where lines converge at a vanishing point — the basis of realistic 3D rendering. |
| Homogeneous Coordinates    | A mathematical tool in projective geometry used to represent points in projective space (necessary for 3D-to-2D projections). |
| Ray Tracing / Ray Casting  | Algorithmic methods, not exactly "named math terms" but grounded in geometry and linear algebra.    |
| Linear Algebra             | Underpins all the above — especially vector math for defining rays and transforms.                  |



# Essential Concepts to Learn for 2D → 3D Projection in C

### 🔹 1. Vectors
- Understand vector **definition**, **addition**, and **subtraction**
- Learn the **dot product** (used for angles and lighting)
- Learn the **cross product** (for calculating normals in 3D)
- Understand **normalization** (unit vectors)  
  💡 *In C:* Use a struct like:  
  `struct Vector3 { float x, y, z; };`

---

### 🔹 2. Matrices
- Work with **2x2** (2D), **3x3**, and **4x4** (3D) matrices
- Learn **matrix multiplication**
- Understand the **identity matrix**  
  💡 *Use 4x4 matrices for 3D transformations (like OpenGL does).*

---

### 🔹 3. Transformations
These are implemented using matrix math:

- **Translation** – Move objects in space  
- **Rotation** – Rotate around an axis  
- **Scaling** – Resize objects  
- **Shear (optional)** – Skew objects  
- **Perspective** – Simulate depth (distant objects appear smaller)

---

### 🔹 4. Coordinate Systems
- **Local/Object space**  
- **World space**  
- **View/Camera space**  
- **Clip space / Screen space**  
  💡 *Each step in rendering (model → world → view → screen) uses a transformation matrix.*

---

### 🔹 5. Projection
- **Orthographic projection** – Parallel lines stay parallel (used in CAD)
- **Perspective projection** – Mimics human vision (used in 3D games)  
  💡 *Learn to build a perspective projection matrix by hand.*

---

### 🔹 6. Ray Casting Math
- Define a ray as: **origin + direction vector**
- Compute **intersections with planes/walls**
- Use the **DDA (Digital Differential Analyzer)** algorithm for grid-based ray casting (as in Wolfenstein 3D)

---

### 🔹 7. Homogeneous Coordinates
- Add a 4th component to vectors (x, y, z, w)
- Enables **translation** and **perspective** in matrix math  
  💡 *w = 1.0 for position, w = 0.0 for direction vector*

---

### 🔹 8. Trigonometry
- **sin**, **cos**, **atan2**
- Used for **rotation**, **angles**, and **field of view**

---

### 🔹 9. Camera System
- **Position**, **direction**, **FOV** (field of view)
- **View matrix** (inverse of camera transform)
- How **rays** are cast from the camera through screen space


# MODULES

### 🟩 1. Vector Basics
- What is a vector? (vs. scalar)
- Notation:  
  **𝑣** = ⟨𝑥, 𝑦, 𝑧⟩
- Vector representation: arrow, direction, magnitude
- 2D and 3D vectors

---

### 🟦 2. Vector Operations
- **Addition & Subtraction**
- **Scalar multiplication/division**
- **Magnitude (length):**  
  |𝑣| = √(𝑥² + 𝑦² + 𝑧²)
- **Normalization (unit vector):**  
  **𝑣/|𝑣|**

---

### 🟨 3. Dot Product
- Formula:  
  **𝑎 ⋅ 𝑏** = |𝑎| |𝑏| cos(θ)
- Used to:  
  - Find angles between vectors  
  - Determine if vectors are orthogonal (perpendicular)  
  - Project one vector onto another

---

### 🟥 4. Cross Product (3D only)
- Formula:  
  **𝑎 × 𝑏**
- Result is a vector perpendicular to both inputs
- Used for:  
  - Calculating surface normals  
  - Determining orientation and area of parallelograms

---

### 🟪 5. Vector Projection
- Project **𝑎** onto **𝑏**:  
  **proj(𝑏) 𝑎** = (𝑎 ⋅ 𝑏) / |𝑏|² 𝑏
- Useful for shadows, collisions, etc.

---

### 🟧 6. Applications
- **Distance between points**
- **Vector reflection** (e.g., bouncing rays)
- **Moving in a direction:**  
  **𝑝𝑜𝑠** += **𝑑𝑖𝑟** ⋅ **𝑠𝑝𝑒𝑒𝑑** ⋅ **𝑑𝑡**
- **Camera movement, ray direction, light direction**

---

### 🧠 Optional Advanced Topics (After Basics)
- **Vector interpolation** (LERP, SLERP)
- **Angle between vectors** using **atan2** or **acos**
- **Changing bases / coordinate systems**
- **Higher-dimensional vectors** (4D for homogeneous coordinates)

