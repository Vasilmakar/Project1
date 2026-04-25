#pragma once

#include <iostream>
#include "../../Parameters.h"
#include "dispatch_algorithm.hpp"
#include "../../data/save_data.hpp"

template <typename T>
void dispatchStructure(std::string path) {
    int size = 0;

    switch(Parameters::structure) {
        case Parameters::Structures::array: {
            T* array = nullptr;
            get_data(path, array, size);
            dispatchAlgorithm(array, size);
            std::cout << "do pliku" << std::endl;
            save_data_array(Parameters::outputFile, array, size);
            delete[] array;
            break;
        }
        case Parameters::Structures::singleList: {
            SingleList<T> list;
            get_data(path, list, size);
                         std::cout << "В structure" << std::endl;
            dispatchAlgorithm(list.head, size); 
             std::cout << "do pliku" << std::endl;
            save_data_single(Parameters::outputFile, list.head);
            break;
        }
        case Parameters::Structures::doubleList: {
            DoubleList<T> list;
            get_data(path, list, size);
            dispatchAlgorithm(list.head, size);
            save_data_double(Parameters::outputFile, list.head);
            break;
        }
        default: 
        std::cerr << "Not supported" << std::endl;
        break;
    }
}