 main()
 {
     int a;
     double b, c;

     a = 6;
     b = 0.7;
     while (a < 10 && b < 3.0) {
	 if (a < 8) {
	     a = a + 1;
	     b = b * 2;
	     c = a - b;
	 }
	 else {
	     a = a - 2;
	     b = b + 0.8;
	 }
	 c = a - b;
	 printf("%.2lf-%d-%.2lf\n", c, a, b);
     }
 }
