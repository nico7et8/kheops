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


    double length = width -200;
    double step = 1;

    cairo_set_line_width (cr, 0.5);

    double * noise; 

    double r, g, b;

    for (size_t k=0 ; k <100 ; ++k) {

        noise = perlin1D (length, 5, 300);

        r = RAND1;
        g = RAND1;
        b = RAND1;
        cairo_set_source_rgba (cr, r, g, b, 1);

        double x=100;
        double y0= height/2;
        double y = y0;
        cairo_move_to (cr, x, y);

        for (size_t i=0 ; i < length ; ++i) {
            y = y0 + noise[i]; 
            cairo_line_to (cr, x, y);
            x += step;
        }
        cairo_stroke (cr);
        cairo_line_to (cr, width-100, k);
    }

    cairo_move_to (cr, 100, 400);
    cairo_line_to (cr, 1100, 400);
    cairo_set_line_width (cr, 2);
    cairo_set_source_rgb (cr, 1, 0, 0);
    cairo_stroke (cr);


    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "png/perlin1D_test.png");
    cairo_surface_destroy (surface);
    
    return 0;

}
