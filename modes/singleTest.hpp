#pragma once
#include <iostream>
#include "../Parameters.h"
#include "../algorithms/quick_sort.hpp"
#include <string>
template <typename T>
void runSingleFileTest(std::string path1) {
    std::string path = path1;
    int size = 0; //size danych do sortowania

    switch(Parameters::structure) {
        case Parameters::Structures::array: {
            T* array = nullptr;
           
            get_data(path, array, size); 
            
          
            quickSort(array, size, PivotType::random);
            
            delete[] array; 
            break;
        }
        case Parameters::Structures::singleList: {
            SingleList<T> list;

            get_data(path, list, size);
            
            quickSort(list.head, PivotType::random);
            break;
        }
        case Parameters::Structures::doubleList: {  
            DoubleList<T> list;
            get_data(path, list, size);
            
            quickSort(list.head, PivotType::random);
            break;
        }
    }
}