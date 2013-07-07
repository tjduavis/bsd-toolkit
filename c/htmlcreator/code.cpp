// BTP200 Presentation
// Simple XHTML Creator
// Ryan Minkyu Wang
// hxtmlcreator.cpp

#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
using namespace std;
#define TESTMODE 1

// CLASS-STRING BEGINS HERE //////////////////////////////////////////////////
class String {
	char*   sTring;
	int     indent;
	int     newlin;
public:
	String();             
	~String();                     
	void    init();
	void    init(const String& recstr);                 
	bool    save(FILE *fp) const; 
	void    assi(char* recstr, int recind, int tagend);                         
	void    disp();
	String& operator=(const String& rhside);
};

String& String::operator=(const String& rhside) {
	if (this != &rhside)
		init(rhside);
	return *this;
}
void String::init(const String& recstr) {
	int     length = 0;
	while (recstr.sTring[length++] != '\0');
	if (sTring) delete[] sTring;
	sTring = new char[length + 1];
	for (int no = 0; no < length; no++)
		sTring[no] = recstr.sTring[no];
	sTring[length] = '\0';
	indent = recstr.indent;
	newlin = recstr.newlin;
}
String::String() {init();}
String::~String() {if (sTring) delete[] sTring;}
void String::disp() {
	for (int no = 0; no < indent; no ++) cout << ' ';
	cout << sTring;
	if (newlin != 0) cout << endl;
}
void String::init() {
	sTring = NULL;
	indent = 0;
	newlin = 0;
}
bool String::save(FILE *fp) const {
	bool    rvalue = true;
	int     stored = 0;
	int     str_no = 0;
	for (int no = 0; no < indent; no++) fprintf(fp, " "); 
	while (sTring[str_no] != '\0') fprintf(fp, "%c", sTring[str_no++]);
	if (newlin != 0) fprintf(fp, "\n");
	return rvalue;
}
void String::assi(char* recstr, int recind, int tagend) {
	int     nochar = 0;
	newlin = tagend;
	indent = recind;
	while (recstr[nochar] != '\0') nochar++;
	if (sTring) delete[] sTring;
	sTring = new char[nochar + 1];
	for (int no = 0; no < nochar; no++) sTring[no] = recstr[no];
	sTring[nochar] = '\0';
}
// CLASS-STRING ENDS HERE ////////////////////////////////////////////////////

// CLASS-WIZARD BEGINS HERE //////////////////////////////////////////////////
class Wizard {
public:
	String* bf_subs;
	String* ch_subs;
	String* af_subs;
	int     numb_bf;
	int     numb_ch;
	int     numb_af;
	Wizard();                  
	~Wizard();                         
	void    ASSI(char* recstr, int recint, int tagend);
	void    init();                    
	void    save(FILE *fp) const;        
	void    load(char* f_name);           
	void    disp();    
	void    edit(const String* recstr, int rec_NO);                  

};
void Wizard::edit(const String* recstr, int rec_NO) {
	if (ch_subs) delete[] ch_subs;
	ch_subs = new String[rec_NO];
	for (int WASAGA = 0; WASAGA < rec_NO; WASAGA++)
		ch_subs[WASAGA] = recstr[WASAGA];
	numb_ch = rec_NO;
}
void Wizard::ASSI(char* recstr, int recint, int tagend) {
	ch_subs[numb_ch].assi(recstr, recint, tagend);
	numb_ch ++;
}
Wizard::Wizard() {init();}
Wizard::~Wizard() {
	if (bf_subs) delete[] bf_subs;
	if (ch_subs) delete[] ch_subs;
	if (af_subs) delete[] af_subs;
}
void Wizard::disp() {
	for (int no = 0; no < numb_bf; no ++) {bf_subs[no].disp();}
	for (int no = 0; no < numb_ch; no ++) {ch_subs[no].disp();}
	for (int no = 0; no < numb_af; no ++) {af_subs[no].disp();}
}
void Wizard::init() {
	bf_subs = NULL;
	ch_subs = NULL;
	af_subs = NULL;
	numb_bf = 0;
	numb_ch = 0;
	numb_af = 0;
}
void Wizard::save(FILE *fp) const {
	if (bf_subs) {
		for (int no = 0; no < numb_bf; no++) {
			bf_subs[no].save(fp); 
			if (TESTMODE) cout << ".";
		}
	}
	if (ch_subs) {
		for (int no = 0; no < numb_ch; no++) {
			ch_subs[no].save(fp); 
			if (TESTMODE) cout << ".";
		}
	}
	if (af_subs) {
		for (int no = 0; no < numb_af; no++) {
			af_subs[no].save(fp);
			if (TESTMODE) cout << ".";
		}
	}
	cout << endl << "[SAVE COMPLETE]" << endl;
}
void Wizard::load(char* f_name) {
	FILE    *fp = NULL;
	int     read_ki = 0;  
	int     read_in = 0;    
	int     read_nl = 0;    
	char    read_st[201];   
	int     read_ch = 0;
	int     read_bf = 0;
	int     read_af = 0;
	bool    rvalue = true;
	if ((fp = fopen(f_name, "r")) != NULL) {
		numb_bf = 0;
		numb_af = 0;
		do {
			fscanf(fp, "|%d|%d|%d|%[^\n]\n", &read_ki, &read_in, &read_nl, read_st);
			if (read_ki == 1) read_bf++;
			if (read_ki == 2) read_af++;
		} while (!feof(fp));
		rewind(fp);
		if (bf_subs) delete[] bf_subs;
		if (af_subs) delete[] af_subs;
		numb_bf = read_bf;
		numb_af = read_af;
		bf_subs = new String[numb_bf];
		af_subs = new String[numb_af];
		read_bf = 0;
		read_af = 0;
		do {
			read_ch = fscanf(fp, "|%d|%d|%d|%[^\n]\n", &read_ki, &read_in, &read_nl, read_st);
			if (read_ki == 1) bf_subs[read_bf++].assi(read_st, read_in, read_nl);
			if (read_ki == 2) af_subs[read_af++].assi(read_st, read_in, read_nl);
		} while (!feof(fp));
		fclose(fp);
	} else
		cout << "ERROR: CANNOT READ FILE" << endl;
}
// CLASS-WIZARD ENDS HERE ////////////////////////////////////////////////////

