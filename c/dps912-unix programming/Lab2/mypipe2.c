/* Name: Timothy Duavis   Student Number: 019-261-049 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/file.h>

/*
* Copy mypipe.c to a file called mypipe2.c
* Modify mypipe2.c so that it creates another child and further pipes the output of head to wc (word count) in the new child. 
* The output of the new child should go to the screen. In other words, "mypipe2 mypipe2.c" should produce the same output as
* "od -bc < mypipe2.c | head | wc"
*
* What does the program do?
*   - The program executes the following commands through two pipes "od -bc < mypipe2.c | head | wc"
* How many pipes does it use? What kind?
*   - The program uses 2 pipes. The pipes are regular pipes that uses 1-dimensional array with 2 elements.
* How many processes does the program create during its run? Include the parent process in your count.
*   - The program uses 4 processes during its run.
* What is the purpose of the dup2( ) function?
*   - The purpose of the dup2 function is to take a file descriptor and copy it and 
*     then replace it to another file descriptor set in the second parameter
*/

int main(int argc, char *argv[]) {
   int i, filefd, pipefd[2], od_pid, head_pid, pid;
   int wc_pid, pipe2fd[2];
   for (i = 1; i < argc; i++) {
      filefd = open(argv[i], O_RDONLY);
      if (filefd < 0){
         printf("%s could not be opened\n", argv[i]);
         continue;
      }
      dup2(filefd, STDIN_FILENO);
      close(filefd);
      pipe(pipefd);
      if ((od_pid = fork()) == 0) {
         dup2(pipefd[1], STDOUT_FILENO);
         close(pipefd[0]);
         close(pipefd[1]);
         execl("/usr/bin/od", "od", "-bc", NULL);
         exit(EXIT_FAILURE);
      }
      pipe(pipe2fd);
      if ((head_pid = fork()) == 0) {
         dup2(pipefd[0], STDIN_FILENO);
         dup2(pipe2fd[1], STDOUT_FILENO);
         close(pipefd[0]);
         close(pipefd[1]);
         execl("/usr/bin/head", "head", NULL);
         exit(EXIT_FAILURE);
      }
      if ((wc_pid = fork()) == 0) { 
         dup2(pipe2fd[0], STDIN_FILENO);
         close(pipe2fd[0]);
         close(pipe2fd[1]);
         execl("/usr/bin/wc", "wc", NULL);
         exit(EXIT_FAILURE);
      }
      close(pipefd[0]);
      close(pipefd[1]);
      close(pipe2fd[0]);
      close(pipe2fd[1]);
      do {
         pid = wait(NULL);
         if (pid == od_pid)
            od_pid = 0;
         if (pid == head_pid)
            head_pid = 0;
         if (pid == wc_pid)
            wc_pid = 0;
      } while ((od_pid != 0 || head_pid != 0 || wc_pid != 0) && pid != -1);
   }
   exit(EXIT_SUCCESS);
}
