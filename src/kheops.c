#include "kheops.h"
#include <stdio.h>
#include <math.h>
#include "perlin.h"

unsigned kheops_depth = 3;
double kheops_amplitude = 0.2;

void kheops_set_depth (unsigned depth) {
    kheops_depth = depth;
}

void kheops_set_amplitude (double amplitude) {
    kheops_amplitude = amplitude;
}

void kheops_line_to (cairo_t * cr, double x1, double y1) {
    double x0, y0, vx, vy;
    double norm;
    double dx, dy;
    double x, y;
    cairo_get_current_point (cr, &x0, &y0);
    vx = x1 - x0;
    vy = y1 - y0;
    norm = sqrt (vx * vx + vy * vy);
    dx = vx / norm;
    dy = vy / norm;
    x = x0;
    y = y0;
    double px, py, px0, py0;
    double * noise = perlin1D ((int)norm, kheops_depth, kheops_amplitude*norm);
    px0 = 0;
    py0 = 0;
    for (int c=0 ; c < (int)norm ; ++c) {
        x += dx;
        y += dy;
        px = noise[c] * dy;
        py = noise[c] * dx;
        cairo_move_to (cr, x0 + px0, y0+py0);
        cairo_line_to (cr, x + px, y + py);
        x0 = x;
        y0 = y;
        px0 = px;
        py0 = py;
    }
}
