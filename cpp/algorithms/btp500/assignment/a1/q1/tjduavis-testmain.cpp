#include "markpath.h"

int main(void) {
	char map[25][25];

	//default fill map
	for (int i=0; i < 25; i++) {
		for (int j=0; j < 25; j++) {
			map[i][j] = 'x';
		}
	}
	//fill paths
	/*for (int i=1; i < 4; i++)
		map[i][2] = ' ';
	for (int i=2; i < 5; i++)
		map[3][i] = ' ';*/
	
	//start non-winnable
	/*map[6][5] = ' ';*/

	//straight vertical test
	/*map[3][5] = 'G';
	map[4][5] = 'x';
	map[5][5] = ' ';
	map[6][5] = ' ';*/
	
	//straight horizontal test
	/*map[5][5] = 'G';
	map[5][4] = 'x';
	map[5][3] = ' ';
	map[5][2] = ' ';
	map[5][1] = ' ';*/

	//l-shape horizontal test -east first
	map[2][5] = ' ';
	map[3][5] = ' ';
	map[4][5] = ' ';

	map[5][5] = ' ';
	map[5][6] = ' ';
	map[5][7] = ' ';
	map[5][8] = ' ';
	map[5][9] = ' ';
	map[5][10] = ' ';
	map[5][11] = ' ';
	map[5][12] = ' ';

	map[5][9] = ' ';
	map[4][9] = ' ';
	map[3][9] = ' ';
	map[2][9] = 'x';

	map[2][12] = ' ';
	map[3][12] = ' ';
	map[4][12] = ' ';

	map[5][12] = ' ';
	map[6][12] = ' ';
	map[7][12] = ' ';
	map[8][12] = ' ';

	map[8][12] = ' ';
	map[8][11] = ' ';
	map[8][10] = 'x';

	map[7][9] = ' ';
	map[6][9] = ' ';
	map[5][9] = ' ';

	map[8][9] = ' ';
	map[9][9] = ' ';
	map[10][9] = ' ';
	map[11][9] = ' ';

	map[11][8] = ' ';
	map[11][7] = ' ';
	map[11][6] = '*';
	map[11][5] = 'G';
	//print map
	for (int i=0; i < 25; i++) {
		for (int j=0; j < 25; j++) {
			printf("%c",map[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	printf("\n");

	if (MarkPath(map,2,5))
		printf("Map is solvable\n");
	else
		printf("Map is not solvable\n");

	//print map
	for (int i=0; i < 25; i++) {
		for (int j=0; j < 25; j++) {
			printf("%c",map[i][j]);
		}
		printf("\n");
	}
	getchar();
	return 0;
}