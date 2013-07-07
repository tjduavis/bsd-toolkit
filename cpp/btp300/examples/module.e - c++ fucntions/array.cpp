 /* Dynamic Array Class
  * array.cpp
  * BTP300
  * Oct 5 2005
  */

 #include <iostream>
 #include <new>
 using namespace std;

 class Array {
     int* a;
     unsigned n;
     void init(unsigned no) {
         a = NULL;
         if (no)
             a = new (nothrow) int[no];
         n = a ? no : 0;
     }

 public:
     Array(unsigned no = 0) {init(no);}
     ~Array() {if (a) delete [] a;}
     Array(const Array& src) {
         init(src.n);
         for (unsigned i = 0; i < src.n; i++)
             a[i] = src.a[i];
     }
     Array& operator=(const Array& src) {
         if (&src != this) {
             if (a) delete [] a;
             init(src.n);
             for (unsigned i = 0; i < src.n; i++) 
                 a[i] = src.a[i];
         }
         return *this;
     }
     int& operator[](unsigned i) { return a[i];}
     unsigned length() const {return n;}
 };

 const unsigned size = 5;

 int main (void) {
     Array x(size);

     for (unsigned i = 0; i < size; i++)
         x[i] = i;

     for (int i = size - 1; i >= 1; i--)
         cout << x[i] << ',';
     cout << x[0] << endl;

     return 0;
 }