// CLASS-HEADER BEGINS HERE //////////////////////////////////////////////////
class Header:public Wizard {
public:
	void conf();
};
void Header::conf() {
	char    sinput[101];
	bool    stop_c = false;
	bool    stop_d = false;
	int     getchr = 0;
	int     no_chr = 0;
	while (!stop_c) {
		stop_d = false;
		while (!stop_d) {
			no_chr = 0;
			cout << "           Web-Page Title       : ";
			while((getchr = getchar()) != '\n' && getchr != EOF) {
				if (no_chr < 101)
					sinput[no_chr++] = (char) getchr;
			}
			sinput[no_chr] = '\0';
			if (strlen(sinput) > 0) stop_d = true;
		}
		if (ch_subs) delete[] ch_subs;
		ch_subs = new String[1];
		Wizard::ASSI(sinput, 0, 0);
		stop_d = false;
		while (!stop_d) { 
			cout << "           Confirm? (Y,N)       : ";
			cin >> sinput;
			cin.clear();
			cin.ignore(2000, '\n');
			if (sinput[0] == 'Y' || sinput[0] == 'y' ||
			    sinput[0] == 'N' || sinput[0] == 'n') {
				stop_d = true;
				if (sinput[0] == 'Y' || sinput[0] == 'y') stop_c = true;
			} 
		}                                        
	}
}
// CLASS-HEADER ENDS HERE ////////////////////////////////////////////////////

