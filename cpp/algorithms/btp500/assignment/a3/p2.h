#ifndef P2_H
#define P2_H
#include "player.h"
#include "cdolivei.h"
/*put your code for your Player 1 AI here.  make sure your error
checking is for Player 1 (+ve values on the board) in this one.
You are welcome to add any members (both data and functions) that
you like.  Just be aware that main only will use getmove()*/
using namespace cdolivei;
class P2:public Player{
GameTree p;
public:
  P2();
  void getmove(int& row,int& col, int board[][6]);
};
#endif