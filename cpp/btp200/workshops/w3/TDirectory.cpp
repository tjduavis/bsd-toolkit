/*
* TDirectory.cpp
* Author: Timothy Duavis
* Last Modified: Feb 1/05
* Purpose: structure definitions for workshop3.cpp
*/

//Listing Memeber Function Definitions
/*---------------------------------------------*/

#include "TDirectory.h"

bool Listing::loadFileData (FILE* fp)
{
	bool ok;
	int valid;
	char fName[STR_SIZE], lName[STR_SIZE], l[STR_SIZE], pNum[STR_SIZE];

	if (fp != NULL)
	{
			valid = fscanf(fp,"%[^|]|%[^|]|%[^|]|%[^\n]\n",&fName, &lName, &l,&pNum);
			cout << valid << endl;
			if (valid == 4)
			{
				strcpy(firstName,fName);
				strcpy(lastName,lName);
				strcpy(location,l);
				strcpy(phoneNum,pNum);
				ok = true;
			}
	}
	else
	{
		rewind(fp);
		ok = false;
	}

	return ok;
};

//TDirectory memeber Function Definition
/*--------------------------------------*/
bool TDirectory::loadFileData(const char* filename)
{
	FILE* fileDir;
	bool success;
	int lineRead;

	NumEntry = 0;

	fileDir = fopen(filename,"r");
	cout << fileDir << endl;

	if(fileDir!=NULL)
	{
	//reads total lines in file entry
		do
		{
			lineRead = fgetc(fileDir);
			if (lineRead == '\n')
				NumEntry++;
		}while(lineRead != EOF);
	}
	else
		cout << "error" << endl;

	cout << NumEntry << endl;

	//instance list declared dynamic memory
	list = new Listing [NumEntry];
	for (int i=0; i<NumEntry; i++)
	{
		success = list[i].loadFileData(fileDir);
		if (success == false)
			i = NumEntry;
	};

	fclose(fileDir);

	return success;
};

void TDirectory::display() const
{
	for(int i=0; i<NumEntry; i++)
	{
		cout << list[i].given();
		cout << list[i].surname();
		cout << list[i].address();
		cout << list[i].telephone();
		cout << endl;
	}
}

void TDirectory::close()
{
	delete [] list;
}