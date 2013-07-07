/* Name: Timothy Duavis   Student Number: 019-261-049 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
/*
* Modify process4.c so that it creates another child just before the parent terminates. The new child should sleep for 5 seconds, 
* letting the parent terminate, then execute another "ps -f".
* Compile the program and run it. You should see the zombie "ls" process again in the output of the first "ps". 
* The second "ps" should show that the second "ps" process itself became an orphan, adopted by PID 1, and that the zombie process is gone.
* Run "ps -f" again after the 5 seconds expire, and the orphan process should be gone.
* Walkthrough process4.c and ensure that you understand exactly how it works. Make sure you can answer the following questions
* for your satisfaction:
*
* What does the program do?
*  - The program executes multiple shell commands.
*  - This is done by creating multiple processes within the entire processes,
*    using unix process scheduling techninques provided by the fork, waitpid system functions.
* How many processes does the program create during its run? 
* Include the parent process in your count.
*  - There are 6 processes in total.
*  - The fork in line 44 creates two processes
*  - The fork in line 50 creates two more processes
*  - The fork in line 57 creates the last two processes
* What is the purpose of the fork( ) function?
*  - The fork() function creates new or spawn child processes.
*  - The child process are exact copies in terms of init data, stack and heap
*    but not address space.
* What is the purpose of the execlp( ) function?
*  - The purpose of execlp is to execute a command shell.
*  - A successful execution ends the process which demonstrates the topics of
*    multiple processes within a program unix techniques.
* What is the purpose of the waitpid( ) function?
*  - The purpose of waitpid allows a parent process to wait
*    for its child process to terminate before executing preventing the child process to 
*    become an orphan.
*
*/

int main(void) {
   pid_t result;
   int retcode;
   if ((result = fork()) == 0) {   /* create a new child */
      execlp("ls", "ls", NULL);
      printf("execlp() failed");
      exit(1);
   }
   sleep(2);   /* try to ensure that the child will terminate before we continue */
   if ((result = fork()) == 0) {   /* create a new child */
      execlp("ps", "ps", "-f", NULL);
      printf("execlp() failed on ps -f command 1 of 2");
      exit(1);
   }
   printf("The parent will now wait for child with process id %d before terminating.\n",result);
   waitpid(result, &retcode, 0);
   if ((result = fork()) == 0) {   /* create a new child */
      execlp("sleep", "sleep", "5", NULL);
      printf("execlp() failed on sleep(5) command");
      exit(1);
   }
   execlp("ps", "ps", "-f", NULL);
   printf("execlp() failed on ps -f command 2 of 2\n");
   return(0);
}
