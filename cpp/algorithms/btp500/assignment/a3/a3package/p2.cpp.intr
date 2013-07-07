#include "p2.h"
#include "leung.h"
extern "C"{
  #include "dio.h"
}
P2::P2(){
  /*call my InitLocation function from my namespace*/
  leung::InitLocation(curpos_);
}
void P2::getmove(int& row,int& col, int board[][6]){
  int key;
  dio_cursor(curpos_[row_][col_].row_,curpos_[row_][col_].col_);
  key=dio_getchar();
  while(!leung::isGood(board,key,-1,row_,col_)){
    dio_cursor(curpos_[row_][col_].row_,curpos_[row_][col_].col_);
    key=dio_getchar(); 
  }
  row=row_;
  col=col_;
}
