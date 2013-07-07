/*********************************************************/
/*                                                       */
/*   Written by: Timothy Duavis                          */
/*   Student Number: 019-261-049                         */
/*   Section: A/B                                        */ 
/*   Assignment #1 Version 1.0                           */
/*   The program demonstrates the use of recurssion      */ 
/*   functions.                                          */
/*   The program finds out whether a map that is 25 x 25 */
/*   is solvable. A solvable map contains a G with no X  */
/*   blocking its path. If it is solvable the path to G  */
/*   marked with a * else it is left blank.              */
/*                                                       */
/*   Course: BTP500-Fall 2006                            */
/*   Professor: Catherine Leung                          */
/*                                                       */
/*                                                       */
/*********************************************************/
bool MarkPath(char map[][25],int starty,int startx) {
	if (startx > 0 && starty > 0) {
		if (map[starty][startx] == 'X' || map[starty][startx] == '*')
			return false;
		else if (map[starty][startx] == 'G') {
			map[starty][startx] = '*';
			return true;
		} else {
			map[starty][startx] = '*'; //valid path
			if (MarkPath(map,starty,startx-1)) //NORTH DIRECTION
				return true;
			if (MarkPath(map,starty,startx+1)) //SOUTH DIRECTION
				return true;
			if (MarkPath(map,starty+1,startx)) //EAST DIRECTION
				return true;
			if (MarkPath(map,starty-1,startx)) //WEST DIRECTION
				return true;
			map[starty][startx] = ' '; //default value
		}
	}
	return false;
}