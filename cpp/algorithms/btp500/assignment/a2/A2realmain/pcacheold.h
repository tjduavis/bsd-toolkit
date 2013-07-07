/**
 * Assignment 2
 */

#include "permhash.h"
#include <fstream>

template <class CT>
struct CacheTable {
	PermHashEntry<CT> entry;
	int oldStatus;
};
template <class CT>
class PCacheHash : public PermHash<CT> {
	//long debugger;
	int cacheSize;
	int numOfBuckets;
	int cacheCapacity;
	int sizeOfIndex;
	CacheTable<CT>** cacheEntry;
	int oldest;
	int cachecap();
	int cachesize();
	int getElement(int hashValue);
	int getIndex(int hashValue);
	void updateStatus(int min);
	int searchCache(const char* key);
public:
	PCacheHash(const char* fname, int max, double over, double cachez, int numbuckets);
	PCacheHash(const PCacheHash& src);
	virtual ~PCacheHash();
	PCacheHash& operator=(const PCacheHash& rhs);
	virtual bool remove(const char* key);
	virtual bool find(const char* key, CT& holder);
	virtual bool update(const CT& data);
};
template <class CT>
int PCacheHash<CT>::cachecap() { return cacheCapacity; };
template <class CT>
int PCacheHash<CT>::cachesize() { return cacheSize; };
template <class CT>
int PCacheHash<CT>::getElement(int hashValue) {
	int element = 0;
	if (hashValue) {
		if (hashValue < numOfBuckets)
			element = hashValue;
		else {
			element = hashValue % numOfBuckets;
			if (element < 0) 
				element = numOfBuckets - 1;
		}
	}
	return element;
};
template <class CT>
int PCacheHash<CT>::getIndex(int hashValue) { 
	int index;
	if (hashValue < numOfBuckets)
		index = 0;
	else {
		index = ( hashValue - getElement(hashValue) ) / numOfBuckets;
	}
	return index;
};
template <class CT>
void PCacheHash<CT>::updateStatus(int min) {
	if (min != cachesize() - 1) {
		int index, element;
		for (int i = 0; i < cachecap(); i++) {
			index = getIndex(i);
			element = getElement(i);
			if (!cacheEntry[index][element].entry.isempty) {
				if (cacheEntry[index][element].oldStatus > min)
					cacheEntry[index][element].oldStatus -= 1;
				if (cacheEntry[index][element].oldStatus == 0)
					oldest = i;
			}
		}
	}
};
template<class CT>
int PCacheHash<CT>::searchCache(const char* key)  {
	int found = -1;
	int hashValue = HashFunction(key,cachecap());
	int index, element;
	index = getIndex(hashValue);
	element = getElement(hashValue);
	
	if (!cacheEntry[index][element].entry.isempty) {
		if(strcmp(cacheEntry[index][element].entry.rec.key(),key) == 0) {
			found = hashValue;
		} else {
			// loop stops when we either have searched entire table,
			// find empty space or find a match
			// considering that hashtable can loop from current at end to next current is at beg
			bool keepSearching = true;
			int i; // next entry
			hashValue == cachecap() - 1 ? i = 0 : i = hashValue + 1;
			for (; keepSearching && i != hashValue; i++) {
				if (i == cachecap()) { i = 0; } // check if i will reach last entry
				index = getIndex(i);
				element = getElement(i);
				if (!cacheEntry[index][element].entry.isempty) {
					if (strcmp(cacheEntry[index][element].entry.rec.key(),key) == 0) {
						keepSearching = false;
						found = i;
					}
				} else {
					keepSearching = false;
				}
			} //end for
		}
	}
	return found;
};

