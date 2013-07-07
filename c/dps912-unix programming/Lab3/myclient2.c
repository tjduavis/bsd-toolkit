/* Name: Timothy Duavis   Student Number: 019-261-049 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/socket.h>
int main(int argc, char *argv[]) {
   struct sockaddr_un saddr;
   socklen_t slen = sizeof(saddr);
   int socket_fd, ch;
   FILE *socket_stream;
   if (argc != 2) {
      fprintf(stderr, "Usage: %s recipient\n", argv[0]);
      exit(EXIT_FAILURE);
   }
   saddr.sun_family = AF_UNIX;
   sprintf(saddr.sun_path, "/tmp/%s.socket", argv[1]);
   socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
   int connectStat;
   connectStat = connect(socket_fd, (struct sockaddr *)&saddr, slen);
   if (connectStat == -1) {
     perror("connect");
     exit(1);
   }
   socket_stream = fdopen(socket_fd, "w");
   if (socket_stream == NULL) {
     perror("fdopen");
     exit(1);
   }
   while ((ch = getchar()) != EOF)
      putc(ch, socket_stream);
   fclose(socket_stream);
   exit(EXIT_SUCCESS);
}
