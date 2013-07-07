/*******************************************************************************
 * Assignment 4 Draft Version                                                  *
 * FILE           : Field.h                                                    * 
 * Author         : Timothy Duavis                                             *
 * Last Modified  : December 15, 2005                                          *
 * Description    : An object-oriented wrapper, for Direct Terminal Library    *
 *                  This wrapper will be the foundation for typical data       *
 *                  programs, which contains a Field and Screen.               *
 *                  *This program is powered by Chris' dtio                    *
 * Upgrade(s)     : New derieved fields with usefull characteristics.          *
 * Specs created  : Chris S. - Seneca College                                  * 
 *******************************************************************************/
 
#include <cstdio>
#include <cstring>
#include <new>
using namespace std;
extern "C" {
        #include "dtio.h"
}

#define BOXBORDER 8

// helper function for various Derived Fields.
// validates a field containing strings only have numerical
// attributes. flag 'flPt' differentiates between floating
// point attributes. vs integer attributes.
// 
inline bool numericStr(char* str,bool flPt) {
        bool success = true;
        for (int j = 0; j < strlen(str); j++) {
                switch(str[j]) {
                        case '0':
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                        case '8':
                        case '9':
                        case '-':
                        case ' ':
                                break;
                        case '.':
                                if (flPt)
                                        success = true;
                                else
                                        success = false;
                                break;
                        default:
                                j = strlen(str);
                                success = false;
                        }
                }
        return success;
}

// Field class, represents either a label
// or an editable string.
//
class Field {
        int row;
        int column;
        int width;
        char* str;
        bool toEdit;
        int index;
        
        void initField(const Field& src) {
                initField(src.row,src.column,src.width,src.str);
                index = src.index;
                toEdit = src.toEdit;
        }
        void initField(int rChk,int cChk, int wChk, const char* sChk) {
                int i = 0;
                if (rChk > dtioRows()) row = dtioRows() - 1;
                else if (rChk > 0)     row = rChk;
                else                   row = 0;
                
                if (cChk > dtioColumns())  column = dtioColumns() - 1;
                else if (cChk > 0)         column = cChk;
                else                       column = 0;
        
                if (cChk + wChk > dtioColumns()) 
                        width = dtioColumns() - column;
                else
                        width = wChk;
                str = new char[width+1];
                if (sChk) {
                        for (i = 0; i < width; i++)
                                str[i] = sChk[i];
                        str[i] = '\0';
                } else {
                        str[i] = '\0';
                }
        }               
        public:
        Field() : str(NULL), toEdit(true) { row = column = width = index = 0; }
        Field(const Field& src) {
                initField(src);
        }
        Field(int r, int c, int w, const char* s = NULL, bool e = true) {
                initField(r,c,w,s);
                index = 0;
                toEdit = e;
        }       
        ~Field() { if (str) delete [] str; }
        Field& operator=(const Field& rhs) {
                if (this != &rhs) {
                        if (str) delete [] str;
                        initField(rhs);
                }
                return *this;   
        }
        virtual void display() {
                dtioDisplay(str,row,column,width);
        }
        virtual int edit() {
                int exit = 0;
                dtioCursor(row,index);
                if (toEdit) {
                        exit = dtioEdit(str, row, column, width, &index);
                } else if (str[0] != '\0') {
                        dtioDisplay(str, row, column, width);
                }
                return exit;
        }
        virtual bool editable() const {
                bool editField = false;
                if (toEdit) { editField = true; }
                return editField;
        }
        virtual void* data() { return str; }
        virtual Field* clone() const {
                Field* temp = new Field(row, column, width, str, toEdit);
                return  temp ? temp : NULL;
        }
};

// An uneditable, display-only field, that draws
// a box around other fields.
//
class Box : public Field {
        int rowBox;
        int colBox;
        int widthBox;
        int heightBox;
        char borderBox[BOXBORDER];
        
        public:
        Box(int rowB, int colB, int widthB, int heightB, const char* border = NULL)
        : Field(rowB, colB, widthBox, NULL, false) {
                rowBox = rowB;
                colBox = colB;
                widthBox = widthB;
                heightBox = heightB;
                if (!border || strlen(border) < BOXBORDER)
                        strcpy(borderBox,"+-+|+-+|");
                else
                        strcpy(borderBox,border);
        }
        Field* clone() const {
                Field* temp = new Box(*this);
                return temp ? temp : NULL;
        }
        void display() {
                //left top corner, first character      
                dtioCursor(rowBox,colBox++);
                dtioPutchar(borderBox[0]);
                //top bar, second character
                for (int j = 1; j < widthBox; j++) {
                        dtioPutchar(borderBox[1]);
                        dtioCursor(rowBox,colBox++);
                }
                //right top corner, third character
                dtioPutchar(borderBox[2]);
                dtioCursor(++rowBox,--colBox);
                //right bar, fourth character
                for (int j = 1; j < heightBox; j++) {
                        dtioPutchar(borderBox[3]);
                        dtioCursor(rowBox++,colBox);
                }
                //right bottom corner, fifth character
                dtioPutchar(borderBox[4]);
                dtioCursor(--rowBox,--colBox);
                
                //bottom bar, sixth character
                for (int j = 1; j < widthBox; j++) {
                        dtioPutchar(borderBox[5]);
                        dtioCursor(rowBox,colBox--);
                }
                //left bottom corner, seventh character
                dtioPutchar(borderBox[6]);
                dtioCursor(--rowBox,++colBox);
                //left bar, eighth character
                for (int j = 1; j < heightBox; j++) {
                        dtioPutchar(borderBox[7]);
                        dtioCursor(rowBox--,colBox);
                }
        }
};

