#ifndef SCREEN_H
#define SCREEN_H
#include <string.h>
class Field;
class Screen{
  Field** fields_;
  int* autodel_;
  int cap_;
  int sz_;
  void grow();
  /*this function returns index of first editable field, -1
    if no fields are editable*/
  int first();
  /*this function returns index of last editable field*/
  int last();
  /*this function returns index of previous editable field
    given index of current editable field*/
  int prev(int curr);
  /*this function returns index of next editable field
    given index of current editable field*/
  int next(int curr);
  /*this function returns index of nearest editable field
    given a FIELD NUMBER, -1 if no fields are editable*/
  int nearest(int curr);
  int endit(int key,int curridx);
public:
  Screen();
  int add(Field* fp, int autodelete=0);
  void draw(int fnum=0) const;
  int edit(int* fpnum=NULL,int clear=0);
  int locate(const Field* fp) const;
  Field* fieldptr(int n) const;
  int numfields() const;
};
class Field{
  static int ins_;
  virtual int edit();
  virtual void draw() const;
  friend Screen;
protected:
  int row_;
  int col_;
  int flen_;
  int slen_;
  int start_;
  int offset_;
  char* str_;
  int editable_;
public:
  Field(int row,int col, int flen,int slen);
  Field(const char* str,int row, int col, int flen,int slen, int offset=0,int start=0);
  virtual int editable() const;
  virtual void* data();
  virtual void set(void* data);
  virtual void clear();
  virtual ~Field();
};
class Button:public Field{
  virtual int edit();
  static int currbid_;
  void* cmd_;
  char* err_;
  int errnum_;
  int term_;
  Screen* scr_;
  int (*task_)(void*,int,Screen*);
  int bid_;
  int cpos_;
public:
  Button(char* btname, void* cmd,char* errmsg,  int row, int col,  int errnum, 
     int terminating, Screen *scr=NULL, int (*task)(void*, int, Screen *)=NULL);
  virtual int editable() const;
  int ButtonID();
  void addScreen(Screen* scr);
  void addtask(int (*task)(void*, int, Screen*));
  virtual void set(void* data);
  virtual void* data();
  virtual void clear();
  virtual ~Button();
};
#endif