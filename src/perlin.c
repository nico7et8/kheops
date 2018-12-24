
#include "perlin.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double mix (double t, double v1, double v2) {
    return (1 - t) * v1 + t*v2;
}

double smooth (double t) {
    return t * t * t * (t*(t*6-15)+10);    
}

unsigned expo (void) {
    return rand() % 2 + 2;
}

double * perlin1D (const unsigned samples, const unsigned depth, double amplitude) {
    double * values = calloc (samples, sizeof (double));
    unsigned octave, X0, X1;
    double x, dx, dist, y1, y2;
    size_t i;
    unsigned e;
    unsigned n = 1;
    for (octave = 0 ; octave < depth; ++octave) {
        e = expo();
        double grads[n+1];
        for (i = 0 ; i <= n ; ++i) {
            grads[i] = RAND11;
        }
        dx = (double) n / (samples-1);
        x = 0;
        for (i=0 ; i < samples ; ++i) {
            X0 = (int)x;
            X1 = X0+1;
            dist = x - X0;
            y1 = dist * grads[X0];
            y2 = (dist-1) * grads[X1];
            values[i] += mix(smooth(dist), y1, y2) * amplitude;
            x += dx;
        }
        if (amplitude <= 1 || 3 * n > samples) {
            /* printf ("max octave = %d\n", octave); */
            break;
        }
        else {
            amplitude /= e;
            n *= e;
        }
    }
    return values;
}




