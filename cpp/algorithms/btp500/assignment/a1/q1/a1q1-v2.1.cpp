/* BTP500 Assignment 1 
 * Question 1 */

#include "markpath.h"

bool MarkPath(char map[][25],int startx,int starty) {
	static bool solv = false;
	static int reverse = 0;
	static int backAndForth = 0;
	static int i = 0;

	if (map[startx][starty] == 'G') {
		printf("-%c- %d,%d",map[startx][starty],startx,starty);
		solv = true;
	} else if (backAndForth > 1) {
		solv = false;
	} else {
		if (map[startx-1][starty] != 'x' 
			|| reverse == 1 && map[startx][starty+1] == 'x' || reverse == 1 && map[startx][starty-1] == 'x') {
			//north-direction
			printf("%c %d,%d -%d",map[startx+1][starty-1],startx+1,starty-1,i++);
			if (reverse > 2) 
				backAndForth = 0;
			else if (reverse != 2) {
				reverse = 2;
				backAndForth++;
			}
			if (!MarkPath(map,startx-1,starty)) 
				map[startx-1][starty] = ' ';
			else {
				map[startx-1][starty] = '*';
				map[startx][starty] = '*';
			}
		} else if (map[startx+1][starty] != 'x' 
			|| reverse == 2 && map[startx+1][starty-1] == 'x') {
			//south-direction
			printf("%c %d,%d -%d",map[startx+1][starty-1],startx+1,starty-1,i++);
			if (reverse > 2) 
				backAndForth = 0;
			else if (reverse != 1) {
				reverse = 1;
				backAndForth++;
			}
			if (!MarkPath(map,startx-1,starty)) 
				map[startx+1][starty] = ' ';
			else {
				map[startx+1][starty] = '*';
				map[startx][starty] = '*';
			}
		} else if (map[startx][starty+1] != 'x' || reverse == 3) {
			printf("%d",backAndForth);
			//east-direction
			if (reverse < 3 && reverse) 
				backAndForth = 0;
			else if (reverse != 4) {
				reverse = 4;
				backAndForth++;
			}
			if (!MarkPath(map,startx,starty+1)) 
				map[startx][starty+1] = ' ';
			else {
				map[startx][starty+1] = '*';
				map[startx][starty] = '*';
			}
		} else if (map[startx][starty-1] != 'x' || reverse == 4) {
			//west-direction
			if (reverse < 3) 
				backAndForth = 0;
			else if (reverse != 3) {
				reverse = 3;
				backAndForth++;
			}
			if (!MarkPath(map,startx,starty-1)) 
				map[startx][starty-1] = ' ';
			else {
				map[startx][starty-1] = '*';
				map[startx][starty] = '*';
			}
		}
	}
	return solv;
}