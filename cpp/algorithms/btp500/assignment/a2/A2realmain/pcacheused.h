/**
 * Assignment 2
 */

#include "permhash.h"

template <class CT>
struct CacheTable {
	PermHashEntry<CT> rec;
	int usedStatus;
};

template <class CT>
class PCacheHash : public PermHash {
	int cacheSize;
	int numOfBuckets;
	int cacheCapacity;
	CacheTable<CT>** cacheEntry;
	int leastUsed;
	int cachecap() { return cacheCapacity; }
	int getElement(int hashValue) {
		int element = hashValue;
		if (hashValue) {
			element = (hashValue % numOfBuckets) - 1;
			if (element == 0) element = numOfBuckets - 1;
		}
		return element;
	}
	int getIndex(int hashValue) { return hashValue ? (hashValue / numOfBuckets) - 1 : hashValue; }
	int searchCache(const char* key)  {
		int found = -1;
		int hashValue = HashFunction(key,cachecap());
		int j = 0, index, element;
		index = getIndex(hashValue);
		element = getElement(hashValue);
		if (!cacheEntry[index][element].isempty) {

			cacheEntry[index][element].usedStatus += 1;
			if (cacheEntry[index][element].usedStatus < cacheEntry[leastUsed][leastUsed].usedStatus)
				leastUsed = hashValue;

			if(strcmp(cacheEntry[index][element].rec.key(),key) == 0) {
				found = hashValue;
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
					cacheEntry[index][element].usedStatus += 1;
					if (cacheEntry[index][element].usedStatus < cacheEntry[leastUsed][leastUsed].usedStatus)
						leastUsed = i;
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
		int index, element;
		// update data in cache in perm hash
		for (int i = 0; i < cachecap(); i++) {
			index = getIndex(i);
			element = getElement(i);
			PermHash::update(cacheEntry[index][element].rec);
		}
		// release memory in the heap
		if (cacheEntry) delete [] cacheEntry;
	}
	
	// find how to implment in inheritance
	PCacheHash& operator=(const PCacheHash& rhs) {
		if (*this != &rhs) {
			PermHash::operator=(rhs);
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
			int i = 0;
			PermHashEntry<PH> emptyDataHolder;
			int index, element;
			index = getIndex(rm);
			element = getElement(rm);
			
			emptyDataHolder.isempty = true;
			cacheEntry[index][element].rec = emptyDataHolder;

			int next = rm;
			next + 1 == cachecap() ? next = 0 : next++; // cluster update incrementer
			index = getIndex(next);
			element = getElement(next);
			bool seq = false;
			while (!cacheEntry[index][element].rec.isempty) {
				seq = true; // use update sequence for tracking least accessed
				cacheEntry[index][element].usedStatus += 1;
				if (cacheEntry[index][element].usedStatus < cacheEntry[leastUsed][leastUsed].usedStatus)
					leastUsed = hashValue;
				int proper = HashFunction(cacheEntry[index][element].rec.key(),cachecap());
				// adjust permhash to accomodate various capcity sizes
				if (PermHash::isbetween(rm,proper,next,cachecap())) {
					cacheEntry[getIndex(rm)][getElement(rm)].rec = cacheEntry[index][element].rec;
					cacheEntry[getIndex(rm)][getElement(rm)].isempty = false;
					cacheEntry[index][element].rec.isempty = true;
					rm = next;
				}
				next + 1 == cachecap() ? next = 0 : next++; // cluster update incrementer
				index = getIndex(next);
				element = getElement(next);
			} // end while
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
		} else {
			findStatus = PermHash::find(key,holder);
		}
		return findStatus;
	}
	
	// retire the least accessed
	virtual bool update(const TYPE& data) {
		bool rc = false;
		if(size() < max()) {
			int index, element;
			int newHashValue = HashFunction(data.key(),cachecap());
			int i = newHashValue;
			if (cachesize() == cachecap()) {
				// retire to perm table then replace the least used entry
				index = getIndex(leastUsed);
				element = getElement(leastUsed);
				rc = PermHash::update(cacheEntry[index][element].rec);
				if (rc) { 
					cacheEntry[index][element].rec = data;
					cacheEntry[index][element].usedStatus = 1;
				}
			} else {
				index = getIndex(i);
				element = getElement(i);
				if (cacheEntry[index][element].isempty) {
					cacheEntry[index][element].rec = data;
					cacheEntry[index][element].isempty = false;
					cacheEntry[index][element].usedStatus = 1;
					rc = true;
					csize++;
				} else if (strcmp(cacheEntry[index][element].rec.key(),data.key())==0) {
					cacheEntry[index][element].rec = data;
					cacheEntry[index][element].usedStatus += 1;
					if (cacheEntry[index][element].usedStatus < cacheEntry[leastUsed][leastUsed].usedStatus)
						leastUsed = i;
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
							index = getIndex(i);
							element = getElement(i);
							if (cacheEntry[index][element].isempty) {
								rc = true;
								keepgoing = false;
								cacheEntry[index][element].isempty = false;
								cacheEntry[index][element].rec = data;
								cacheEntry[index][element].usedStatus = 1;
								csize++;
							} else if (strcmp(cacheEntry[index][element].rec.key(),data.key()) == 0) {
								rc = true;
								keepgoing = false;
								cacheEntry[index][element].rec = data;
								cacheEntry[index][element].usedStatus += 1;
								if (cacheEntry[index][element].usedStatus < cacheEntry[leastUsed][leastUsed].usedStatus)
									leastUsed = i;
							}
						} // end if
					} // end while
				} // end if
			} // end if
		}
		return updateStatus;
	}
};