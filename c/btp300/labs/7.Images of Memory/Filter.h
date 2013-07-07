/* Images of Memory
 * Workshop 7
 * Filter.h
 */
 #include <iostream>
 #include <iomanip>
 #include <fstream>
 #include <string.h>
 using namespace std;
 
 class Filter {
	 char* fileStr;
	 bool (*criterion)(const Account&) = NULL;
	 
	 public:
	 Filter(char fileRecord, const Account& accCrit) {
		 int len = strlen(fileRecord);
		 fileStr = new char [len+1];
		 strcpy(fileStr,fileRecord);
		 
		 criterion = accCrit;
		 ifstream fp(fileStr);
	 }		 
	 bool eof() { return fp.eof(io::eofbit); }
	 Account read() {
