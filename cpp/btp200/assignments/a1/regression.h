// Regression Analysis Calculator - Header File
// Assignment 1
// regression.h
// BTP200
// Jan 20 2005
// Jan 28 2005 - Data => DataSet

#define MAX_DATA_SETS 10
#define MAX_FILENAME 21
#define LOAD      1
#define STATS     2
#define QUIT      0
#define NOPTIONS  3
int menu(void);
double getPosDouble();
int findFile(const char*, const DataSet* data, int);
void displayDataSet(const DataSet* data, int noDataSets);
void displayStats(const DataSet* data, int noDataSets);
void loadDataSet(DataSet* data, int* noDataSets);
