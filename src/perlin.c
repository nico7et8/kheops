
#include "perlin.h"
#include <math.h>
#include <stdio.h>

double mix (double t, double v1, double v2) {
    return (1 - t) * v1 + t*v2;
}
double grad1D[256];

double smooth (double t) {
    return t * t * t * (t*(t*6-15)+10);    
}

unsigned set_factor (void) {
    // returns either 2 or 3
    return rand() % 2 + 2;
}

double * perlin1D (const size_t samples, const unsigned depth, double amplitude) {
    double * perlin = calloc (samples, sizeof (double));
    unsigned octave, X0, X1;
    double x, dx, dist, y1, y2;
    unsigned factor, n = 1;
    for (octave = 0 ; octave < depth; ++octave) {
        factor = set_factor();
        double grads[n+1];
        for (size_t i = 0 ; i <= n ; ++i) {
            grads[i] = RAND11;
        }
        dx = (double) n / (samples-1);
        x = 0;
        for (size_t i=0 ; i < samples ; ++i) {
            X0 = (int)x;
            X1 = X0+1;
            dist = x - X0;
            y1 = dist * grads[X0];
            y2 = (dist-1) * grads[X1];
            perlin[i] += mix(smooth(dist), y1, y2) * amplitude;
            x += dx;
        }
        if (amplitude <= 1 || 3 * n > samples) {
            break;
        }
        else {
            amplitude /= factor;
            n *= factor;
        }
    }
    return perlin;
}

double ** perlin2D (const size_t xSamples, const size_t ySamples, const unsigned depth, double amplitude) {
    double ** perlin =  malloc (ySamples * sizeof (double *));
    for (size_t row=0 ; row < ySamples ; ++row) {
        perlin[row] = calloc (xSamples, sizeof (double));
    }
    return perlin;
}
