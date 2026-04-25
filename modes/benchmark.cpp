#include <iostream>
#include "../Parameters.h"
#include "../data_generator/generate_random.hpp"
#include "../algorithms/quick_sort.hpp"
#include "Tests/a_test.hpp"
#include "benchmark.hpp"
using namespace std;

template <typename T>
void runStructureTest() {
    int size = Parameters::structureSize;

    switch(Parameters::structure) {
        case Parameters::Structures::array: {
            T* data = generateArray<T>(size, 1);
            for(int i = 0 ; i < Parameters::iterations; i++){
                quickSort(data, 0, size - 1); 
            }
            delete[] data;
            break;
        }
        case Parameters::Structures::singleList: {
            SingleList<T> list = generateSingleList<T>(size, 1);
            quickSort(&list.head); 
            break;
        }
        case Parameters::Structures::doubleList: {
            DoubleList<T> list = generateDoubleList<T>(size, 1);
            quickSort(list.head, list.tail);
            break;
        }
        default:
            cout << "Structure is not supported!\n";
            break;
    }
}

void benchmark() {
    cout << "Starting benchmark for " << Parameters::iterations << " iterations...\n";

    switch(Parameters::dataType) {
        case Parameters::DataTypes::typeInt:
            runStructureTest<int>();
            break;
        case Parameters::DataTypes::typeFloat:
            runStructureTest<float>();
            break;
        case Parameters::DataTypes::typeDouble:
            runStructureTest<double>();
            break;
        default:
            cout << "That type is not implemented yet.\n";
            break;
    };


}