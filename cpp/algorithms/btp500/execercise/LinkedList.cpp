#include <iostream>
using namespace std;
#include "LinkedList.h"

int main (void) {
    LinkedList<int> list;

    list.insert(1);
    list.insert(2);
    list.append(3);
    list.print();

/*
  T.Insert(10);
  T.Insert(3);
  T.Insert(9);
  T.Insert(12);
  T.Insert(18);
  T.Insert(11);
  T.Insert(7);
  T.Insert(2);
  T.Insert(6);
  T.Insert(8);
  T.Print();
  cout << "************" << endl;
  T.Remove(10);
  T.Print();*/

}
