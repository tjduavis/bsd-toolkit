/* big-endian to little-endian */
/* b-l_endian_union.c */

#include <stdio.h>

int littleEndian_Union(int);

int main(void){
   int value = 32769;
   int le;
   
   le = littleEndian_Union(value);
   
   printf("big Endian = %x\n",value);
   printf("& big Endian = %d\n",&value);
   printf("little Endian_UNION = %x\n",le);
   printf("& little Endian_UNION = %d\n",&le);

   return 0; 
}

int littleEndian_Union(int bigEndian) {
   union u { int vi;  char c[4];}; 
   union v { int ni;  char d[4];};
   union u un; 
   union v vn; 
   un.vi = bigEndian; 
   vn.d[0]=un.c[3]; 
   vn.d[1]=un.c[2]; 
   vn.d[2]=un.c[1]; 
   vn.d[3]=un.c[0];
   
   return vn.ni;
} 	
