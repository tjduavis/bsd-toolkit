#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MAX_CLIENTS 3
#define PORT 8029
int main(int argc, char *argv[]) {
   struct sockaddr_in server_address;
   socklen_t server_len = sizeof(server_address);
   int server_sockfd, client_sockfd, reuse = 1, fd, fd2, port = PORT, num_clients = 0;
   fd_set readfds, testfds;
   char kb_message[BUFSIZ + 1];
   char message[BUFSIZ + 2];  /* extra byte for message type indicator */
   if (argc > 1)
      sscanf(argv[1], "%i", &port);
   printf("\n*** Server program starting (enter \"quit\" to stop): \n");
   fflush(stdout);
   server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
   setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
   server_address.sin_family = AF_INET;
   server_address.sin_addr.s_addr = htonl(INADDR_ANY);
   server_address.sin_port = htons(port);
   bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
   listen(server_sockfd, 5);
   FD_ZERO(&readfds);
   FD_SET(server_sockfd, &readfds);
   FD_SET(STDIN_FILENO, &readfds); /* add keyboard to file descriptor set */
   while (1) {
      testfds = readfds;
      select(4 + MAX_CLIENTS, &testfds, NULL, NULL, NULL);
      for (fd = 0; fd < 4 + MAX_CLIENTS; fd++) {
         if (FD_ISSET(fd, &testfds)) {
            if (fd == server_sockfd) { /* new connection request */
               client_sockfd = accept(server_sockfd, NULL, NULL);
               if (num_clients < MAX_CLIENTS) {
                  FD_SET(client_sockfd, &readfds);
                  num_clients++;
               } else {
                  sprintf(message, "XSorry, too many clients.  Try again later.\n");
                  write(client_sockfd, message, strlen(message));
                  close(client_sockfd);
               }
            } else if (fd == STDIN_FILENO) { /* keyboard activity */
               fgets(kb_message, BUFSIZ + 1, stdin);
               if (strcmp(kb_message, "quit\n") == 0) {
                  sprintf(message, "XServer is shutting down.\n");
                  for (fd2 = 4; fd2 < 4 + MAX_CLIENTS; fd2++) {
                     if (FD_ISSET(fd2, &readfds)) {
                        write(fd2, message, strlen(message));
                        close(fd2);
                     }
                  }
                  close(server_sockfd);
                  exit(EXIT_SUCCESS);
               } else {
                  sprintf(message, "M%s", kb_message);
                  for (fd2 = 4; fd2 < 4 + MAX_CLIENTS; fd2++)
                     if (FD_ISSET(fd2, &readfds))
                        write(fd2, message, strlen(message));
               }
            } else {
               /* client leaving - when client ends he issues a ctrl-c, sending through the socket a
                  end-of-file to the server or vice-versa. This is how this server works using the c-socket  */
               close(fd);
               FD_CLR(fd, &readfds);
               num_clients--;
            }
         }
      }
   }
}
 
