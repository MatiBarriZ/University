#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>

using namespace std;

int replics = 30;
int iters = 25;
auto start = chrono::high_resolution_clock::now();
auto finish = chrono::high_resolution_clock::now();


void evaluation_insertion_set(unordered_set<long long> &set, double &time, int count, long long key, double** Set, int tElem[], int i){

	start = chrono::high_resolution_clock::now();
	set.insert(key);
	finish = chrono::high_resolution_clock::now();
	time += chrono::duration_cast<chrono::microseconds> (finish - start).count();
    
    for(int k = 0; k < iters; k++){
        if(count <= tElem[k]){
            Set[k][i]=time;
        }
    }
}

void evaluation_searching_set(unordered_set<long long> &set, long long element, double Set[], int i){

    start = chrono::high_resolution_clock::now();
	set.find(element);
	finish = chrono::high_resolution_clock::now();
    Set[i] += chrono::duration_cast<chrono::microseconds> (finish - start).count();

}

void PRINT_OF_INSERT(int tElem[], double** tposet_id, double** tposet_name){
    double temp_one, temp_two;

    double time_set_id[iters];
    double time_set_name[iters];
    for(int i = 0; i<iters; i++){
        for(int j = 0; j<replics; j++){
            temp_one += tposet_id[i][j];
            temp_two += tposet_name[i][j];
        }
        time_set_id[i] = temp_one/replics;
        time_set_name[i] = temp_two/replics;
    }

    cout << "EXPERIMENTAL INSERT EVALUATION WITH KEY: USER_ID " << endl;
    cout << "\n";
	cout << "Inserted \t";
	for(int i = 0; i < iters; i++){
		if(i == iters-1){
		    cout << tElem[i];
	    }
        else{
            cout << tElem[i] << " "<< ',';
        }
	}
    cout << "\n";
    cout << "Value [ms] \t";
    for(int i = 0; i < iters; i++){
		if(i == iters-1){
		    cout << time_set_id[i];
	    }
        else{
            cout << time_set_id[i] << " "<< ',';
        }
	}
    cout << '\n'<< endl;
    
	cout << "EXPERIMENTAL INSERT EVALUATION WITH KEY: USER_NAME " << endl;
    cout << "\n" << endl;
    cout << "Inserted \t";
	for(int i = 0; i < iters; i++){
        if(i == iters-1){
		    cout << tElem[i];
	    }
        else{
            cout << tElem[i] << " "<< ',';
        }
    }
    cout << "\n";
    cout << "Value [ms] \t";
    for(int i = 0; i < iters; i++){
        if(i == iters-1){
		    cout << time_set_id[i];
	    }
        else{
            cout << time_set_id[i] << " "<< ',';
        }
	}
    cout << endl;
}

long long ASCII_NAME_RADIX(string name_user){

    long long ascii_value, name_value, radix;

    for(int i = 5; i>=0 ; i--){
        if (name_user.size() >= i){ 
            ascii_value = name_user[i];
            radix = pow(128, i);
            name_value += ascii_value * radix;
        }
    }
    return name_value;
}

double** CREATE_MATRIX(int n, int m){
	
    double** newMatrix = new double*[n];
    for (int i = 0; i < n; i++){
        newMatrix[i] = new double[m];
    }
    return newMatrix;
}

void DELETE_MATRIX(double** &matrix, int rows){
   
    for(int e = 0; e < rows; e++){
        delete [] matrix[e];
	}
	delete [] matrix;
}

