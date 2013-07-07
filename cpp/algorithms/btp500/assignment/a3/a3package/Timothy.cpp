/**
 * Student Number: 019-261-049
 * Section: A/B
 * Assignment 3
 * Description: Game tree for critical mass with a custom evaluation function.
 */

#include "Timothy.h"
#include <iostream>
#define NULL 0
#define MAX_WINNING_SCORE 300
#define FIRST_TOP_POSITION 1
#define LAST_TOP_POSITION 6
using namespace std;

// The evaluation board determins the value the terminating
// (either by winner or by default height level) by figuring
// how much pieces the player has on the outer edges thens
// adds how much are not. the non-outer edges are divided by 2
// because the strategy for owning more pieces at the outer
// edges is 2 times better than not owning.
// This strategy uses 2 times as an arbitrary number.
int tjduavis::eval(int board[][6],int player) {
	int index, element;
	double totalOuter, totalInner;
	totalOuter = totalInner = 0.0;
	for (int i = 1; i < 31; i++) {
		index = getIndex(i);
		element = getElement(i);
		if (Owner(board,index,element) == player) {
			if (isOuter(index, element)) {
				totalOuter +=1;
			} else {
				totalInner +=1;
			}
		}
	}
	totalOuter = totalOuter / 32;
	totalInner = (totalInner / 2) / 18;
	totalOuter *= 100;
	totalInner *= 100;
	return totalOuter + totalInner;
}
// Simple constructor that sets the values of 
// the possibility nodes to a NULL value
tjduavis::Node::Node(){
  for(int i=0;i<5;i++){
    for(int j=0;j<6;j++){
      possiblity[i][j]=NULL;
    }
  }
}
// Builds the game tree recursively and sets the values bottom up.
// Borrowed from Catherine Leung, Computer Science Professor
// at Seneca College 2006
tjduavis::Node* tjduavis::GameTree::CreateTree(int board[][6],int turn, int h){
  Node* nn=new Node();
  int copy[5][6];
  if (CheckWin(board)) {
	 nn->score = MAX_WINNING_SCORE;
  } else if (h == 3) {
	 nn->score = eval(board,player);
  } else {
	CopyBoard(copy,board);
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 6; j++) {
		  if (Owner(copy,i,j) != (player * -1)) {
			  copy[i][j] ? copy[i][j] += copy[i][j]/copy[i][j] : copy[i][j] = player;
		  }
		  Explode(board);
		  nn->possiblity[i][j] = CreateTree(copy,turn + 1,h + 1);   //recursively create the subtree
		  CopyBoard(copy,board);									//undo the move
      }
    }
	// Logic to assign the possibility nodes with score values that sets the player's best
	// possible position and sets thes the worst score value for the opponents.
	bool setgood=false;
    if (turn % 2) {
      for (int i = 0; i < 5; i++){
        for (int j = 0; j < 6; j++){
          if (nn->possiblity[i][j] && Owner(copy,i,j) != (player * -1)){
            if (!setgood || nn->possiblity[i][j]->score < nn->score) {
             nn->score=nn->possiblity[i][j]->score;
             setgood=true;
            }
          }
        }//for
      }//for
    } else {
      for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 6; j++) {
          if(nn->possiblity[i][j] && Owner(copy,i,j) != (player * -1)) {
			if (!setgood || nn->possiblity[i][j]->score > nn->score) {
              nn->score=nn->possiblity[i][j]->score;
              setgood=true;
			  bestrow=i;
			  bestcol=j;
            }
          }
        }//for
      }//for
	}
  }
  return nn;
}
// Wrapper destructor that calls DestryTree for the traversal
// deallocation of all the possibility nodes.
tjduavis::GameTree::~GameTree(){
  DestroyTree(root);
}

// Deallocates all the nodes of the possibilty nodes.
// Copies parameter array orig to parameter array copy.
// Borrowed from Catherine Leung, Computer Science Professor
// at Seneca College 2006
void tjduavis::GameTree::DestroyTree(Node* root){
  if (root){
    for(int i=0; i< 5; i++){
      for(int j=0; j < 6; j++){
        DestroyTree(root->possiblity[i][j]);
      }
    }
    delete root;
  }
}
// Finds the element on a 5 X 6 board specified by
// the position value (1-30) of parameter position.
int tjduavis::getElement(int position) {
	int element;
	if (position) {
		if (position <= 6)
			element = position - 1;
		else {
			element = position % 6;
			if (element < 0) 
				element = 6 - 1;
		}
	}
	return element;
};
// Finds the index on a 5 X 6 board specified by
// the position value (1-30) of parameter position.
int tjduavis::getIndex(int position) { 
	int index;
	if (position <= 6)
		index = 0;
	else {
		index = ( position - getElement(position) ) / 6;
		position % 6 ? index : index--;
	}
	return index;
};
// Determines if the position value (1-30) on a 5 X 6 board 
// specified by parameter index and paramter element 
// are the outer edges.
int tjduavis::isOuter(int index, int element) {
	int rc = false;
	int checkValue = element + 1;
	if (index > 1) {
		for (int i = 0; i < index; i++) {
			checkValue += 6;
		}
	} else {
		checkValue += 6;
	}
	switch (checkValue) {
		case 7:
			rc = true;
			break;		
		case 13:
			rc = true;
			break;
		case 19:
			rc = true;
			break;
		case 25:
			rc = true;
			break;
		case 26:
			rc = true;
			break;
		case 27:
			rc = true;
			break;
		case 28:
			rc = true;
			break;
		case 29:
			rc = true;
			break;
		case 30:
			rc = true;
			break;
	}
	if (!rc) {
		if (checkValue >= FIRST_TOP_POSITION && checkValue <= LAST_TOP_POSITION)
			rc = true;
		else if (checkValue % LAST_TOP_POSITION == 0)
			rc = true;
	}
	return rc;
}

// Copies parameter array orig to parameter array copy.
// Borrowed from Catherine Leung, Computer Science Professor
// at Seneca College 2006
void tjduavis::CopyBoard(int copy[][6],int orig[][6]){
	for(int i=0;i<5;i++){
		for(int j=0;j<6;j++){
			copy[i][j]=orig[i][j];
		}
	}
}

