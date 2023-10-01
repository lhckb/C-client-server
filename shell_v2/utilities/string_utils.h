#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include "proc_utils.h"

#define MAX_ARGS 32
#define MAX_ARG_SIZE 64
#define MAX_INPUT 128

// colors for terminal output
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/*
 * Prints the current error represented by errno to stderr
*/
void print_errno_to_standard_error();

/*
 * @param command String containing command to be broken into an arg list;
 * @param arg_struct Address to the arg struct which will contain the command in question;
*/
void sepparate_command_into_args(char *command, proc_args *arg_struct);

/*
 * @param input String containing full input passed in to the shell;
 * @param commands Points to the commands matrix which will hold all commands after breaking them down;
 * @return Number of commands on success, 0 on failure
*/
int sepparate_input_into_commands(char *input, char **commands);

/* 
 * @param str String to have \n removed;
*/
void remove_line_breaks(char *str);

#endif
