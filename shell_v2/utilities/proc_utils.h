#ifndef PROC_UTILS_H
#define PROC_UTILS_H

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