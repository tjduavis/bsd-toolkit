#include "p2.h"
#include "cdolivei.h"
extern "C"{
  #include "dio.h"
}
P2::P2():p(PLAYER2,3){
}
void P2::getmove(int& row,int& col, int board[][6]){
	p.getMove(board,row,col);
}
