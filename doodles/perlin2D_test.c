#include "perlin.h"
#include <cairo.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main () {

    unsigned width = 1200;
    unsigned height = 800;

    cairo_surface_t * surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cairo_t * cr = cairo_create (surface);

    srand(time(NULL));
    RAND255;

    cairo_set_source_rgb (cr, 255, 255, 255);
    cairo_paint(cr);

    double ** perlin = perlin2D (12, 8, 1, 1);

    for (int row = 0 ; row < 8 ; ++ row) {
        for (int col = 0 ; col < 12 ; ++col) {
            printf ("%02.0f ", perlin[row][col]);
        }
        printf ("\n");
    }

    int margin = 100;
    double c;
    for (size_t row = margin ; row < height - margin ; ++row) {
        for (size_t col = margin ; col < width - margin ; ++col) {
            c = 0.5;
            /* printf ("%f\n", c); */
            cairo_set_source_rgb (cr, c, c, c);
            cairo_rectangle (cr, col, row, 1, 1);
            cairo_fill (cr);
        }
    }

    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "png/perlin2D_test.png");
    cairo_surface_destroy (surface);

    return 0;

}
