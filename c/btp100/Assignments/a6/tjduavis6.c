/*
*  Assignment 6: Version 1.00
*  2005 Sunrise
*  tjduavis6.c
*       Program for grocery stores that produces an itemized
*       bill of sale that meets the forthcoming 2005 point
*       of sale standards.
*       Admits voiding and displays alphabetic descriptions of the items purchased.
*       UPGRADE:        - reads information from product.txt, file
*                       - displays final information to receipt.txt, file
*
*  Programmer: Timothy Duavis
*  Due Date: Dec 5,04
*  Last Modified: Dec 5,2004
*/

#include<stdio.h>
#include <string.h>

#define PST 0.08
#define GST 0.07
#define MAX 100
#define BARCODE 13      /*max number a barcode contains*/
#define DLIMIT 32        /*descriptor string limit*/
/*Control Codes*/
#define RECEIPT 0
#define DISPLAY 17
#define PAYMENT 24

/****Function Protoypes****/
void bufferClear(void);
void loading(long long barcode[],float price[],char taxtype[], char descriptor[][32], int x, int v);
void sums(float price[], char taxtype[],float total[], int x);
void cashInput(float total[],int *i);
int barcodeChk(long long barcode);
int price_valid(float num, char endChk, int p);
int tax_valid(char tax, char endChk);
float SigDigs(float value);

/* upgrade */
void writeReciept(char descriptor[][DLIMIT], char taxtype[], float price[],float total[],int x);

int main(void)
{
/*---array types---*/
	long long barcode[MAX];
	float price[MAX];
	char taxtype[MAX];
	char descriptor[MAX][DLIMIT];
	float total[4];         /*element 0 = total PST Taxes, of items*/
				/*element 1 = total GST Taxes, of items*/
				/*element 2 = total prices, of items*/
				/*element 3 = change from total price*/

	long long barcode1[MAX];
	float price1[MAX];
	char taxtype1[MAX];
	char descriptor1[MAX][32];

/*---local variables---*/
	int exit=0;             /*flag for menu loop*/
	long long choice;       /*prototype for switch statement*/
	int x=0;                /*element variable*/
	int i=1;                /*flag for Balance verifier*/
	int j=0;                /*flag variable for user input loop*/
	int k;                  /*incrementer for display for-loop*/  
	int v;                  /*flag for void indicator*/

	printf("BTP100 Superstore\n");
	printf("=================\n");
	printf("Control Codes:\n");
	printf("\t0 print a receipt and quit\n");
	printf("\t17 display current subtotal\n");
	printf("\t24 accept customer payment\n");
	printf("\t31 void\n");

	/*---menu loop---*/
	while(exit!=1)
	{
		while(j!=1)
		{
			printf("? ");
			scanf("%lld",&choice);
			if(choice==0 || choice==17 || choice==24)
				j=1;
			else if(choice==31)
				v=1;    /*set flag v in loading function true*/
			else
				j=barcodeChk(choice);
		}
		barcode[x]=choice;

		j=0;    /*reset j*/

		switch(choice)
		{
			case RECEIPT:
				if(i!=0)         /*payments still needed*/
				{
					printf("***Balance Owing!***\n");
					printf("Control Code 24 - accept customer payment\n");
				}
				else
					exit=1;
				break;
			case DISPLAY:
				printf("PST @\t8%%\t$\t%10.2f\n",total[0]);
				printf("GST @\t7%%\t$\t%10.2f\n",total[1]);
				printf("Total\t\t$\t%10.2f\n",(total[2]+total[0]+total[1]));
				break;
			case PAYMENT:
				cashInput(total, &i);
				printf("Change\t\t$%10.2f\n",total[3]);
				break;
			default:
				/*barcode check*/
				loading(barcode, price, taxtype, descriptor, x, v);
				v=0; /*set flag for v false*/
				sums(price, taxtype, total, x);
				x++;
		}
	}
	printf("\n");
	/*---Receipt Display---*/
	printf("Your Friendly BTP100 Superstore Receipt\n");
	printf("=======================================\n");
	printf("\tBarcode Tax\tPrice\n");
	for(k=0; k<x; k++)
		printf("%15.17s %c\t%10.2f\n",descriptor[k],taxtype[k],price[k]);

	printf("\n");
	printf("PST @\t8%%\t$\t%10.2f\n",total[0]);
	printf("GST @\t7%%\t$\t%10.2f\n",total[1]);
	printf("Total\t\t$\t%10.2f\n",(total[2]+total[0]+total[1]));
	printf("\n");
	printf("Thank You for Shopping at BTP100\n");
	printf("Have a Nice Day!\n");

	writeReciept(descriptor,taxtype,price,total,x);
	
	return 0;
}

/****Function Definitions****/

