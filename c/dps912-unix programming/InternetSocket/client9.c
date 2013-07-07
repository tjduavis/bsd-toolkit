#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
int main(void) {
   struct addrinfo *ailist;
   struct sockaddr_in *sinp;
   socklen_t len = sizeof(struct sockaddr_in);
   int sockfd, bytes_received;
   char data_buffer[BUFSIZ + 1];
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   getaddrinfo("zenit.senecac.on.ca", NULL, NULL, &ailist);
   sinp = (struct sockaddr_in *)ailist->ai_addr;
   sinp->sin_port = htons(99995);
   connect(sockfd, (struct sockaddr *)sinp, len);
   bytes_received = read(sockfd, data_buffer, BUFSIZ);
   data_buffer[bytes_received] = '\0';
   printf("Message from server: %s\nEnter a line (or ^d to end):\n", data_buffer);
   fflush(stdout);
   while (fgets(data_buffer, BUFSIZ + 1, stdin) != NULL) {
      write(sockfd, data_buffer, strlen(data_buffer) + 1);
      bytes_received = read(sockfd, data_buffer, BUFSIZ);
      data_buffer[bytes_received] = '\0';
      printf("Message from server: %s\nEnter a line (or ^d to end):\n", data_buffer);
      fflush(stdout);
   }
   close(sockfd);
   exit(EXIT_SUCCESS);
}
