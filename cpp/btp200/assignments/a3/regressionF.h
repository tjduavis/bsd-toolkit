// Regression Analysis Calculator - Header File
// Assignment 3
// regressionF.cpp
// BTP200
// Feb 16 2005

#define MAX_DATA_SETS 10
#define MAX_FILENAME 21
#define LOAD      1
#define CHAUV     2
#define ALLGOOD   3
#define DISPLAY   4 
#define ADD       5
#define COMPARE   6 
#define STATS     7
#define REMOVE    8
#define QUIT      0
#define NOPTIONS  9
int menu(void);
double getPosDouble();
int  findFile(const char*, const DataSet* data, int);
void saveDataSets(const DataSet* data, int noDataSets);
void removeDataSet(DataSet* data, int& noDataSets);
void displayDataSet(const DataSet* data, int noDataSets);
void addDataSets(DataSet* data, int& noDataSets);
void setOutliers(DataSet* data, int noDataSets);
void clearOutliers(DataSet* data, int noDataSets);
void compareDataSets(const DataSet* data, int noDataSets);
void loadDataSet(DataSet* data, int& noDataSets);
void displayStats(const DataSet* data, int noDataSets);
