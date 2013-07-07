/* BTP500 Assignment 1 
 * Question 1 */

#include "markpath.h"

bool MarkPath(char map[][25],int startx,int starty) {
	bool solv;
	if (map[startx][starty] == 'x' || map[startx][starty] == '*') {
		solv = false;
		map[startx][starty] == ' ';
	} else if (map[startx][starty] == 'G')
		solv = true;
	else {
		map[startx][starty] = '*';
		if (MarkPath(map,startx-1,starty))
			map[startx-1][starty] = '*';
		if (MarkPath(map,startx+1,starty))
			map[startx+1][starty] = '*';
		if (MarkPath(map,startx,starty+1))
			map[startx][starty+1] = '*';
		if (MarkPath(map,startx,starty-1))
			map[startx][starty-1] = '*';
		map[startx][starty] = ' ';
	}
	return solv;
}