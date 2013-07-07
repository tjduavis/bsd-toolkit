#ifndef EXPGAME_H
#define EXPGAME_H
#include "screen.h"
/*BEGINNING OF UTILITY FUNCTIONS THAT YOU CAN USE IN YOUR GAME.  ALL FUNCTIONS
  LISTED IN THIS SECTION CAN BE USED BY YOUR PROGRAM AS LONG AS YOU SUPPLY IT
  THE PARAMETER IN THE MANNER THAT IT WANTS.  */
/*In all cases below the row/col index of a board are positioned such that 
  row 0, col 0 is the top left column of the board.  
  The board representation is a two dimensional integer array.  A value of 0,
  means empty square, A positive value means player 1 owns the pieces in 
  that square while a negative value means that player 2 owns the pieces in
  that square.  The actual value in the squre represents number of pieces in
  there.  For example -2 means that there are two pieces in the square and
  the pieces belong to player 2*/

/*Returns the absolute value of x*/
int ABS(int x);

/*returns true if the the values of row/col passed in indicate an edge square.
  Note: corners are also atedge*/
int atedge(int row,int col);

/*returns true if the values of the row/col passed in indicate a corner square*/
int atcorner(int row,int col);

/*returns the critical mass of the square at row r and col c*/
int CM(int r,int c);

/*returns the owner of the square at location row r and column c*/
int Owner(int board[][6],int r,int c);


/*returns 0 if nobody won, 1 if player 1 won, and -1 if player 2 won.
  NOTE:  check win just checks to see if all people on the board is 
  the same.  After player 1 makes the first move this function will
  return true but is in fact not a true win as p2 has not yet made a 
  move, thus be careful not to use this till after p2 has made one move*/
int CheckWin(int board[][6]);

/*this function will perform the explosions of the current board if there
  are any. This function returns true if any explosions occur, false
  otherwise.*/
int Explode(int board[][6]);

/*END OF UTILITY FUNCTIONS.  DO NOT USE THE CLASS/FUNCTIONS BELOW IN YOUR CODE, it is
  used by the main to run the game*/

/*finds all the squares that are at critical mass and store the locations
  into loc (loc[i][0] is the row, loc[i][1] is the col. The owner of the
  squares that are at critical mass is stored into who (there can only be
  one owner as a square only changes to critical mass for the one who is 
  moving).  Note who is not a value you give this function, you pass in
  a variable and the person's who's square is at critical mass is stored
  into it.  This function returns the number of squares at critical mass.
  NOTE:  You are unlikely to actually find any use for this function in
  your program*/
int FindCM(int loc[][2],int board[][6],int& who);

/*loc stores location of squares at critical mass and has numloc
  locations.  This functions sets the squares stored at the locations
  stored in loc to 0 on the board array */
void SetCMtoZero(int loc[][2],int board[][6],int numloc);

class ExpGame{
  int board_[5][6];       
  char pboard_[16][38];     //printable board, used to set up 
                            //the visible screen
  int who_;                 //who's turn is it? 1 for p1, -1 for p2
  Screen  scr_;             //the screen where the data will be shown
  Field* boardfld_[16];
  int iswin_;
  void DoExplosion(int showall=0);
  int checkWin();
  void DrawBoard();            //draw the board to the physical screen
public:
  ExpGame();
  int Add(int row, int col);   //adds a piece to the given row/col
                               //does not refresh to physical screen.
                               //returns true if it is valid, false otherwise
  void GetBoard(int bb[][6]);     //copies internal board to parameter
                               //I know this is slow and inefficicient
                               //but I need to make sure that your AI 
                               //won't mess up the board by accident.

  int isWin(){return iswin_;}
};
#endif