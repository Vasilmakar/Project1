#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "../Structures/singleNode.hpp"
#include "../Structures/doubleNode.hpp"


 
template <typename T>
void get_data(const std::string& path, T*& arr, int& size) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Blad" << path << std::endl;
        return;
    }

    if (file >> size) {
        if (size <= 0) return;


        arr = new T[size];

        for (int i = 0; i < size; ++i) {
            if (!(file >> arr[i])) {
                size = i; 
                break;
            }
        }
    }
    file.close();
}


template <typename T>
void get_data(const std::string& path, SingleList<T>& list, int& size) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Blad" << path << std::endl;
        return;
    }

    if (file >> size) {
        T value;
        for (int i = 0; i < size; ++i) {
            if (file >> value) {
                list.push_back(value); 
            } else {
                size = i;
                break;
            }
        }
    }
    file.close();
}



template <typename T>
void get_data(const std::string& path, DoubleList<T>& list, int& size) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Blad "<< path << std::endl;
        return;
    }

    if (file >> size) {
        T value;
        for (int i = 0; i < size; ++i) {
            if (file >> value) {
                list.push_back(value);
            } else {
                size = i;
                break;
            }
        }
    }
    file.close();
}