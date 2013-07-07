/**
 * Student Number: 019-261-049
 * Section: A/B
 * Assignment 3
 * Description: Player 1 that for critical mass game.
 */
#ifndef P1_H
#define P1_H
#include "player.h"
#include "Timothy.h"
class P1: public Player {
  bool firstmove;
public:
  P1();
  void getmove(int& row,int& col, int board[][6]);
};
#endif