/**
 * Student Number: 019-261-049
 * Section: A/B
 * Assignment 3
 * Description: Player 2 that for critical mass game.
 */
#ifndef P2_H
#define P2_H
#include "player.h"
#include "Timothy.h"
class P2: public Player {
  bool firstmove;
public:
  P2();
  void getmove(int& row,int& col, int board[][6]);
};
#endif