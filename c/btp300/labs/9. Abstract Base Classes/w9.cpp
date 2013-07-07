 #include <iostream>
 using namespace std;
 #include "Polygon.h"

 int main() {
    Polygon rect("Rectangle", 4);
    //system("pause");
    rect(0) = Point(1, 1);
    rect(1) = Point(2, 1);
    rect(2) = Point(2, 4);
    rect(3) = Point(1, 4);

    cout << rect << endl;

    return 0;
 }
