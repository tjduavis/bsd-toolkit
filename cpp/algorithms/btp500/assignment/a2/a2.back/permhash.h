/**
 * Assignment 2
 * 
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio>
#include <string.h>
#include "hashutil.h"
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
	void readInHashEntryAt(int hashValue) {
		hashPointer.seekg(hashValue * sizeof(dataHolder_), ios::beg);
		hashPointer.read((char*)data, sizeof(dataHolder_));
	}
	void writeToHashEntryAt(int hashValue) {
		hashPointer.seekp(hashValue * sizeof(dataHolder_), ios::beg);
		hashPointer.write((char*)data, sizeof(dataHolder_));
	}
	// code structure written by Catherine Leung, Seneca College Professor
	int search(char* key)  {
		int found = -1;
		int hashValue=HashFunction(key);
		this.readInHashEntryAt(hashValue);
		if(dataHolder_){
			if(strcmp(dataHolder_.rec_->key_,key)) {
				// loop stops when we either have searched entire table,
				// find empty space or find a match
				// considering that hashtable can loop from current at end to next current is at beg
				for (bool search = true; int i = hashValue; search && i != hashValue; i++) {
					if (i > this.cap()) { i = 1; }
					this.readInHashEntryAt(i);
					if (dataHolder_ && !dataHolder_.isempty()) {
						if (strcmp(dataHolder_.rec_.key(),key)) {
							search = false;
							found = i;
						}
					} else {
						search = false;
					}
				} //end for
			} //end if
		}
		return found;
	}
	// code structure written by Catherine Leung, Seneca College Professor
	bool isbetween(int rm, int proper, int next) {
		bool isIt = false;
		if (proper < next) {
			if (rm >= proper && rm < next) isIt = true;
		} else if (proper > next) {
			if((rm >= proper && rm < this.cap()) || (rm >=0 && rm < next)) isIt = true;
		}
		return isIt;
	}

protected:
	PermHashEntry<PH> dataHolder;
public:
	// Constructor
	PermHash(const char* fname, int max, double over) {
		max_ = max;
		over_ = over;
		cap_ = (1 + over_) * max_;
		cap_ = nextprime(cap_);
		//build permhash entry
		hashPointer.open(fname,ios::in|ios::out);
		if (!hashPointer.fail) {
			size_ = 0;
			hashPointer.seekg(0,io::beg);
			while(!hashPointer.eof()) {
				hashPointer.read((char*)&dataHolder,sizeof(dataHolder);
				if (dataHolder && !dataHolder.isempty()) { size_++; }
			}
		} else {
			// does not exist create the file
			hashPointer.close();
			hashPointer.open(fname, ios::in|ios::out|ios::app|ios::binary);
			size_ = 0;
		}
	}
	PermHash~() {
		hashPointer.close();
	}
	int cap() const { return cap_; }
	int max() const { return max_; }
	int size() const { return size_; }
	// code structure written by Catherine Leung, Seneca College Professor
	virtual bool remove(const char* key) {
		bool removed = false;
		int rm = this.search(key);
		if (rm != -1) {
			int next = HashFunction(key);
			dataHolder.isempty = true;
			dataHolder.rec = NULL;
			writeToHashEntryAt(rm);
			next + 1 > this.cap() ? next = 1 : next++;
			readInHashEntryAt(next);
			while (dataHolder && !dataHolder.isempty()) {
				int proper=HashFunction(dataHolder.rec.key());
				if (isbetween(rm,proper,next) {
					PermHashEntry<PH> temp = dataHolder;
					readInHashEntryAt(rm);
					dataHolder = temp;
					writeToHashEntryAt(dataHolder);
					dataHolder.data = NULL;
					dataHolder.isempty = true;
					writeToHashEntryAt(next);
					rm=next;
					/*
					*/
				}
				next + 1 > this.cap() ? next = 1 : next++;
				readInHashEntryAt(next);
			} // end while 
		} // end if
		return removed;
	}
	// given the key, find the record with the matching key.
	// If one is found assign it to holder and return a true value.
	// Otherwise return a false value
	virtual bool find(const char* key, TYPE& holder) {
		// structure written by Catherine Leung, Seneca College Professor
		int found = this.search(key);
		if(found!=-1 && key){
			readInHashEntryAt(HashFunction(key));
			holder = dataHolder_.rec_;
		}
		return found != -1 ? true : false;
	}
	virtual bool update(const TYPE& data) {
		bool updateStatus = false;
		if (data) {
			if(this.size() < this.cap()){
				int newHashValue = HashFunction(data.key(),this.cap());
				// loop stops when hits first empty spot or if it reaches same spot
				// considering that hashtable can loop from current at end to next current is at beg
				for (bool search = true; int i = newHashValue; search && i != newHashValue; i++) {
					if (i > this.cap()) { i = 1; }
					readInHashEntryAt(i);
					if (dataHolder_ && dataHolder_.isempty_) {
					// insert into empty entry
						updateStatus = true;
						search = false;
						dataHolder.isempty = false;
						dataHolder.rec = holder;
						writeToHashEntryAt(i);
						size_++;
					} else if (!strcmp(dataHolder_.rec_.key(),key)) {
					// update entry
						updateStatus = true;
						search = false;
						dataHolder_.rec = data;
						writeToHashEntryAt(i);
					}
				} // end for
			} // end if
		}
		return updateStatus;
	}
};