#include <stdio.h>
#include "helpers.h"

#define PORT 8080
#define MAX_MSG_BYTES 1024

void log_stdout(char *message) {
  fprintf(stdout, "%s\n", message);
}