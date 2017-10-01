// Lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <exception>
#include "Dynamic_stack.h"
using namespace std; 


int main()
{
	Dynamic_stack stack;
	Dynamic_stack stack2(20);
	Dynamic_stack stack3(0);
	cout << "Stack 1 size: " << stack.size() << endl << "Capcity: " << stack.capacity() << endl;
	cout << "Stack 2 size: " << stack2.size() << endl << "Capacity: "<< stack2.capacity() << endl;
	cout << "Stack 3 size: " << stack3.size() << endl << "Capacity: " << stack3.capacity() << endl;
	try {
		stack3.top();
	}
	catch (underflow &e)
	{
		cout << "Error: Underflow" << endl;
	}
	stack.push(3);
	stack.push(5);
	stack3.push(1);
	cout << "stack 3 top " << stack3.top() << "stack 3 capacity " << stack3.capacity() << endl;
	stack3.push(4);
	cout << "stack 3 top " << stack3.top() << "stack 3 size " << stack3.size() << "stack 3 capcaity" << stack3.capacity() << endl;
	try {
		stack3.pop();
	}
	catch (underflow &e)
	{
		cout << "Error: Underflow" << endl;
	}

	try {
		cout << stack3.top() << endl;
	}
	catch (underflow &e) {
		cout << "Error: Underflow" << endl;
	}

	try {
		stack3.pop();
	}
	catch (underflow &e)
	{
		cout << "Error: Underflow" << endl;
	}

	try {
		cout << stack3.top() << endl;
	}
	catch (underflow &e) {
		cout << "Error: Underflow" << endl;
	}

	try {
		stack3.pop();
	}
	catch (underflow &e)
	{
		cout << "Error: Underflow" << endl;
	}

	stack3.push(6);
	try {
		cout << stack3.top() << endl;
	}
	catch (underflow &e) {
		cout << "Error: Underflow" << endl;
	}

	stack3.clear();
	cout << stack3.capacity() << " " << stack3.empty() << " " << stack3.size() << " " << endl;
	try {
		cout << stack3.top() << endl;
	}
	catch (underflow &e) {
		cout << "Error: Underflow" << endl;
	}
    return 0;
}

