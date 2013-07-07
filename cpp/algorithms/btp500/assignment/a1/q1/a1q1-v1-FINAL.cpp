/* BTP500 Assignment 1 
 * Question 1 */

#include "markpath.h"

bool MarkPath(char map[][25],int startx,int starty) {
	bool solv;
	printf("TRACKER: %d,%d\n",startx,starty);
	if (map[startx][starty] == 'x') {
		solv = false;
	} else if (map[startx][starty] == 'G') {
		printf("check2\n");
		solv = true;
	} else {
		if (map[startx-1][starty] == ' ' || map[startx-1][starty] == 'G') {
			map[startx][starty] = '*';
			printf("N: %d,%d-%d,%d\n",startx,starty,startx-1,starty);
			if (solv = MarkPath(map,startx-1,starty)) {
				map[startx-1][starty] = '*';
			} else {
				map[startx][starty] = ' ';
				map[startx-1][starty] = ' ';
			}
		}
		if (map[startx+1][starty] == ' ' || map[startx+1][starty] == 'G') {
			map[startx][starty] = 's';
			printf("S: %d,%d-%d,%d\n",startx,starty,startx+1,starty);
			if (solv = MarkPath(map,startx+1,starty)) {
				map[startx+1][starty] = 't'; 
			} else {
				map[startx][starty] = 'f';
				map[startx+1][starty] = 'f';
			}
		}
		if (map[startx][starty+1] == ' ' || map[startx][starty+1] == 'G') {
			map[startx][starty] = '*';
			printf("E: %d,%d-%d,%d\n",startx,starty,startx,starty+1);
			if (solv = MarkPath(map,startx,starty+1)) {
				map[startx][starty+1] = 't';
			} else {
				map[startx][starty] = 'f';
				map[startx][starty+1] = 'f';
			}
		}
		if (map[startx][starty-1] == ' ' || map[startx][starty-1] == 'G') {
			map[startx][starty] = '*';
			printf("W: %d,%d-%d,%d\n",startx,starty,startx,starty-1);
			if (solv = MarkPath(map,startx,starty-1)) {
				map[startx][starty-1] = 't';
			} else {
				map[startx][starty] = 'f';
				map[startx][starty-1] = 'f';
			}
		}
	}
	return solv;
}


/*
		if (map[startx-1][starty] == ' ' || map[startx-1][starty] == 'G') {
			map[startx][starty] = '*';
			printf("N: %d,%d-%d,%d\n",startx,starty,startx-1,starty);
			if (solv = MarkPath(map,startx-1,starty)) {
				map[startx-1][starty] = 't';
			} else {
				map[startx][starty] = 'f';
				map[startx-1][starty] = 'f';
			}
		} else {
			solv = false;
			//|| map[startx][starty+1] == 'x' && map[startx][starty-1] == 'x'
		}
		if (map[startx+1][starty] == ' ' || map[startx+1][starty] == 'G') {
			map[startx][starty] = '*';
			printf("S: %d,%d-%d,%d\n",startx,starty,startx+1,starty);
			if (solv = MarkPath(map,startx+1,starty)) {
				map[startx+1][starty] = 't'; 
			} else {
				map[startx][starty] = 'f';
				map[startx+1][starty] = 'f';
			}
		} else {
			//|| map[startx][starty-1] == 'x' && map[startx][starty+1] == 'x'
			solv = false;
		}
		if (map[startx][starty+1] == ' ' || map[startx][starty+1] == 'G') {
			map[startx][starty] = '*';
			printf("E: %d,%d-%d,%d\n",startx,starty,startx,starty+1);
			if (solv = MarkPath(map,startx,starty+1)) {
				map[startx][starty+1] = 't';
			} else {
				map[startx][starty] = 'f';
				map[startx][starty+1] = 'f';
			}
		} else {
			//|| map[startx+1][starty] == 'x' && map[startx-1][starty] == 'x'
			solv = false;
		}
		if (map[startx][starty-1] == ' ' || map[startx][starty-1] == 'G') {
			map[startx][starty] = '*';
			printf("W: %d,%d-%d,%d\n",startx,starty,startx,starty-1);
			if (solv = MarkPath(map,startx,starty-1)) {
				map[startx][starty-1] = 't';
			} else {
				map[startx][starty] = 'f';
				map[startx][starty-1] = 'f';
			}
		} else {
			//|| map[startx+1][starty] == 'x' && map[startx-1][starty] == 'x'
			solv = false;
		}

*/