// An undeditable field that displays a string,
// representing the title of other fields.
//
class Label : public Field {
        public:
        Label(int rL, int cL, const char* iniD, int lL = 0)
        : Field(rL,cL,lL <= 0 ? strlen(iniD) : lL,iniD,false) { }
        Field* clone() const {
                Field* temp = new Label(*this);
                return  temp ? temp : NULL;
        }
};

// An editable field that displays a string
// and lets the user edit the string.
//
class SField : public Field {
        public:
        SField(int rSF, int cSF, int lSF, const char* iniD = NULL)
        : Field(rSF,cSF,lSF,iniD,true) { }
        virtual Field* clone() const {
                Field* temp = new SField(*this);
                return  temp ? temp : NULL;
        }
};

// A SField, with help facility.
//
class HField : public SField {
        void (*h)(void*); 
        
        public:
        HField(int rHF, int cHF, int lHF, const char* iniD = NULL, void (*iniH)(void*) = NULL )
        : SField(rHF,cHF,lHF,iniD) { h = *iniH; }
        virtual Field* clone() const {
                Field* temp = new HField(*this);
                return temp ? temp : NULL;
        }
        virtual int edit() {
                bool finish = false;
                char* tempStr = NULL;
                int result;

                tempStr = new char[strlen((char *)Field::data())+1];
                strcpy(tempStr,(char *)Field::data());
                
                Field::display();               
                do {
                        result = Field::edit();
                        if (result == ESCAPE) {
                                strcpy((char *)Field::data(),tempStr);
                                finish = true;
                        } else if (h) {
                                if (result == F(1)) {
                                        h(Field::data());
                                        Field::display();
                                } else {
                                        finish = true;
                                        strcpy((char *)Field::data(),tempStr);
                                }
                        } else
                                finish = true;
                                
                } while(!finish);
                if (tempStr) delete [] tempStr;
                                
                return result;
        }
};

// A HField, with validation.
//
class VField : public HField {
        bool (*v)(char*);
        void (*h)(void*);
        
        public:
        VField(int rVF, int cVF, int lVF, const char* iniD = NULL, bool (*iniV)(char*) = NULL, void (*iniH)(void*) = NULL)
        : HField(rVF,cVF,lVF,iniD,iniH) {
                h = *iniH;
                v = *iniV;
        }
        virtual Field* clone() const {
                Field* temp = new VField(*this);
                return  temp ? temp : NULL;
        }
        virtual int edit() {
                bool finish = false;
                char* tempStr = NULL;
                int result;
                
                tempStr = new char[strlen((char *)Field::data())+1];
                strcpy(tempStr,(char *)Field::data());  
                
                Field::display();       
                do {
                        result = Field::edit();
                        if (!v) {
                                finish = true;
                        } else if (result == ESCAPE) {
                                strcpy((char *)Field::data(),tempStr);
                                Field::display();
                                finish = true;
                        } else if (result == F(1) && h) {
                                h(Field::data());
                                Field::display();
                        } else {
                                finish = v((char *)Field::data());
                                Field::display();
                        }
                } while (!finish);
                if (tempStr) delete [] tempStr;
                
                return result;
        }
};

// A VField that accepts integer data.
//
class IVField : public VField {
        int initIVal;
        bool (*v)(int&);
        void (*h)(void*);
        
        protected:
        int *initVL() { return &initIVal; }
        void initVL(int x) { initIVal = x; }
        
        public:
        IVField(int rIVF, int cIVF, int lIVF, int initVL = 0, bool (*iniV)(int&) = NULL, void (*iniH)(void*) = NULL)
        : VField(rIVF,cIVF,lIVF,"                            ",NULL,iniH) {
                initIVal = initVL;
                h = *iniH;
                v = *iniV;
        }               
        virtual Field* clone() const {
                Field* temp = new IVField(*this);
                return  temp ? temp : NULL;
        }
        virtual int edit() {
                char* tempStr = NULL;
                char* checkStr = NULL;
                int result = 0;
                bool finish = false;
                bool nonNumTest = true;

                //copy initial data to temp
                tempStr = new char[strlen((char *)Field::data())+1];
                strcpy(tempStr,(char *)Field::data());
                
                Field::display();       
                do {
                        result = Field::edit();
                        if (result == ESCAPE) {
                                finish = true;
                                strcpy((char *)Field::data(),tempStr);
                                Field::display();
                        }
                        if (result == F(1) && h) {
                                h(Field::data());
                                Field::display();
                        } else {
                                //copy edited data to checkStr
                                if (checkStr) delete [] checkStr;
                                checkStr = new char[strlen((char *)Field::data())+1];
                                strcpy(checkStr,(char *)Field::data());                         

                                //check for non-numeric characters except for '-'
                                nonNumTest = numericStr(checkStr,false);
                                if (v) {
                                        if (nonNumTest) {
                                                sscanf((char *)Field::data(),"%d",&initIVal); //convert string into int datatype
                                                finish = v(initIVal);
                                                Field::display();
                                        }
                                } else {
                                        if (nonNumTest) finish = true;
                                }
                                nonNumTest = true;
                        } 
                } while (!finish);
                if (tempStr) delete [] tempStr;
                if (checkStr) delete [] checkStr;
                return result;
        }
        void operator=(int rhs) {
                initIVal = rhs;
                sprintf((char *)Field::data(),"%d", initIVal);  //load string
        }
        operator int() const {
                return initIVal;
        }
        friend bool numericStr(char* str,bool flPt);
};