template<class CT>
PCacheHash<CT>::PCacheHash(const char* fname, int max, double over, double cachez, int numbuckets) : 
PermHash<CT>(fname,max,over) {
	cacheSize = oldest = 0;
	numOfBuckets = numbuckets;
	sizeOfIndex = cachez * max;
	cacheCapacity = sizeOfIndex * numOfBuckets;

	ofstream fout("debug.txt");  // opens output.txt for output 

	if (cacheCapacity > 0 && numOfBuckets > 0) {
		cacheEntry = new CacheTable<CT>* [sizeOfIndex];
		for (int i = 0; i < sizeOfIndex; i++) {
			cacheEntry[i] = new CacheTable<CT>[numbuckets];
		}
		int index, element;
		for (int i = 0; i < cachecap(); i++) {
			index = getIndex(i);
			element = getElement(i);
			cacheEntry[index][element].oldStatus = 0;
			cacheEntry[index][element].entry.isempty = true;
			fout << "position value: " << i << " -(" << index << "," << element << ")" << endl;
		}
	}
	fout.close();
};


template <class CT>
PCacheHash<CT>::PCacheHash(const PCacheHash<CT>& src) : PermHash(src) {
	if (src.cacheCapacity > 0) {
		cacheSize = src.cacheSize;
		numOfBuckets = src.numOfBuckets;
		cacheCapacity = src.cacheCapacity;
		sizeOfIndex = src.sizeOfIndex;
		oldest = src.oldest;
		cacheEntry = new CacheTable<CT>[cacheCapacity][numOfBuckets];
		if (src.cachEntry) {
			for (int i = 0; i < cachecap(); i++) {
				cacheEntry[getIndex(i)][getElement(i)] = src.cacheEntry[getIndex(i)][getElement(i)];
			}
		}
	}
};

template <class CT>
PCacheHash<CT>::~PCacheHash() {
	int index, element;
	for (int i = 0; i < cachecap(); i++) {
		index = getIndex(i);
		element = getElement(i);	
		if (!cacheEntry[index][element].entry.isempty)
			PermHash<CT>::update(cacheEntry[index][element].entry.rec);
	}
	if (cacheEntry) delete [] cacheEntry;
};

template <class CT>
PCacheHash<CT>& PCacheHash<CT>::operator=(const PCacheHash<CT>& rhs) {
	if (*this != &rhs) {
		PermHash<CT>::operator=(rhs);
		if (rhs.cacheCapacity > 0) {
			cacheSize = rhs.cacheSize;
			numOfBuckets = rhs.numOfBuckets;
			cacheCapacity = rhs.cacheCapacity;
			sizeOfIndex = src.sizeOfIndex;
			oldest = src.oldest;
			cacheEntry = new CacheTable<CT>[cacheSize][numOfBuckets];
			if (src.cachEntry) {
				for (int i = 0; i < cachecap(); i++) {
					cacheEntry[getIndex(i)][getElement(i)] = rhs.cacheEntry[getIndex(i)][getElement(i)];
				}
			}
		}
	}
	return *this;
};