// CLASS-MENU (PART-A) BEGINS HERE ///////////////////////////////////////////
class Menu_A:public Wizard {
	int themeN;
public:
	Menu_A();
	void conf();
	void sett();
};
Menu_A::Menu_A() {themeN = 0;}
void Menu_A::sett() {
	bool stop_a = false;
	cout << "           Menu Bar Selection          " << endl;
	cout << "           1: Gray                     " << endl;
	cout << "           2: Black                    " << endl;
	stop_a = false;
	while (!stop_a) {                             
		cout << "           Your Selection: ";
		cin >> themeN;
		cin.clear();
		cin.ignore(2000, '\n');
		if (themeN == 1 || themeN == 2) stop_a = true;
	}
}
void Menu_A::conf() {
	char    inputa[101];
	char    inputb[101];
	int     nomenu = 0;
	int     nocurr = 2;
	int     no_chr = 0;
	int     getchr = 0;
	bool stop_a = false;
	bool stop_b = false;
	while (!stop_a) {
		stop_b = false;
		while (!stop_b) {
			cout << "           Number of Categories (3 to 5) : ";
			cin >> nomenu;
			cin.clear();
			cin.ignore(2000, '\n');
			if (nomenu > 2 && nomenu < 6) stop_b = true;
		}
		if (ch_subs) delete[] ch_subs;
		ch_subs = new String[60];
		stop_b = false;
		while (!stop_b) {
			cout << "           URL for the Parent Page       : ";
			cin >> inputa;
			cin.clear();
			cin.ignore(2000, '\n');
			if (strlen(inputa) <= 100) stop_b = true;
		}
		Wizard::ASSI("<td width=\"120\" height=\"25\" background=\"./pictures/", 20, 0);
		if (themeN == 0) Wizard::ASSI("menu_a_a.gif\">", 0, 0);
		else Wizard::ASSI("menu_b_a.gif\">", 0, 0);
		Wizard::ASSI("<a href=\"", 0, 0);
		Wizard::ASSI(inputa, 0, 0);
		Wizard::ASSI("\">", 0, 0);
		Wizard::ASSI("<span style=\"color:white;\">", 0, 0);
		Wizard::ASSI("Back to Main", 0, 0);
		Wizard::ASSI("</span>", 0, 0);
		Wizard::ASSI("</a>", 0, 0);
		Wizard::ASSI("</td>", 0, 1);
		stop_b = false;
		while (!stop_b) {
			no_chr = 0;
			cout << "           Category (1/" << nomenu << ") - Link Name    : ";
			while((getchr = getchar()) != '\n' && getchr != EOF) {
				if (no_chr < 21)
					inputa[no_chr++] = (char) getchr;
			}
			inputa[no_chr] = '\0';
			if (strlen(inputa) > 0) stop_b = true;
			else for (int no = 0; no < 101; no++) {inputa[no] = '\0';}
		}
		stop_b = false;
		while (!stop_b) {
			cout << "                          - Link URL     : ";
			cin >> inputb;
			cin.clear();
			cin.ignore(2000, '\n');
			if (strlen(inputa) <= 100) stop_b = true;
		}
		Wizard::ASSI("<td width=\"120\" height=\"25\" background=\"./pictures/", 20, 0);
		if (themeN == 0) Wizard::ASSI("menu_a_b.gif\">", 0, 0);
		else Wizard::ASSI("menu_b_b.gif\">", 0, 0);
		Wizard::ASSI("<a href=\"", 0, 0);
		Wizard::ASSI(inputb, 0, 0);
		Wizard::ASSI("\">", 0, 0);
		Wizard::ASSI("<span style=\"color:white;\">", 0, 0);
		Wizard::ASSI(inputa, 0, 0);
		Wizard::ASSI("</span>", 0, 0);
		Wizard::ASSI("</a>", 0, 0);
		Wizard::ASSI("</td>", 0, 1);
		for (int no = 0; no < 101; no++) {inputa[no] = '\0';}
		for (nocurr = 2; nocurr < 5; nocurr++) {
			if (nocurr <= nomenu) {
				stop_b = false;
				while (!stop_b) {
					no_chr = 0;
					cout << "           Category (";
					cout << nocurr << "/" << nomenu << ") - Link Name    : ";
					while((getchr = getchar()) != '\n' && getchr != EOF) {
						if (no_chr < 21)
							inputa[no_chr++] = (char) getchr;
					}
					inputa[no_chr] = '\0';
					if (strlen(inputa) > 0) stop_b = true;
					else for (int no = 0; no < 101; no++) {inputa[no] = '\0';}
				}
				stop_b = false;
				while (!stop_b) {
					cout << "                          - Link URL     : ";
					cin >> inputb;
					cin.clear();
					cin.ignore(2000, '\n');
					if (strlen(inputa) <= 100) stop_b = true;
				}
				Wizard::ASSI("<td width=\"120\" height=\"25\" background=\"./pictures/", 20, 0);
				if (themeN == 0) Wizard::ASSI("menu_a_c.gif\">", 0, 0);
				else Wizard::ASSI("menu_b_c.gif\">", 0, 0);
				Wizard::ASSI("<a href=\"", 0, 0);
				Wizard::ASSI(inputb, 0, 0);
				Wizard::ASSI("\">", 0, 0);
				Wizard::ASSI("<span style=\"color:white;\">", 0, 0);
				Wizard::ASSI(inputa, 0, 0);
				Wizard::ASSI("</span>", 0, 0);
				Wizard::ASSI("</a>", 0, 0);
				Wizard::ASSI("</td>", 0, 1);
				for (int no = 0; no < 101; no++) {inputa[no] = '\0';}
			} else {
				Wizard::ASSI("<td width=\"120\" height=\"25\" background=\"./pictures/", 20, 0);
				if (themeN == 0) Wizard::ASSI("menu_a_b.gif\">", 0, 0);
				else Wizard::ASSI("menu_b_b.gif\">", 0, 0);
				for (int no = 2; no < 9; no++) Wizard::ASSI('\0', 0, 0);
				Wizard::ASSI("</td>", 0, 1);
			}
		}
		if (nocurr == nomenu) {
			stop_b = false;
			while (!stop_b) {
				no_chr = 0;
				cout << "           Category (";
				cout << nocurr << "/" << nomenu << ") - Link Name    : ";
				while((getchr = getchar()) != '\n' && getchr != EOF) {
					if (no_chr < 21)
						inputa[no_chr++] = (char) getchr;
				}
				inputa[no_chr] = '\0';
				if (strlen(inputa) > 0) stop_b = true;
				else for (int no = 0; no < 101; no++) {inputa[no] = '\0';}
			}
			stop_b = false;
			while (!stop_b) {
				cout << "                          - Link URL     : ";
				cin >> inputb;
				cin.clear();
				cin.ignore(2000, '\n');
				if (strlen(inputa) <= 100) stop_b = true;
			}
			Wizard::ASSI("<td width=\"120\" height=\"25\" background=\"./pictures/", 20, 0);
			if (themeN == 0) Wizard::ASSI("menu_a_c.gif\">", 0, 0);
			else Wizard::ASSI("menu_b_c.gif\">", 0, 0);
			Wizard::ASSI("<a href=\"", 0, 0);
			Wizard::ASSI(inputb, 0, 0);
			Wizard::ASSI("\">", 0, 0);
			Wizard::ASSI("<span style=\"color:white;\">", 0, 0);
			Wizard::ASSI(inputa, 0, 0);
			Wizard::ASSI("</span>", 0, 0);
			Wizard::ASSI("</a>", 0, 0);
			Wizard::ASSI("</td>", 0, 0);
			for (int no = 0; no < 101; no++) {inputa[no] = '\0';}
		} else {
			Wizard::ASSI("<td width=\"120\" height=\"25\" background=\"./pictures/", 20, 0);
			if (themeN == 0) Wizard::ASSI("menu_a_b.gif\">", 0, 0);
			else Wizard::ASSI("menu_b_b.gif\">", 0, 0);
			for (int no = 2; no < 9; no++) Wizard::ASSI('\0', 0, 0);
			Wizard::ASSI("</td>", 0, 1);
		}
		stop_b = false;
		while (!stop_b) {
			cout << "           Confirm? (Y,N)                : ";
			cin >> inputa;
			cin.clear();
			cin.ignore(2000, '\n');
			if (inputa[0] == 'y' || inputa[0] == 'Y' || 
			    inputa[0] == 'n' || inputa[0] == 'N') {
				stop_b = true;
				if (inputa[0] == 'Y' || inputa[0] == 'y') stop_a = true;
			}
		}
	}
}
// CLASS-MENU (PART-A) ENDS HERE /////////////////////////////////////////////

