/* Templates
 * Workshop 8
 * Array.h
 * Timothy Duavis
 */
#include "Array.h"

//template<class E>
template<class E>
void Array<E>::init(Array& a) {
	_elements = a._elements;
	_size = a._size;
	_arr = new E [_size];
	for (int i = 0; i < _elements; i++)
		_arr[i] = a._arr[i];
}

template<class E>
Array<E>::Array(E sz) {
	_size = sz;
 	_elements = 0;
 	_arr = new E [_size];
}

template<class E>
Array<E>::Array(Array& src) { init(src); }

template<class E>
Array<E>::~Array() {if (_arr) delete _arr; }

template<class E>
Array<E>& Array<E>::operator=(Array<E>& rhs) {
	if (this != &rhs) {
		if (_arr) delete _arr;
		init(rhs);
	}
}

template<class E>
E& Array<E>::operator[](int i) {
	if (i < 0) 
		i = 0;
	else if (i > _elements)
		i = _elements;
	return _arr[i];
}

template<class E>
void sort(Array<E>& toSort) {
	E holder;
	for(int j = 0; j < toSort._elements; j++) {	
		for(int i = j+1; i < toSort._elements; i++) {
			if( toSort._arr[j] > toSort._arr[i] ) {
				holder = toSort._arr[j]; 		//swap
				toSort._arr[j] = toSort._arr[i];
				toSort._arr[i] = holder;
			}
		}
	}
}