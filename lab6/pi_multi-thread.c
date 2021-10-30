#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long incircle = 0;
long nPoint;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *runner() {
    int count;
    double x, y, z;
    count = 0;
    for (int i = 0; i < nPoint; ++i) 
    {
        x = rand() / ((double)RAND_MAX + 1) * 2.0 - 1.0;
        y = rand() / ((double)RAND_MAX + 1) * 2.0 - 1.0;
        z = x * x + y * y;
        if (z <= 1) 
            count++;
    }
    pthread_mutex_lock(&mutex);
    incircle += count;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(int argc, const char *argv[])
{
    pthread_attr_t attr;
    if (argc != 2) {
        fprintf(stderr, "usage: ./pi_multi-thread <total points>\n");
        return -1;
    }
    
    pthread_attr_init(&attr);

    long totalpoints = atol(argv[1]);
    int thread_count;
    if (totalpoints >= 1000) 
        thread_count = 1000;
    else if (totalpoints >= 100) 
        thread_count = 100;
    else 
        thread_count = 1;
    nPoint = totalpoints / thread_count;

    srand(time(NULL));

    pthread_t *threads = malloc(thread_count * sizeof(pthread_t));

    for (int i = 0; i < thread_count; i++) {
        pthread_create(&threads[i], &attr, runner, (void *) NULL);
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    free(threads);

    printf("%lf\n", (4.0 * (double)incircle) / totalpoints);

    return 0;
}
