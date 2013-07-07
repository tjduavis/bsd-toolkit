/*
  barcode.c
  Sept 25,2004
  Tim Duavis

  UPC validation
*/
main()
{
 long long barcode; /*upc barcode*/
 int chk;           /*digit holder*/
 int counter;       
 int holder[13];    /*array for digit holder*/
 int O_sum;         /*sum of odd digits*/
 int E_sum;         /*sum of even digits*/
 int test;          /*condition holder*/
 int valid;         /*validation -divisible by 10 restriction*/
 int x;

/* printf("Enter 12(UPC), 8(EAN-8), 13(EAN-13)");
 scanf("%d",&x);*/

 printf("Enter your selected digit:");
 scanf("%lld",&barcode);
 printf("barcode is: %lld\n",barcode);

 if(barcode==0)
	barcode+=1;

 for(counter=0;counter<13;counter++) /*12-1 upc digits*/
  {
   chk=barcode%10;
   barcode=barcode/10;
   holder[counter]=chk;
   if(counter>0) /*excluding holder[0] -check digit*/
   {
    test=counter%2;   /*whether digit is even or odd*/
    switch(test)
    {
      case 1:
       O_sum=holder[counter]+O_sum;
       break;
      case 0:
       E_sum=holder[counter]+E_sum;
       break;
    }
   }
  }
  O_sum=O_sum*3;
  valid=O_sum+E_sum+holder[0];
  valid=valid%10;
  if(valid==0)
   printf("Valid UPC!\n\n");
  else
   printf("Invalid UPC!\n\n");
}
