#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 8

char *messages[NUM_THREADS];

struct thread_data
{
   int  thread_id;
   int  sum;
   char *message;
};

struct thread_data thread_data_array[NUM_THREADS];

void *PrintHello(void *threadarg)
{
   int taskid, sum;
   char *hello_msg;
   struct thread_data *my_data;

   sleep(1);
   my_data = (struct thread_data *) threadarg;
   taskid = my_data->thread_id;
   sum = my_data->sum;
   hello_msg = my_data->message;
   printf("Thread %d: %s  Sum=%d\n", taskid, hello_msg, sum);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int *taskids[NUM_THREADS];
   int rc, t, sum;

   sum=0;
   messages[0] = "Add to 0";
   messages[1] = "Add to 1";
   messages[2] = "Add to 2";
   messages[3] = "Add to 3";
   messages[4] = "Add to 4"; 
   messages[5] = "Add to 5";
   messages[6] = "Add to 6";
   messages[7] = "Add to 7";

   for(t=0;t<NUM_THREADS;t++) {
     sum = sum + t;
     thread_data_array[t].thread_id = t;
     thread_data_array[t].sum = sum;
     thread_data_array[t].message = messages[t];
     printf("Creating thread %d\n", t);
     rc = pthread_create(&threads[t], NULL, PrintHello, (void *) &thread_data_array[t]);
     if (rc) {
       printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
     }
   }
   pthread_exit(NULL);
}
