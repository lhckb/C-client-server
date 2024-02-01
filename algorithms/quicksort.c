#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARR_MAX 25
#define RANDOM_MAX 25

typedef struct node_t {
  int value;
  struct node_t *next;
} node_t;

// node_t* init_list() {
//   node_t new_node;
//   // new_node.value = NULL;
//   new_node.next = NULL;
//   return &new_node;
// }

// void free_list(node_t* head) {
//   node_t* pointer = head;
//   while (pointer->next != NULL) {
//     node_t* current = pointer;
//     pointer = pointer->next;
//     free(current);
//     fprintf(stdout, "freed memory\n")
//   }
//   free(pointer);
// }

void print_list_to_stdout(node_t* head) {
  node_t* pointer = head->next;

  fprintf(stdout, "--------------------\n");

  int i = 0;
  for (node_t* pointer = head->next; i < 5; pointer = pointer->next) {
    fprintf(stdout, "%d\n", pointer->value);
    // pointer = pointer->next;
    i++;
  }

  fprintf(stdout, "--------------------\n");
}

int add_value_to_list(node_t* head, int value) {
  node_t* head_copy
  node_t new_node;
  new_node.value = value;
  new_node.next = NULL;

  node_t* pointer = head;
  while (pointer != NULL) {
    if (pointer->next == NULL) {
      pointer->next = &new_node;
      fprintf(stdout, "Added value %d to list\n", new_node.value);
      return 0;
    }

    pointer = pointer->next;
  }

  return -1;
}

void merge_arrays(int array1[], int array2[], int array3[]) {
  
}

int* quicksort(int array[], size_t array_size) {
  if (array_size < 2) {
    return array;
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

  node_t head_node;
  head_node.next = NULL;
  head_node.value = '\0';

  // int array[ARR_MAX] = {0};
  // size_t original_size = sizeof(array) / sizeof(int);

  int max_list_size = rand() % ARR_MAX;
  fprintf(stderr, "Max list size: %d\n", max_list_size);
  for (int i = 0; i < max_list_size; i++) {
    // array[i] = rand() % RANDOM_MAX;
    int new_value = rand() % RANDOM_MAX;
    if (add_value_to_list(&head_node, new_value) < 0) {
      fprintf(stderr, "Error adding value to list\n");
      exit(EXIT_FAILURE);
    }
  }

  // quicksort(array, original_size);
  print_list_to_stdout(&head_node);

  // printf("%d\n", array[0]);

  // free_list(&head_node);
  exit(EXIT_SUCCESS);
}