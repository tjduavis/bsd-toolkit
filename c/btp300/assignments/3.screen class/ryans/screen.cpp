#include <cstdio>
#include <cstring>
#include <stdlib.h>
#define	PADDING 100
#define MOD_DEFAULT true
#define TEST 1
using namespace std;

extern "C" {
	#include "dtio.h"
}

class Field {
public:
	int	row;
	int	col;
	int	wth;
	char*	ini;
	bool	mod;

	Field(int rec_row, int rec_col, int rec_wth):row(rec_row),col(rec_col),wth(rec_wth) {
		mod = MOD_DEFAULT;
		if (rec_row < 0) row = 0;
		if (rec_col < 0) col = 0;
		if (rec_wth < 0) wth = 0;
		if (rec_row > dtioRows()) {row = dtioRows() - 1;}
		if (rec_col > dtioColumns()) {col = dtioColumns() - 1;}
		if (rec_col + rec_wth > dtioColumns()) wth = dtioColumns() - col;
		ini = (char*)malloc(sizeof(char) * (wth + PADDING));
		for (int tmp = 0; tmp < (wth + PADDING); tmp++) {ini[tmp] = '\0';}
		for (int tmp = 0; tmp < wth; tmp++) {ini[tmp] = ' ';}
	}
	Field(int rec_row, int rec_col, int rec_wth, bool rec_mod):row(rec_row),col(rec_col),wth(rec_wth),mod(rec_mod) {
		if (rec_row < 0) row = 0;
		if (rec_col < 0) col = 0;
		if (rec_wth < 0) wth = 0;
		if (rec_row > dtioRows()) {row = dtioRows() - 1;}
		if (rec_col > dtioColumns()) {col = dtioColumns() - 1;}
		if(rec_col + rec_wth > dtioColumns()) wth = dtioColumns() - col;
		ini = (char*)malloc(sizeof(char) * (wth + PADDING));
		for (int tmp = 0; tmp < (wth + PADDING); tmp++) {ini[tmp] = '\0';}
		for (int tmp = 0; tmp < wth; tmp++) {ini[tmp] = ' ';}
	}
  	Field(int rec_row, int rec_col, int rec_wth, const char *rec_ini):row(rec_row),col(rec_col),wth(rec_wth),ini(NULL) {
		if (rec_row < 0) row = 0;
		if (rec_col < 0) col = 0;
		if (rec_wth < 0) wth = 0;
		if (rec_row > dtioRows()) {row = dtioRows() - 1;}
		if (rec_col > dtioColumns()) {col = dtioColumns() - 1;}
		mod = MOD_DEFAULT;
		if(rec_col + rec_wth > dtioColumns()) wth = dtioColumns() - col;
		ini = (char*)malloc(sizeof(char) * (strlen(rec_ini) + PADDING));
		for (int tmp = 0; tmp < (strlen(rec_ini) + PADDING); tmp++) {ini[tmp] = '\0';}
		for (int tmp = 0; tmp < wth; tmp++) {ini[tmp] = ' ';}
		for (int tmp = 0; tmp < strlen(rec_ini); tmp++) {ini[tmp] = rec_ini[tmp];} 
		ini[strlen(rec_ini)] = '\0';
	} 	
  	Field(int rec_row, int rec_col, int rec_wth, const char *rec_ini, bool rec_mod):row(rec_row),col(rec_col),wth(rec_wth),ini(NULL),mod(rec_mod) {
		if (rec_row < 0) row = 0;
		if (rec_col < 0) col = 0;
		if (rec_wth < 0) wth = 0;
		if (rec_row > dtioRows()) {row = dtioRows() - 1;}
		if (rec_col > dtioColumns()) {col = dtioColumns() - 1;}
		if (rec_col + rec_wth > dtioColumns()) wth = dtioColumns() - col;
		ini = (char*)malloc(sizeof(char) * (strlen(rec_ini) + PADDING));
		for (int tmp = 0; tmp < (strlen(rec_ini) + PADDING); tmp++) {ini[tmp] = '\0';}
		for (int tmp = 0; tmp < wth; tmp++) {ini[tmp] = ' ';}
		for (int tmp = 0; tmp < strlen(rec_ini); tmp++) {ini[tmp] = rec_ini[tmp];}
	} 		
	Field(const Field& rec_fld) {
		row = rec_fld.row;
		col = rec_fld.col;
		wth = rec_fld.wth;
		mod = rec_fld.mod;
		ini = (char*)malloc(sizeof(char) * (strlen(rec_fld.ini) + PADDING));
		for (int tmp = 0; tmp < (strlen(rec_fld.ini) + PADDING); tmp++) {ini[tmp] = '\0';}
		for (int tmp = 0; tmp < wth; tmp++) {ini[tmp] = ' ';}
		for (int tmp = 0; tmp < strlen(rec_fld.ini); tmp++) {ini[tmp] = rec_fld.ini[tmp];}
	}
	~Field() {free(ini); ini = NULL;}
	Field&	operator=(const Field& rec_fld) {
		if (&rec_fld != this) {
			row = rec_fld.row;
			col = rec_fld.col;
			wth = rec_fld.wth;
			mod = rec_fld.mod;
			ini = (char*)malloc(sizeof(char) * (strlen(rec_fld.ini) + PADDING));
			for (int tmp = 0; tmp < (strlen(rec_fld.ini) + PADDING); tmp++) {ini[tmp] = '\0';}
		 	for (int tmp = 0; tmp < strlen(rec_fld.ini); tmp++) {ini[tmp] = rec_fld.ini[tmp];} 
			ini[strlen(rec_fld.ini)] = '\0';
		}
		return *this;
	} 
	Field* 	clone(void) {
		Field 	*rtn_fld = (Field*)malloc(sizeof(Field));
		*rtn_fld = *this;
		return rtn_fld;
	}
	void*	data(void) {return ini;}
	void	display(void) {dtioDisplay(ini, row, col, wth);}
	bool	editable(void) {return mod;}
	int	edit(void) {
		bool 	keepgetting = true;
		int	return_value = 0;
		if (mod) {
			while (keepgetting) {
				return_value = dtioEdit(ini, row, col, wth, 0);
				switch (return_value) {
					case 	UP:
						keepgetting = false;
						break;
					case 	DOWN:	
						keepgetting = false;
						break;
					case 	TAB:
						keepgetting = false;
						break;
					case 	ENTER:
						keepgetting = false;
						break;
					case 	F(1):
						keepgetting = false;
						break;
					default:
						break;
				}
			}
		}
		return return_value;
	}				
};

