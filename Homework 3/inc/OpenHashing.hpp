#include <string>
#include <list>
#include <iostream>
#include <cmath>
#include <algorithm>

#define DISP -1

#ifndef OPEN_HASHING_HPP
#define OPEN_HASHING_HPP

using namespace std;

class OpenHashing{

public:

	OpenHashing(int size);
	~OpenHashing();
	int get_Capacity();
	int get_Quantity();

	bool search(long long k);
	void eliminate(long long k);
    void insert(long long k);

private:
	list<long long> *table;
	int capacity; 
	int quantity;
	float A = (sqrt(5) - 1) / 2;
    int __iniSize(int size);
	int __divFunction(long long k);
	int __mulFunction(long long k);

};

#endif