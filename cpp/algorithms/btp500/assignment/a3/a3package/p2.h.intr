#ifndef P2_H
#define P2_H
#include "player.h"
#include "leung.h"
/*put your code for your Player 1 AI here.  make sure your error 
checking is for Player 1 (+ve values on the board) in this one.  
You are welcome to add any members (both data and functions) that
you like.  Just be aware that main only will use getmove()*/
class P2:public Player{
  leung::Locations curpos_[5][6];
  int row_;
  int col_;
public:
  P2();
  void getmove(int& row,int& col, int board[][6]);
};
#endif