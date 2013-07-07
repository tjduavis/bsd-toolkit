/* Assignment 1                        */
/* Course:          DPS912             */
/* Family Name:     Duavis             */
/* Given Name:      Timothy Joseph     */
/* Student Number:  019261049          */
/* Zenit Username:  dps912_081a06      */
/* Professor:       Les Czegel         */
/* Due Date:        February 22, 2008  */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define SERVER "zenit.senecac.on.ca"
#define PORT 9999
int main(int argc, char *argv[]) {
   int crate_status = 1;
   int port = PORT;
   
   if (argc > 1) { /* Program config setups */           
      if (strcmp(argv[1],"-p") == 0) { /* Accept port from "-p" arguement */
         port = atoi(argv[2]);
         if (port <= 0) {
            crate_status = 0;
            fprintf(stderr,"Error: port must be numeric\n");
         }
         else if (strchr(argv[2],'.') != NULL) { /* port number is float based */
            crate_status = 0;
            fprintf(stderr,"Error: port must be numeric\n");
         }
         else if (port < 1024 || port > 99999) {
            crate_status = 0;
            fprintf(stderr,"Error: port must be between 9999 and 99999\n");
         }
      } else
         fprintf(stderr,"Usage: crate [ -p port_number ]\n");
      
   } /* End of Program config setups */
   
   if (crate_status) { /* Program network setups */
      int evaluation_value[4];
      int i;
      
      struct addrinfo *ailist;
      struct sockaddr_in *sinp;
      socklen_t len = sizeof(struct sockaddr_in);
      int sock_fd, result;
      
      char message[BUFSIZ + 1];
      char menu_prompt[BUFSIZ + 1];
      char course[BUFSIZ + 1];      
      int response;
         
      sock_fd = socket(AF_INET, SOCK_STREAM, 0);
      getaddrinfo(SERVER, NULL, NULL, &ailist);
      sinp = (struct sockaddr_in *)ailist->ai_addr;
      sinp->sin_port = htons(port);
      connect(sock_fd, (struct sockaddr *)sinp, len);
      
      result = read(sock_fd, message, BUFSIZ);
      message[result] = '\0';
      printf("%s", message + 1);         
      
      while (1) {
         if (message[0] == 'M') {
            printf("Enter number, (v)iew ratings or (q)uit:");
            fflush(stdout);
            fgets(menu_prompt, BUFSIZ + 1, stdin);
            
            if (strcmp(menu_prompt,"v\n") == 0) { /* View the average course rate */
               strcpy(message,"v");
               write(sock_fd, message, strlen(message));
               system("clear");
               result = read(sock_fd, message, BUFSIZ);
               message[result] = '\0';
               printf("%s", message);                  
               printf("(Press <ENTER> to continue)");
               fgets(menu_prompt, BUFSIZ + 1, stdin);
               
               strcpy(message,"M");
               write(sock_fd, message, strlen(message));
               result = read(sock_fd, message, BUFSIZ);
               message[result] = '\0';
               system("clear");
               printf("%s", message + 1);               
            }
            else if (strcmp(menu_prompt,"q\n") == 0) { /* quit course rating program */
               exit(0);
            }
            else { /* course rating processing */
               /* printf("start course rating processing\n"); */
               response = atoi(menu_prompt);
               if (response <= 0) {
                  fprintf(stderr,"Error: invalid options\n");
               } else if (response > 4) {
                  fprintf(stderr,"Error: please select either options 1 - 4\n");
               }
               else {
                  int user_val = 0;
                  for (i = 0; i < 4; i++)
                     evaluation_value[i] = 0;
                  
                  printf("ctest1\n");
                  /* send an evaluation flag with course option */
                  sprintf(message,"E%d",response);
                  write(sock_fd, message, strlen(message));
                  printf("ctest2\n");
               
                  /* receive course name */
                  result = read(sock_fd, course, BUFSIZ);
                  course[result] = '\0';                  
                  printf("ctest4\n");
                  do { /* enter user input for course ratings */
                     printf("\n");
                     /* send interest level from user input */
                     /* with validation */
                     do {
                        printf("Enter Interest Level (1 - 10): ");
                        fgets(menu_prompt, BUFSIZ + 1, stdin);
                        user_val = atoi(menu_prompt);
                        if (user_val <= 0 || user_val > 10) {
                           user_val = 0;
                           printf("Invalid: Enter Interest Level (1-10):");
                           fgets(menu_prompt, BUFSIZ + 1, stdin);
                        } 
                        else
                           evaluation_value[0] = user_val;
                     } while (!user_val);
                     user_val = 0;
                  
                     /* send teaching level from user input */
                     /* with validation */
                     do {
                        printf("Enter Teaching Level (1 - 10): ");
                        fgets(menu_prompt, BUFSIZ + 1, stdin);
                        user_val = atoi(menu_prompt);
                        if (user_val <= 0 || user_val > 10) {
                           user_val = 0;
                           printf("Invalid: Enter Teaching Level (1-10):");
                           fgets(menu_prompt, BUFSIZ + 1, stdin);
                        }
                        else
                           evaluation_value[1] = user_val;
                     } while (!user_val);
                     user_val = 0;
                     
                     /* send evaluation level from user input */
                     /* with validation */
                     do {
                        printf("Enter Evaluation Level (1 - 10): ");
                        fgets(menu_prompt, BUFSIZ + 1, stdin);
                        user_val = atoi(menu_prompt);
                        if (user_val <= 0 || user_val > 10) {
                           user_val = 0;
                           printf("Invalid: Enter Evaluation Level (1-10):");
                           fgets(menu_prompt, BUFSIZ + 1, stdin);
                        }
                        else
                           evaluation_value[2] = user_val;
                     } while (!user_val);
                     user_val = 0;
                     
                     /* send bird level from user input */
                     /* with validation */
                     do {
                        printf("Enter Bird level (1 - 10): ");
                        fgets(menu_prompt, BUFSIZ + 1, stdin);
                        user_val = atoi(menu_prompt);
                        if (user_val <= 0 || user_val > 10) {
                           user_val = 0;
                           printf("Invalid: Enter Interest Level (1-10):");
                           fgets(menu_prompt, BUFSIZ + 1, stdin);
                        }
                        else
                           evaluation_value[3] = user_val;
                     } while (!user_val);
                     
                     fflush(stdout);
                     
                     printf("\n");
                     printf("%s Rating Information:\n",course);
                     printf("\n");
                     printf("Interest:%d Teaching:%d Evaluation:%d Bird-factor:%d\n",
                            evaluation_value[0],evaluation_value[1],evaluation_value[2],evaluation_value[3]);
                     printf("\n");
                     printf("Is this rating correct? (y/n): ");
                     fgets(menu_prompt, BUFSIZ + 1, stdin);
                  } while(strcmp(menu_prompt,"y\n")); /* end of enter user input for course ratings */
                  fflush(stdout);
                  
                  /* send user inputed values to server for registration */
                  sprintf(message,"%d %d %d %d",evaluation_value[0],evaluation_value[1],evaluation_value[2],evaluation_value[3]);
                  write(sock_fd, message, strlen(message) + 1);
                  
                  printf("\n");
                  printf("Your vote has been registered.\n");
                  
                  printf("(Press <ENTER> to continue)");
                  fgets(menu_prompt, BUFSIZ + 1, stdin);
                  strcpy(message,"M");
                  write(sock_fd, message, strlen(message) + 1);
                  
                  result = read(sock_fd, message, BUFSIZ);
                  message[result] = '\0';
                  system("clear");
                  printf("%s", message + 1);                  
               }
            } /* end of course rating processing */
         } else {
            printf("message from server = %s\n", message);
         }
         
      }      
   } /* End of Program network setups */   
   
   return 0;
} /* End of Main */

