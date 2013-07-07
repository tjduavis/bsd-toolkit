/* BTP500 Assignment 1 
 * Question 1 */

bool MarkPath(char map[][25],int starty,int startx) {
	if (startx > 0 && starty > 0) {
		if (map[starty][startx] == 'X' || map[starty][startx] == '*') {
			return false;
		} else if (map[starty][startx] == 'G') {
			map[starty][startx] = '*';
			return true;
		} else {
			map[starty][startx] = '*';
			if (MarkPath(map,starty,startx-1)) return true;
			if (MarkPath(map,starty,startx+1)) return true;
			if (MarkPath(map,starty+1,startx)) return true;
			if (MarkPath(map,starty-1,startx)) return true;
			map[starty][startx] = ' ';
		}
	}
	return false;
}