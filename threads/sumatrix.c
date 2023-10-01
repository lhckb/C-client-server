#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/syscall.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

struct routine_params_t {
  int coord_line;
  int coord_col;
  int **matrix1;
  int **matrix2;
  int **result;
  char *operation;
};
typedef struct routine_params_t routine_params_t;

void print_matrix(int, int, int **);
void create_matrix(int, int, int **, bool);
void *operate_coordinate(void *);
void print_errno_to_standard_error();
void free_matrix(int **, int);

int main(int argc, char* argv[]) {
  srand((int) time(NULL));

  if (argc != 4) {
    fprintf(stderr, "%s\nExpected 3 arguments, got %d instead\n", argv[0], argc - 1);
    exit(EXIT_FAILURE);
  } 
  if (argv[1][0] < '1' || argv[2][0] < '1') {
    fprintf(stderr, "Matrix sizes must be a number greater than 0\n");
    exit(EXIT_FAILURE);
  }
  if (strcmp(argv[3], "mult") != 0 && strcmp(argv[3], "sum") != 0) {
    fprintf(stderr, "Invalid argument %s. Expected mult or sum\n", argv[3]);
    exit(EXIT_FAILURE);
  }

  int lines = atoi(argv[1]);
  int cols = atoi(argv[2]);
  char *op = argv[3];

  int **matrix = (int **) malloc(lines * sizeof(int *));
  int **matrix2 = (int **) malloc(lines * sizeof(int *));
  int **result_matrix = (int **) malloc(lines * sizeof(int *));
  create_matrix(lines, cols, matrix, true);
  create_matrix(lines, cols, matrix2, true);
  create_matrix(lines, cols, result_matrix, false);

  fprintf(stdout, "Matrix 1:\n");
  print_matrix(lines, cols, matrix);
  fprintf(stdout, "Matrix 2:\n");
  print_matrix(lines, cols, matrix2);

  // create and join threads
  pthread_t *threads = (pthread_t *) calloc(lines, sizeof(pthread_t));
  routine_params_t *params_list = (routine_params_t *) calloc(lines, sizeof(routine_params_t));

  int tcount = 0;
  for (int i = 0; i < lines; i++) {
    for (int j = 0; j < cols; j++) {
      fprintf(stdout, "Creating thread %d\n", tcount);
      routine_params_t params = {i, j, matrix, matrix2, result_matrix, op};
      params_list[tcount] = params;
      if(pthread_create(&threads[i], NULL, (void*) operate_coordinate, (void*) &params_list[tcount++])) {
        print_errno_to_standard_error();
      }
    }
  }

  for (int i = 0; i < lines; i++) {
    if (pthread_join(threads[i], NULL)) {
      print_errno_to_standard_error();
    }
  }

  fprintf(stdout, "Result Matrix:\n");
  print_matrix(lines, cols, result_matrix);

  free(threads);
  free(params_list);
  free_matrix(matrix, lines);
  free_matrix(matrix2, lines);
  free_matrix(result_matrix, lines);
  exit(EXIT_SUCCESS);
}

void print_matrix(int lines, int cols, int **mat) {
  for (int i = 0; i < lines; i++) {
    fprintf(stdout, "|");
    for (int j = 0; j < cols; j++) {
      fprintf(stdout, " %d |", mat[i][j]);
    }
    fprintf(stdout, "\n");
  }
}

void create_matrix(int lines, int cols, int **mat, bool populate) {
  for (int i = 0; i < lines; i++) {
    mat[i] = (int*) calloc(cols, sizeof(int));
    for (int j = 0; j < cols; j++) {
      if (populate) mat[i][j] = rand()%9999;
    }
  }
}

void *operate_coordinate(void *routine_params) {
  routine_params_t *params = (routine_params_t *) routine_params;
  int line = params->coord_line;
  int col = params->coord_col;
  int **mat1 = params->matrix1;
  int **mat2 = params->matrix2;
  int **res = params->result;
  char *op = params->operation;

  int outcome;
  if (strcmp(op, "sum") == 0) {
    outcome = mat1[line][col] + mat2[line][col];
  }
  else if (strcmp(op, "mult") == 0) {
    outcome = mat1[line][col] * mat2[line][col];
  }
  res[line][col] = outcome;

  pid_t thread_id = syscall(__NR_gettid);

  fprintf(stdout, "Thread id %d with coords (%d, %d) returned %d\n", thread_id, line, col, outcome);

  pthread_exit(NULL);
}

void print_errno_to_standard_error() {
  fprintf(stderr, "[ERROR] errno %d\n", errno);
  strerror(errno);  //todo: fix this - returns a pointer. this call essentially is useless
}

void free_matrix(int **mat, int lines) {
  for (int i = 0; i < lines; i++) {
    free(mat[i]);
  }
  free(mat);
}
