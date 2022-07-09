#include "../inc/OpenHashing.hpp"

/* Open Hashing Class Definition */

OpenHashing::OpenHashing(int size){
    int tam = __iniSize(size);
	capacity = tam;
    table = new list<long long>[capacity];
}

OpenHashing::~OpenHashing(){
	delete [] table;
}

int OpenHashing::get_Quantity(){
	return quantity;
}

int OpenHashing::get_Capacity(){
	return capacity;
}

/* Open Hashing Methods Definitions */

bool OpenHashing::search(long long k){

    int slot = __divFunction(k);

    list<long long> :: iterator it;
    for(it = table[slot].begin(); it != table[slot].end(); it++){
        if (*it == slot) return true;
    }
    return false;
}

void OpenHashing::eliminate(long long k){

    int slot = __divFunction(k);

    list<long long> :: iterator it;
    for(it = table[slot].begin(); it != table[slot].end(); it++){
        if (*it == slot) break;
    }
    
    if (it != table[slot].end()){ 
        table[slot].erase(it); 
    }
}

void OpenHashing::insert(long long k){

    long long slot = __divFunction(k);
    table[slot].push_front(k);

	quantity++;
}

/* Open Hashing Other Methods Definitions */

int OpenHashing::__iniSize(int size){

    int value = 1.3 * size;
    bool prime = true;
    int i = 0;

    for(int i = 2; i<value && prime == true; i++){
        if (value % i == 0) prime = false;
    }

    while (prime == false){
        value++;
        bool flag = false;
        for(int i = 2; i<value && flag == false; i++){
            if (value % i == 0) flag = true; 
        }
        if (flag == false) prime = true; 
    }
    return value;
}

int OpenHashing::__divFunction(long long k){
  return k%capacity;
}

int OpenHashing::__mulFunction(long long k) {
  double a = (double)k*A;
  a -= (long long)a;

  return capacity*a;
}