// CLASS-MENU (PART-B) BEGINS HERE ///////////////////////////////////////////
class Menu_B:public Wizard {
public:
	void conf();
	void none();
};
void Menu_B::none() {
	if (ch_subs) delete[] ch_subs;
	ch_subs = new String[4];
	Wizard::ASSI("<tr>", 24, 1);
	Wizard::ASSI("<td height=\"180\">", 26, 0);
	Wizard::ASSI("</td>", 0, 1);
	Wizard::ASSI("</tr>", 26, 1);
}
void Menu_B::conf() {
	char    inputa[101];
	char    inputb[101];
	int     nomenu = 0;
	int     nocurr = 0;
	int     getchr = 0;
	int     no_chr = 0;
	bool stop_a = false;
	bool stop_b = false;
	while (!stop_a) {
		stop_b = false;
		while (!stop_b) {
			cout << "           Number of Categories (upto 6) : ";
			cin >> nomenu;
			cin.clear();
			cin.ignore(2000, '\n');
			if (nomenu > 0 && nomenu < 7) stop_b = true;
		}
		if (ch_subs) delete[] ch_subs;
		ch_subs = new String[78];
		for (nocurr = 0; nocurr < 6; nocurr++) {
			if (nocurr < nomenu) {
				stop_b = false;
				while (!stop_b) {
					cout << "           Category (";
					cout << nocurr + 1 << "/" << nomenu << ") - Link Name    : ";
					no_chr = 0;
					while((getchr = getchar()) != '\n' && getchr != EOF) {
						if (no_chr < 31)
							inputa[no_chr++] = (char) getchr;
					}
					if (no_chr == 31) while (getchar() != '\n');
					inputa[no_chr] = '\0';
					if (strlen(inputa) > 0) stop_b = true;
				}
				stop_b = false;
				while (!stop_b) {
					cout << "                          - Link URL     : ";
					cin >> inputb;
					cin.clear();
					cin.ignore(2000, '\n');
					if (strlen(inputa) <= 100) stop_b = true;
				}
				stop_b = false;
				Wizard::ASSI("<tr ", 24, 0);
				Wizard::ASSI("valign=\"middle\">", 0, 1);
				Wizard::ASSI("<td height=\"25\">", 26, 1);
				Wizard::ASSI("<a href=\"", 28, 0);
				Wizard::ASSI(inputb, 0, 0);
				Wizard::ASSI("\">", 0, 1);
				Wizard::ASSI("<span style=\"color:white;\">", 30, 0);
				Wizard::ASSI(inputa, 0, 0);
				Wizard::ASSI("</span>", 0, 1);
				Wizard::ASSI("</a>", 28, 1);
				Wizard::ASSI("</td>", 26, 1);
				Wizard::ASSI("</tr>", 24, 1);
				Wizard::ASSI("<tr><td height=\"5\"></td></tr>", 24, 1);
			} else {
				Wizard::ASSI("<tr ", 24, 0);
				Wizard::ASSI("valign=\"middle\">", 0, 1);
				Wizard::ASSI("<td height=\"25\"></td>", 26, 1);
				for (int no = 3; no < 11; no++) Wizard::ASSI('\0', 0, 0);
				Wizard::ASSI("</tr>", 24, 1);
				Wizard::ASSI("<tr><td height=\"5\"></td></tr>", 24, 1);
			}
		}
		stop_b = false;
		while (!stop_b) {
			cout << "           Confirm? (Y,N)                : ";
			cin >> inputa;
			cin.clear();
			cin.ignore(2000, '\n');
			if (inputa[0] == 'y' || inputa[0] == 'Y' ||
			    inputa[0] == 'n' || inputa[0] == 'N') {
				stop_b = true;
				if (inputa[0] == 'Y' || inputa[0] == 'y') stop_a = true;
			}
		}
	}
}
// CLASS-MENU (PART-B) ENDS HERE /////////////////////////////////////////////

