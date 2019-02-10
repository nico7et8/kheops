#include "dottify.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {

    int i = 0;
    int step = 200;
    char title[255];
    char index[5];

        cairo_surface_t * surface; 

        while (step) {
            surface = dottify ("source-images/sport-girl.png", step--);
            strcpy (title, "png/dots/dottify-test-");
            sprintf (index, "%03d", i++);
            strcat (title, index); 
            strcat (title, ".png"); 
            /* printf ("step = %d\t%s\n", step, title); */
            cairo_surface_write_to_png (surface, title);
        }
        cairo_surface_destroy (surface);


    return 0;
}
