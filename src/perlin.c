
#include "perlin.h"
#include <math.h>
#include <stdio.h>

double mix (double t, double v1, double v2) {
    return (1 - t) * v1 + t*v2;
}

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
        n *= factor;
        amplitude /= factor;
        if (amplitude < 1 || 2 * n > samples) {
            break;
        }
    }
    return perlin;
}

double ** perlin2D (const size_t xSamples, const size_t ySamples, const unsigned depth, double amplitude) {
    double ** perlin;
    perlin = malloc (ySamples * sizeof (double *));
    for (size_t row=0 ; row < ySamples ; ++row) {
        * (perlin + row) = calloc (xSamples, sizeof (double));
    }
    unsigned octave, X0, Y0, X1, Y1;
    double x, y, dxy, distX, distY;
    double v00, v01, v10, v11, v1, v2;
    unsigned factor, n=1;
    unsigned maxSamples = (xSamples > ySamples) ? xSamples : ySamples;
    for (octave = 0 ; octave < depth; ++octave) {
        factor = set_factor();
        double grads[n+1][n+1][2];
        double gx, gy, norm;
        for (size_t j=0 ; j <= n ; ++j) {
            for (size_t i=0 ; i <= n ; ++i) {
                gx = RAND11;
                gy = RAND11;
                norm = sqrt (gx * gx + gy * gy);
                grads[j][i][0] = gx / norm;
                grads[j][i][1] = gy / norm;
            }
        }
        dxy = (double) n / maxSamples;
        size_t row, col;
        y = 0;
        for (row = 0 ; row < ySamples ; ++row) {
            x = 0;
            Y0 = (int) y;
            Y1 = Y0 + 1;
            distY = y - Y0;
            for (col = 0 ; col < xSamples ; ++ col) {
                X0 = (int) x;
                X1 = X0 + 1;
                distX = x - X0;
                v00 = grads[Y0][X0][0] * distX + grads[Y0][X0][1] * distY;
                v01 = grads[Y0][X1][0] * (distX-1) + grads[Y0][X1][1] * distY;
                v10 = grads[Y1][X0][0] * distX + grads[Y1][X0][1] * (distY-1);
                v11 = grads[Y1][X1][0] * (distX-1) + grads[Y1][X1][1] * (distY-1);
                v1 = mix (smooth(distX), v00, v01);
                v2 = mix (smooth(distX), v10, v11);
                perlin [row][col] += mix (smooth(distY), v1, v2) * amplitude;
                x += dxy;
            }
            y += dxy;
        }
        amplitude /= factor;
        n *= factor;
        if (maxSamples < 2 * n) {
            /* printf ("break\n"); */
        /* printf ("%d\n", n); */
            break;
        }
        /* printf ("%d\n", n); */
    }
    return perlin;
}


