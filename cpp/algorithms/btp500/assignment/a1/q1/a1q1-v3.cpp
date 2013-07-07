/* BTP500 Assignment 1 
 * Question 1 */

#include "markpath.h"

bool MarkPath(char map[][25],int startx,int starty) {
	static bool solv = false;
	if (map[startx][starty] == 'G') {
		solv = true;
	} else {
		if (MarkPath(map,startx,starty+1)) {
			if (map[startx][starty+1] != 'x') {
				map[startx][starty+1] = '*';
			}
		} else if (MarkPath(map,startx,starty-1)) {
			if (map[startx][starty-1] != 'x') {
				map[startx][starty-1] = '*';
			}
		}
	}
	return solv;
}