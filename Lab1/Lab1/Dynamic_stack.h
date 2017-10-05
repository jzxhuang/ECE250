/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  jzxhuang@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Fall) 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include <iostream>
using namespace std;


class Dynamic_stack {

	private:
		int *array;
		int count;		
		int array_size;
		int initial_size;
	
	public:
		Dynamic_stack(int = 10);
		~Dynamic_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;
			
		void push( int const & );
		int pop();
		void clear();		
};

Dynamic_stack::Dynamic_stack( int n ):
count( 0 ),
array_size( n ),
initial_size(n)
{
	if (n < 1) {								// if input arg is less than 1, set array size and initial size to 1
		array_size = 1;
		initial_size = 1;
	}
	array = new int[array_size];				// create array of size array_size
}


Dynamic_stack::~Dynamic_stack() {
	delete[] array;								// destructor - delete array
}


int Dynamic_stack::top() const {
	if (this->empty()) {						// if empty, throw underflow eception
		underflow u;
		throw u;
	}
	else
		return  array[count-1];					// otherwise, return top entry of stack
}


int Dynamic_stack::size() const {				// return count which gives the # of elements in the stack
	return  count;
}


bool Dynamic_stack::empty() const {				// return true if the stack is empty, else false
	return (count==0);  
}


int Dynamic_stack::capacity() const {			// return the size of the array
	return array_size;
}


void Dynamic_stack::push( int const &obj ) {
	if (count == array_size) {					// if array is full, double array size
		int* newArr = new int[array_size * 2];	// create new array
		for (int i = 0; i < count; i++)			// copy elements from existing array to new array
			newArr[i] = array[i];
		delete[] array;							//	delete old array and set array member variable to new array
		array = newArr;
		array_size *= 2;						// update member variable array size
	}
	array[count] = obj;							// in all cases, we want to set next array element (array[count]) to the input argument and increment count
	count++;
}


int Dynamic_stack::pop() {
	if (this->empty()) {						// if empty, throw underflow exception
		underflow u;
		throw u;
	}
	else {										// otherwise, return top element of array and delete the top element. decrement count
		int return_pop = array[count - 1];
		array[count-1]=nullptr;
		count--;
		return return_pop;
	}
}

void Dynamic_stack::clear() {
	delete[] array;								//delete the array
	if (array_size != initial_size) {			// if array size does not equal initial size, set array size to equal initial size
		array_size = initial_size;				
	}
	array = new int[array_size];			    // create new empty array of array size
	count = 0;									// reset count to 0
}
#endif
