/**
 * Assignment 2
 */

#include "permhash."

#define INDEX_OF_CACHE_DATA 0
#define INDEX_OF_ACCESS_TRACKER 1
#define LEAST_ACCESSED( SIZE_OF_CACHE ) SIZE_OF_CACHE + 1
#define RESET_ACCESS_STATUS 0

struct CacheTable {
	PermHashEntry data_;
	int accessStatus_;
};

template <class PCH>
class PCacheHash : public PermHash {
	int cachecap_;
	int numbuckets_;
	CacheTable<T>** cacheEntry_;
	int maxIndexInCacheTable() {
		return cachecap_ * max_;
	}
	int maxElementsInCacheTable() {
		return maxIndexInCacheTable() * numbuckets_;
	}
	int getElement() {

	}
	int getIndex() {

	}
	// taken from btp500 course notes
	// author of course notes: Catherine Leung
	void InsertionSort(CacheTable& arr[][numbuckets_]){
		int curr;
		int i, j;
		for(i=1;i<maxIndexInCacheTable();i++){
			curr=arr[i][INDEX_OF_ACCESS_TRACKER];
			for(j=i;j>0 && arr[j-1][INDEX_OF_ACCESS_TRACKER] > curr;j--){
				arr[j][INDEX_OF_ACCESS_TRACKER]=arr[j-1][INDEX_OF_ACCESS_TRACKER];
			}
			arr[j][INDEX_OF_ACCESS_TRACKER]=curr;
		}
	}
	// taken from btp500 course notes
	// author of course notes: Catherine Leung
	// modified the swap function to run it manually 
	// instead of creating another swap function
	void QuickSort(CacheTable arr[][numbuckets_], int left, int right) {
		if(right-left <=3){
			InsertionSort(arr,left,right);
		} else {
			int pivotpt=right;
			int i=left;
			int j=right-1;
			int pivot=arr[pivotpt][INDEX_OF_ACCESS_TRACKER];
			while(i<j){
				while(arr[i][INDEX_OF_ACCESS_TRACKER]<pivot) i++;
				while(arr[j][INDEX_OF_ACCESS_TRACKER]>pivot) j--;
				if(i<j) {
					int swap; // swap value holder
					swap = arr[i++][INDEX_OF_ACCESS_TRACKER];
					arr[i++][INDEX_OF_ACCESS_TRACKER] = arr[j--][INDEX_OF_ACCESS_TRACKER];
					arr[j--][INDEX_OF_ACCESS_TRACKER] = swap;
				}
			}
			// swap
			int swap; // swap value holder
			swap = arr[i][INDEX_OF_ACCESS_TRACKER];
			arr[i][INDEX_OF_ACCESS_TRACKER] = arr[pivotpt][INDEX_OF_ACCESS_TRACKER];
			arr[pivotpt][INDEX_OF_ACCESS_TRACKER] = swap;

			QuickSort(arr,left,i-1);
			QuickSort(arr,i+1,right);
		}
	}
	// taken from btp500 course notes
	// author of course notes: Catherine Leung
	void QuickSort(CacheTable& arr[][numbuckets_]){
		QuickSort(arr,0,arr.size()-1);
	}
public:
	PCacheHash(const char* fname, int max, double over, double cachecap, int numbuckets) : 
	PermHash(fname,max,over) {
		// create cache
		if (cachecap > 0 numbuckets > 0) {
			// valid value
			cachecap_ = cachecap;
			numbuckets_ = numbuckets;
			cacheEntry_ = new CacheTable[cachecap * max][numbuckets];
		} else {
			// safe empty state
			cachecap_ = numbuckets_ = cacheEntry_ = NULL;
		}
	}
	PCacheHash(const PCacheHash& src) : PermHash(src) {
		if (src.cachecap_ > 0 && numbuckets_ > 0) {
			cachecap_ = src.cachecap_;
			cachecap_ = src.numbuckets_;
			over_ = src.over_;
			cacheEntry_ = new CacheTable<PermHashEntry>[cachecap_ * max_][numbuckets_];
			int indexLevel_, element_;
			for (int cacheHashValue = 0; int level_ = 1; cacheHashValue < maxElementsInCacheTable(); cacheHashValue++) {
				indexLevel_ = ((numbuckets_ * level_) / numbuckets_) - 1;
				element_ = (numbuckets_ % cacheHashValue) - 1;
				cacheEntry[indexLevel_][element_] = src.cacheEntry_[indexLevel_][element_];
				if ( (i + 1) == (numbuckets_ * level_) ) {
						level_++;
				}
			}
		} else {
			cachecap_ = cachecap_ = cacheEntry_ = NULL;
		}
	}
	~PCacheHash() {
		// release memory in the heap
		if (cacheEntry__) delete [] cacheEntry__;
	}
	// find how to implment in inheritance
	PCacheHash& operator=(const PCacheHash& rhs) {
		if (*this != &rhs) {
			// DUPLICATE CHECK
			if (rhs.cachecap_ > 0 && rhs.numbuckets_ > 0) {
			// CHECK RHS INTEGRITY
				cachecap_ = src.cachecap_;
				numbuckets_ = src.numbuckets_;
				cacheEntry_ = new CacheTable<PermHashEntry>[cachecap_ * max_][numbuckets_];
				for (int cacheHashValue = 0; int level_ = 1; cacheHashValue < maxElementsInCacheTable(); cacheHashValue++) {
					indexLevel_ = ((numbuckets_ * level_) / numbuckets_) - 1;
					element_ = (numbuckets_ % cacheHashValue) - 1;

					if (index == numbuckets_ * index) {
					// check if its the multiple of the numbuckets_
						index--;
						element = numbuckets_ - 1;
					} else {
						element = (numbuckets_ % i) - 1; 
					}

					cacheEntry[indexLevel_][element_] = src.cacheEntry_[indexLevel_][element_];
					if ( (i + 1) == (numbuckets_ * level_) ) {
						level_++;
					}
				} // FOR
			} // IF-RHS INTEGRITY
		} /// IF-DUPLICATE CHECK
		return *this;
	}

