#include <fstream>
#include <iostream>
#include <vector>
#include "get_data.hpp"
using namespace std;

vector<int> get_data(string path){
    vector<int> data;
    string line;
    ifstream MyFile(path);
    while(getline(MyFile, line)){
        data.push_back(stoi(line));
    }
    return data;
}