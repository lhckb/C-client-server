/*
 * lsh - Lewis' Shell
 * @author Luís Cruz - https://github.com/lhckb
 * 
 * This is a simplified implementation of a Unix Shell aiming to help me learn how a shell works under the hood.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "utilities/string_utils.h"
#include "utilities/proc_utils.h"
#include <stdbool.h>

char style[4] = "seq";

int main(void) {
  // proc_args args_struct;
  proc_args command_list[MAX_INPUT / 2 + 1];
  char general_input[MAX_INPUT + 1];  // +1 accounts for \n at the end
  char *commands[MAX_INPUT / 2 + 1];
  int comm_count;

  // main loop
  while (true) {
    
    fprintf(stdout, ANSI_COLOR_GREEN "%s> " ANSI_COLOR_RESET, style);
  
    // release buffers for stdout (still dont know why)
    if (fflush(stdout) != 0) {
      print_errno_to_standard_error();
      exit(EXIT_FAILURE);
    }

    read(STDIN_FILENO, general_input, MAX_INPUT);

    if (strcmp(general_input, "style seq\n") == 0) {
      strcpy(style, "seq");
    }
    else if (strcmp(general_input, "style par\n") == 0) {
      strcpy(style, "par");
    }
    else if (strcmp(general_input, "exit\n") == 0) {
      fprintf(stdout, ANSI_COLOR_CYAN "stopping shell...\n" ANSI_COLOR_RESET);
      exit(EXIT_SUCCESS);
    }
    else {
      comm_count = sepparate_input_into_commands(general_input, commands);

      for (int i = 0; i < comm_count; i++) {
        sepparate_command_into_args(commands[i], &command_list[i]);
      }

      strcmp(style, "seq") == 0 ? call_exec_seq(command_list, comm_count) : call_exec_par(command_list, comm_count);
      
      memset(command_list, 0, comm_count);
    }

    memset(general_input, 0, MAX_INPUT + 1);
  }

  exit(EXIT_SUCCESS);
}
