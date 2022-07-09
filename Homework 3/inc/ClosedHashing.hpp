#ifndef CLOSED_HASHING_HPP
#define CLOSED_HASHING_HPP

#include <string>
#include <iostream>
#include <cmath>

#define DISP -1
#define ELIM -2

using namespace std;

class ClosedHashing{

public:

	ClosedHashing(int size);
	~ClosedHashing();
	int get_Quantity();
	int get_Capacity();

	int search(long long k);
	void eliminate(long long k);
	void insert(long long k);

private:

	long long* table; 
	int capacity; 
	int quantity;
	float A = (sqrt(5) - 1) / 2;
    int __iniSize(int size);
	int __divFunction(long long k);
	int __mulFunction(long long k);
	int __doubleHashing(long long k,  int i);
	void __resize();
};

#endif