#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
double compute_pi(int nPoint)
{
    srand(time(NULL));
    int count;
    double x, y, z, pi;
    count = 0;
    for (int i = 0; i < nPoint; ++i) 
    {
        x = rand() / ((double)RAND_MAX + 1) * 2.0 - 1.0;
        y = rand() / ((double)RAND_MAX + 1) * 2.0 - 1.0;
        z = x * x + y * y;
        if (z <= 1) 
            count++;
    }
    pi = (double) count / nPoint * 4;
    return pi;
}

int main(int argc, const char *argv[]) 
{
    if (argc != 2) {
        fprintf(stderr, "usage: ./pi_serial <total points>\n");
        return -1;
    }
    long totalpoints = atol(argv[1]);
    printf("%lf\n", compute_pi(totalpoints));
    return 0;
}
