/*************************************************************************

  gcc -pthread test_param2.c -o test_param2 -std=gnu99

 */

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#define NUM_THREADS 10

int global_int = 0;
int shared_arr[NUM_THREADS] = {0};

/********************/
void *work(void *i)
{
  long int k;
  int f = *((int*)(i));  // get the value being pointed to
  int *g = (int*)(i);    // get the pointer itself
  
  int *arr = (int *)i;
  
  int global_i = global_int;
  global_int +=1 ;
  
  arr[global_i] += global_int;
  /* busy work */
  k = 0;
  for (long j=0; j < 10000000; j++) {
    k += j;
  }

  printf("Hello World from %lu with value %d\n", pthread_self(), f); 
  //*g+=3;
  //f += 3;

  printf("updated shared array\n");
 
 
  printf("\n"); 
  printf("in work(): f=%2d, k=%ld, *g=%d\n", f, k, *g);

  pthread_exit(NULL);
}

/*************************************************************************/
int main(int argc, char *argv[])
{
  long k, t;
  pthread_t id[NUM_THREADS];

  for (t = 0; t < NUM_THREADS; ++t) {
    if (pthread_create(&id[t], NULL, work, (void *)shared_arr)) {
      printf("ERROR creating the thread\n");
      exit(19);
    }
  }

  /* busy work */
  k = 0;
  for (long j=0; j < 100000000; j++) {
    k += j;
  }

  printf("k=%ld\n", k);
  printf("After creating the threads.  My id is %lx, t = %d\n",
                                                 (long)pthread_self(), t);
  printf("final state of shared array:\n[");
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("%d", shared_arr[i]);
    }
  return(0);

} /* end main */