/*
* Buffer Clear
*       Clears buffer, so there are no garbage after user input

*       Functions takes nothing in and returns nothing.
*/

void bufferClear(void)
{
	/*clears input buffer*/
	while(getchar()!='\n')
		;/*null statement*/
}

/*
*  Loading - Function
*       Loads barcode array, and in each barcode there is
*       parrallel arrays for price, and tax type.
*
*  Last Modified: Dec 05/04
*  Programmer: Timothy Duavis
*/

void loading(long long barcode[],float price[],char taxtype[], char descriptor[][DLIMIT], int x, int v)
{
/***Local Variables***/
	int r=0;
	int t=0;                /*flag for user-input loop and return value of scanf*/
	int count=0;            /*indicator for duplicates*/
	int duplicate;          /*element location for duplicates*/
	char endChk;
	char taxtypeChk;        /*character that will be validated before loading into array*/
	float priceBeta;        /*fl-pt. that will be validated before loading into array*/

	FILE *fp=NULL;
	int empty;
	int skip=0;
	long long barcode1;
	float price1;
	char taxtype1;
	char descriptor1[32];

	/*upgrade 2
	*       first check the product.txt file for duplicates
	*/

	fp=fopen("products.txt","r");
	if(fp!=NULL)
	{
		do
		{
			empty=fscanf(fp,"%lld;%31[^;];%c;%f",&barcode1,descriptor1,&taxtype1,&price1);
			if(barcode[x]==barcode1)
			{
				empty=EOF;
				skip=1;
				strcpy(descriptor[x], descriptor1);
				price[x]=price1;
				taxtype[x]=taxtype1;
			}

		}while(empty!=EOF);
	}
	else
		printf("***ERROR in I/O***\n");
	fclose(fp);

	if(skip!=1)
	{

		printf("Description for %lld : ",barcode[x]);
		bufferClear();
		scanf("%[^\n]%*c",descriptor[x]);

		while(t!=1)
		{
			printf("Price for %5lld : ",barcode[x]);
			t=scanf("%f%c",&priceBeta,&endChk);

			t=price_valid(priceBeta,endChk,t);
		}
			price[x]=priceBeta;
			t=0;    /*reset t*/

		while(t!=1)
		{
			printf("\tTaxable status\n");
			printf("\t(G = GST, P = PST, B = Both, N=none) : ");
			scanf("%c%c",&taxtypeChk,&endChk);
			t=tax_valid(taxtypeChk,endChk);
		}
		taxtype[x]=taxtypeChk;
		t=0;    /*reset t*/

	}

	/* void flag is true */
	/* if void flag is off and there is no duplciate append to file products.txt */
	if(v==1)
		price[x]=(-(price[x]));
	else if(v==0 && skip!=1)
	{
		/***print to file, products.txt****/
		fp=fopen("products.txt","a");
		if(fp!=NULL)
			fprintf(fp,"%lld;%s;%c;%.2f\n",barcode[x],descriptor[x],taxtype[x],price[x]);
		else
			printf("***ERROR in I/O***\n");
		fclose(fp);
	}
	       
}


/*
*  Sums - Function
*       Sums up the price for each barcode,
*       with or without tax.
*
*  Last Modified: Nov 15/04
*  Programmer: Timothy Duavis
*/

void sums(float price[], char taxtype[],float total[], int x)
{
/*---local variables---*/
	float taxP=0;
	float taxG=0;
	float priceSum=0;

	/*tax on price*/
	switch(taxtype[x])
	{
		case 'G':
			taxG=price[x]*GST;
			break;
		case 'P':
			taxP=price[x]*PST;
			break;
		case 'B':
			taxP=price[x]*PST;
			taxG=price[x]*GST;
			break;
		case 'N':
			taxP=0;
			taxG=0;
			break;
	}
	total[0]+=taxP;
	total[1]+=taxG;
	total[2]+=price[x];

	/*correct decimal places*/
	total[0]=SigDigs(total[0]);
	total[1]=SigDigs(total[1]);
	total[2]=SigDigs(total[2]);

}

/*
*  Cash Tendered - Function
*       Simple function where user enters cash that will
*       subtract from total.
*
*  Last Modified: Nov 15/04
*  Programmer: Timothy Duavis
*/

void cashInput(float total[], int *i)
{
/*local variables*/
	float cash;
	float diff;
	int n=0;          /*flag for user-input validation and return value for scanf*/
	char endChk;

	bufferClear();
	while(n!=1)
	{
		printf("Cash Tendered\t$ ");
		n=scanf("%f%c",&cash,&endChk);
		n=price_valid(cash,endChk,n);
	}

	diff=cash-(total[2]+total[1]+total[0]);
	diff=SigDigs(diff);

	if(diff<0)
	{
		total[2]=(-(diff));
		total[3]=0;
		*i=1;
	}
	else
	{
		total[3]=diff;
		*i=0;
	}

}

