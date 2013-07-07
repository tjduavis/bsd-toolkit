#ifndef LEUNG_H
#define LEUNG_H
namespace leung{
/*this struct stores the cursor location for squares*/
  struct Locations{
    int row_;
    int col_;
  };
  void InitLocation(Locations curpos[][6]);
  int isGood(int board[][6],int key,int who,int& row,int &col);
};
#endif