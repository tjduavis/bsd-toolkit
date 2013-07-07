#include<stdio.h>

int do_something(int a, int b)
{
	int c;

	printf("a is %d, ",a);
	c=a+b-1;
	printf("c is %d\n",c);
	return c;
}	

main()
{
	int n,m;
	n=1;
	m=7;
	while(m<10)
	{
		n=do_something(n,m);
		m=m+1;
		printf("n is %d and m is %d\n",n,m);
	}
	printf("Phew!\n");
}