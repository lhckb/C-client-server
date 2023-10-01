#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "string_utils.h"
#include "proc_utils.h"
#include <stdbool.h>

void print_errno_to_standard_error() {
  fprintf(stderr, "[ERROR] errno %d\n", errno);
  char *err_str = strerror(errno);
  fprintf(stderr, "%s\n", err_str);
}

int sepparate_input_into_commands(char *input, char *commands[MAX_INPUT / 2 + 1]) {
  remove_line_breaks(input);
  int index = 0;
  char *piece;

  piece = strtok(input, ";");
  while (piece != NULL) {
    // fprintf(stdout, "Piece %s", piece);
    commands[index] = piece;
    index++;
    piece = strtok(NULL, ";");
  }

  commands[index] = NULL;
  return index;
}

void sepparate_command_into_args(char *command, proc_args *arg_struct) {
  remove_line_breaks(command);
  char *args[MAX_ARG_SIZE];
  int index = 0;
  char *piece;

  piece = strtok(command, " ");
  while (piece != NULL) {
    args[index] = piece;
    index++;
    piece = strtok(NULL, " ");
  }

  arg_struct->proc_name = args[0];
  arg_struct->args = args;
  arg_struct->args[index] = NULL;
}

void remove_line_breaks(char *str) {
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] == '\n' || str[i] == EOF) {
      str[i] = 0;
    }
  }
}
