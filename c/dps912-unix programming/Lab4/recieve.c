#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define SERVER "localhost"
#define PORT 8029
int main(int argc, char *argv[]) {
   struct addrinfo *ailist;
   struct sockaddr_in *sinp;
   socklen_t len = sizeof(struct sockaddr_in);
   int sockfd, port = PORT, result;
   char message[BUFSIZ + 1];
   if (argc > 1)
      sscanf(argv[1], "%d", &port);
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   getaddrinfo(SERVER, NULL, NULL, &ailist);
   sinp = (struct sockaddr_in *)ailist->ai_addr;
   sinp->sin_port = htons(port);
   connect(sockfd, (struct sockaddr *)sinp, len);
   while (1) {
      result = read(sockfd, message, BUFSIZ);
      message[result] = '\0';
      printf("%s", message + 1);
      if (message[0] == 'X') {
         close(sockfd);
         exit(EXIT_SUCCESS);
      }
   }
}

