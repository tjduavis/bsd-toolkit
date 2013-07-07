/*
* BTP100a
* Workshop 4: Table of Primes
*
* -Prime number verifier function
*
* Programmer: Timothy Duavis
* Date Modified: Oct 5/2004
*/

#include<stdio.h>

int main(void)
{
        int x,y,z,a,b=0;
        printf("prime number verifier function\n");
        scanf("%d",&y);
        b=y-(y-2);
        for(x=b;x<y;x++)
        {
                printf("%d",x);
                z=y%x;
                if(z==0)
                       a=1;
                printf("z:%d, a:%d\n",z,a);  
       }

        if(a==1)
                printf("%d is not a prime number\n",y);
        else
                printf("%d is a prime number\n",y);


        return 0;
}

