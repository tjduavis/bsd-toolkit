/**
 * Assignment 2
 */

#include "permhash.h"

template <class CT>
struct CacheTable {
	PermHashEntry<CT> rec;
	int accessStatus;
};

template <class CT>
class PCacheHash : public PermHash {
	int cacheSize;
	int numOfBuckets;
	int cacheCapacity;
	CacheTable<CT>** cacheEntry;
	int leastAccessed;
	int cachecap() { return cacheCapacity; }
	int getElement(int hashValue) {
		int element = (hashValue % numOfBuckets) - 1;
		if (element == 0) element = numOfBuckets - 1;
		return element;
	}
	int getIndex(int hashValue) { return (hashValue / numOfBuckets) - 1; }
	void updateSeqStatus(int m1, int m2, int md1, int zeromin) {
		if (md1 > 0 && cacheEntry) {
			int min, max, mod1, mod2;
			min = m1;
			max = m2;
			mod1 = md1;
			!zeromin ? mod2 = mod1 + 1 / min : mod2 = mod1 / min;
			int index, element;
			for (int i = 0; i < cachecap(); i++) {
				index = getIndex(i);
				element = getElement(i);
				if (!cacheEntry[index][element].isempty) {
					if (cacheEntry[index][element].accessStatus == (max - mod2)) {
						cacheEntry[index][element].accessStatus = max;
					}
					if (cacheEntry[index][element].accessStatus < min && cacheEntry[index][element].accessStatus < max) {
						cacheEntry[index][element].accessStatus += mod1;
					} else if (cacheEntry[index][element].accessStatus > min && cacheEntry[index][element].accessStatus < max) {
						cacheEntry[index][element].accessStatus += mod2;
					}
					if (cacheEntry[index][element].accessStatus > cacheEntry[leastAccessed][leastAccessed].accessStatus)
						leastAccessed = i;
				}
			}
		}
	}
	void updateStatus(int last, int max) {
		if (last >= 0 && md1 > 0) {
			int mod1 = md1;
			rc = last;
			int index = getIndex(last);
			int element = getElement(last);
			cacheEntry[index][element].accessStatus = 0;
			for (int i = 0; i < max; i++) {
				index = getIndex(i);
				element = getElement(i);
				if (!cacheEntry[index][element].isempty)
					cacheEntry[getIndex(i)][getElement(1)].accessStatus += 1;
			}
			if (max > cacheEntry[getIndex(leastAccessed)][getElement(leastAccessed)].accessStatus)
				leastAccessed = i;
		}
	}
	int searchCache(const char* key)  {
		int found = -1;
		int hashValue = HashFunction(key,cachecap());
		int j = 0, min, max, index, element;
		index = getIndex(hashValue);
		element = getElement(hashValue);
		min = max = cacheEntry[index][element].accessStatus;
		if (!cacheEntry[index][element].isempty) {
			cacheEntry[index][element].accessStatus = j;
			if(strcmp(cacheEntry[index][element].rec.key(),key) == 0) {
				found = hashValue;
				updateStatus(hashValue,max);
			} else {
				// loop stops when we either have searched entire table,
				// find empty space or find a match
				// considering that hashtable can loop from current at end to next current is at beg
				bool keepSearching = true;
				int i; // next entry
				hashValue + 1 == cachecap() ? i = 0 : i = hashValue + 1;
				for (; keepSearching && i != hashValue; i++) {
					if (i == cap()) { i = 0; } // check if i will reach last entry
					if (!cacheEntry[getIndex(i)][getElement(i)].isempty) {
						if (strcmp(cacheEntry[getIndex(i)][getElement(i)].rec.key(),key) == 0) {
							keepSearching = false;
							found = i;
						}
					} else {
						keepSearching = false;
					}
					index = getIndex(i);
					element = getElement(i);
					j + 1 == cachecap() ? j = 0 : j++;
					cacheEntry[index][element].accessStatus = j;
					if (min > cacheEntry[index][element].accessStatus)
						min = cacheEntry[index][element].accessStatus;
					if (max < cacheEntry[index][element].accessStatus)
						max = cacheEntry[index][element].accessStatus;
				} //end for
			}
		}	
		return found;
	}
public:
	PCacheHash(const char* fname, int max, double over, double cachez, int numbuckets) : 
	PermHash(fname,max,over) {
		// create cache
		cacheSize = cachez;
		numOfBuckets = numbuckets;
		cacheCapacity = cachez * max();
		if (cacheSize > 0 && numOfBuckets > 0) {
			cacheEntry = new CacheTable<CT>[cachecap()][numOfBuckets];
		}
	}
	PCacheHash(const PCacheHash& src) : PermHash(src) {
		if (src.cacheCapacity > 0) {
			cacheSize = src.cacheSize;
			numOfBuckets = src.numOfBuckets;
			cacheCapacity = src.cacheCapacity;
			cacheEntry = new CacheTable<CT>[cacheCapacity][numOfBuckets];
			if (src.cachEntry) {
				for (int i = 0; i < cachecap(); i++) {
					cacheEntry[getIndex(i+1)][getElement(i+1)] = src.cacheEntry[getIndex(i+1)][getElement(i+1)];
				}
			}
		}
	}
	~PCacheHash() {
		// update data in cache in perm hash
		// release memory in the heap
		if (cacheEntry) delete cacheEntry;
	}
	// find how to implment in inheritance
	PCacheHash& operator=(const PCacheHash& rhs) {
		if (*this != &rhs) {
			if (src.cacheCapacity > 0) {
				cacheSize = src.cacheSize;
				numOfBuckets = src.numOfBuckets;
				cacheCapacity = src.cacheCapacity;
				cacheEntry = new CacheTable<CT>[cacheCapacity][numOfBuckets];
				if (src.cachEntry) {
					for (int i = 0; i < cachecap(); i++) {
						cacheEntry[getIndex(i)][getElement(i)] = src.cacheEntry[getIndex(i)][getElement(i)];
					}
				}
			}
		}
		return *this;
	}
	