class Node {
public:
	Field _data;
	Node *_next;
	Node(Field fld, Node* nod):_data(fld),_next(nod){;}
	inline 	Node* 	next(void) 	const {return _next;}
	inline	Field	data(void)	const {return _data;}
	inline	Field*	dataadd(void)	{return &_data;}
	void	set(Node *received) {_next = received;}
};

class Screen {
public:
	int	num;
	Node 	*fst;
	Node 	*lst;
	Screen(void) {
		num = 0;
		fst = NULL;
		lst = NULL;
	}				
	Screen(const Screen& rec_scr) {
		Node *pnt = rec_scr.fst;
		fst = NULL;
		lst = NULL;
		while (pnt) {
			Node *tmp = new Node(*pnt->data().clone(), NULL);
			if (fst) lst->set(tmp);
			else fst = tmp;
			lst = tmp;
			pnt = pnt->next();
		}
	}	
	~Screen(void) {
		Node *pnt = fst;
		while (pnt) {
			fst = fst->next();
			delete(pnt);
			pnt = fst;
		}
	}
	void	operator=(const Screen& rec_scr) {
		if (this != &rec_scr) {
			Node *pnt = rec_scr.fst;
			fst = NULL;
			lst = NULL;
			while (pnt) {
				Node *tmp = new Node(*pnt->data().clone(), NULL);
				if (fst) lst->set(tmp);
				else fst = tmp;
				lst = tmp;
				pnt = pnt->next();
			}
		}
	}
	int	add(int rec_row, int rec_col, int rec_wth) {
		Field *tmp = new Field(rec_row, rec_col, rec_wth, "", true);
		Node *pnt = new Node(*tmp, NULL);
		if (fst) lst->set(pnt);
		else fst = pnt;
		lst = pnt;
		num++;
		return num;
	}
	int	add(int rec_row, int rec_col, int rec_wth, const char *rec_ini) {
		Field *tmp = new Field(rec_row, rec_col, rec_wth, rec_ini, true);
		Node *pnt = new Node(*tmp, NULL);
		if (fst) lst->set(pnt);
		else fst = pnt;
		lst = pnt;
		num++;
		return num;
	}
	int	add(int rec_row, int rec_col, int rec_wth, bool rec_mod) {
		Field *tmp = new Field(rec_row, rec_col, rec_wth, "", rec_mod);
		Node *pnt = new Node(*tmp, NULL);
		if (fst) lst->set(pnt);
		else fst = pnt;
		lst = pnt;
		num++;
		return num;
	}
	int	add(int rec_row, int rec_col, int rec_wth, const char *rec_ini, bool rec_mod) {
		Field *tmp = new Field(rec_row, rec_col, rec_wth, rec_ini, rec_mod);
		Node *pnt = new Node(*tmp, NULL);
		if (fst) lst->set(pnt);
		else fst = pnt;
		lst = pnt;
		num++;
		return num;
	}
	int	add(const Field &add_fld) {
		Field *tmp = new Field(add_fld.row, add_fld.col, add_fld.wth, add_fld.ini, add_fld.mod);
		Node *pnt = new Node(*tmp, NULL);
		if (fst) lst->set(pnt);
		else fst = pnt;
		lst = pnt;
		num++;
		return num;
	}
	Screen& operator+=(const Field& add_fld) {
		Field *tmp = new Field(add_fld.row, add_fld.col, add_fld.wth, add_fld.ini, add_fld.mod);
		Node *pnt = new Node(*tmp, NULL);
		if (fst) lst->set(pnt);
		else fst = pnt;
		lst = pnt;
		num++;
		return *this;
	}
	void	display(bool clr) {
		if (clr) dtioClear();
		Node* pnt;
		for (pnt = fst; pnt; pnt = pnt->next()) pnt->_data.display();
	}
	void	display() {
		Node* pnt;
		for (pnt = fst; pnt; pnt = pnt->next()) pnt->_data.display();
	}
	Field* 	getField(int fld_num) {
		int	tmp = 0;
		Field* 	fld;
		Node*   pnt;
		pnt = fst;
		for (tmp = 0; tmp < fld_num; tmp++) {pnt = pnt->next();}
		fld = pnt->dataadd();
		return fld;
	}
	int	remove(int del) {
		if (fst && del >= 0) {
			int	counter = 0;
			int 	tmp = 0;
			int	cnt = 0;
			Node	*pre = NULL;
			Node    *ltr = NULL;
			cnt = 1;
			pre = fst;
			while (pre->next()) {
				pre = pre->next();
				cnt++;
			}
			if (del == 0) {
				pre = fst;
				pre = pre->next();
				fst = pre;
			} 
			if (del < cnt - 1) {
				pre = fst;
				for (tmp = 0; tmp < del - 1; tmp++) {pre = pre->next();}
				ltr = pre->next();
				pre->set(ltr->next());			
			} 
			if (del == cnt -1) {
				pre = fst;
				for (tmp = 0; tmp < del - 1; tmp++) {pre = pre->next();}
				pre->set(NULL);
				lst = pre;
			} 
			cnt = 1;
			pre = fst;
			while (pre->next()) {
				pre = pre->next();
				cnt++;
			}
			num = cnt;	
		}
		return num;
	}	

