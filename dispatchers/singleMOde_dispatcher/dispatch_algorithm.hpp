#pragma once

#include <iostream>
#include "../../Parameters.h"
#include "../../algorithms/quick_sort.hpp"
#include "../../algorithms/shell_sort.hpp"
#include "../../algorithms/bucket_sort.hpp"
// Переконайся, що шляхи до цих файлів правильні:
#include "../Structures/singleNode.hpp"
#include "../Structures/doubleNode.hpp"


template <typename T>
void dispatchAlgorithm(T* data, int size) {
    switch(Parameters::algorithm) {
        case Parameters::Algorithms::quick:
            quickSortArray(data, size, Parameters::pivot);
            std::cout<<"Inside \n";
            break;
        case Parameters::Algorithms::shell:
            shellSortArray(data, size, Parameters::shellParameter);
            std::cout<<"Inside Shell\n";
            break;
        case Parameters::Algorithms::bucket:
            bucketArraySort(data, size);
            std::cout<<"Inside Bucket\n";
            break;
        default: 
            std::cerr << "Nie wspierany" << std::endl;
            break;
    }
}


template <typename T>
void dispatchAlgorithm(SingleNode<T>* data, int size) {
    switch(Parameters::algorithm) {
        case Parameters::Algorithms::quick:
            quickSortSingleList(data, Parameters::pivot);
            break;
        case Parameters::Algorithms::shell:
            shellSortSingleList(data, Parameters::shellParameter);
            std::cout<<"Inside single Shell\n";
            break;
        case Parameters::Algorithms::bucket:
            bucketSingleListSort(data); 
            std::cout<<"Inside single Bucket\n";
            break;
        default: 
            std::cerr << "Nie wspierany!" << std::endl;
            break;
    }
}

template <typename T>
void dispatchAlgorithm(DoubleNode<T>* data, int size) {
    switch(Parameters::algorithm) {
        case Parameters::Algorithms::quick:
            quickSortDoubleList(data, Parameters::pivot);
            break;
        case Parameters::Algorithms::shell:
            shellSortDoubleList(data, Parameters::shellParameter);
            break;
        case Parameters::Algorithms::bucket:
            bucketDoubleListSort(data); 
            break;
        default: 
            std::cerr << "Nie wspierany!" << std::endl;
            break;
    }
}