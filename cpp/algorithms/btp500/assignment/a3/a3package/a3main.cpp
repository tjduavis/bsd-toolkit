#include <stdio.h>
#include "player.h"
#include "p1.h"
#include "p2.h"
#include "screen.h"
#include "expgame.h"
int main(void)
{
  Screen InitScreen;
  Screen endscr;
  int board[5][6];
  Player* p[2];
  char tmp[41];
  p[0]=new P1();     //You need two copies of your object.  one called
  p[1]=new P2();     //P1, one called P2.  Put P1's code
                     //in the files p1.h and p1.cpp  Put P2's code 
                     //in the files p2.h and p2.cpp.   You MUST use these
                     //file names.
  int round=0;            //used to keep track of whose turn it is
  int row,col;            //used to pass back the row/col values
  int forfeit=0;          //if your computer player makes an invalid move
                          //your game is forfeited and the opponent
                          //automatically wins
  Field endF1("",8,20,40,0);
  Field endF2("",10,20,40,0);
  Field endF3("",11,20,40,0);
  Field endF4("",12,20,40,0);
  InitScreen.add(new Field("Ready to go.  Hit key to begin",11,25,40,0),1);
  InitScreen.edit(NULL,1);
  ExpGame currgame;
  currgame.GetBoard(board);
  p[0]->getmove(row,col,board);
  if(!currgame.Add(row,col))
    forfeit=1;
  else{
    currgame.GetBoard(board);
    p[1]->getmove(row,col,board);
    if(!currgame.Add(row,col))
      forfeit=-1;
  }
  while(!forfeit && !currgame.isWin()){
    currgame.GetBoard(board);
    p[round%2]->getmove(row,col,board);
	if(!currgame.Add(row,col)){
      forfeit=round%2?-1:1;
    }
	round++;
  }
  endF1.set("Game over.");
  if(!forfeit){
    if(currgame.isWin()>0){
      endF3.set("Player 1 has won!");
    }
    else{
      endF3.set("Player 2 has won!");
    }
  }
  else{
    sprintf(tmp,"to row=%d, col=%d",row,col);
    if(forfeit==-1){
      endF2.set("Player 2 has made an invalid move");
      endF3.set(tmp);
      endF4.set("Player 1 has won!");
    }
    else{
      endF2.set("Player 1 has made an invalid move");
      endF3.set(tmp);
      endF4.set("Player 2 has won!");
    }
  }
  endscr.add(&endF1);
  endscr.add(&endF2);
  endscr.add(&endF3);
  endscr.add(&endF4);
  endscr.edit(NULL,1);
}
