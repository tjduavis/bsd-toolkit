/**
 * Assignment 2
 */

#define INDEX_OF_CACHE_DATA 0
#define INDEX_OF_ACCESS_TRACKER 1
#define RESET_ACCESS_STATUS 1

template <class T>
struct CacheTable {
	T data_;
};

template <class PCH>
class PCacheHash : public PermHash {
	int cachecap_;
	int numbuckets_;
	double over_;
	CacheTable cache**;
	int sizeOfCacheTable() {
		return cachecap_ * numbuckets_;
	}
	PermHashEntry cachePermHashEntry;
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
	// remove the entry with the specified key
	// first search in the cache
	// then regardless of the success of the first attempt
	// check to see if it is able to be removed in the hashtable file
	virtual bool remove(const char* key) {
		bool removeStatus = false;
		for (int i = 0; i < sizeOfCacheTable(); i++) {
			if (cache[i].data_.rec_.key() == key) {
				// set the entry to empty
				cache[i][INDEX_OF_ACCESS_TRACKER] = RESET_ACCESS_STATUS;
				removeStatus = true;
			}
		}
		// remove hashtable file and
		// check the returnStatus if remove in hashtbale file succeeded
		removeStatus = PermHash::remove(key);
		return removeStatus;
	}
	// finds the key wih the same value of the generic variable holder
	// search first in the in-memory cache then if it is not in the
	// the in-memory cache try the hashtable file
	virtual bool find(const char* key, PCH& holder) {
		bool findStatus = false;
		// first search in the cache
		for (int i = 0; i < sizeOfCacheTable(); i++) {
			// compare key first with requested key
			// then data stored with requested data
			if (cache[i].data_.rec_.key() == key && cache[i].data_.rec. == holder) {
				findStatus = true;
			}
			// update all the cache entry's access tracker since were used to search
			cache[i][INDEX_OF_ACCESS_TRACKER] += 1;
		}
		if (!findStatus) {
			// check to see search query is in perm hash table file
			findStatus = PermHash::find(key,holder);
		}
		return findStatus;
	}
	// update the cache first then perm hash table file
	// retiring method is least used entry
	virtual bool update(const TYPE& data) {
		bool updateStatus = false;
		int leastUsed_; //identifier for the least used entry
		for (int i = 0; i < sizeOfCacheTable(); i++) {
			// find the least used entry
			// check first if comparing entry which is one entry a head of current entry has not reached the max
			if (i + 1 < (sizeOfCacheTable() - 1) && cache[i][INDEX_OF_ACCESS_TRACKER] <= cache[i + 1][INDEX_OF_ACCESS_TRACKER]) {
				leastUsed_ = i;
			}
			// check to see if data to be update is in the cache table
			if (cache[i].rec_.key() == key)
				cachedAlready = updateStatus = true;
		}
		if (!cachedAlready) {
			// if not in the cache 
			// insert the data in the perm hash replacing the least used
			// where the least used access tracker's status is set to 1 for
			// using it to insert
			updateStatus = PermHash::update(data);
			cache[leastUsed_].rec_ = data;
			cache[leastUsed_][INDEX_OF_ACCESS_TRACKER] = RESET_ACCESS_STATUS;
		} else {
			// update the times used and the data 
			cache[leastUsed_].rec_ = data;
			cache[leastUsed_][INDEX_OF_ACCESS_TRACKER] += 1;
		}
		return updateStatus;	
	}
};