/*
*  Barcode Checker - Function
*       Program that validates a Universal Product Code (UPC),
*       European Article Numbering (EAN) symbol,EAN-8 amd EAN-13,
*       using the same calculations as UPC system.
*
*  Last Modified: Nov 13, 04
*  Programmer: Timothy Duavis
*/

int barcodeChk(long long barcode)
{

	int chk;                /*digit holder*/
	int counter;
	int holder[BARCODE];    /*array for digit holder*/
	int O_sum=0;            /*sum of odd digits*/
	int E_sum=0;            /*sum of even digits*/
	int test;               /*condition holder*/
	int valid;              /*validation -divisible by 10 restriction*/
	int c;                  /*flag for barcode loop in main*/

	for(counter=0;counter<BARCODE;counter++) /*12-1 upc digits*/
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
		c=1;
	else
	{
		c=0;
		printf("***Invalid UPC/EAN Code***\n");
	}

	return c;
}

/*
*  Price Validation - Function
*       Robust user input validations.
*       Floating point validation.
*
*  Last Modified: Nov 14,04
*  Programmer: Timothy Duavis
*/

int price_valid(float num, char endChk, int p)
{
	/*---Local Variable---*/
	int i;  /*flag for exit of menu in function main*/

	/*---Error Conditions---*/

	if(p==0)
	{
		i=0;
		printf("Error Input ***Must be numeric***\n");
		bufferClear();
	}
	else if(endChk!='\n')
	{
		i=0;
		printf("Error Input ***Trailing characters detected***\n");
		bufferClear();
	}
	else if(p<0)
	{
		i=0;
		printf("Error Input ***Value must be non-negative***\n");
	}
	else if(p==2)
		i=1;

	return i;
}

/*
*  Tax Type Validation - Function
*       Robust user input validations.
*       Character type validation.
*
*  Last Modified: Nov 14,04
*  Programmer: Timothy Duavis
*/

int tax_valid(char tax, char endChk)
{
	/*---Local Variables---*/
	int t;  /*flag to exit out of loop in function loading*/

	if(endChk!='\n')
		t=0;
	else if(tax=='B' || tax=='P' || tax=='G' || tax=='N')
		t=1;
	else
	{
		printf("Error Input **** %c: Invalid choice***\n",tax);
		t=0;
	}

	return t;
}

/*
*  SigDigs - Function
*       Specifies the signicant digit, inorder for correct
*       number of decimal places

*
*  Last Modified: Nov 15,04
*  Programmer: Timothy Duavis
*/

float SigDigs(float value)
{
	int truncated, remainder,rounding_test;
	float decimal;

	/*------Rounding Conversions------*/

	truncated=value;                /*convert value into whole value*/
	decimal=value-truncated;        /*get the decimal*/
	remainder=decimal*1000000;      /*turn decimal into a whole value*/
	remainder/=1000;                /*truncate the last three values*/
	rounding_test=remainder%10;     /*value to determine to round or not*/
	remainder/=10;          /*truncate the test value*/
	decimal=remainder;
	decimal/=100;           /*convert into decimal*/
	value=truncated+decimal;

	/*greater than 4 and less than -4 round up*/
	if((rounding_test>4 && rounding_test>0) || (rounding_test<(-4) && rounding_test<0))
		value+=0.01;

	return value;
}

/*
*  writeRecipt - Function
*       Writes final result to file called receipt.txt.
*
*  Programmer: Timothy Duavis
*  Last Modified: Dec 5,04
*/

void writeReciept(char descriptor[][32], char taxtype[], float price[],float total[],int x)
{
	int k;
	FILE *fp=NULL;

	fp=fopen("receipt.txt","w");
	if(fp!=NULL)
	{
		 /*---Receipt Display---*/
		fprintf(fp,"Your Friendly BTP100 Superstore Receipt\n");
		fprintf(fp,"=======================================\n");
		fprintf(fp,"\tBarcode Tax\tPrice\n");
		for(k=0; k<x; k++)
			fprintf(fp,"%15.17s %c\t%10.2f\n",descriptor[k],taxtype[k],price[k]);

		fprintf(fp,"\n");
		fprintf(fp,"PST @\t8%%\t$\t%10.2f\n",total[0]);
		fprintf(fp,"GST @\t7%%\t$\t%10.2f\n",total[1]);
		fprintf(fp,"Total\t\t$\t%10.2f\n",(total[2]+total[0]+total[1]));
		fprintf(fp,"\n");
		fprintf(fp,"Thank You for Shopping at BTP100\n");
		fprintf(fp,"Have a Nice Day!\n");
	}
	else
		printf("***ERROR in I/O***\n");
}
