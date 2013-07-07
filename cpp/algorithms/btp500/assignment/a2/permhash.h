/**
 * Assignment 2
 * 
 */

#include <fstream>
#include <stdio>
#include "hashutil.h"

#define ON 1
#define OFF 0
#define TEST1 2
#define TEST2 3
#define DEBUG OFF

using namespace std;

template<class PH>
struct PermHashEntry {
	bool isempty;
	PH rec;
};

template<class PH>
class PermHash {
	int cap_;
	int max_;
	int size_;
	double over_;
	fstream hashPointer;
	void readInHashEntryAt(int hashValue);
	void writeToHashEntryAt(int hashValue);
	int search(const char* key);
	bool isbetween(int rm, int proper, int next);
protected:
	PermHashEntry<PH> dataHolder;
public:
	PermHash(const char* fname, int max, double over);
	~PermHash();
	int cap() const;
	int max() const;
	int size() const;
	virtual bool remove(const char* key);
	virtual bool find(const char* key, PH& holder);
	virtual bool update(const PH& data);
};

template <class PH>
void PermHash<PH>::readInHashEntryAt(int hashValue) {
	hashPointer.seekg(sizeof(int),ios::beg);
	hashPointer.seekg(hashValue > 0 ? hashValue * sizeof(dataHolder) : sizeof(dataHolder), ios::cur);
	hashPointer.read((char*)&dataHolder, sizeof(dataHolder));
};
template <class PH>
void PermHash<PH>::writeToHashEntryAt(int hashValue) {
	hashPointer.seekp(sizeof(int),ios::beg);
	hashPointer.seekp(hashValue > 0 ? hashValue * sizeof(dataHolder) : sizeof(dataHolder), ios::cur);
	hashPointer.write((char*)&dataHolder, sizeof(dataHolder));
};
// code structure written by Catherine Leung, Seneca College Professor
template <class PH>
int PermHash<PH>::search(const char* key)  {
	int found = -1;
	int hashValue=HashFunction(key,cap());
	
	#if DEBUG == TEST1
	cout << "search::start_ parameter key = " << key << endl;
	//getchar();
	#endif

	#if DEBUG == TEST1
	if (strcmp(key,"aback") == 0) {
		cout << "\tsearch:: [hashvalue= " << hashValue << "]" << endl;
		//getchar();
	}
	#endif
	
	readInHashEntryAt(hashValue);
	
	#if DEBUG == ON
	cout << "\tsearch:: testing my dataHolder's empty flag = " << dataHolder.isempty << endl;
	cout << "\tsearch:: testing my read dataHolder's key = " << dataHolder.rec.key() << endl;
	#endif
	
	if (!dataHolder.isempty) {
		if(strcmp(dataHolder.rec.key(),key) == 0) {
			found = hashValue;
		} else {
			// loop stops when we either have searched entire table,
			// find empty space or find a match
			// considering that hashtable can loop from current at end to next current is at beg
			bool keepSearching = true;
			int i = hashValue + 1; // next entry
			for (; keepSearching && i != hashValue; i++) {
				if (i > cap()) { i = 0; } // check if i will reach last entry
				readInHashEntryAt(i);
				if (!dataHolder.isempty) {
					if (strcmp(dataHolder.rec.key(),key) == 0) {
						keepSearching = false;
						found = i;
					}
				} else {
					keepSearching = false;
				}
			} //end for
		}
	}
	
	#if DEBUG == TEST2
	if (strcmp("aback",key)==0) {
	cout << "search::end_ return call = " << found << endl;
	// getchar();
	}
	#endif
	
	return found;
};
// code structure written by Catherine Leung, Seneca College Professor
template <class PH>
bool PermHash<PH>::isbetween(int rm, int proper, int next) {
	bool isIt = false;
	if (proper < next) {
		if (rm >= proper && rm < next) isIt = true;
	} else if (proper > next) {
		if((rm >= proper && rm < cap()) || (rm >=0 && rm < next)) isIt = true;
	}
	return isIt;
}

