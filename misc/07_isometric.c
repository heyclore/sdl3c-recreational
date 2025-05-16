#include <stdio.h>
#include <math.h>

#define GRID_ROWS 4
#define GRID_COLS 4
#define TILE_SIZE 5.0f
#define PI 3.14159265

typedef struct {
    float x, z;
} Vec2;

// Convert degrees to radians
float degToRad(float degrees) {
    return degrees * (PI / 180.0f);
}

// Rotate point around origin (2D)
Vec2 rotatePoint(Vec2 point, float angleDeg) {
    float angleRad = degToRad(angleDeg);
    Vec2 result;
    result.x = point.x * cos(angleRad) - point.z * sin(angleRad);
    result.z = point.x * sin(angleRad) + point.z * cos(angleRad);
    return result;
}

// Get isometric projection of grid cell coordinate
Vec2 isoProject(float row, float col) {
    Vec2 result;
    float half = TILE_SIZE / 2.0f;
    result.x = (col - row) * half;
    result.z = (col + row) * half;
    return result;
}

// Get vertices of one tile (4 corners)
void getTileVertices(float row, float col, Vec2 vertices[4]) {
    // Corners: top-left, top-right, bottom-right, bottom-left
    float r = row;
    float c = col;

    vertices[0] = isoProject(r, c);           // Top-left
    vertices[1] = isoProject(r, c + 1);       // Top-right
    vertices[2] = isoProject(r + 1, c + 1);   // Bottom-right
    vertices[3] = isoProject(r + 1, c);       // Bottom-left
}

int main() {
    for (int rotation = 0; rotation < 360; rotation += 45) {
        printf("\n=== Rotation: %d degrees ===\n", rotation);

        for (int row = 0; row < GRID_ROWS; row++) {
            for (int col = 0; col < GRID_COLS; col++) {
                Vec2 corners[4];
                getTileVertices((float)row, (float)col, corners);

                // Apply rotation to all 4 corners
                for (int i = 0; i < 4; i++) {
                    corners[i] = rotatePoint(corners[i], (float)rotation);
                }

                // Print tile with its 4 vertices
                printf("Tile [%d,%d] vertices:\n", row, col);
                for (int i = 0; i < 4; i++) {
                    printf("  V%d: (%.2f, %.2f)\n", i, corners[i].x, corners[i].z);
                }
            }
        }
    }

    return 0;
}

