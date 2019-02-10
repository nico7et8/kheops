#include "kheops.h"
#include <stdio.h>
#include <math.h>
#include "perlin.h"

double kheops_amp_delta = 0.2;
unsigned kheops_amp_depth = 3;

void kheops_set_amp_delta (double amplitude) {
    kheops_amp_delta = amplitude;
}

void kheops_set_amp_depth (unsigned depth) {
    kheops_amp_depth = depth;
}

void kheops_move_to (cairo_t * cr, double x, double y) {
    cairo_move_to (cr, x, y);
}

void kheops_stroke (cairo_t * cr) {
    cairo_stroke (cr);
}

void kheops_rel_line_to (cairo_t * cr, const double x1, const double y1) {
    const double norm = sqrt (x1 * x1 + y1 * y1);
    const double dx = x1 / norm;
    const double dy = y1 / norm;
    double * noise = perlin1D ((int)norm, kheops_amp_depth, kheops_amp_delta*norm);
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
    double x0, y0, vx, vy;
    cairo_get_current_point (cr, &x0, &y0);
    vx = x1 - x0;
    vy = y1 - y0;
    const double norm = sqrt (vx * vx + vy * vy);
    const double dx = vx / norm;
    const double dy = vy / norm;
    double * noise = perlin1D ((int)norm, kheops_amp_depth, kheops_amp_delta*norm);
    double x, y;
    x = x0;
    y = y0;
    for (int c=1 ; c < (int)norm ; ++c) {
        x += dx;
        y += dy;
        cairo_line_to (cr, x + noise[c]*dy, y - noise[c]*dx);
    }
}

/* void kheops_line_to (cairo_t * cr, const double x1, const double y1) { */
    /* double x0, y0; */
    /* cairo_get_current_point (cr, &x0, &y0); */
    /* kheops_rel_line_to (cr, x1 - x0, y1 - y0); */
/* } */

double vect_norm (double x, double y) {
    return sqrt (x*x + y*y);
}

double fast_bezier_length (size_t steps, double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3) {
    double x[steps+1], y[steps+1];
    double t = 0; double r = 1;
    double dt = 1 / (double)steps;
    double len = 0;
    x[0] = x0;
    y[0] = y0;
    for (size_t i=1 ; i < steps + 1 ; ++i) {
        t += dt;
        r = 1-t;
        x[i]=r*r*r*x0 + 3*t*r*r*x1 + 3*t*t*r*x2 + t*t*t*x3;
        y[i]=r*r*r*y0 + 3*t*r*r*y1 + 3*t*t*r*y2 + t*t*t*y3;
        len += sqrt((x[i]-x[i-1])*(x[i]-x[i-1]) + (y[i]-y[i-1])*(y[i]-y[i-1]));
    }
    return len;
}

void kheops_curve_to (cairo_t * cr, double x1, double y1, double x2, double y2, double x3, double y3) {
    double x0, y0, xa, ya, xb, yb, xm, ym;
    double dxa, dya, dxb, dyb, dxm, dym;
    double xp1, yp1, xp2, yp2, xp, yp;
    cairo_get_current_point (cr, &x0, &y0);
    double len = fast_bezier_length (4, x0, y0, x1, y1, x2, y2, x3, y3);
    size_t steps = (size_t)(0.1 * len);
    dxa = (x1 - x0) / steps; dya = (y1 - y0) / steps;
    dxb = (x3 - x2) / steps; dyb = (y3 - y2) / steps;
    dxm = (x2 - x1) / steps; dym = (y2 - y1) / steps;
    cairo_move_to (cr, x0, y0);
    xa=x0; ya=y0; xb=x2; yb=y2; xm = x1; ym = y1;
    double t = 0, dt = (double) 1 / steps, r;
    double nx, ny, norm;
    double * noise = perlin1D (steps+1, kheops_amp_depth, len * kheops_amp_delta);
    for (size_t i=0 ; i < steps ; ++i) {
        xa+=dxa; ya+=dya;
        xb+=dxb; yb+=dyb;
        xm+=dxm; ym+=dym;
        t += dt; r = 1-t;
        xp1 = r*xa + t*xm;
        yp1 = r*ya + t*ym;
        xp2 = r*xm + t*xb;
        yp2 = r*ym + t*yb;
        xp = r*xp1 + t*xp2;
        yp = r*yp1 + t*yp2;
        norm = sqrt ((xp-x0)*(xp-x0) + (yp-y0)*(yp-y0));
        nx = (yp-y0) / norm;
        ny = (xp-x0) / norm;
        cairo_line_to (cr, xp + noise[i+1]*nx, yp+noise[i+1]*ny);
        /* cairo_line_to (cr, xp, yp); */
    }
}

