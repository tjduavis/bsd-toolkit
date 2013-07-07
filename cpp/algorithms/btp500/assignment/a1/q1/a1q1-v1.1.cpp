/* BTP500 Assignment 1 
 * Question 1 */

#include "markpath.h"

bool MarkPath(char map[][25],int startx,int starty) {
	if (map[startx][starty] == 'x')	return false;
	else if (map[startx][starty] == 'G') return true;
	else {
		map[startx][starty] = '*';
		if (MarkPath(map,startx-1,starty)) {
			map[startx-1][starty] = 't';
			return true;
		} else {
			map[startx][starty] = ' ';
			return false;
		}
		if (MarkPath(map,startx+1,starty)) {
			map[startx+1][starty] = 't'; 
			return true;
		} else {
			map[startx][starty] = ' ';
			return false;
		}
		if (MarkPath(map,startx,starty+1)) {
			map[startx][starty+1] = 't';
			return true;
		} else {
			map[startx][starty] = ' ';
			return false;
		}
		if (MarkPath(map,startx,starty-1)) {
			map[startx][starty-1] = 't';
			return true;
		} else {
			map[startx][starty] = ' ';
			return false;
		}
	}
}

		/*
		if (map[startx-1][starty] == ' ') {
			//map[startx-1][starty] = '*';
			printf("N: %d,%d-%d,%d\n",startx,starty,startx-1,starty);
			if (solv = ) {
				
			} else {
				map[startx][starty] = 'f';
				map[startx-1][starty] = 'f';
			}

		} 
		if (map[startx+1][starty] == ' ') {
			//map[startx][starty] = '*';
			//map[startx+1][starty] = '*';
			printf("S: %d,%d-%d,%d\n",startx,starty,startx+1,starty);
			if (solv = ) {
				
			} else {
				map[startx][starty] = 'f';
				map[startx+1][starty] = 'f';
			}

		}
		if (map[startx][starty+1] == ' ') {
			//map[startx][starty] = '*';
			//map[startx][starty+1] = '*';
			printf("E: %d,%d-%d,%d\n",startx,starty,startx,starty+1);
			if (solv = ) {
				
			} else {
				map[startx][starty] = 'f';
				map[startx][starty+1] = 'f';
			}
		}
		if (map[startx][starty-1] == ' ') {
			//map[startx][starty] = '*';
			//map[startx][starty-1] = '*';
			printf("W: %d,%d-%d,%d\n",startx,starty,startx,starty-1);
			if (solv = ) {
				
			} else {
				map[startx][starty] = 'f';
				map[startx][starty-1] = 'f';
			}
		}*/
