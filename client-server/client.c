/**
 * Client side of a client-server application in C using unix sockets
 * @author Luís Cruz
 *  
 * Functionality:
 * - Opens Socket using socket()
 * - Request Socket connection using connect()
 * - read() and write()
 * - finally, close()
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "helpers/helpers.h"
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {

  int res;
  struct sockaddr_in server_addr;
  socklen_t server_addr_size;

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr("192.168.100.2");

  // char *message;
  char message[MAX_MSG_BYTES];
  strcpy(message, argv[1]);
  // fprintf(stdout, "Write your message to be sent:\n");
  // scanf("%s", message);
  // fprintf(stdout, "%s", message);

  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd == -1) {
    fprintf(stderr, "There was a problem opening the Socket. Errno = %d\n", errno);
    return EXIT_FAILURE;
  }
  log_stdout("Socket opened");

  res = connect(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
  if (res == -1) {
    fprintf(stderr, "There was a problem connecting to server. Errno = %d\n", errno);
    return EXIT_FAILURE;
  }
  log_stdout("Connected to server...");

  res = send(sock_fd, message, strlen(message), 0);
  if (res == -1) {
    fprintf(stderr, "There was a problem sending message to server. Errno = %d\n", errno);
    return EXIT_FAILURE;
  }
  log_stdout("Message sent.");

  log_stdout("Closing client...");
  close(sock_fd);

  return EXIT_SUCCESS;
}