	int	edit(void) {
		Node 	*pnt = NULL;
		Node 	*nxt = NULL;
		bool*	editable = NULL;
		bool 	clearscr = false;
		int 	countfld = 0;
		Node	*currentN = NULL;
		int	rtn_key = 0;
		int 	trk_pos = 0;
		int	trk_nxt = 0;
		bool	proceed = true;
		int	tmp = 0;
		int	targetposition = 0;
		int	secondposition = 0;
		pnt = fst;
		nxt = fst;
		if (fst) {
			countfld = 1;
			currentN = fst;
			proceed = false;
			while (currentN->next()) {
				currentN = currentN->next();
				countfld++;
			}
			editable = new bool[countfld];
			for (tmp = 0; tmp < countfld; tmp++) {editable[tmp] = false;}
			currentN = fst;
			for (tmp = 0; tmp < countfld; tmp++) {
				if (currentN->_data.editable()) editable[tmp] = true;
				currentN = currentN->next();
			}
			if (editable[trk_pos]) {
				currentN = fst;
				for (tmp = 0; tmp < trk_pos; tmp++) {currentN = currentN -> next();}
				proceed = true;
			} else {
				trk_pos = -1;
				for (tmp = 0; tmp < countfld; tmp++) {
					if (editable[tmp] && (trk_pos < 0)) {trk_pos = tmp;}
				}
				currentN = fst;
				for (tmp = 0; tmp < trk_pos; tmp++) {currentN = currentN -> next();}
				proceed = true;
			}			
		} else {
			proceed = false;
		}
		while (proceed) {
			display(clearscr);
			currentN = fst;
			for (tmp = 0; tmp < trk_pos; tmp++) {currentN = currentN -> next();}
			rtn_key = currentN->_data.edit();
			switch (rtn_key) {
				case 	UP:
					trk_nxt = -1;
					for (tmp = 0; tmp < trk_pos; tmp++) {
						if (editable[tmp]) {trk_nxt = tmp;}
					}
					if (trk_nxt < 0) {
						trk_nxt = -1;
						for (tmp = 0; tmp < countfld; tmp++) {
							if (editable[tmp]) {trk_nxt = tmp;}
						} 
					}
					if (trk_nxt < 0) {proceed = false;}
					trk_pos = trk_nxt;
					break;
				case 	DOWN:
					trk_nxt = -1;
					for (tmp = trk_pos + 1; tmp < countfld; tmp++) {
						if (editable[tmp] && (trk_nxt < 0)) {trk_nxt = tmp;}
					}
					if (trk_nxt < 0) {
						trk_nxt = -1;
						for (tmp = 0; tmp <= trk_pos; tmp++) {
							if (editable[tmp] && (trk_nxt < 0)) {trk_nxt = tmp;}
						}
					}
					if (trk_nxt < 0) {proceed = false;}
					trk_pos = trk_nxt;
					break;
				case 	TAB:
					trk_nxt = -1;
					for (tmp = trk_pos + 1; tmp < countfld; tmp++) {
						if (editable[tmp] && (trk_nxt < 0)) {trk_nxt = tmp;}
					}
					if (trk_nxt < 0) {
						trk_nxt = -1;
						for (tmp = 0; tmp <= trk_pos; tmp++) {
							if (editable[tmp] && (trk_nxt < 0)) {trk_nxt = tmp;}
						}
					}
					if (trk_nxt < 0) {proceed = false;}
					trk_pos = trk_nxt;
					break;

				case 	ENTER:
					trk_nxt = -1;
					for (tmp = trk_pos + 1; tmp < countfld; tmp++) {
						if (editable[tmp] && (trk_nxt < 0)) {trk_nxt = tmp;}
					}
					if (trk_nxt < 0) {
						proceed = false;
					}
					trk_pos = trk_nxt;
					break;

				default:
					proceed = false;
					break;
			}
		}
		return rtn_key;
	}