// CLASS-MAIN (PART-A) BEGINS HERE ///////////////////////////////////////////
class Main_A:public Wizard {
	int bg_sub;
public:
	Main_A();
	void conf();
	void setp(int recsub);
};
Main_A::Main_A() {
	bg_sub = 0;
}
void Main_A::setp(int recsub) {
	bg_sub = recsub;
}
void Main_A::conf() {
	bool    stop_a = false;
	bool    stop_b = false;
	int     select = 0;
	char    inputa = NULL;
	while (!stop_a) {
		cout << "           1: RM-type 1 - One with the Ring        " << endl;
		cout << "           2: RM-type 2 - One with the Dinner Table" << endl;
		cout << "           3: TJ-type 1 - One with the Spider Man  " << endl;
		cout << "           4: TJ-type 2 - One with the Something   " << endl;
		stop_b = false;
		while (!stop_b) {
			cout << "           Your Selection : ";
			cin >> select;
			cin.clear();
			cin.ignore(2000, '\n');
			if (select > 0 && select < 5) stop_b = true;
		}
		stop_b = false;
		while (!stop_b) {
			cout << "           Confirm? (Y,N) : ";
			cin >> inputa;
			cin.clear();
			cin.ignore(2000, '\n');
			if (inputa == 'y' || inputa == 'Y' ||
			    inputa == 'n' || inputa == 'N') {
				stop_b = true;
				if (inputa == 'Y' || inputa == 'y') stop_a = true;
			}
		}
		if (ch_subs) delete[] ch_subs;
			ch_subs = new String[1];
		if (select == 1 && bg_sub == 0) {
			Wizard::ASSI("<td background=\"./pictures/bg_a_a.gif\">", 14, 1);
		} else if (select == 2 && bg_sub == 0) {
			Wizard::ASSI("<td background=\"./pictures/bg_b_a.gif\">", 14, 1);
		} else if (select == 3 && bg_sub == 0) {
			Wizard::ASSI("<td background=\"./pictures/bg_c_a.gif\">", 14, 1);
		} else if (select == 4 && bg_sub == 0) {
			Wizard::ASSI("<td background=\"./pictures/bg_d_a.gif\">", 14, 1);
		} else if (select == 1 && bg_sub == 1) {
			Wizard::ASSI("<td background=\"./pictures/bg_a_b.gif\">", 14, 1);
		} else if (select == 2 && bg_sub == 1) {
			Wizard::ASSI("<td background=\"./pictures/bg_b_b.gif\">", 14, 1);
		} else if (select == 3 && bg_sub == 1) {
			Wizard::ASSI("<td background=\"./pictures/bg_c_b.gif\">", 14, 1);
		} else {
			Wizard::ASSI("<td background=\"./pictures/bg_d_b.gif\">", 14, 1);
		}
	}
}
// CLASS-MAIN (PART-A) ENDS HERE /////////////////////////////////////////////

