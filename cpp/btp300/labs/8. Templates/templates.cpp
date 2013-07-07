 #include <iostream>
 #include <iomanip>
 using namespace std;

 template <class T, int n = 1, int start = 0>
 class A {
     T t[n];
     T junk;
   public:
     A() {
         for (int i = 0; i < n; i++)
             t[i] = i + start;
         if (n > 0) junk = t[0];
     }
     T& operator[](int i) {
         cout << "step1";
         return i < 0 || i >= n ? junk : t[i];
     }
     T operator[](int i) const {
         cout << "step2";
         return i < 0 || i >= n ? junk : t[i] + 1; 
     }
     void display(int i) const {
         cout << setw(2) << operator[](i);
     }
 };

 int main () {
     A<int, 6> a;
     A<char, 4, 'F'> b;

     a[2] = 8;
     b[3] = 'A';
     for (int i = 0; i < 5; i++) {
         a.display(i);
         cout << '|';
         b.display(i);
         cout << endl;
     }

     return 0;
  } 
