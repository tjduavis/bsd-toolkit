#ifndef P1_H
#define P1_H
#include "player.h"
#include "Timothy.h"
/*put your code for your Player 1 AI here.  make sure your error 
checking is for Player 1 (+ve values on the board) in this one.  
You are welcome to add any members (both data and functions) that
you like.  Just be aware that main only will use getmove()*/
class P1: public Player {
  bool firstmove;
public:
  P1();
  void getmove(int& row,int& col, int board[][6]);
};
#endif