/*
 * workshop3.cpp
 * Author: Timothy Duavis
 * Date Modified: Feb 1/05
 * Description:A simple program that reads data from a file and displays.
 * Purpose:     To design a C++ struct that has instances of another C++ struct, and
 *                      to use dynamic memory allocation.
 */

#include "TDirectory.h"

int main (void)
{
	TDirectory Dir;
	char userFile[FILE_LENGTH];
	bool success;

	//header
	cout << "Telephone Directory" << endl;
	cout << "===================" << endl;

	//User Input
	cout << "Enter the name of the listings file : " << endl;
	cin >> userFile;
	cout << userFile << endl;

	success = Dir.loadFileData(userFile);
	cout << success << endl;
	if (success == true )
		Dir.display();
	else
		cout << "File Read ERROR" << endl;

	//clean up before ending program
	Dir.close();

	return 0;
};