// CLASS-MAIN (PART-B) BEGINS HERE ///////////////////////////////////////////
class Main_B:public Wizard {
	int bg_sub;
public:
	Main_B();
	void conf();
	void setp(int recsub);
};
Main_B::Main_B() {bg_sub = 0;}
void Main_B::setp(int recsub) {bg_sub = recsub;}
void Main_B::conf() {
	int     lineno = 0;
	String* temp_s = NULL;
	String* progss = NULL;
	bool    stop_a = false;
	bool    stop_b = false;
	bool    stop_c = false;
	int     select = 0;
	int     no_chr = 0;
	int     getchr = 0;
	char    inputH[401];
	while (!stop_a) {
		cout << "           1: I Want to Write Using Tags  " << endl;
		cout << "           2: I Want to Use <IFRAME> Tag  " << endl;
		cout << "           3: Leave It Blank              " << endl;
		stop_b = false;
		while (!stop_b) {
			cout << "           Your Selection : ";
			cin >> select;
			cin.clear();
			cin.ignore(2000, '\n');
			if (select > 0 && select < 5) stop_b = true;
		}
		stop_b = false;
		if (select == 1) {
			cout << "_________________________________________" << endl << endl;
			cout << "[!] Writing Mode Started. Enter 0 to Quit." << endl;
			cout << "[!] Do Not Exceed 400 Characters per Line" << endl;
			cout << "_________________________________________" << endl << endl;
			stop_b = false;
			lineno = 0;
			while (!stop_b) {
				stop_c = false;
				while (!stop_c) {
					cout << "LINE " << setw(3) << lineno + 1 << " : ";
					no_chr = 0;
					while((getchr = getchar()) != '\n' && getchr != EOF) {
						if (no_chr < 401)
							inputH[no_chr++] = (char) getchr;
					}
					if (strlen(inputH) > 0) stop_c = true;
					inputH[no_chr] = '\0';
					lineno ++;
				}
				if (inputH[0] != '0') {
					if (lineno != 0) {
						if (temp_s) delete[] temp_s;
						temp_s = new String[lineno];
						for (int no = 0; no < lineno; no++)
							temp_s[no] = progss[no];
					}
					if (progss) delete[] progss;
					progss = new String[lineno + 1];
					if (lineno != 0)
						for (int no = 0; no < lineno; no++)
							progss[no] = temp_s[no];
					progss[lineno].assi(inputH, 0, 1);
				} else {
					cout << "_________________________________________" << endl << endl;
					stop_b = true;
					Wizard::edit(progss, lineno);
				}
			}
		} else if (select == 2) {
			stop_b = false;
			while (!stop_b) {
				cout << "           Frame Height   : ";
				cin >> inputH;
				cin.clear();
				cin.ignore(2000, '\n');
				if (strlen(inputH) < 100 && strlen(inputH) > 0) stop_b = true;
			}
			if (ch_subs) delete[] ch_subs;
			ch_subs = new String[6];
			Wizard::ASSI("<iframe width=\"625\" frameborder=\"0\" height=\"", 24, 0);
			Wizard::ASSI(inputH, 0, 0);
			stop_b = false;
			while (!stop_b) {
				cout << "           URL for Main   : ";
				cin >> inputH;
				cin.clear();
				cin.ignore(2000, '\n');
				if (strlen(inputH) < 100 && strlen(inputH) > 0) stop_b = true;
			}
			Wizard::ASSI("\" src=\"", 0, 0);
			Wizard::ASSI(inputH, 0, 0);
			Wizard::ASSI("\" scrolling=\"", 0, 0);
			stop_b = false;
			while (!stop_b) {
				cout << "           Scrolling (Y,N): ";
				cin >> inputH;
				cin.clear();
				cin.ignore(2000, '\n');
				if (inputH[0] == 'y' || inputH[0] == 'Y' ||
				    inputH[0] == 'n' || inputH[0] == 'N') {
					stop_b = true;
					if (inputH[0] == 'Y' || inputH[0] == 'y') {
						Wizard::ASSI("yes\"></iframe>", 0, 1);
					} else {
						Wizard::ASSI("no\"></iframe>", 0, 1);
					}
				}
			}
		} else {
			if (ch_subs) delete[] ch_subs;
			ch_subs = new String[1];
			Wizard::ASSI("\0", 0, 0);
		}
		stop_b = false;
		while (!stop_b) {
			cout << "           Confirm? (Y,N) : ";
			cin >> inputH;
			cin.clear();
			cin.ignore(2000, '\n');
			if (inputH[0] == 'y' || inputH[0] == 'Y' ||
			    inputH[0] == 'n' || inputH[0] == 'N') {
				stop_b = true;
				if (inputH[0] == 'Y' || inputH[0] == 'y') stop_a = true;
			}
		}
	}
}
// CLASS-MAIN (PART-B) ENDS HERE /////////////////////////////////////////////

// CLASS-MAIN (PART-C) BEGINS HERE ///////////////////////////////////////////
class Main_C:public Wizard {
public:
	void    desc(char* recdes, char* rectit);
};
void Main_C::desc(char* recdes, char* rectit) {
	if (ch_subs) delete[] ch_subs;
	ch_subs = new String[6];
	Wizard::ASSI("<span class=\"title\">", 24, 0);
	Wizard::ASSI(rectit, 0, 0);
	Wizard::ASSI("<br /><br /></span>", 0, 1);
	Wizard::ASSI("<span>", 24, 0);
	Wizard::ASSI(recdes, 0, 0);
	Wizard::ASSI("</span>", 0, 1);
}

