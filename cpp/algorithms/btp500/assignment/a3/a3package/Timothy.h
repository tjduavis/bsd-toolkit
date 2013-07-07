/**
 * Student Number: 019-261-049
 * Section: A/B 
 * Assignment 3
 * Description: Game tree for critical mass with a custom evaluation function.
 */
#ifndef TIMOTHY_H
#define TIMOTHY_H
#include <stdio>
#include "expgame.h"
namespace tjduavis {
	// custom evaluation function that determines the best position
	// on the board
	int eval(int board[][6],int player);

	// Game Tree code structure borrowed from 
	// Catherine Leung, BTP500 Professor 2006, Seneca College
	struct Node {
		int score;
		Node* possiblity[5][6];
		Node();
	};

	class GameTree{
		int player;
		Node* root;
		Node* CreateTree(int board[][6],int p, int h);
		int bestrow;
		int bestcol;
	public:
		GameTree(int board[][6],int p) {
			player = p;
			root = CreateTree(board,p,0);
		}
		void GetBest(int& r,int&c) {
			r=bestrow;
			c=bestcol;
		}
		~GameTree();
		void DestroyTree(Node* root);
	};

	// utility functions for custom evaulation
	int getElement(int position);
	int getIndex(int position);
	int isOuter(int index, int element);
	void CopyBoard(int copy[][6],int orig[][6]);

}// namespace
#endif