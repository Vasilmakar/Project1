// #include <fstream>
// #include <iostream>
// #include <vector>
// #include "get_data.hpp"
// using namespace std;

// vector<int> get_data(string path){
//     vector<int> data;
//     string line;
//     ifstream MyFile(path);
//     getline(MyFile, line);
//     int count = stoi(line);
//     while (data.size() < count && getline(MyFile, line)) {
//         if (!line.empty()) { 
//             data.push_back(stoi(line));
//         }
//     }
    
//     if (data.size() < count) {
//         cout << "File has only" << data.size() << " numbers " << count << " requested.\n";
//     }

//     return data;
// }