// CLASS-MAIN (PART-C) ENDS HERE /////////////////////////////////////////////

// CLASS-MAIN (PART-D) BEGINS HERE ///////////////////////////////////////////
class Main_D:public Wizard {
public:
	void conf();
};
void Main_D::conf() {
	bool    stop_a = false;
	bool    stop_b = false;
	int    select = 0;
	char    embadd[101];
	cout << "           Please Select an Emblem Type   " << endl;
	cout << "           1: SenecaRT Default Emblem     " << endl;
	cout << "           2: Seneca College Emblem Type A" << endl;
	cout << "           3: Seneca College Emblem Type B" << endl;
	cout << "           4: Seneca College BSD Emblem   " << endl;
	cout << "           5: Custom Emblem               " << endl;
	while (!stop_a) {
		stop_b = false;
		while (!stop_b) {
			cout << "           Your Choice: ";
			cin >> select;
			cin.clear();
			cin.ignore(2000, '\n');
			if (select > 0 && select < 6) stop_b = true;
		}
		if (select == 1) {
			if (ch_subs) delete[] ch_subs;
			ch_subs = new String[1];
			Wizard::ASSI("./pictures/embl_a.gif", 0, 0);
		} else if (select == 2) {
			if (ch_subs) delete[] ch_subs;
			ch_subs = new String[1];
			Wizard::ASSI("./pictures/embl_b.gif", 0, 0);
		} else if (select == 3) {
			if (ch_subs) delete[] ch_subs;
			ch_subs = new String[1];
			Wizard::ASSI("./pictures/embl_c.gif", 0, 0);
		} else if (select == 4) {
			if (ch_subs) delete[] ch_subs;
			ch_subs = new String[1];
			Wizard::ASSI("./pictures/embl_d.gif", 0, 0);
		} else {
			stop_b = false;
			while (!stop_b) {
				cout << "           Emblem URL : ";
				cin >> embadd;
				cin.clear();
				cin.ignore(2000, '\n');
				if (strlen(embadd) > 0) stop_b = true;
			}
			if (ch_subs) delete[] ch_subs;
			ch_subs = new String[1];
			Wizard::ASSI(embadd, 0, 0);
		}
		stop_b = false;
		while (!stop_b) {
			cout << "           Confirm? (Y,N) : ";
			cin >> embadd;
			cin.clear();
			cin.ignore(2000, '\n');
			if (embadd[0] == 'y' || embadd[0] == 'Y' ||
			    embadd[0] == 'n' || embadd[0] == 'N') {
				stop_b = true;
				if (embadd[0] == 'Y' || embadd[0] == 'y') stop_a = true;
			}
		}
	}        
}
// CLASS-MAIN (PART-D) ENDS HERE /////////////////////////////////////////////

