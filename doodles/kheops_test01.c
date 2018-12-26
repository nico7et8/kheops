#include <cairo.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "kheops.h"

int main () {

    unsigned width = 1280;
    unsigned height = 720;
    unsigned margin = 100;

    srand (time(NULL));

    cairo_surface_t * surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cairo_t * cr = cairo_create (surface);

    cairo_set_antialias (cr, CAIRO_ANTIALIAS_BEST);

    kheops_set_amplitude (0.05);
    kheops_set_depth (20);

    double x0, y0, x1, y1;
    x0 = margin;
    x1 = width - margin;
    y0 = height/2;
    y1 = height/2 - 100;

    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint (cr);
    cairo_set_source_rgb (cr, 1, 0, 0);
    cairo_set_line_width (cr, 0.5);
    const double dash[] = {20.0, 10};

    cairo_move_to (cr, x0, y0);
    cairo_set_dash (cr, dash, 2, 0);
    cairo_line_to (cr, x1, y1);
    cairo_stroke (cr);

    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_set_line_width (cr, 1);
    cairo_set_dash (cr, NULL, 0, 0);

    cairo_move_to (cr, x0, y0+20);
    cairo_line_to (cr, x1, y1+20);
    cairo_stroke (cr);

    cairo_move_to (cr, x0, y0+40);
    kheops_line_to (cr, x1, y1+40);
    cairo_stroke (cr);

    cairo_move_to (cr, x0, y0+60);
    cairo_line_to (cr, x1, y1+60);
    cairo_stroke (cr);

    cairo_move_to (cr, x0, y0+80);
    kheops_line_to (cr, x1, y1+80);
    cairo_stroke (cr);



    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "png/kheops_test01.png");
}