template <class CT>
bool PCacheHash<CT>::update(const CT& data) {
	bool rc = false;
	if(PermHash<CT>::size() < PermHash<CT>::max()) {
		int newHashValue = HashFunction(data.key(),cachecap());
		int i = newHashValue;
		if (cachesize() == cachecap()) {
			int index = getIndex(i);
			int element = getElement(i);
			if (strcmp(cacheEntry[index][element].entry.rec.key(),data.key())==0) {
				cacheEntry[index][element].entry.rec = data;
			} else if (i = searchCache(data.key()) != -1) {
				index = getIndex(i);
				element = getElement(i);
				cacheEntry[index][element].entry.rec = data;
			} else {
				index = getIndex(oldest);
				element = getElement(oldest);
				rc = PermHash<CT>::update(cacheEntry[index][element].entry.rec);
				if (rc) { 
					int min = cacheEntry[index][element].oldStatus;
					cacheEntry[index][element].entry.rec = data;
					cacheEntry[index][element].oldStatus = cachesize() - 1;
					updateStatus(min);
				}
			}
		} else {
			int index = getIndex(i);
			int element = getElement(i);
			if (cacheEntry[index][element].entry.isempty) {
				cacheEntry[index][element].entry.rec = data;
				cacheEntry[index][element].entry.isempty = false;
				PermHash<CT>::update(cacheEntry[index][element].entry.rec);
				rc = true;
				cacheSize++;
				cacheEntry[index][element].oldStatus = cachesize() - 1;
				if (cacheEntry[index][element].oldStatus == 0) oldest = i;
			} else if (strcmp(cacheEntry[index][element].entry.rec.key(),data.key())==0) {
				cacheEntry[index][element].entry.rec = data;
				cacheEntry[index][element].entry.isempty = false;
				rc = true;
			} else {
				i++;
				bool keepgoing = true;
				while (keepgoing) {
					if (i == cachecap()) i = 0;
					if (i == newHashValue) {
						keepgoing = false;
					} else {
						index = getIndex(i);
						element = getElement(i);
						if (cacheEntry[index][element].entry.isempty) {
							rc = true;
							keepgoing = false;
							cacheEntry[index][element].entry.isempty = false;
							cacheEntry[index][element].entry.rec = data;
							PermHash<CT>::update(cacheEntry[index][element].entry.rec);
							cacheSize++;
							cacheEntry[index][element].oldStatus = cachesize() - 1;
							if (cacheEntry[index][element].oldStatus == 0) oldest = i;
						} else if (strcmp(cacheEntry[index][element].entry.rec.key(),data.key()) == 0) {
							rc = true;
							keepgoing = false;
							cacheEntry[index][element].entry.isempty = false;
							cacheEntry[index][element].entry.rec = data;
						}
					} // end if
					if (keepgoing) i++;
				} // end while
			} // end if
		} // end if
	}
	return rc;
};
// finds the key wih the same value of the generic variable holder
// search first in the in-memory cache then if it is not in the
// the in-memory cache try the hashtable file
template <class CT>
bool PCacheHash<CT>::find(const char* key, CT& holder) {
	bool findStatus = false;
	int found = searchCache(key);
	if (found != -1) {
		int index   = getIndex(found);
		int element = getElement(found);
		holder = cacheEntry[index][element].entry.rec;
		findStatus = true;
	} else {
		findStatus = PermHash<CT>::find(key,holder);
	}
	return findStatus;
};

// remove the entry with the specified key
// first search in the cache
// then regardless of the success of the first attempt
// check to see if it is able to be removed in the hashtable file
template<class CT>
bool PCacheHash<CT>::remove(const char* key) {
	bool rc = false;
	int rm = searchCache(key);
	if (rm != -1) {
		rc = true;
		int index, element;
		PermHashEntry<CT> emptyDataHolder;
		emptyDataHolder.isempty = true;
		index = getIndex(rm);
		element = getElement(rm);
		cacheEntry[index][element].entry = emptyDataHolder;
		int min = cacheEntry[index][element].oldStatus;
		updateStatus(min);		
		int next = rm;
		next + 1 == cachecap() ? next = 0 : next++; // cluster update incrementer
		index = getIndex(next);
		element = getElement(next);
		while (!cacheEntry[index][element].entry.isempty) {
			int proper = HashFunction(cacheEntry[index][element].entry.rec.key(),cachecap());
			// adjust permhash to accomodate various capcity sizes
			if (PermHash<CT>::isbetween(rm,proper,next,cachecap())) {
				cacheEntry[getIndex(rm)][getElement(rm)].entry.rec = cacheEntry[getIndex(next)][getElement(next)].entry.rec;
				cacheEntry[getIndex(rm)][getElement(rm)].entry.isempty = false;
				cacheEntry[getIndex(next)][getElement(next)].entry.isempty = true;
				rm = next;
			}
			next + 1 == cachecap() ? next = 0 : next++; // cluster update incrementer
			index = getIndex(next);
			element = getElement(next);
		} // end while
		cacheSize--;
		PermHash<CT>::remove(key);
	} else { rc = PermHash<CT>::remove(key); }
	return rc;
};