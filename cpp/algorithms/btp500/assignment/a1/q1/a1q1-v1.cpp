/* BTP500 Assignment 1 
 * Question 1 */

#include "markpath.h"

bool MarkPath(char map[][25],int startx,int starty) {
	bool solv;
	static bool reverse = false;
	printf("TRACKER: %d,%d\n",startx,starty);
	if (map[startx][starty] == 'x') {
		printf("check1\n");
		solv = false;
	} else if (map[startx][starty] == 'G') {
		printf("check2\n");
		map[startx][starty] = '*';
		solv = true;
	} else {
		map[startx][starty] = '*';
		if (map[startx-1][starty] == ' ' || map[startx-1][starty] == 'G') {
			reverse = true;
			printf("N: %d,%d-%d,%d\n",startx,starty,startx-1,starty);
			if (solv = MarkPath(map,startx-1,starty)) {
				map[startx-1][starty] = 't';
			} else {
				map[startx][starty] = 'f';
				map[startx-1][starty] = 'f';
			}
		} else if (map[startx][starty+1] == 'x' && map[startx][starty-1] == 'x' && reverse) {
			printf("N-False: %d,%d-%d,%d\n",startx,starty-1,startx,starty+1);
			solv = false;
		}
		reverse = false;
		if (map[startx+1][starty] == ' ' || map[startx+1][starty] == 'G') {
			reverse = true;
			map[startx][starty] = '*';
			printf("S: %d,%d-%d,%d\n",startx,starty,startx+1,starty);
			if (solv = MarkPath(map,startx+1,starty)) {
				map[startx+1][starty] = 't'; 
			} else {
				map[startx][starty] = 'f';
				map[startx+1][starty] = 'f';
			}
		} else if (map[startx][starty-1] == 'x' && map[startx][starty+1] == 'x' && reverse) {
			printf("S-False: %d,%d-%d,%d\n",startx,starty-1,startx,starty-1);
			solv = false;
		}
		reverse = false;
		if (map[startx][starty+1] == ' ' || map[startx][starty+1] == 'G') {
			reverse = true;
			map[startx][starty] = '*';
			printf("E: %d,%d-%d,%d\n",startx,starty,startx,starty+1);
			if (solv = MarkPath(map,startx,starty+1)) {
				map[startx][starty+1] = 't';
			} else {
				map[startx][starty] = 'f';
				map[startx][starty+1] = 'f';
			}
		} else if (map[startx+1][starty] == 'x' && map[startx-1][starty] == 'x' && reverse) {
			printf("E-False: %d,%d-%d,%d\n",startx,starty-1,startx,starty-1);
			solv = false;
		}
		reverse = false;
		if (map[startx][starty-1] == ' ' || map[startx][starty-1] == 'G') {
			reverse = true;
			map[startx][starty] = '*';
			printf("W: %d,%d-%d,%d\n",startx,starty,startx,starty-1);
			if (solv = MarkPath(map,startx,starty-1)) {
				map[startx][starty-1] = 't';
			} else {
				map[startx][starty] = 'f';
				map[startx][starty-1] = 'f';
			}
		} else if (map[startx+1][starty] == 'x' && map[startx-1][starty] == 'x' && reverse) {
			printf("W-False: %d,%d-%d,%d\n",startx,starty-1,startx,starty-1);
			solv = false;
		}
	}
	return solv;
}