#include "kheops.h"
#include <stdio.h>
#include <math.h>
#include "perlin.h"

double khepos_amp_delta = 0.2;
unsigned kheops_amp_depth = 3;

void kheops_set_amp_delta (double amplitude) {
    khepos_amp_delta = amplitude;
}

void kheops_set_amp_depth (unsigned depth) {
    kheops_amp_depth = depth;
}

void kheops_rel_line_to (cairo_t * cr, const double x1, const double y1) {
    const double norm = sqrt (x1 * x1 + y1 * y1);
    const double dx = x1 / norm;
    const double dy = y1 / norm;
    double * noise = perlin1D ((int)norm, kheops_amp_depth, khepos_amp_delta*norm);
    double x, y;
    x = 0;
    y = 0;
    double dnoise = 0;
    for (int c=1 ; c < (int)norm ; ++c) {
        x += dx;
        y += dy;
        dnoise = noise[c] - noise[c-1];
        cairo_rel_line_to (cr, dx + dnoise*dy, dy - dnoise*dx);
    }
}

void kheops_line_to (cairo_t * cr, const double x1, const double y1) {
    double x0, y0;
    cairo_get_current_point (cr, &x0, &y0);
    kheops_rel_line_to (cr, x1 - x0, y1 - y0);
}
