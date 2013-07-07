 #include <iostream>
 using namespace std;
 #include "Array.h"

 int main ( ) {
    Array<int> x(3);
    for (int i = 0; i < 3; i++)
        x[i] = 9 - i;
    x[-1] = 9;
    sort(x);
    cout << "hello" << x[2] << endl;
    for (int i = 0; i < 6; i++)
        cout << x[i] << endl;

    Array<> y(2);
    y[0] = 1.1;
    y[1] = 2.1;
    for (int i = 0; i < 2; i++)
        cout << y[i] << endl;

    Array<char *> z(3), w(1);
    z[0] = "one";
    z[1] = "two";
    z[2] = "three";
    z[3] = "???";
    for (int i = 0; i < 4; i++)
        cout << z[i] << endl;
    w = z;
    sort(w);
    for (int i = 0; i < 4; i++)
        cout << w[i] << endl;
    return 0;
 }
