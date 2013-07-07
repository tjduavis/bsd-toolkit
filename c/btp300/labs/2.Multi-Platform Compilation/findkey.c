/* Multi-Platform Compilation - Workshop2
*
* FILE: 	     findkey.c
* Author: 		 Timothy Duavis
* Last Modified: Sept 18/2005
*
* Description: design a direct terminal I/O * library that hides platform dependencies.
*/

#include <stdio.h>
#include "dtio.h"

int main(void) {
	int disp = 0;
	dtioStart();
	
	while ( disp != 27 ) {
		disp = dtioGetchar();
		if ( disp != 27 ) printf(" : %5d\n",disp);
		dtioFlush();
	}
	dtioStop();
 	
  	return 0;
}