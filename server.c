/**
 * Server side of a client-server application in C using unix sockets
 * @author Luís Cruz
 *  
 * Functionality:
 * - Opens Socket using socket()
 * - Binds a port to socket using bind()
 * - accept() a connection
 * - read() and write()
 * - finally, close()
 * 
*/

// use setsockopt to reuse a port

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "helpers/helpers.h"
#include <unistd.h>
#include <string.h>

#define QUEUE_SIZE 10
#define MAX_MSG_BYTES 1024

int main(void) {

  char buffer[MAX_MSG_BYTES];

  int optionTrue = 1;
  int res;
  struct sockaddr_in server_addr;
  int server_addr_size = sizeof(server_addr);

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd == -1) {
    fprintf(stderr, "There was a problem opening the Socket. Errno = %d\n", errno);
    return EXIT_FAILURE;
  }
  log_stdout("Socket opened");

  setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optionTrue, sizeof(int));

  res = bind(sock_fd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_in));
  if (res == -1) {
    fprintf(stderr, "There was a problem bindind to port %d. Errno = %d\n", PORT, errno);
    return EXIT_FAILURE;
  }
  log_stdout("Port bound");

  res = listen(sock_fd, QUEUE_SIZE);
  if (res == -1) {
    fprintf(stderr, "There was a problem listening on the socket. Errno = %d\n", errno);
    return EXIT_FAILURE;
  }
  log_stdout("Listening...");

  while(1) {
    memset(buffer, 0, MAX_MSG_BYTES);
    
    int client_fd = accept(sock_fd, (struct sockaddr *) &server_addr, (socklen_t *) &server_addr_size);
    if (client_fd == -1) {
      fprintf(stderr, "There was a problem accepting some connection. Errno = %d\n", errno);
      return EXIT_FAILURE;
    }
    log_stdout("Connection accepted");

    int bytes_read = read(client_fd, buffer, MAX_MSG_BYTES);
    if (bytes_read == -1) {
      fprintf(stderr, "Could not read message. Errno = %d\n", errno);
      return EXIT_FAILURE;
    }
    
    fprintf(stdout, "Bytes read from client: %d\n", bytes_read);
    fprintf(stdout, "Message from client:\n%s\n", buffer);
  }

  log_stdout("Closing server...");
  close(sock_fd);

  return EXIT_SUCCESS;
}