	int	edit(int *pfield) {
		Node 	*pnt = NULL;
		Node 	*nxt = NULL;
		bool*	editable = NULL;
		bool 	clearscr = false;
		int 	countfld = 0;
		Node	*currentN = NULL;
		int	rtn_key = 0;
		int 	trk_pos = pfield[0];
		int	trk_nxt = 0;
		bool	proceed = true;
		int	tmp = 0;
		int	targetposition = 0;
		int	secondposition = 0;
		pnt = fst;
		nxt = fst;
		if (fst) {
			countfld = 1;
			currentN = fst;
			proceed = false;
			while (currentN->next()) {
				currentN = currentN->next();
				countfld++;
			}
			editable = new bool[countfld];
			for (tmp = 0; tmp < countfld; tmp++) {editable[tmp] = false;}
			currentN = fst;
			for (tmp = 0; tmp < countfld; tmp++) {
				if (currentN->_data.editable()) editable[tmp] = true;
				currentN = currentN->next();
			}
			if (editable[trk_pos]) {
				currentN = fst;
				for (tmp = 0; tmp < trk_pos; tmp++) {currentN = currentN -> next();}
				proceed = true;
			} else {
				trk_pos = -1;
				for (tmp = 0; tmp < countfld; tmp++) {
					if (editable[tmp] && (trk_pos < 0)) {trk_pos = tmp;}
				}
				currentN = fst;
				for (tmp = 0; tmp < trk_pos; tmp++) {currentN = currentN -> next();}
				proceed = true;
			}			
		} else {
			proceed = false;
		}
		while (proceed) {
			display(clearscr);
			currentN = fst;
			pfield[0] = trk_pos;
			for (tmp = 0; tmp < trk_pos; tmp++) {currentN = currentN -> next();}
			rtn_key = currentN->_data.edit();
			switch (rtn_key) {
				case 	UP:
					trk_nxt = -1;
					for (tmp = 0; tmp < trk_pos; tmp++) {
						if (editable[tmp]) {trk_nxt = tmp;}
					}
					if (trk_nxt < 0) {
						trk_nxt = -1;
						for (tmp = 0; tmp < countfld; tmp++) {
							if (editable[tmp]) {trk_nxt = tmp;}
						} 
					}
					if (trk_nxt < 0) {proceed = false;}
					trk_pos = trk_nxt;
					break;
				case 	DOWN:
					trk_nxt = -1;
					for (tmp = trk_pos + 1; tmp < countfld; tmp++) {
						if (editable[tmp] && (trk_nxt < 0)) {trk_nxt = tmp;}
					}
					if (trk_nxt < 0) {
						trk_nxt = -1;
						for (tmp = 0; tmp <= trk_pos; tmp++) {
							if (editable[tmp] && (trk_nxt < 0)) {trk_nxt = tmp;}
						}
					}
					if (trk_nxt < 0) {proceed = false;}
					trk_pos = trk_nxt;
					break;
				case 	TAB:
					trk_nxt = -1;
					for (tmp = trk_pos + 1; tmp < countfld; tmp++) {
						if (editable[tmp] && (trk_nxt < 0)) {trk_nxt = tmp;}
					}
					if (trk_nxt < 0) {
						trk_nxt = -1;
						for (tmp = 0; tmp <= trk_pos; tmp++) {
							if (editable[tmp] && (trk_nxt < 0)) {trk_nxt = tmp;}
						}
					}
					if (trk_nxt < 0) {proceed = false;}
					trk_pos = trk_nxt;
					break;

				case 	ENTER:
					trk_nxt = -1;
					for (tmp = trk_pos + 1; tmp < countfld; tmp++) {
						if (editable[tmp] && (trk_nxt < 0)) {trk_nxt = tmp;}
					}
					if (trk_nxt < 0) {
						proceed = false;
					}
					trk_pos = trk_nxt;
					break;

				default:
					proceed = false;
					break;
			}
		}
		return rtn_key;
	}

