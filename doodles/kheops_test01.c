#include <cairo.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "kheops.h"

int main () {

    unsigned width = 900;
    unsigned height = 900;

    srand (time(NULL));

    cairo_surface_t * surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cairo_t * cr = cairo_create (surface);

    cairo_set_antialias (cr, CAIRO_ANTIALIAS_BEST);
    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint (cr);
    cairo_set_source_rgba (cr, 0, 0, 0, 1);
    cairo_set_line_width (cr, 1);

    kheops_set_amp_delta (0.04);
    kheops_set_amp_depth (5);
    double step = 0.1;

    cairo_move_to (cr, width*0.33, height*0.33);
    cairo_curve_to (cr,width*0.33 - 100, height*0.33, width*0.33 + 100, height*0.66, width*0.33, height*0.66);  
    cairo_stroke (cr);

    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "png/kheops_test01.png");
}
