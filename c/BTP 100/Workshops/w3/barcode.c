main
{
 int barcode;
 int check;
	
 printf("Enter your UPC digit:");
 scanf("%d",&barcode);
		
  check=barcode%10;
  printf("%d",check);	
  /*if(chk==9)*/
  return 0;	
}
  