	int	edit(bool edt_clr) {
		int	numfortest = 0;
		Node 	*pnt = NULL;
		Node 	*nxt = NULL;
		bool*	editable = NULL;
		bool 	clearscr = edt_clr;
		int 	countfld = 0;
		Node	*currentN = NULL;
		int	rtn_key = 0;
		int 	trk_pos = 0;
		int	trk_nxt = 0;
		bool	proceed = true;
		int	tmp = 0;
		int	targetposition = 0;
		int	secondposition = 0;
		pnt = fst;
		nxt = fst;
		if (fst) {
			countfld = 1;
			currentN = fst;
			proceed = false;
			while (currentN->next()) {
				currentN = currentN->next();
				countfld++;
			}
			editable = new bool[countfld];
			for (tmp = 0; tmp < countfld; tmp++) {editable[tmp] = false;}
			currentN = fst;
			for (tmp = 0; tmp < countfld; tmp++) {
				if (currentN->_data.editable()) editable[tmp] = true;
				currentN = currentN->next();
			}
			if (editable[trk_pos]) {
				currentN = fst;
				for (tmp = 0; tmp < trk_pos; tmp++) {currentN = currentN -> next();}
				proceed = true;
			} else {
				trk_pos = -1;
				for (tmp = 0; tmp < countfld; tmp++) {
					if (editable[tmp] && (trk_pos < 0)) {trk_pos = tmp;}
				}
				currentN = fst;
				for (tmp = 0; tmp < trk_pos; tmp++) {currentN = currentN -> next();}
				proceed = true;
			}		
		} else {
			proceed = false;
		}
		while (proceed) {
			display(clearscr);
			currentN = fst;
			for (tmp = 0; tmp < trk_pos; tmp++) {currentN = currentN -> next();}
			rtn_key = currentN->_data.edit();
			switch (rtn_key) {
				case 	UP:
					trk_nxt = -1;
					for (tmp = 0; tmp < trk_pos; tmp++) {
						if (editable[tmp]) {trk_nxt = tmp;}
					}
					if (trk_nxt < 0) {
						trk_nxt = -1;
						for (tmp = 0; tmp < countfld; tmp++) {
							if (editable[tmp]) {trk_nxt = tmp;}
						} 
					}
					if (trk_nxt < 0) {proceed = false;}
					trk_pos = trk_nxt;
					break;
				case 	DOWN:
					trk_nxt = -1;
					for (tmp = trk_pos + 1; tmp <= countfld; tmp++) {
						if (editable[tmp] && (trk_nxt < 0)) {trk_nxt = tmp;}
					}
					if (trk_nxt < 0) {
						trk_nxt = -1;
						for (tmp = 0; tmp < countfld; tmp++) {
							if (editable[tmp] && (trk_nxt < 0)) {trk_nxt = tmp;}
						}
					}
					if (trk_nxt < 0) {proceed = false;}
					trk_pos = trk_nxt;
					break;
				case 	TAB:
					trk_nxt = -1;
					for (tmp = trk_pos + 1; tmp < countfld; tmp++) {
						if (editable[tmp] && (trk_nxt < 0)) {trk_nxt = tmp;}
					}
					if (trk_nxt < 0) {
						trk_nxt = -1;
						for (tmp = 0; tmp < countfld; tmp++) {
							if (editable[tmp] && (trk_nxt < 0)) {trk_nxt = tmp;}
						}
					}
					if (trk_nxt < 0) {proceed = false;}
					trk_pos = trk_nxt;
					break;

				case 	ENTER:
					trk_nxt = -1;
					for (tmp = trk_pos + 1; tmp < countfld; tmp++) {
						if (editable[tmp] && (trk_nxt < 0)) {trk_nxt = tmp;}
					}
					if (trk_nxt < 0) {
						proceed = false;
					}
					trk_pos = trk_nxt;
					break;


				case 	F(1):
					proceed = false;
					break;
				default:
					proceed = false;
					break;
			}
		}
		return rtn_key;
	}

