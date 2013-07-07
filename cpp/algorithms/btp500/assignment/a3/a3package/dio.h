#ifndef DIO_H
#define DIO_H
#define AIX 1
#define BORLAND 2
#define PLATFORM BORLAND

#if PLATFORM == AIX
#define LEFT 1860
#define RIGHT 1861
#define HOME 1862
#define END 1960
#define INS 1931
#define DEL 1930
#define BS 8
#define PGUP 1939
#define UP 1859
#define DOWN 1858
#define PGDN 1938
#define ENTER 10
#define TAB 9
#define ESC 27
#define F1 1865
#define F2 1866
#define F3 1867
#define F4 1868
#define F5 1869
#define F6 1870
#define F7 1871
#define F8 1872
#define F9 1873
#define F10 1874
#else 
#define LEFT 1075
#define RIGHT 1077
#define HOME 1071
#define END 1079
#define INS 1082
#define DEL 1083
#define BS 8
#define PGUP 1073
#define UP 1072
#define DOWN 1080
#define PGDN 1081
#define ENTER 13
#define TAB 9
#define ESC 27
#define F1 1059
#define F2 1060
#define F3 1061
#define F4 1062
#define F5 1063
#define F6 1064
#define F7 1065
#define F8 1066
#define F9 1067
#define F10 1068
#endif
void dio_start(void);
void dio_stop(void);
int dio_rows(void);
int dio_cols(void);
void dio_clear(void);
void dio_flush(void);
void dio_cursor(int row,int col);
int dio_getchar(void);
void dio_putchar(int c);
void dio_puts(const char* s);
void dio_draw(const char* s,int row,int col, int width);
int dio_edit(char* str, int slen, int row, int col, int flen, 
                                  int* start, int* offset,int* insert);
void dio_sleep(int time);
#endif