#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "generate_random.hpp"
#include <string>
using namespace std;
void generateData(int length, string name){
    ofstream MyFile(name);
    srand(time(0));
    for(int i = 0; i < length; i++){
        MyFile<<rand() % length<<"\n";
    }
    MyFile.close();
};