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


    size_t steps = 1200;
    double length = width;
    double step = (double) length / steps;

    cairo_set_line_width (cr, 0.5);

    double * noise; 

    double r, g, b;

    size_t kmax=32000;

    for (size_t k=0 ; k <kmax ; ++k) {

        noise = perlin1D (steps, 100, 50);

        r = RAND1;
        g = RAND1;
        b = RAND1;
        /* printf ("(%d, %d, %d)\n", r, g, b); */
        cairo_set_source_rgba (cr, r, r, r, 0.1);

        double x=0;
        double y=(double)k/40;
        cairo_move_to (cr, x, y);

        for (size_t i=0 ; i < steps ; ++i) {
            y = (double)k/40 + noise[i]; 
            cairo_line_to (cr, x, y);
            x += step;
        }
        cairo_stroke (cr);
        cairo_line_to (cr, width, k);
    }

    /* cairo_move_to (cr, 100, 400); */
    /* cairo_line_to (cr, 1100, 400); */
    /* cairo_set_line_width (cr, 2); */
    /* cairo_set_source_rgb (cr, 1, 0, 0); */
    /* cairo_stroke (cr); */


    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "png/perlin_test.png");
    cairo_surface_destroy (surface);
    
    return 0;

}
