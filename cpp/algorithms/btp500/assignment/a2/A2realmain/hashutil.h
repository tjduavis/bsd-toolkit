#ifndef HASHUTIL_H
#define HASHUTIL_H
/**********************************************************/
/*                                                        */
/* Author: Catherine Leung                                */
/* header for heap utility functions                      */
/*                                                        */
/**********************************************************/
/*code for hash function comes from: 
  Data Structures and Algorithm Analysis in C++, Third Edition 
  by Mark Allen Weiss. page 188.
  Function returns a hash index*/
int HashFunction(const char* key, int tablesize);
/*this function returns the first number >= N that is a prime*/
int nextprime(int N);
/*this function returns true if N is a prime, false otherwise*/
int isprime(int N);
#endif
