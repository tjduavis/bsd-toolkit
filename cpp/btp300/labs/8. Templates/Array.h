/* Templates
 * Workshop 8
 * Array.h
 * Timothy Duavis
 */
 
 #include <cstring>
 
 template <class E = double> //default data type parameter
 class Array {
 	int _size;
 	E* _arr;
 	void init(Array& a) {
		_size = a._size;
		_arr = new E [_size];
		for (int i = 0; i < _size; i++)
			_arr[i] = a._arr[i];
	}
 	public:
 	Array() : _size(0), _arr(NULL) {}
 	Array(int sz) {
		_size = sz;
 		_arr = new E [_size];
	}
	Array(Array& src) { init(src); }
 	~Array() {if (_arr) delete _arr; }
 	Array& operator=(Array& rhs) {
		if (this != &rhs) {
			if (_arr) delete _arr;
			init(rhs);
		}
		return *this;
	}
	inline unsigned int size() const { return _size; }
 	E& operator[] (int i) {
	 	E* dummy = NULL;
		if (i < 0) 
			i = 0;
		else if (i >= _size) {
			dummy = _arr;
		}else {
			dummy = (_arr + i + 1);
		}
			
		return *dummy;
	}
	friend void sort(Array& toSort) {
		E holder;
		for(int j = 0; j < toSort._size; j++) {	
			for(int i = j+1; i < toSort._size; i++) {
				if( toSort._arr[j] > toSort._arr[i] ) {
					holder = toSort._arr[j]; 		//swap
					toSort._arr[j] = toSort._arr[i];
					toSort._arr[i] = holder;
				}
			}
		}
	}
 };