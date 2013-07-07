/**
 * Assignment 2
 */

#include "permhash.h"

template <class CT>
struct CacheTable {
	PermHashEntry<CT> rec;
	int accessStatus;
};


template <class PCH>
class PCacheHash : public PermHash {
	int cacheSize;
	int numOfBuckets;
	int cacheCapacity;
	double over_;
	CacheTable cache**;
	int sizeOfCacheTable() {
		return cachecap_ * numbuckets_;
	}
public:
	// constructor that sets up cache
	// using bucketing as it collision detecting method
	PCacheHash(const char* fname, int max, double over, double cachecap, int numbuckets) : 
	PermHash(fname,max,over) {
		// create cache
		// but first check if numbuckets contains a valid value for holding entries
		if (numbuckets > 0) {
			cache = new CacheTable<PermHashEntry>[cachecap * max]<int>[numbuckets];
			// set up cache values
			for (int i = 0; i < sizeOfCacheTable(); i++) {
				cache[i][INDEX_OF_CACHE_DATA] = cachePermHashEntry;
				cache[i][INDEX_OF_ACCESS_TRACKER] = RESET_ACCESS_STATUS;
			}
		}
	}
	// find out if a PermHash-constructor is needed as well? (most likely -but unsure of implementation details
	PCacheHash(const PCacheHash& src) : PermHash();
	~PCacheHash() {
		// delete everything but update hash table first
		for (int i = 0; i < sizeOfCacheTable(); i++) {
			PermHash::update(cache_[i][INDEX_OF_CACHE_DATA]);
		}
		if (cache_) delete [] cache_;
	}
	PCacheHash& operator=(const PCacheHash& rhs);
	virtual bool remove(const char* key) {
		bool removeStatus = false;
		int removedAccessTrackersStatus_; // holds the access tracker 
										  // status of the correspondingcache entry
		for (int i = 0; i < sizeOfCacheTable(); i++) {
			if (cache[i].data_.rec_.key() == key) {
				// set the entry to empty
				cache[i].data_.isempty_ = true;
				removedAccessTrackersStatus = cache[i][INDEX_OF_ACCESS_TRACKER];
				cache[i][INDEX_OF_ACCESS_TRACKER] = RESET_ACCESS_STATUS;
				removeStatus = true;
			}
		}
		if (removeStatus) {
			// update the remaining cache entry's access status
			for (int i = 0; i < sizeOfCacheTable(); i++) {
				if (cache[i][INDEX_OF_ACCESS_TRACKER] < removedAccessTrackersStatus_) {
					cache[i][INDEX_OF_ACCESS_TRACKER] += 1;
				}
			}
			// check the returnStatus if remove in hashtbale file succeeded
			removeStatus = PermHash::remove(key);
		} else {
			// try to see if parent remove function can remove it
			removeStatus = PermHash::remove(key);
		}
		return removeStatus;
	}
	virtual bool find(const char* key, PCH& holder) {
		bool findStatus = false;
		// first search in the cache
		for (int i = 0; i < sizeOfCacheTable(); i++) {
			// compare key first with requested key
			// then data stored with requested data
			if (cache[i].data_.rec_.key() == key && cache[i].data_.rec. == holder) {
				findStatus = true;
			}
		}
		if (!findStatus) {
			// check to see search query is in perm hash table
			findStatus = PermHash::find(key,holder);
		}
		return findStatus;
	}
	virtual bool update(const TYPE& data) {
		bool updateStatus = false;
		bool cachedAlready = false;
		// retire the earlist added item.
		int earliestItem_;
		for (int i = 0; i < sizeOfCacheTable(); i++) {
			// check to see if data to be update is in the cache table
			if (i + 1 < (sizeOfCacheTable() - 1) && cache[i][INDEX_OF_ACCESS_TRACKER] < cache[i + 1][INDEX_OF_ACCESS_TRACKER]) {
				earliestItem_ = i;
			}
			if (cache[i].rec_.key() == key)
				cachedAlready = updateStatus = true;
		}
		// update
		if (!cachedAlready) {
			// if not in the cache update the perm hash table first
			updateStatus = PermHash::update(data);
			cache[i].rec_ = data;
		} else {
			// update the data 
			cache[i].rec_ = data;
		}
		return updateStatus;
	}
};