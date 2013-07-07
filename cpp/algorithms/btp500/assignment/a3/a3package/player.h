#ifndef PLAYER_H
#define PLAYER_H
 /*Abstract base class Player.  Your objects will be derived from this.  
  This object stores no information and has one single pure virtual function
  which your object must override.  It's job is simply to provide a
  clean interface for the main*/
class Player{
public:
  /*The getmove function is passed references to two ints and a board.
    the board is an integer array [5][6].  a 0 represents empty spot.
    +ve values for player 1, -ve values for player 2, thus an element with
    -3 means there are 3 pieces on the corresponding square and they belong to
    player 2.  Your function will use the board information to figure out
    which row and which column to put the piece in and pass them back.
    row must be between 0 and 4, col must be between 0 and 5.
    Your program must pass back valid values (in terms of range and placement
    rules) or you will lose the game.*/
  virtual void getmove(int& row,int& col, int board[][6])=0;
};

#endif