	int	edit(int *pfield, bool edt_clr) {
		Node 	*pnt = NULL;
		Node 	*nxt = NULL;
		bool*	editable = NULL;
		bool 	clearscr = edt_clr;
		int 	countfld = 0;
		Node	*currentN = NULL;
		int	rtn_key = 0;
		int 	trk_pos = pfield[0];
		int	trk_nxt = 0;
		bool	proceed = true;
		int	tmp = 0;
		int	targetposition = 0;
		int	secondposition = 0;
		pnt = fst;
		nxt = fst;
		// COUNT THE NUMBER OF CURRENTLY STORED FIELDS STORED IF FIRST FIELD IS ASSIGNED
		if (fst) {
			countfld = 1;
			currentN = fst;
			proceed = false;
			// ADD 1 TO COUNTFLD IF NODE CONTAINS ADDRESS OF NEXT ITEM
			while (currentN->next()) {
				currentN = currentN->next();
				countfld++;
			}
			// NOW COUNTFLD INDICATES NUMBER OF FIELD STORED IN THE SCREEN CLASS
			editable = new bool[countfld];
			// ARRAY THAT HOLDS INFORMATION - WHETHER IT IS EDITABLE OR NOT - HAS BEEN CREATED
			for (tmp = 0; tmp < countfld; tmp++) {editable[tmp] = false;}
			// ALL ARRAY ITEMS HAVE BEEN INITIALIZED TO BE FALSE
			currentN = fst;
			for (tmp = 0; tmp < countfld; tmp++) {
				if (currentN->_data.editable()) editable[tmp] = true;
				currentN = currentN->next();
			}
			// VALUE SET TO BE TRUE IF CORRESPONDING FIELD IS EDITABLE
			// DETERMINING FIRST FIELD TO BE EDITED. CHECK IF PFIELD IS VALID
			if (editable[trk_pos]) {
				currentN = fst;
				for (tmp = 0; tmp < trk_pos; tmp++) {currentN = currentN -> next();}
				proceed = true;
			} else {
				trk_pos = -1;
				// SEARCHING FOR THE FIRST OCCURANCE OF EDITABLE FIELD
				for (tmp = 0; tmp < countfld; tmp++) {
					if (editable[tmp] && (trk_pos < 0)) {trk_pos = tmp;}
				}
				// FIELD NUMBER OF THE FIRST EDITABLE FIELD IS STORED IN THE VARIABLE TRK_POS 
				currentN = fst;
				for (tmp = 0; tmp < trk_pos; tmp++) {currentN = currentN -> next();}
				proceed = true;
			}			
			// TRACKING INFORMATION AND POINTER TO THE FIRST EDITABLE ITEM IS NOW READY
		} else {
			// IF FIRST FIELD IS NOT ASSIGNED, IT DOES NOT GO THROUGH THE WHILE LOOP BELOW
			proceed = false;
		}
		// FIELD ITEMS ARE DISPLAYED
		while (proceed) {
			display(clearscr);
			// RESET POINTER TO THE FIELD AGAIN USING FORLOOP
			currentN = fst;
			pfield[0] = trk_pos;
			for (tmp = 0; tmp < trk_pos; tmp++) {currentN = currentN -> next();}
			rtn_key = currentN->_data.edit();
			// ONLY TRK_POS IS REQURED TO BE SET TO DETERMINE THE NEXT FIELD TO BE EDITED
			switch (rtn_key) {
				case 	UP:
					// CHECK IF THERE IS AN EDITABLE FIELD BEFORE THE CURRENT FIELD
					trk_nxt = -1;
					for (tmp = 0; tmp < trk_pos; tmp++) {
						if (editable[tmp]) {trk_nxt = tmp;}
					}
					if (trk_nxt < 0) {
						// IF THERE IS NO EDITABLE FIELD BEFORE THE CURRENT FIELD,
						// SEARCH FOR THE LAST EDITABLE FIELD OF THE CURRENT SCREEN CLASS
						trk_nxt = -1;
						for (tmp = 0; tmp < countfld; tmp++) {
							if (editable[tmp]) {trk_nxt = tmp;}
						} 
					}
					if (trk_nxt < 0) {proceed = false;}
					trk_pos = trk_nxt;
					break;
				case 	DOWN:
					// CHECK IF THERE IS AN EDITABLE FIELD AFTER THE CURRENT FIELD
					trk_nxt = -1;
					for (tmp = trk_pos + 1; tmp < countfld; tmp++) {
						if (editable[tmp] && (trk_nxt < 0)) {trk_nxt = tmp;}
					}
					if (trk_nxt < 0) {
						// IF THERE IS NO EDITABLE FIELD AFTER THE CURRENT FIELD,
						// SEARCH FOR THE FIRST EDITABLE FIELD OF THE CURRENT SCREEN CLASS
						trk_nxt = -1;
						for (tmp = 0; tmp <= trk_pos; tmp++) {
							if (editable[tmp] && (trk_nxt < 0)) {trk_nxt = tmp;}
						}
					}
					if (trk_nxt < 0) {proceed = false;}
					trk_pos = trk_nxt;
					break;
				case 	TAB:
					// CHECK IF THERE IS AN EDITABLE FIELD AFTER THE CURRENT FIELD
					trk_nxt = -1;
					for (tmp = trk_pos + 1; tmp < countfld; tmp++) {
						if (editable[tmp] && (trk_nxt < 0)) {trk_nxt = tmp;}
					}
					if (trk_nxt < 0) {
						// IF THERE IS NO EDITABLE FIELD AFTER THE CURRENT FIELD,
						// SEARCH FOR THE FIRST EDITABLE FIELD OF THE CURRENT SCREEN CLASS
						trk_nxt = -1;
						for (tmp = 0; tmp <= trk_pos; tmp++) {
							if (editable[tmp] && (trk_nxt < 0)) {trk_nxt = tmp;}
						}
					}
					if (trk_nxt < 0) {proceed = false;}
					trk_pos = trk_nxt;
					break;

				case 	ENTER:
					// CHECK IF THERE IS AN EDITABLE FIELD AFTER THE CURRENT FIELD
					trk_nxt = -1;
					for (tmp = trk_pos + 1; tmp < countfld; tmp++) {
						if (editable[tmp] && (trk_nxt < 0)) {trk_nxt = tmp;}
					}
					if (trk_nxt < 0) {
						// IF THERE IS NO EDITABLE FIELD AFTER THE CURRENT FIELD,
						// IT EXITS THE WHILE LOOP
						proceed = false;
					}
					trk_pos = trk_nxt;
					break;
				default:
					proceed = false;
					break;
			}
		}
		return rtn_key;
	}
};