	// remove the entry with the specified key
	// first search in the cache
	// then regardless of the success of the first attempt
	// check to see if it is able to be removed in the hashtable file
	virtual bool remove(const char* key) {
		bool removeStatus = false;
		if (key) {
		// integrity of key
			int element; // elements per index of the cache table
			int index;   // index of the the cache table
			int cacheHashValue = HashValue(key); // cache hash value of query
			int accessStatusOfRemovedEntry;
			
			index = cacheHashValue / numbuckets_ ;   
			if (index == numbuckets_ * index) {
			// check if its the multiple of the numbuckets_
				index--;
				element = numbuckets_ - 1;
			} else {
				element = (cacheHashValue % numbuckets_) - 1; 
			}
			
			if (cacheEntry_[index][element].accessStatus_ 
			&& cacheEntry_[index][element].data_.key() == key) {
			// check if item is in the entry
				accessStatusOfRemovedEntry = cacheEntry_[index][element].accessStatus_;
				// remove the hash value in the cacheTable
				CacheTable emptyEntry;
				emptyEntry.data_ = dataHolder_;
				emptyEntry.accessStatus_ = 0;
				cacheEntry_[index][element] = emptyEntry;
				// update entries in the cache hashtable
				for (int i = 0; int level = 1; i < maxElementsInCacheTable(); i++) {
					index = ((numbuckets_ * level) / numbuckets_) - 1;
					if (index == numbuckets_ * index) {
					// check if its the multiple of the numbuckets_
						index--;
						element = numbuckets_ - 1;
					} else {
						element = (i % numbuckets_) - 1; 
					}

					if (cacheEntry[index][element].accessStatus) {
						if (cacheEntry[index][element].accessStatus > accessStatusOfRemovedEntry) {
							cacheEntry[index][element].accessStatus -= 1;
						} else {
							cacheEntry[index][element].accessStatus += 1;
						}
					}

					if ( (i + 1) == (numbuckets_ * level) ) {
						level++;
					}
				}
			}// end if-check if item is in the entry
			removeStatus = PermHash::remove(key);
		} // end if-integrity of key
		return removeStatus;
	}

	// finds the key wih the same value of the generic variable holder
	// search first in the in-memory cache then if it is not in the
	// the in-memory cache try the hashtable file
	virtual bool find(const char* key, PCH& holder) {
		bool findStatus = false;
		if (key) {
			int element; // elements per index of the cache table
			int index;   // index of the the cache table
			index = cacheHashValue / numbuckets_ ;   
			if (index == numbuckets_ * index) {
			// check if its the multiple of the numbuckets_
				index--;
				element = numbuckets_ - 1;
			} else {
				element = (cacheHashValue % numbuckets_) - 1; 
			}
			if (cacheEntry_[index][element].data_.key() == key && cacheEntry_[index][element].data_.rec_ == holder) {
				findStatus = true;
				cacheEntry_[index][element].accessStatus = 1;
				// update entire cache table
				findStatus = PermHash::find(key,holder);
				// update entries in the cache hashtable
				for (int i = 0; int level = 1; i < maxElementsInCacheTable(); i++) {
					index = ((numbuckets_ * level) / numbuckets_) - 1;
					if (index == numbuckets_ * index) {
					// check if its the multiple of the numbuckets_
						index--;
						element = numbuckets_ - 1;
					} else {
						element = (i % numbuckets_) - 1; 
					}

					if (cacheEntry[index][element].accessStatus) {
						if (cacheEntry[index][element].accessStatus > accessStatusOfRemovedEntry) {
							cacheEntry[index][element].accessStatus -= 1;
						} else {
							cacheEntry[index][element].accessStatus += 1;
						}
					}

					if ( (i + 1) == (numbuckets_ * level) ) {
						level++;
					}
				}
			} else {
				findStatus = PermHash::find(key,holder);
			}
		}
		return findStatus;
	}
	// retire the least accessed
	virtual bool update(const TYPE& data) {
		bool updateStatus = false;
		// integrity
		if (data) {
			// update perm hashtable
			updateStatus = PermHash::update(data);
			if (updateStatus) {
				int hashValue = HashFunction(data.key());
				// check if 
				// update cachetable
				for (int i = 0; int level = 1; i < maxElementsInCacheTable(); i++) {
					index = ((numbuckets_ * level) / numbuckets_) - 1;
					if (index == numbuckets_ * index) {
					// check if its the multiple of the numbuckets_
						index--;
						element = numbuckets_ - 1;
					} else {
						element = (i % numbuckets_) - 1; 
					}

					if (cacheEntry[index][element].accessStatus) {
						if (cacheEntry[index][element].accessStatus > accessStatusOfRemovedEntry) {
							cacheEntry[index][element].accessStatus -= 1;
						} else {
							cacheEntry[index][element].accessStatus += 1;
						}
					}
					if ( (i + 1) == (numbuckets_ * level) ) {
						level++;
					}
				}
			}
		}
		return updateStatus;	
	}
};