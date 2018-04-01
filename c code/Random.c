#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ftp://ftp.taygeta.com/pub/c/boxmuller.c
double ranf() { /* ranf() is uniform in 0..1 */
    return (double)rand() / (double)RAND_MAX ;
}
double *gauss(double mu, double sigma, int size) {
	double x1, x2, w, y1;
	static double y2;
	static int use_last, i;

    double *rnd_numbers;
    rnd_numbers = (double*)malloc(sizeof(double)*size);

    for (i = 0; i<size; i++) {
        use_last = 0;
        if (use_last) {
            y1 = y2;
            use_last = 0;
        }
        else {
            do {
                x1 = 2.0 * ranf() - 1.0;
                x2 = 2.0 * ranf() - 1.0;
                w = x1 * x1 + x2 * x2;
            } while ( w >= 1.0 );
            w = sqrt( (-2.0 * log( w ) ) / w );
            y1 = x1 * w;
            y2 = x2 * w;
            use_last = 1;
        }
        rnd_numbers[i] = mu + y1 * sigma;
    }
	return rnd_numbers;
}

int RandInRage(int min, int max) {
    return (rand() + min) % (max + 1);
}