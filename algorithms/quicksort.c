#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARR_MAX 256
#define RAND_MAX 25

void quicksort(int array[]) {
  
}

void main(void) {
  srand(time(NULL));

  int array[ARR_MAX] = {0};

  int num = rand();
  printf("%d\n", num);

  // for (int i = 0; i < rand(); i++) {
  //   array[i] = rand();
  // }

  printf("%d\n", array[0]);

  exit(EXIT_SUCCESS);
}