template <class PH>
PermHash<PH>::PermHash(const char* fname, int max, double over) {
	max_ = max;
	over_ = over;
	cap_ = (1 + over_) * max_;
	cap_ = nextprime(cap_);
	//build permhash entry
	hashPointer.open(fname,ios::in|ios::out|ios::binary);
	int sizeOfFile;
	bool nodata = false;
	if (!hashPointer.fail()) {
		hashPointer.seekg(0,ios::end);
		sizeOfFile=hashPointer.tellg();
		hashPointer.seekg(0,ios::beg);
		if (sizeOfFile==0) nodata = true;
	} else {
		hashPointer.clear();
		hashPointer.open(fname,ios::in|ios::out|ios::binary|ios::trunc);
		nodata = true;
	}
	if (nodata) {
		// build hash file
		dataHolder.isempty = true;
		size_ = 0;
		hashPointer.seekg(0, ios::beg);
		hashPointer.write((char*)&size_,sizeof(int));
		hashPointer.write((char*)&max_,sizeof(int));
		hashPointer.write((char*)&cap_,sizeof(int));
		for (int i = 0; i < cap(); i++) {
			writeToHashEntryAt(i+1);
		}
	} else {
		// re-set perm hash values from file
		hashPointer.seekg(0, ios::beg);
		hashPointer.read((char*)&size_,sizeof(int));
		hashPointer.read((char*)&max_,sizeof(int));
		hashPointer.read((char*)&cap_,sizeof(int));
	}

};
template <class PH>
PermHash<PH>::~PermHash() {
	if (hashPointer.is_open()) {
		hashPointer.seekg(0, ios::beg);
		hashPointer.write((char*)&size_,sizeof(int));
		hashPointer.close();
	}
};
template <class PH>
int PermHash<PH>::cap() const { return cap_; }
template <class PH>
int PermHash<PH>::max() const { return max_; }
template <class PH>
int PermHash<PH>::size() const { return size_; }
// code structure written by Catherine Leung, Seneca College Professor
template <class PH>
bool PermHash<PH>::remove(const char* key) {
	bool removed = false;
	int rm = search(key);
	if (rm != -1) {
		int next = rm;
		dataHolder.isempty = true;
		writeToHashEntryAt(rm);
		next > cap() ? next = 0 : next++;
		readInHashEntryAt(next);
		while (!dataHolder.isempty) {
			int proper=HashFunction(dataHolder.rec.key(),cap());
			if (isbetween(rm,proper,next)) {
				PermHashEntry<PH> temp = dataHolder;
				readInHashEntryAt(rm);
				dataHolder = temp;
				writeToHashEntryAt(rm);
				dataHolder.isempty = true;
				writeToHashEntryAt(next);
				rm=next;
			}
			next + 1 > cap() ? next = 0 : next++;
			readInHashEntryAt(next);
		} // end while 
		removed = true;
		size_--;
	} // end if
	return removed;
};
// given the key, find the record with the matching key.
// If one is found assign it to holder and return a true value.
// Otherwise return a false value
// code structure written by Catherine Leung, Seneca College Professor
template <class PH>
bool PermHash<PH>::find(const char* key, PH& holder) {
	bool findStatus = false;
	#if DEBUG == TEST1
	cout << "find::start_ parameter (key) = " << key << endl;
	cout << "find::start_ parameter (holder) = " << holder << endl;
	//getchar();
	#endif
	int found = search(key);

	#if DEBUG == ON
	if (strcmp(key,"aback") == 0) {
		cout << "in find" << found << endl;
		cout << "****************************************" << endl
	}
	#endif

	if(found!=-1){
		readInHashEntryAt(found);
		holder = dataHolder.rec;
		findStatus = true;
	}

	#if DEBUG == ON
	if (strcmp(key,"of") == 0)
		cout << "findStatus == " << findStatus << endl;
	#endif

	#if DEBUG == TEST1
	cout << "find::end_ return call = " << findStatus << endl;
	getchar();
	#endif
	return findStatus;
};
template <class PH>
bool PermHash<PH>::update(const PH& data) {
	bool updateStatus = false;

	#if DEBUG == TEST2
	if (strcmp(data.key(),"injustice")==0) {
		cout << "\tupdate::start_ parameter" << endl;
		cout << "\tdata.key = " << data.key() << endl;
		cout << "\tdata's hashvalue = " << HashFunction(data.key(),cap()) << endl;
	//getchar();
	}
	#endif

	#if DEBUG == TEST2
	if (strcmp(data.key(),"injustice")==0) {
	readInHashEntryAt(HashFunction(data.key(),cap()));
	cout << "\t\tupdate:: dataHolder value before process" << endl;
	cout << "\t\t\tdataHolder.rec.key() = " << "[" << dataHolder.rec.key() << "]" << endl;
	cout << "\t\t\t" << dataHolder.rec.key() << " = " << HashFunction(dataHolder.rec.key(),cap()) << endl;
	cout << "************************************" << endl;
	cout << dataHolder.rec << endl;
	cout << "************************************" << endl;
	}
	#endif

	if(size() < max()) {
		int newHashValue = HashFunction(data.key(),cap());
		// loop stops when hits first empty spot or if it reaches same spot
		// considering that hashtable can loop from current at end to next current is at beg
		int i = newHashValue;
		readInHashEntryAt(i);
		if (dataHolder.isempty) {

			#if DEBUG == TEST2
			if (strcmp(data.key(),"injustice")==0)
			cout << "\n\t\t\tupdate:: inserted into empty spot @ hash value = " << i << endl;
			#endif

			#if DEBUG == TEST2
			if (strcmp(data.key(),"injustice")==0) {
			cout << "\n\t\t\tupdate:: dataHolder = " << endl;
			cout << "******************************" << endl;
			cout << dataHolder.rec << endl;
			cout << "******************************" << endl;
			}
			#endif

			dataHolder.rec = data;
			dataHolder.isempty = false;
			updateStatus = true;
			writeToHashEntryAt(i);

			size_++;
		} else if (strcmp(dataHolder.rec.key(),data.key())==0) {
			updateStatus = true;
			dataHolder.rec = data;
			writeToHashEntryAt(i);

			#if DEBUG == TEST2
			if (strcmp(data.key(),"injustice")==0)
			cout << "\n\t\t\tupdate:: updated1 into empty spot @ hash value = " << i << endl;
			#endif

		} else {
			bool keepgoing = true;
			i++; // next entry
			while (keepgoing) {
				if (i > cap()) i = 0;
				if (i == newHashValue) {
					keepgoing = false;
				} else {
					readInHashEntryAt(i);

					#if DEBUG == TEST2
					if (strcmp(data.key(),"injustice")==0) {
					cout << "\n\t\t\tupdate:: dataHolder @ hashValue = " << i << endl;
					cout << "******************************" << endl;
					cout << dataHolder.rec << endl;
					cout << "******************************" << endl;
					}
					#endif

					if (dataHolder.isempty) {
						
						#if DEBUG == TEST2
						if (strcmp(data.key(),"injustice")==0)
						cout << "\n\t\t\tupdate:: next empty spot @ hash value = " << i << endl;
						#endif

						updateStatus = true;
						keepgoing = false;
						dataHolder.isempty = false;
						dataHolder.rec = data;
						writeToHashEntryAt(i);				
						size_++;
					} else if (strcmp(dataHolder.rec.key(),data.key()) == 0) {
						updateStatus = true;
						keepgoing = false;
						dataHolder.rec = data;
						writeToHashEntryAt(i);

						#if DEBUG == TEST2
						if (strcmp(data.key(),"injustice")==0)
						cout << "\n\t\t\tupdate2:: updated an entry @ hash value = " << i << endl;
						#endif
					}
				}
				if (keepgoing) i++;
			} // end while
		} // end if
	}

	#if DEBUG == TEST2
	if (strcmp(data.key(),"injustice")==0) {
	cout << "\t\tupdate:: dataHolder value after process" << endl;
	cout << "\t\tupdate:: dataHolder.rec" << endl;
	cout << "\t\tupdate:: dataHolder.rec.key() " << dataHolder.rec.key() << endl;
	cout << "hashvalue = " << HashFunction(dataHolder.rec.key(),cap()) << endl;
	cout << "*******************************************" << endl;
	cout << dataHolder.rec << endl;
	cout << "*******************************************" << endl;
	//cout << "\t\tdataHolder.rec.key() = " << "[" << dataHolder.rec.key() << "]" << endl;
	cout << "\n\t\tupdate:: size = " << size() << "\n" << endl;
	}
	#endif

	#if DEBUG == TEST2
	if (strcmp(data.key(),"injustice")==0)
	cout << "\tupdate::end_ return call = " << updateStatus << endl;
	//getchar();
	#endif

	return updateStatus;
};