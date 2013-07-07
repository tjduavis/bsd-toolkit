// Regression Analysis Calculator - Header File
// Assignments 2
// outliers.h
// BTP200
// Chris Szalwinski
// Feb 5 2005
// modified (CS) Feb 7 2005 - header comments

#define MAX_DATA_SETS 10
#define MAX_FILENAME 21
#define LOAD      1
#define CHAUV     2
#define ALLGOOD   3
#define DISPLAY   4
#define COMPARE   5
#define STATS     6
#define QUIT      0
#define NOPTIONS  7
int menu(void);
double getPosDouble(const char*);
int findFile(const char*, const DataSet*, int);
void displayDataSet(const DataSet*, int);
void displayStats(const DataSet*, int);
void setOutliers(DataSet*, int);
void clearOutliers(DataSet*, int);
void compareDataSets(const DataSet*, int);
void loadDataSet(DataSet*, int*);