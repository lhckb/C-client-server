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

void free_list(node_t* head) {
  if (head->next == NULL) {
    free(head);
  }
  else {
    free_list(head->next);
  }
}

void print_list_to_stdout(node_t* head) {
  node_t* pointer = head->next;
  if (pointer != NULL) {
    fprintf(stdout, "value: %d\n", pointer->value);
    print_list_to_stdout(head->next);
  }
}

void add_value_to_list(node_t* head, int value) {
  node_t pointer = *head;
  if (pointer.next == NULL) {
    node_t* new_node = (node_t*) malloc(sizeof(node_t*));
    new_node->value = value;
    new_node->next = NULL;
    head->next = new_node;
    fprintf(stdout, "Added value %d to list\n", new_node->value);
  }
  else {
    add_value_to_list(pointer.next, value);
  }
}

int main(void) {
  srand(time(NULL));

  node_t* head_node = (node_t*) malloc(sizeof(node_t));
  head_node->next = NULL;
  head_node->value = '\0';

  int max_list_size = rand() % ARR_MAX;
  fprintf(stderr, "Max list size: %d\n", max_list_size);

  for (int i = 0; i < max_list_size; i++) {
    int new_value = rand() % RANDOM_MAX;
    add_value_to_list(head_node, new_value);
  }

  fprintf(stdout, "--------------------\n");
  print_list_to_stdout(head_node);
  fprintf(stdout, "--------------------\n");

  free_list(head_node);
  free(head_node);
  exit(EXIT_SUCCESS);
}