int main(int argc, char* argv[]){

    if(argc != 2){
        cout << "ERROR!! USE " << argv[0] << " <FILENAME> where:\n" <<"<FILENAME> filename to read \n";
        return -1;
    }
    char* filename = argv[1];	
    
    ifstream file;
    
    file.open(filename);
    if(!file.is_open()){
        cout << "ERROR!!! the file " << filename << " could not be opened \n";
        return -1;
    }

    freopen("../results/mainUSET.txt","w",stdout); 

    /* Amount of data */
	int quantity = 26101;
	long long max_id = 0;
	long long min_id = 999999999999999999;

	long long max_name = 0;
	long long min_name = 999999999999999999;

    /* Save items for the experimental evaluation of searching */
	vector<long long> vector_elem_id;
    vector<long long> vector_elem_name;

    /* Save items that don't exist */
	vector<long long> vector_others_v1_id;
	vector<long long> vector_others_v2_id;
	vector<long long> vector_others_v1_name;
	vector<long long> vector_others_v2_name;

    /* Save items for queries on the data found. Allows you to create vectors with keys that do not exist */
	unordered_set<long long> myset_id;
    unordered_set<long long> myset_name;

    /* Time interval between each size and instance */
    double **tposet_id = CREATE_MATRIX(iters,replics);
    double **tposet_name = CREATE_MATRIX(iters,replics);

    /* Evaluation Sizes */
    int tElem[] = {239., 752.,  1240.,  1438.,  2301.,  3140.,  4909., 5782., 7860., 8242., 
       9215., 11125., 12555., 13379., 14065., 15256., 15351., 16644., 18643.,
       19259., 20588., 21321., 22358., 23754., 25560}; //Change variable iters!
    
    /* Data Structs */
 	unordered_set<long long> SET_ID;
	unordered_set<long long> SET_NAME;

    /* Reading data from file */
    string university, user_id, user_name, number_tweets, friends_count, followers_count, created_at;
    long long id_key, name_value;

    while(file.good()){
        
        getline(file, university, ';');
        getline(file, user_id, ';');
        getline(file, user_name, ';');
        getline(file, number_tweets, ';');
        getline(file, friends_count, ';');
        getline(file, followers_count, ';');
        getline(file, created_at, '\n');

        if (university == "university") continue;

        id_key = stoll(user_id, nullptr, 10);
        //cout << "user_name: " << user_name << endl;
        name_value = ASCII_NAME_RADIX(user_name);
        //cout << "name_value: " << name_value << endl;
        vector_elem_id.push_back(id_key);
        myset_id.insert(id_key);

        if(max_id < id_key) max_id = id_key;
        if(min_id > id_key) min_id = id_key;

        vector_elem_name.push_back(name_value);
        myset_name.insert(name_value);
        if(max_name < name_value) max_name = name_value;
        if(min_name > name_value) min_name = name_value;
    }

    file.close();

    /* EXPERIMENTAL EVALUATION INSERTION */

    for(int i = 0; i < replics; i++){
        
        double time_arbol_id = 0.0;
        double time_arbol_name = 0.0;

        for(int j = 0; j < vector_elem_id.size() - 1; j++){
            
            evaluation_insertion_set(SET_ID, time_arbol_id, j, vector_elem_id[j], tposet_id, tElem, i);

            evaluation_insertion_set(SET_NAME, time_arbol_name, j, vector_elem_name[j], tposet_name, tElem, i);
        }
    }

    PRINT_OF_INSERT(tElem, tposet_id, tposet_name);

    /* Delete used matrix */
    DELETE_MATRIX(tposet_id, iters);
    DELETE_MATRIX(tposet_name, iters);

    /* Measuring the size of data structures */

    size_t count1 = 0;
    for (unsigned i = 0; i < SET_ID.bucket_count(); ++i) {
        size_t bucket_size = SET_ID.bucket_size(i);
        if (bucket_size == 0) {
            count1++;
        }
        else {
            count1 += bucket_size;
        }
    }
    size_t count2 = 0;
    for (unsigned i = 0; i < SET_NAME.bucket_count(); ++i) {
        size_t bucket_size = SET_NAME.bucket_size(i);
        if (bucket_size == 0) {
            count2++;
        }
        else {
            count2 += bucket_size;
        }
    }
    cout << "\n";
    cout << "SIZE OF UNORDERED SET WITH USER_ID " << (count1 * sizeof(long long))*pow(10,-3) << "[KB]" << endl;
    cout << "SIZE OF UNORDERED SET WITH USER_NAME " << (count2 * sizeof(long long))*pow(10,-3) << "[KB]" << endl;
    cout << "\n";

    /* A VECTOR IS CREATED WITH ITEMS THAT ARE NOT IN THE DATA */

    /* Vectors with key "User_Id" */
    
	long long temp;
	while(vector_elem_id.size() != vector_others_v1_id.size()){
		temp = vector_elem_id[(long long)rand() % quantity] + (long long)rand();
		if(myset_id.count(temp)==0){
			vector_others_v1_id.push_back(temp);
		}
	}

	while(vector_elem_id.size() != vector_others_v2_id.size()){
		temp = min_id + (long long)rand() % max_id;
		if(myset_id.count(temp)==0){
			vector_others_v2_id.push_back(temp);
		}
	}

    /* Vectors with key "User_Name" */

	while(vector_elem_name.size() != vector_others_v1_name.size()){
		temp = vector_elem_name[(long long)rand() % quantity] + (long long)rand();
		if(myset_name.count(temp)==0){
			vector_others_v1_name.push_back(temp);
		}
	}

	while(vector_elem_name.size() != vector_others_v2_name.size()){
		temp = min_name + (long long)rand() % max_name;
		if(myset_name.count(temp)==0){
			vector_others_v2_name.push_back(temp);
		}
	}

    /* EXPERIMENTAL EVALUATION SEARCH */

    /* Mean of searching */
    int n[25] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000,
              11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000, 21000, 22000, 23000, 24000, 25000};

    srand(time(NULL));
	long long element;

    double tposet_id_existing[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, tposet_name_existing[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    double tposet_id_notexisting_v1[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, tposet_name_notexisting_v1[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    double tposet_id_notexisting_v2[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, tposet_name_notexisting_v2[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    for(int i = 0; i < 25; i++){
        for(int k = 0; k < n[i]; k++){
            /** SEARCHING WITH KEY USER_ID **/

            /* SEARCH EXISTING VALUES */
            element = vector_elem_id[(long long)rand() % quantity];
            evaluation_searching_set(SET_ID, element, tposet_id_existing, i);

            /* SEARCH FOR NON-EXISTENT HIGH VALUES IN THE DATA WITH SIMILAR NUMBERS TO THE RANGE OF EXISTING VALUES */
            element = vector_others_v1_id[(long long)rand() % quantity];
            evaluation_searching_set(SET_ID, element, tposet_id_notexisting_v1, i);

            /* SEARCH FOR SMALL VALUES NOT EXISTING IN THE DATA */
            element = vector_others_v2_id[(long long)rand() % quantity];
            evaluation_searching_set(SET_ID, element, tposet_id_notexisting_v2, i);

            /** SEARCHING WITH KEY USER_NAME **/

            /* SEARCH EXISTING VALUES */
            element = vector_elem_name[(long long)rand() % quantity];
            evaluation_searching_set(SET_NAME, element, tposet_name_existing, i);

            /* SEARCH FOR NON-EXISTENT BIG VALUES IN THE DATA WITH SIMILAR NUMBERS TO THE RANGE OF EXISTING VALUES */
            element = vector_others_v1_name[(long long)rand() % quantity];
            evaluation_searching_set(SET_NAME, element, tposet_name_notexisting_v1, i);

            /* SEARCH FOR SMALL VALUES NOT EXISTING IN THE DATA */
            element = vector_others_v2_name[(long long)rand() % quantity];
            evaluation_searching_set(SET_NAME, element, tposet_name_notexisting_v2, i);
        }
        
        tposet_id_existing[i] /= n[i];
        tposet_id_notexisting_v1[i] /= n[i];
        tposet_id_notexisting_v2[i] /= n[i];

        tposet_name_existing[i] /= n[i];
        tposet_name_notexisting_v1[i] /= n[i];
        tposet_name_notexisting_v2[i] /= n[i];
    }

    cout << "**  EXPERIMENTAL EVALUATION SEARCH WITH KEY USER_ID **" << endl;
    cout << "\n" << endl;
    cout << "Amount of searching ";
    for(int i = 0; i < 25; i++){
        if (i == iters-1){
            cout << n[i];
        }
        else{
            cout << n[i] << " " << ",";
        }
    }
    cout << "\n";
    cout << "Existing value \t \t";
    for(int i = 0; i < 25; i++){
        if (i == iters-1){
            cout << tposet_id_existing[i];
        }
        else{
            cout << tposet_id_existing[i] << " " << ",";
        }
    }
    cout << "\n";
    cout << "Non-existing big values \t";
    for(int i = 0; i < 25; i++){
        if (i == iters-1){
            cout << tposet_id_notexisting_v1[i];
        }
        else{
            cout << tposet_id_notexisting_v1[i] << " " << ",";
        }
    }
    cout << "\n";
    cout << "Non-existing small values \t";
    for(int i = 0; i < 25; i++){
        if (i == iters-1){
            cout << tposet_id_notexisting_v2[i];
        }
        else{
            cout << tposet_id_notexisting_v2[i] << " " << ",";
        }
    }

    cout << "\n";
    cout << "\n";
    cout << "** EXPERIMENTAL EVALUATION SEARCH WITH KEY USER_NAME **" << endl;
    cout << "\n" << endl;

    cout << "Amount of searching \t";
    for(int i = 0; i < 25; i++){
        if (i == iters-1){
            cout << n[i];
        }
        else{
            cout << n[i] << " " << ",";
        }
    }
    cout << "\n";
    cout << "Existing value \t \t";
    for(int i = 0; i < 25; i++){
        if (i == iters-1){
            cout << tposet_name_existing[i];
        }
        else{
            cout << tposet_name_existing[i] << " " << ",";
        }
    }
    cout << "\n";
    cout << "Non-existing big values \t";
    for(int i = 0; i < 25; i++){
        if (i == iters-1){
            cout << tposet_name_notexisting_v1[i];
        }
        else{
            cout << tposet_name_notexisting_v1[i] << " " << ",";
        }
    }
    cout << "\n";
    cout << "Non-existing small values \t";
    for(int i = 0; i < 25; i++){
        if (i == iters-1){
            cout << tposet_name_notexisting_v2[i];
        }
        else{
            cout << tposet_name_notexisting_v2[i] << " " << ",";
        }
    }
    
    cout << "\n";

    return 0;
}
