#include <cairo.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "kheops.h"

int main () {

    unsigned width = 1000;
    unsigned height = 1000;

    srand (time(NULL));

    cairo_surface_t * surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cairo_t * cr = cairo_create (surface);

    cairo_set_antialias (cr, CAIRO_ANTIALIAS_BEST);
    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint (cr);
    cairo_set_source_rgba (cr, 0, 0, 0, 1);
    cairo_set_line_width (cr, 0.1);

    double tangent= 400;
    double shift = 0;

    kheops_set_amp_delta (0.05);
    kheops_set_amp_depth (10);

    for (size_t i=0 ; i < 500 ; ++i) {

    kheops_move_to (cr, 600, 200);
    kheops_curve_to (cr, 600+tangent, 200, 600-tangent, 600, 600, 600);
    kheops_stroke (cr);
    }
    
    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "png/kheops_test01.png");
}
