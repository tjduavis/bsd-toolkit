extern "C"{
  #include "dio.h"
}
#include "leung.h"
#include "expgame.h"

void leung::InitLocation(Locations currpos[][6]){
  for(int i=0;i<5;i++){
    for(int j=0;j<6;j++){
      currpos[i][j].row_=4+(i*3);
      currpos[i][j].col_=23+(j*6);
    }
  }
}
int leung::isGood(int board[][6],int key,int who,int& row,int &col){
  int rc=0;
  if(key!=LEFT && key!=RIGHT && key!=UP && key!=DOWN 
                                       && key!=' ' && key!=ENTER){
    rc=0;
  }
  else{
    switch(key){
      case LEFT:
        if(col!=0){
          col=col-1;
        }
        break;
      case RIGHT:
        if(col!=5){
          col=col+1;
        }
        break;
      case UP:
        if(row!=0){
          row=row-1;
        }
        break;
      case DOWN:
        if(row!=4){
          row=row+1;
        }
        break;
      default:
        if(board[row][col]==0 || Owner(board,row,col)==who)
          rc=1;
    }/*switch*/
  }/*else*/
  return rc;
}
