#ifndef PROC_UTILS_H
#define PROC_UTILS_H

/**
 * Struct simplifies what should be passed into execvp
 * @param proc_name Is the file path to the program (e.g.: /bin/ls)
 * @param args Is the full string of args to the program including file path
*/
struct proc_args {
  char *proc_name;
  char **args;
};
typedef struct proc_args proc_args;

/* 
 * @param args Arg struct list for the processes that will be called in sequence;
 * @param comm_count number of processes that will be executed (array size);
*/
void call_exec_seq(proc_args args[], int comm_count);

/* 
 * @param args Arg struct list for the processes that will be called in parallel;
 * @param comm_count number of processes that will be executed (array size);
*/
void call_exec_par(proc_args args[], int comm_count);

#endif