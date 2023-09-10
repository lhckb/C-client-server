#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/syscall.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

void print_matrix(int lines, int cols, int **mat);
void create_matrix(int lines, int cols, int **mat, bool populate);
void *sum_coordinate(void *);
void print_to_standard_error();
void free_matrix(int **mat, int lines);

struct routine_params_t {
  int coord_line;
  int coord_col;
  int **matrix1;
  int **matrix2;
  int **result;
};
typedef struct routine_params_t routine_params_t;

int main(int argc, char* argv[]) {
  srand((int) time(NULL));

  if (argc != 3) {
    fprintf(stdout, "%s\nExpected 2 arguments, got %d instead\n", argv[0], argc - 1);
    exit(EXIT_FAILURE);
  } 
  if (argv[1][0] < '1' || argv[2][0] < '1') {
    fprintf(stdout, "Arguments must be a number greater than 0\n");
    exit(EXIT_FAILURE);
  }

  int lines = atoi(argv[1]);
  int cols = atoi(argv[2]);

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
      routine_params_t params = {i, j, matrix, matrix2, result_matrix};
      params_list[tcount] = params;
      if(pthread_create(&threads[i], NULL, (void*) sum_coordinate, (void*) &params_list[tcount++])) {
        print_to_standard_error();
      }
    }
  }

  for (int i = 0; i < lines; i++) {
    if (pthread_join(threads[i], NULL)) {
      print_to_standard_error();
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

void *sum_coordinate(void *routine_params) {
  routine_params_t *params = (routine_params_t *) routine_params;
  int line = params->coord_line;
  int col = params->coord_col;
  int **mat1 = params->matrix1;
  int **mat2 = params->matrix2;
  int **res = params->result;

  int sum = mat1[line][col] + mat2[line][col];
  res[line][col] = sum;

  pid_t thread_id = syscall(__NR_gettid);

  fprintf(stdout, "Thread id %d with coords (%d, %d) returned %d\n", thread_id, line, col, sum);

  pthread_exit(NULL);
}

void print_to_standard_error() {
  fprintf(stderr, "[ERROR] errno %d\n", errno);
  strerror(errno);
}

void free_matrix(int **mat, int lines) {
  for (int i = 0; i < lines; i++) {
    free(mat[i]);
  }
  free(mat);
}
