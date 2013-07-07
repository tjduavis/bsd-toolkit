#if !defined(cdolivei_H)
#define cdolivei_H

#include "expgame.h"
//#define VERBOSE 1
#include <string.h>
#include <iostream>
using namespace std;
namespace cdolivei {
    const int ROWS = 5;
    const int COLUMNS = 6;
    const int WON = 500;
    const int LOST = 0;

    enum PLAYERS {
		PLAYER1 = 1,
		PLAYER2 = -1
	};

    /* A node contains the board after a player did a certain move
     * As well as pointers to it's children. Empty children are NULLs.
     * Nodes also create their children possibilities
     */
    class Node {
        int board[ROWS][COLUMNS];				/* The board after an explosion*/
        Node *possible_moves[ROWS*COLUMNS];     /* The possible moves derived from the board */
        bool leaf;								/* Whether the node is a leaf node */
        int evaluation;							/* A number we give to this node */
        int x_placement;						/* Where we placed the piece (column) */
        int y_placement;						/* Where we placed the piece (row) */
        int height;								/* The distance from the original root node */
    public :
        Node(int[][COLUMNS], int[][COLUMNS], int, int, int, bool, int);
        ~Node();
        void print(int);
        void print();
        int evaluate(int, int[][COLUMNS]);
        int getEvaluation(void) { return evaluation; }
        int getHeight(void) { return height; }
		bool isleaf(void) { return leaf; }

        Node *findBoard(int[][COLUMNS]);
        bool operator==(int[][COLUMNS]);
		Node* pickMove(int&, int&);
    };

    class GameTree {
        Node *root;
        Node *position;
        PLAYERS player;
        int height;				/* How many levels to add on to the tree */
        //int treeheight;			/* The height of the entire tree */

    private :
    	void Initialize(int[][COLUMNS]);
    public :
        GameTree(PLAYERS, int = 1);
        ~GameTree(void);
        void print();
        void getMove(int[][COLUMNS],int&,int&);
    };

    /* copies the board from src to dest, assuming there is enough space.
     * If src is NULL, we copy an empty board
     */
    void copyBoard(int src[][COLUMNS], int dest[][COLUMNS]);
    bool checkBoard(int[][COLUMNS]);
}
#endif  /* cdolivei_H_ */
