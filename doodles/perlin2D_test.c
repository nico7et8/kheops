#include "perlin.h"
#include <cairo.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main () {

    unsigned width = 1000;
    unsigned height = 1000;

    cairo_surface_t * surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cairo_t * cr = cairo_create (surface);

    srand(time(NULL));
    RAND255;

    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint(cr);

    int margin = 50;

    double ** perlin1 = perlin2D (width - 2 * margin, height - 2 * margin, 9, 1);
    double ** perlin2 = perlin2D (width - 2 * margin, height - 2 * margin, 9, 1);
    double ** perlin3 = perlin2D (width - 2 * margin, height - 2 * margin, 9, 1);

    double c1, c2, c3;
    for (size_t row = margin ; row < height - margin ; ++row) {
        for (size_t col = margin ; col < width - margin; ++col) {
            c1 = 0.5 + perlin1[row - margin][col - margin];
            c2 = 0.5 + perlin2[row - margin][col - margin];
            c3 = 0.5 + perlin3[row - margin][col - margin];
            cairo_set_source_rgb (cr, c1, c2, c3);
            cairo_rectangle (cr, col, row, 1, 1);
            cairo_fill (cr);
        }
    }

    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "png/perlin2D_test.png");
    cairo_surface_destroy (surface);

    return 0;

}
