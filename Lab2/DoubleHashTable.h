#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H
using namespace std;


/****************************************
 * UW User ID:  jzxhuang
 * Submitted for ECE 250
 * Semester of Submission:  Fall 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):	//constructor, initializes member variables and 2 arrays, sets state to empty for status array	
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {		//destructor... delete arrays
	delete [] array;
	delete [] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {			// return number of elements currently in the hash table	
	return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {		// return the number of bins in the hash table
	return array_size;
}



template<typename T >
bool DoubleHashTable<T >::empty() const {		// return true if the hash table is empty, otherwise false	
	return (count == 0);
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {	// 1st hash function...
	int bin = static_cast<int>(obj);			// cast obj to int and mod with M	
	return (bin % array_size);
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {	// 2nd hash function
	int bin = static_cast<int>(obj);			// cast obj to int, divide by M and mod with M
	bin = (bin/array_size) % array_size;
	if (bin < 0)								// if negative, make positive by adding M (how would this ever happen???)
		bin += array_size;						
	if (bin%2 == 0 && bin != 0)					// if even and not zero, make odd by adding 1					// note... why am I doing this?
		bin++;
	if (bin == 0 && array_state[bin] != EMPTY)	// if even and zero, check if array[0] is occupied or not. if yes, add 1
		bin++;
	return bin;
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
	int probe = h1(obj), initial = h1(obj);
	int offset = h2(obj);
	while (array[probe] == OCCUPIED){			// does deleted count as occupied ... ?							
		if(array[probe] == obj)					// if the object in table matches object passed in, return true
			return true;
		probe = (probe + offset) % array_size;	// otherwise, continue iterating using the double hash function
		if (probe == initial)					// prevent inf loop! if we iterate back to the initial, break... this can happen for full hash tables
			break;
	}	

	return false;
}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {	    // return the object at index n... no error checking required as per the project description  
	return T(array[n]);
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
	 count++;									// increment count
	 if (count == array_size){					// if table is full, throw overflow exception
		 overflow u;
		 throw u;
	 }
	 
	 int probe = h1(obj);
	 int offset = h2(obj);
	 while(array_state[probe] != EMPTY)			// iterate through using double hash function until an empty slot in the table is found
		 probe = (probe + offset) % array_size;
	 array[probe] = obj; 						// insert object into table and set state to OCCUPIED
	 array_state[probe] = OCCUPIED;
	 return ; 
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
	 int probe = h1(obj);
	 int initial = h1(obj);
	 int offset = h2(obj);
	 while(array_state[probe] == OCCUPIED){		// while there is an object at index of probe
		 if(array[probe] == obj && array_state[probe] != DELETED){	// check if the object matches the one to be deleted. ignore if already deleted ( CONFIRM THIS)
			 array_state[probe] == DELETED;		// set state to deleted
			 count--;							// decrement count
			 return true;
		 }
		 probe = (probe + offset) % array_size;	// if no match, iterate through by adding second hash function to probe
		 if (probe == initial)					// if probe = initial value, we have no match and have iterated through the whole table (full). break to prevent inf. loop
			 break;
	 }
	return false;								// if no matches, return false
}

template<typename T >
void DoubleHashTable<T >::clear() {	
	 delete [] array;							// clear table
	 array = new T [array_size];
	 for (int i = 0; i< array_size; i++){		// reset state table to empty
		 array_state[i] = EMPTY;
	 }
	 count = 0;									// reset count to 0
	 return ; 
}

template<typename T >
void DoubleHashTable<T >::print() const {		// I did not use this function
      // enter your implemetation here 	
	return;
}

#endif
