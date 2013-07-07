/**
 * Student Number: 019-261-049
 * Section: A/B
 * Assignment 3
 * Description: Player 1 that for critical mass game.
 */
#include "p1.h"
#include "Timothy.h"
extern "C"{
  #include "dio.h"
}
#include <stdlib.h>
#include <stdio>
P1::P1(){
  firstmove = true;
}
void P1::getmove(int& row,int& col, int board[][6]){
	if (firstmove) {
		bool findValid = false;
		int r, c;
		while (!findValid) {
			r = rand()%5;
			c = rand()%6;
			if (Owner(board,r,c) != -1) {
				row = r;
				col = c;
				findValid = true;
			}
		}
		firstmove = false;
	} else {
		tjduavis::GameTree T(board,1);
		T.GetBest(row,col);
	}
}