	// remove the entry with the specified key
	// first search in the cache
	// then regardless of the success of the first attempt
	// check to see if it is able to be removed in the hashtable file
	virtual bool remove(const char* key) {
		bool rc = false;
		int rm = searchCache(key);
		if (rm != -1) {
			int min, max, i, zeromin; max = i = zeromin = 0;
			PermHashEntry<PH> emptyDataHolder;
			int index, element;
			index = getIndex(rm);
			element = getElement(rm);
			
			emptyDataHolder.isempty = true;
			cacheEntry[index][element].rec = emptyDataHolder;
			min = max = cacheEntry[index][element].accessStatus;
			cacheEntry[index][element].accessStatus = i;
			
			int next = rm;
			bool seq = false;
			while (!cacheEntry[getIndex(next)][getElement(next)].rec.isempty) {
				seq = true; // use update sequence for tracking least accessed
				i + 1 == cachecap() ? i = 0 : i++; // bucket incrementer for least accessed value
				next + 1 == cachecap() ? next = 0 : next++; // cluster update incrementer
				index = getIndex(next);
				element = getElement(next);

				if (!min) {
					zeromin = true;
					min = cacheEntry[index][element].accessStatus;
				} else if (min > cacheEntry[index][element].accessStatus)
					min = cacheEntry[index][element].accessStatus;
				if (max < cacheEntry[index][element].accessStatus)
					max = cacheEntry[index][element].accessStatus;
				cacheEntry[index][element].accessStatus = i;

				int proper = HashFunction(cacheEntry[getIndex(next)][getElement(next)].rec.key(),cachecap());
				// adjust permhash to accomodate various capcity sizes
				if (PermHash::isbetween(rm,proper,next,cachecap())) {
					cacheEntry[getIndex(rm)][getElement(rm)].rec = cacheEntry[getIndex(next)][getElement(next)].rec;
					cacheEntry[getIndex(next)][getElement(next)].rec.isempty = true;
					rm = next;
				}
			} // end while
			if (seq) updateSeqStatus(min,max,next,zeromin);
			if (!rc) rc = PermHash::remove(key);
		}
		return rc;
	}
	
	// finds the key wih the same value of the generic variable holder
	// search first in the in-memory cache then if it is not in the
	// the in-memory cache try the hashtable file
	virtual bool find(const char* key, CT& holder) {
		bool findStatus = false;
		int found = searchCache(key);
		if (found != -1) {
			holder = cacheEntry[getIndex(found)][getElement(found)].data;
			findStatus = true;
		}
		return findStatus;
	}
	
	// retire the least accessed
	virtual bool update(const TYPE& data) {
		bool rc = false;
		if(size() < max()) {
			int newHashValue = HashFunction(data.key(),cachecap());
			int i = newHashValue;
			int j = 0;
			if (cachesize() == cachecap()) {
				// retire to perm table then replace the least used entry
				rc = PermHash::update(cacheEntry[getIndex(leastUsed)][getElement(leastUsed)].rec);
				if (rc) { 
					int index = getIndex(leastAccessed);
					int element = getElement(leastAccessed);
					int max = cacheEntry[index][element].accessStatus;
					cacheEntry[index][element].rec = data;
					cacheEntry[index][element].accessStatus = j;
					updateStatus(leastAccessed,max);
				}
			} else {
				int index = getIndex(i);
				int element = getElement(i);
				int min, max, zeromin, j, seq; min = max = zeromin = j = seq = 0;
				
				min = max = cacheEntry[index][element].accessStatus;
				cacheEntry[index][element].accessStatus = j;

				if (cacheEntry[index][element].isempty) {
					cacheEntry[index][element].rec = data;
					cacheEntry[index][element].isempty = false;					
					rc = true;
					csize++;
				} else if (strcmp(cacheEntry[index][element].rec.key(),data.key())==0) {
					cacheEntry[index][element].rec = data;
					rc = true;
				} else {
				// loop stops when hits first empty spot or if it reaches same spot
				// considering that hashtable can loop from current at end to next current is at beg
					bool keepgoing = true;
					while (keepgoing) {
						if (i + 1 == newHashValue) {
							keepgoing = false;
						} else {
							seq = 1; // true
							i + 1 == cachecap() ? i = 0 : i++;
							j + 1 == cachecap() ? i = 0 : j++;
							index = getIndex(i);
							element = getElement(i);
							if (!min) {
								zeromin = true;
								min = cacheEntry[index][element].accessStatus;
							} else if (min > cacheEntry[index][element].accessStatus)
								min = cacheEntry[index][element].accessStatus;
							if (max < cacheEntry[index][element].accessStatus)
								max = cacheEntry[index][element].accessStatus;
							cacheEntry[index][element].accessStatus = j;
							if (cacheEntry[index][element].isempty) {
								rc = true;
								keepgoing = false;
								cacheEntry[index][element].isempty = false;
								cacheEntry[index][element].rec = data;
								csize++;
							} else if (strcmp(cacheEntry[index][element].rec.key(),data.key()) == 0) {
								rc = true;
								keepgoing = false;
								cacheEntry[getIndex(i)][getElement(i)].rec = data;
							}
						} // end if
					} // end while
				} // end if
				seq ? updateSeqStatus(min,max,i,zeromin) : updateStatus(i);
			} // end if
		}
		return updateStatus;
	}
};