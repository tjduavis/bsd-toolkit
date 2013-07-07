/* Name: Timothy Duavis   Student Number: 019-261-049 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/stat.h>
/*
* What do the programs do?
* What is the purpose of the socket( ) function in each program?
* What is the purpose of the connect( ) function in the client?
* What is the purpose of the bind( ) function in the server?
* What is the purpose of the listen( ) function in the server?
* What is the purpose of the accept( ) function in the server?
* What is the purpose of the fdopen( ) function in each program?
*
* Modify myserver2.c and myclient2.c so that the return values of all functions mentioned in step 10 are examined and, if appropriate, perror( ) 
* is used to issue an error message and the program is terminated unsuccessfully. Hint: check sections 2 and 3 of the "man" pages for each function. 
* For example, find "RETURN VALUE" in the following "man" page: man 2 socket
*
*/
int main(int argc, char *argv[]) {
   struct sockaddr_un saddr;
   socklen_t slen = sizeof(saddr);
   int server_fd, client_fd, ch;
   FILE *client_stream;
   saddr.sun_family = AF_UNIX;
   sprintf(saddr.sun_path, "/tmp/%s.socket", getlogin());
   unlink(saddr.sun_path);    
   server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
   if (server_fd == -1) {
     perror("socket");
     exit(1);
   }
   int bindStat;
   bindStat = bind(server_fd, (struct sockaddr *)&saddr, slen);
   if (bindStat == -1) {
     perror("bind");
     exit(1);
   }
   chmod(saddr.sun_path, 0666);
   int listenStat;
   listenStat = listen(server_fd,1);
   if (listenStat == -1) {
     perror("listen");
     exit(1);     
   }
   int acceptStat;
   while (1) {
      client_fd = accept(server_fd, NULL, NULL);
      if (acceptStat == -1) {
        perror("accept");
        exit(1);     
      }
      client_stream = fdopen(client_fd, "r");
      while ((ch = getc(client_stream)) != EOF)
         putchar(ch);
      fflush(stdout);
      fclose(client_stream);
   }
   close(server_fd);
}
