#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define n 100000
#define nsteps 10

int main() {
    int itotal[nsteps];
    int iseed;
    double pi = 3.1415926;
    
    for (int i = 0; i < nsteps; i++) {
        itotal[i] = 0;
    }
    
    iseed = 876524;
    srand(iseed);

    for (int i = 0; i < n; i++) {
        double x = 0.0;
        double y = 0.0;

        for (int istep = 0; istep < nsteps; istep++) {
            double angle = 2.0 * pi * ((double)rand() / RAND_MAX);
            x = x + cos(angle);
            y = y + sin(angle);
        }

        int itemp = (int)sqrt(x * x + y * y);
        itotal[itemp]++;
    }

    printf("total = ");
    for (int i = 0; i < nsteps; i++) {
        printf("%d ", itotal[i]);
    }
    printf("\n");

    return 0;
}
