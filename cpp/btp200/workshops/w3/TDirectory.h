/*
* TDirectory.h
* Author: Timothy Duavis
* Last Modified: Feb 1/05
* Purpose: structure prototype and libraries for workshop3.cpp
*/

#include<new>
#include<string.h>
#include<iostream>
using namespace std;

#define FILE_LENGTH 21
#define STR_SIZE 16

struct Listing
{
	private:
		char firstName[STR_SIZE];
		char lastName[STR_SIZE];
		char location[STR_SIZE];
		char phoneNum[STR_SIZE];
	public:
		bool loadFileData (FILE* fp);
		const char* given() const
		{
			return firstName;
		}
		const char* surname() const
		{
			return lastName;
		}
		const char* address() const
		{
			return location;
		}
		const char* telephone() const
		{
			return phoneNum;
		}
};

struct TDirectory
{
	private:
		int NumEntry;
		Listing* list;
	public:
		bool loadFileData(const char* filename);
		void display() const;
		void close();
};
