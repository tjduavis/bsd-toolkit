/* BTP500 Assignment 1 
 * Question 1 */

#include "markpath.h"

bool MarkPath(char map[][25],int startx,int starty) {
	//FILE* fp=fopen("a1log.txt","a");
	bool solv;
	printf("TRACKER: %d,%d\n",startx,starty); getchar();
	if (map[startx][starty] == 'x') {
		printf("check1\n"); getchar();
		solv = false;
	} else if (map[startx][starty] == 'G') {
		printf("check2\n"); getchar();
		map[startx][starty] = '*';
		solv = true;
	} else {
		map[startx][starty] = '*';
		if (map[startx-1][starty] == ' ' || map[startx-1][starty] == 'G') {
			printf("N: %d,%d-%d,%d\n",startx,starty,startx-1,starty); getchar();
			if (solv = MarkPath(map,startx-1,starty)) {
				map[startx-1][starty] = 'n'; getchar();
			} else {
				map[startx-1][starty] = 'N'; getchar();
			}
		} else if (map[startx][starty+1] == 'x' && map[startx][starty-1] == 'x') {
			printf("N-False: %d,%d-%d,%d\n",startx,starty-1,startx,starty+1); getchar();
			solv = false;
		}
		if (map[startx+1][starty] == ' ' || map[startx+1][starty] == 'G') {
			map[startx][starty] = '*';
			printf("S: %d,%d-%d,%d\n",startx,starty,startx+1,starty); getchar();
			if (solv = MarkPath(map,startx+1,starty)) {
				map[startx+1][starty] = 's'; getchar();
			} else {
				map[startx+1][starty] = 'S'; getchar();
			}
		} else if (map[startx][starty-1] == 'x' && map[startx][starty+1] == 'x') {
			printf("S-False: %d,%d-%d,%d\n",startx,starty-1,startx,starty-1); getchar();
			solv = false;
		}
		if (map[startx][starty+1] == ' ' || map[startx][starty+1] == 'G') {
			map[startx][starty] = '*';
			printf("E: %d,%d-%d,%d\n",startx,starty,startx,starty+1); getchar();
			if (solv = MarkPath(map,startx,starty+1)) {
				map[startx][starty+1] = 'e';
			} else {
				map[startx][starty+1] = 'E';
			}
		} else if (map[startx+1][starty] == 'x' && map[startx-1][starty] == 'x') {
			printf("E-False: %d,%d-%d,%d\n",startx+1,starty,startx-1,starty); getchar();
			solv = false;
		}
		if (map[startx][starty-1] == ' ' || map[startx][starty-1] == 'G') {
			map[startx][starty] = '*';
			printf("W: %d,%d-%d,%d\n",startx,starty,startx,starty-1); getchar();
			if (solv = MarkPath(map,startx,starty-1)) {
				map[startx][starty-1] = 'w';
			} else {
				map[startx][starty-1] = 'W';
			}
		} else if (map[startx+1][starty] == 'x' && map[startx-1][starty] == 'x') {
			printf("W-False: %d,%d-%d,%d\n",startx+1,starty,startx-1,starty); getchar();
			solv = false;
		}
	}
	//fclose(fp);
	return solv;
}