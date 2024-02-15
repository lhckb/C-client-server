#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARR_MAX 25
#define RANDOM_MAX 25

void print_array_to_stdout(int array[], size_t size) {
  for (int i = 0; i < size; i++) {
    fprintf(stdout, "%d\n", array[i]);
  }
  fprintf(stdout, "-----------------------\n");
}

void quicksort(int array[], size_t array_size) {
  if (array_size < 2) {
    
  }
  else {
    int pivot = array[0];
    int smaller_or_equal[ARR_MAX] = {0};
    int larger[ARR_MAX] = {0};

    int i = 0, j = 0, k = 0;
    for ( ; i < array_size; i++) {
      if (array[i] <= pivot) {
        smaller_or_equal[j] = array[i];
        ++j;
      }
      else {
        larger[k] = array[i];
        ++k;
      }
    }

    memset(&smaller_or_equal[j], '\0', (ARR_MAX - j) * sizeof(int));
    memset(&larger[k],           '\0', (ARR_MAX - k) * sizeof(int));
  }
}

int main(void) {
  srand(time(NULL));

  int array[ARR_MAX] = {0};

  int max_array_size = rand() % ARR_MAX;
  fprintf(stdout, "Max array size: %d\n", max_array_size);

  for (int i = 0; i < max_array_size; i++) {
    int new_value = rand() % RANDOM_MAX;
    array[i] = new_value;
  }

  print_array_to_stdout(array, max_array_size);

  exit(EXIT_SUCCESS);
}
