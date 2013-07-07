/*==============================================================================/
 *                                                                             * 
 * Assignment 3 Version 1.0 - Field Class                                      *
 *                                                                             * 
 * FILE           : Field.h                                                    * 
 * Author         : Timothy Duavis                                             *
 * Last Modified  : November 11, 2005                                          *
 *                                                                             *
 * Description    : 
 *                                                                             * 
 * Specs created  : Chris S. - Seneca College                                  * 
 *                                                                             *  
/*=============================================================================*/

class fieldNode {
	Field data;
    fieldNode* next;
    fieldNode* prev;
	
    public:
    fieldNode(Field d, fieldNode* n) : data(d), next(n) { }
    fieldNode* goNext() { return next; }
    fieldNode* goPrev() { return prev; }
    Field getData() { return data; }
    void setNext(fieldNode* n) { next = n; }
    void setPrev(fieldNode* n) { prev = n; }
};