// macro2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>

#define PI (3.14 + 1)
#define AREA(r) PI * r * r

int main(void)
{
	double ra = 2.35, rb = 3.56;
	double area_a = AREA(ra), area_b = AREA(rb);
	
	printf("area a: %10.2lf\narea b: %10.2lf\n",area_a, area_b);
	getchar();
	return 0;
}
