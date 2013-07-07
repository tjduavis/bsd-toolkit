/*********************************************************/
/*                                                       */
/*   Written by: Catherine Leung                         */
/*   Version 1.0                                         */
/*   This is the official test main for Question 1       */
/*   of Assignment 1                                     */
/*   BTP500-Fall 2006                                    */
/*                                                       */
/*   To compile this program on phobos:                  */
/*       c++ a1q1.cpp a1q1main.cpp -qstaticinline        */
/*   To compile this program on the PC :                 */
/*       bcc32 a1q1.cpp a1q3main.cpp                     */
/*                                                       */
/*   You will also need to have the file maze*.txt an    */
/*   maze*sol.txt files in the same directory in order   */
/*   for this main to run                                */
/*                                                       */
/*   V1.1 changes, took variable names out of MarkPath   */
/*   function prototype                                  */
/*                                                       */
/*********************************************************/
#include <stdio.h>
const int numfiles = 14;
bool MarkPath(char [][25],int ,int );
bool ReadMazeFile(const char* fname,char map[][25],int& numrows,int& row,int& col);
bool ReadSolFile(const char* fname, char map[][25],int numrows,int& solution);
bool CompareMap(char map[][25],char answerkey[][25],int numrows);
void PrintMap(char map[][25],int numrows);
int main(void){	
  char map[25][25];  //array holding our maze
  char key[25][25];  //array holding the correct solution
  int row,col;       //starting positions.
  int numrows;       //number of rows for the given map
  int haspath;       //read from file, indicates if there is a solution
  bool rc;           //stores return value from MarkPath
  bool isgood=true;  //a flag, true if MarkPath() function works, false otherwise
  int i;             //loop counter
  char mazename[20]="mazeA.txt";     //name of the file containing the maze
  char keyname[20]="mazeAsol.txt";   //name of the file containing the solution
  for(i=0;i<numfiles && isgood;i++){
    mazename[4]=i+'A';             
    keyname[4]=i+'A';
    isgood=ReadMazeFile(mazename,map,numrows,row,col);
  	if(!isgood){
      printf("Unable to continue test.  Unable to open file: %s\n",mazename);
    }
    else{
      isgood=ReadSolFile(keyname,key,numrows,haspath);
      if(!isgood){
        printf("Unable to continue test.  Unable to open file: %s\n",keyname);
      }
      if(isgood){
        rc= MarkPath(map,row,col);
        if(rc==haspath){
          isgood=CompareMap(map,key,numrows);
          if(!isgood){
            printf("Path is incorrectly marked when testing maze from file: %s\n",mazename);
            printf("\nThe correct path:\n");
            PrintMap(key,numrows);
            printf("\nYour function's path:\n");
            PrintMap(map,numrows);
          }//!isgood
        }//rc==haspath
        else{
          printf("Return value was incorrect when testing maze from file: %s\n",mazename);
          printf("Correct return value: %s\n",haspath?"true":"false");
          printf("Return value from your function: %s\n",rc?"true":"false");
          isgood=false;
        }
      }//isgood
    }//else
  }//for
  if(isgood)
    printf("Congratulations, your question 1's code is working correctly!\n");
 return 0;
}
bool ReadMazeFile(const char* fname,char map[][25],int& numrows,int& row,int& col){
  FILE* fp=fopen(fname,"r");
  bool rc=true;
  if(fp){
    fscanf(fp,"%d %d %d\n",&numrows,&row,&col);
    for(int i=0;i<numrows;i++){
      for(int j=0;j<25;j++){
        fscanf(fp,"%c",&map[i][j]);
      }
      fscanf(fp,"\n");
    }
    fclose(fp);
  }
  else
    rc=false;
  return rc;
}
bool ReadSolFile(const char* fname, char map[][25],int numrows,int& solution){
  bool rc=true;
  int sol;
  FILE* fp=fopen(fname,"r");
  if(fp){
    fscanf(fp,"%d\n",&sol);
    solution=(bool)sol;
    for(int i=0;i<numrows;i++){
      for(int j=0;j<25;j++){
        fscanf(fp,"%c",&map[i][j]);
      }
      fscanf(fp,"\n");
    }
    fclose(fp);
  }
  else
    rc=false;
  return rc;
}
void PrintMap(char map[][25],int numrows){
  for(int i=0;i<numrows;i++){
    for(int j=0;j<25;j++){
      printf("%c",map[i][j]);
    }
    printf("\n");
  }
}
bool CompareMap(char map[][25],char answerkey[][25],int numrows){
  bool isgood=true;
  for(int i=0;i<numrows && isgood;i++){
    for(int j=0;j<25 && isgood;j++){
      if(map[i][j]!=answerkey[i][j])
        isgood=false;
    }
  }
  return isgood;
}
