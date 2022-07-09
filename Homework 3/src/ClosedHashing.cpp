#include "../inc/ClosedHashing.hpp"

ClosedHashing::ClosedHashing(int size){
    int tam = __iniSize(size);
	capacity = tam;
	quantity = 0;
	table = new long long[capacity];
	for(int i = 0; i < capacity; i++) table[i] = DISP;
}

ClosedHashing::~ClosedHashing(){
	delete [] table;
}

int ClosedHashing::get_Quantity(){
	return quantity;
}

int ClosedHashing::get_Capacity(){
	return capacity;
}

int ClosedHashing::search(long long k){

	int pos;	
	pos = __doubleHashing(k, 0);
	int i = 1;

    if (table[pos] == k){
        return pos;
    }

	while(table[pos] != DISP & table[pos] != ELIM){        
		pos = __doubleHashing(k+i, i); 
        i++;
        if (table[pos] == k){
            return pos;
        }
	}
	return DISP;
}

void ClosedHashing::eliminate(long long k){

	int pos;	
    bool flag = false;
	pos = __doubleHashing(k, 0);
	int i = 1;

    if (table[pos] == k){
        cout << "El elemento " << table[pos] << " fue ELIMINADO del indice: " << pos << endl;
        table[pos] = DISP;
        cout << "Nueva casilla: " << table[pos] << endl;
        flag = true;
    }

	while(table[pos] != DISP & table[pos] != ELIM){        
		pos = __doubleHashing(k+i, i); 
        i++;
        if (table[pos] == k){
            cout << "El elemento " << table[pos] << " fue ELIMINADO del indice: " << pos << endl;
            table[pos] = ELIM;
            cout << "Nueva casilla: " << table[pos] << endl;
            flag = true;
            break;
        }
	}
    if (flag == false) cout << "El elemento no se encuentra en la tabla" << endl; 
}

void ClosedHashing::insert(long long k){
    float fc = 0.7;
	if((float)quantity/(float)capacity > fc){	
        __resize();
	}

	int pos;	
	pos = __doubleHashing(k, 0);
	int i = 1;

	while(table[pos] != DISP & table[pos] != ELIM){
		pos = __doubleHashing(k+i, i);
		i++;
	}
	table[pos] = k;
	quantity++;
}

int ClosedHashing::__iniSize(int size){

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

void ClosedHashing::__resize(){

	long long aux[capacity];
    int temp = capacity;

	for(int i = 0; i < capacity; i++) aux[i] = table[i];
	
	capacity *= 2;
    capacity = __iniSize(capacity);

	table = new long long[capacity];
	for(int i = 0; i < capacity; i++){
		table[i] = DISP;
	}
	
	quantity = 0;


	for(int i = 0; i < temp; i++){
		if(aux[i] != DISP){
			insert(aux[i]);
		}
	}	
}

int ClosedHashing::__divFunction(long long k) {
  return k%capacity;
}

int ClosedHashing::__mulFunction(long long k) {
  double a = (double)k*A;
  a -= (long long)a;

  return capacity*a;
}

int ClosedHashing::__doubleHashing(long long k,  int i) {
    return (__divFunction(k) + i*(__divFunction(k)+1)) % capacity;
}

