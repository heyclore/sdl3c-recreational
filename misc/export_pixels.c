#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Export as 0xRRGGBBAA per pixel
void export_as_uint32(const uint32_t *pixels, int width, int height, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) { perror("File open failed"); return; }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint32_t pixel = pixels[y * width + x];
            fprintf(f, "0x%08X", pixel);
            if (x < width - 1) fprintf(f, ", ");
        }
        fprintf(f, "\n");
    }

    fclose(f);
}

// Export as (R, G, B, A) tuple
void export_as_rgba(const uint32_t *pixels, int width, int height, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) { perror("File open failed"); return; }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint32_t p = pixels[y * width + x];
            uint8_t r = (p >> 24) & 0xFF;
            uint8_t g = (p >> 16) & 0xFF;
            uint8_t b = (p >> 8) & 0xFF;
            uint8_t a = p & 0xFF;
            fprintf(f, "(%3d, %3d, %3d, %3d)", r, g, b, a);
            if (x < width - 1) fprintf(f, ", ");
        }
        fprintf(f, "\n");
    }

    fclose(f);
}

int main() {
    int width = 2, height = 2;
    uint32_t *pixels = malloc(width * height * sizeof(uint32_t));
    if (!pixels) {
        perror("Allocation failed");
        return 1;
    }

    // Fill 2x2 image with distinct colors
    pixels[0] = (255 << 24) | (0 << 16) | (0 << 8) | 255;     // Red
    pixels[1] = (0 << 24) | (255 << 16) | (0 << 8) | 255;     // Green
    pixels[2] = (0 << 24) | (0 << 16) | (255 << 8) | 255;     // Blue
    pixels[3] = (255 << 24) | (255 << 16) | (255 << 8) | 255; // White

    export_as_uint32(pixels, width, height, "pixels_uint32.txt");
    export_as_rgba(pixels, width, height, "pixels_rgba.txt");

    free(pixels);
    return 0;
}

