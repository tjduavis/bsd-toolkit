main()
{
	double x;
	int n, m;
	
	n=0;
	m=10;
	for(x=2.5; n<m; x=x+0.3)
	{
		if(n<3)
		{
			n=n+1;
			m=m-2;
		}
		else
			n=n+1;
		printf("%d %d %.1lf\n",n,m,x);
	}
	printf("%.1lf\n",x);
}