// A IVField, that accepts integer data only within
// a specified range.
//
class MMIField : public IVField {
        int minVal;
        int maxVal;
        void (*h)(void*);
        
        public:
        MMIField(int rMMI, int cMMI, int lMMI, int iniMMIVl = 0, int minVl = 0, int maxVl = 0, void (*iniH)(void*) = NULL)
        : IVField(rMMI,cMMI,lMMI,iniMMIVl,NULL,iniH) {
                minVal = minVl;
                maxVal = maxVl;
                h = *iniH;
        }
        int edit() {
                char* tempStr = NULL;
                int result = 0;
                bool finish = false;

                //copy initial data to temp
                tempStr = new char[strlen((char *)Field::data())+1];
                strcpy(tempStr,(char *)Field::data());
                
                Field::display();       
                do {
                        result = Field::edit();
                        if (result == ESCAPE) {
                                finish = true;
                                strcpy((char *)Field::data(),tempStr);
                        } else if(result == F(1) && h) {
                                int temp;
                                h((void *)&temp);
                                sprintf((char *)Field::data(),"%d",temp);
                                IVField::initVL(temp);  
                        } else if (numericStr((char *)Field::data(),false)) {
                                //checks if data is in specified range
                                sscanf((char *)Field::data(),"%d",(int *)IVField::initVL()); //convert string into int datatype
                                if ((int)IVField::initVL() >= minVal || (int)IVField::initVL() <= maxVal) {
                                        finish = true;
                                }
                        }
                } while (!finish);
                if (tempStr) delete [] tempStr;
                return result;
        }
        Field* clone() const {
                Field* temp = new MMIField(*this);
                return  temp ? temp : NULL;
        }
        friend bool numericStr(char* str,bool flPt);
};
                
// A VField that accepts floating point values.
//
class DVField : public VField {
        int decDV;
        double initDVal;
        bool (*v)(double&);
        void (*h)(void*);
        
        public:
        DVField(int rDV, int cDV, int lDV, int dDV = 2, double initDL = 0.0, bool (*iniV)(double&) = NULL, void (*iniH)(void*) = NULL)
        : VField(rDV,cDV,lDV,"                            ",NULL,iniH) {
                decDV = dDV;
                initDVal = initDL;
                h = *iniH;
                v = *iniV;
        }               
        virtual Field* clone() const {
                Field* temp = new DVField(*this);
                return  temp ? temp : NULL;
        }
        virtual int edit() {
                char* tempStr = NULL;
                char* checkStr = NULL;          
                int result = 0;
                bool finish = false;
                bool nonNumTest = true;

                //copy initial data to temp
                tempStr = new char[strlen((char *)Field::data())+1];
                strcpy(tempStr,(char *)Field::data());
                
                Field::display();       
                do {
                        result = Field::edit();
                        if (result == ESCAPE) {
                                finish = true;
                                strcpy((char *)Field::data(),tempStr);
                        }
                        if (result == F(1) && h) {
                                h(Field::data());
                                Field::display();
                        } else {
                                //copy edited data to checkStr
                                if (checkStr) delete [] checkStr;
                                checkStr = new char[strlen((char *)Field::data())+1];
                                strcpy(checkStr,(char *)Field::data());
                                                                
                                //check for non-numeric characters except for '-' and '.'
                                nonNumTest = numericStr(checkStr,true);
                                if (v) {
                                        if (nonNumTest) {
                                                sscanf((char *)Field::data(),"%lf",&initDVal); //convert string into double datatype
                                                finish = v(initDVal);
                                                sprintf((char *)Field::data(),"%lf", initDVal,decDV);
                                                Field::display();
                                        }       
                                } else {
                                        if (nonNumTest) finish = true;
                                }
                                nonNumTest = true; //reset
                        }
                } while (!finish);
                if (tempStr) delete [] tempStr;
                if (checkStr) delete [] checkStr;
                return result;
        }
        void operator=(double rhs) {
                initDVal = rhs;
                sprintf((char *)Field::data(),"%.2lf", initDVal,decDV); //load string
        }
        operator double() const {
                return initDVal;
        }
        friend bool numericStr(char* str,bool flPt);
};