// MAIN BEGINS HERE //////////////////////////////////////////////////////////
int main () {
	FILE    *fp = NULL;
	Header* header = NULL;
	Menu_A* menu_a = NULL;
	Menu_B* menu_b = NULL;
	Main_A* main_a = NULL;
	Main_B* main_b = NULL;
	Main_C* main_c = NULL;
	Main_D* main_d = NULL;
	int     themeS = 0;
	int     pictuS = 0;
	bool    stop_a = false;
	bool    stop_b = false;
	bool    stop_c = false;
	int     inputS = 0;
	int     subcat = 0;
	int     navsel = 0;
	int     getchr = 0;
	int     no_chr = 0;
	char    f_name[101];
	char    p_titl[31];
	char    p_desc[101];
	while (!stop_a) {
		if (header) delete[] header;
		if (menu_a) delete[] menu_a;
		if (menu_b) delete[] menu_b;
		if (main_a) delete[] main_a;
		if (main_b) delete[] main_b;
		if (main_c) delete[] main_c;
		if (main_d) delete[] main_d;
		header = new Header[1];
		menu_a = new Menu_A[1];
		menu_b = new Menu_B[1];
		main_a = new Main_A[1];
		main_b = new Main_B[1];
		main_c = new Main_C[1];
		main_d = new Main_D[1];
		header[0].Wizard::load("header.dat");
		menu_a[0].Wizard::load("menu_a.dat");
		menu_b[0].Wizard::load("menu_b.dat");
		main_a[0].Wizard::load("main_a.dat");
		main_b[0].Wizard::load("main_b.dat");
		main_c[0].Wizard::load("main_c.dat");
		main_d[0].Wizard::load("main_d.dat");
		cout << "_____________________________________" << endl << endl;
		cout << "Welcome to BTP200 HTML Creator (V0.1)" << endl;
		cout << "Created by " << endl;
		cout << "Timothy J. Duavis and Ryan M. Wang   " << endl;
		cout << "_____________________________________" << endl << endl;
		cout << "Step (1/8) Web Page Theme Selection" << endl;
		cout << "           1: SenecaRT With Sub-Categories   " << endl;
		cout << "           2: SenecaRT Without Sub-Categories" << endl;
		stop_b = false;
		while (!stop_b) {
			cout << "           Your Selection : ";
			cin >> subcat;
			cin.clear();
			cin.ignore(2000, '\n');
			if (subcat > 0 && subcat < 3) stop_b = true;
		}
		cout << "Step (2/8) Basic Web Page Information" << endl;
		header[0].conf();
		stop_b = false;
		while (!stop_b) {
			cout << "           Web-Page Topic       : ";
			no_chr = 0;
			while((getchr = getchar()) != '\n' && getchr != EOF) {
				if (no_chr < 31)
					p_titl[no_chr++] = (char) getchr;
			}
			p_titl[no_chr] = '\0';
			if (strlen(p_titl) > 0) stop_b = true;
		}
		stop_b = false;
		while (!stop_b) {
			cout << "           Web-Page Name        : ";
			cin >> f_name;
			cin.clear();
			cin.ignore(2000, '\n');
			if ((fp = fopen(f_name, "w")) != NULL) {
				stop_b = true;
				fclose(fp);
			}
		}
		stop_b = false;
		while (!stop_b) {
			cout << "           Web-Page Description : ";
			no_chr = 0;
			while((getchr = getchar()) != '\n' && getchr != EOF) {
				if (no_chr < 31)
					p_desc[no_chr++] = (char) getchr;
			}
			p_desc[no_chr] = '\0';
			if (strlen(p_desc) > 0) stop_b = true;
		}
		main_c[0].desc(p_desc, p_titl);
		cout << "Step (3/8) Navigation Bar Configuration" << endl;
		menu_a[0].sett();
		menu_a[0].conf();
		cout << "Step (4/8) Picture Selection" << endl;
		main_a[0].conf();
		if (subcat == 1) {
			cout << "Step (5/8) Sub-Category Configuration" << endl;
			menu_b[0].conf();
		} else {
			cout << "Step (5/8) Sub-Category Configuration" << endl;
			cout << "           Skipped." << endl;
			menu_b[0].none();
		}
		main_a[0].setp(subcat);
		cout << "Step (6/8) Emblem Configuration" << endl;
		main_d[0].conf();
		cout << "Step (7/8) Main Page Configuration" << endl;
		main_b[0].conf();
		stop_b = false;
		while (!stop_b) {
			cout << "Step (8/8) Finishing Web Page Configuration        " << endl;
			cout << "           1: Display XHTML Code                   " << endl;
			cout << "           2: Save and Quit                        " << endl;
			cout << "           3: Discard and Go Back to the First Step" << endl;
			cout << "           4: Discard and Quit                     " << endl;
			stop_c = false;
			while (!stop_c) {
				cout << "           Your Selection : ";
				cin >> inputS;
				cin.clear();
				cin.ignore(2000, '\n');
				if (inputS > 0 && inputS < 5) stop_c = true;
			}
			if (inputS == 1) {
				header[0].Wizard::disp();
				main_d[0].Wizard::disp();
				menu_a[0].Wizard::disp();
				main_a[0].Wizard::disp();
				menu_b[0].Wizard::disp();
				main_c[0].Wizard::disp();
				main_b[0].Wizard::disp();
			} else if (inputS == 2) {
				if ((fp = fopen(f_name, "w")) != NULL) {
					if (TESTMODE) cout << "[SAVING HEADER]";
					header[0].Wizard::save(fp);
					if (TESTMODE) cout << "[SAVING MAIN_D]";
					main_d[0].Wizard::save(fp);
					if (TESTMODE) cout << "[SAVING MENU_A]";
					menu_a[0].Wizard::save(fp);
					if (TESTMODE) cout << "[SAVING MAIN_A]";
					main_a[0].Wizard::save(fp);
					if (TESTMODE) cout << "[SAVING MENU_B]";
					menu_b[0].Wizard::save(fp);
					if (TESTMODE) cout << "[SAVING MAIN_C]";
					main_c[0].Wizard::save(fp);
					if (TESTMODE) cout << "[SAVING MAIN_B]";
					main_b[0].Wizard::save(fp);
					fclose(fp);
				} else
					cout << "ERROR: CANNOT SAVE" << endl;
				stop_a = true;
				stop_b = true;
			} else if (inputS == 3) {
				stop_b = true;
			} else {
				stop_a = true;
				stop_b = true;
			}
		}
	}
	cout << endl << "Thank You for Using BTP200 XHTML Creator!" << endl << endl;
	return 0;
}
// MAIN ENDS HERE ////////////////////////////////////////////////////////////
