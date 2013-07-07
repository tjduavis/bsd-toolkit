 // Direct Access
 // direct.cpp
 // BTP300
 // Nov 2 2005

 #include <iostream>
 #include <fstream>
 using namespace std;

 int main(int argc, char* argv[]) {

     ofstream fout(argv[1]);          // open for output
     fout << "Line 1" << endl;        // line 1
     fout << "Line 2" << endl;        // line 2
     fout << "Line 3" << endl;        // line 3
     fout.seekp(0, ios::beg);         // to the start of the file
     fout << "****";                  // overwrite four characters
     fout.seekp(4, ios::cur);         // 4 char's beyond current position 
     fout << "#";                     // overwrite one character
     streampos pos = fout.tellp();    // remember current position
     fout.seekp(0, ios::end);         // to end of the file
     fout << "The last line" << endl; // add a line
     fout.seekp(pos);                 // jump back to pos
     fout << "^";                     // overwrite one character
     fout.close();                    // close file

     ifstream fin(argv[1]);           // open for reading
     char c;
     int n = 2;
     while (fin.get(c)) {              // read one character at a time
         cout << "|" << c << "|";     // display the character 
     	 if (c == n) cout << "it works" << endl;
     }
     fin.clear();                     // clear the failed (eof) state
     fin.seekg(-8, ios::end);         // move back 8 bytes from end
     while (fin.get(c))               // read one character at a time
         cout << c;                   // display the character read

     return 0;
 }
