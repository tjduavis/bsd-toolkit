#include <cstdio>
#include <cstring>
using namespace std;
#include "Screen.h"

int main(void) {
	dtioStart();
	dtioClear();

	Screen s1;
	s1.add(10, 30, 25, "Test Screen",false);
	s1.add(13, 10, 5, "Name:XXX", false);
	//Field f1(10, 22, 15, "This is a test of a Field");
	
	system("pause");
	strcpy((char *)s1.getField(0)->data(),"<-Name: should be gone");
	//strcpy((char *)f1.data(),"<-Name: should");
	
	s1.display(false);
	//f1.display();
	printf("\n");
	system("pause");
	dtioStop();
	//printf("test");
	return 0;
}