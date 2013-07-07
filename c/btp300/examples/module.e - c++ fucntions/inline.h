 /* Inline Functions
  * inline.h
  * BTP300
  * Oct 5 2005
  */

 #include <string.h> 
  
 class Student {
     unsigned no;
     char m[31];
 public:
     Student():no(0) {m[0] = '\0';}
     Student(unsigned n, const char* name):no(n) {strcpy(m, name);} 
     const char* name() const;
     unsigned number() const;
 };
 inline unsigned Student::number() const {return no;}
 inline const char* Student::name() const {return m;}