#include <iostream>
#include "benchmark.hpp"
#include "../AiZO-P1-sortingAlgorithms/Parameters.h"
#include "../Structures/doubleNode.hpp"
#include "../Structures/singleNode.hpp"

using namespace std;


template <typename T>
struct Form{

    string name;
    T* structure;

    Form(std::string val1, T* val2){
        name = val1;
        structure =val2;
    };
    
};


template<typename T>
void sorting(T form){
    switch(Parameters::Algorithms)
        case Parameters::Algorithms::quick :
            quickSort(form);
}


template<typename T>
T* getForm(){
    srand(time(0));
    int size = Parameters::structureSize;
    T* array(size);
    SingleList<T> singleList;
    DoubleList<T> doubleList;

    switch(Parameters::structure)
        case Parameters::Structures::array : 
        for(int i = 0; i < size; i++){
            array[i] = rand() % size;
        };
        Form form = new Form("Array", array);
        return form;
        
        case Parameters::Structures::singleList :
            for(int i = 0; i < size; i++){
                singleList.push_back(rand() % size);
            };
            Form form = new Form("SingleList", singleList);
            return form;

        case Parameters::Structures::doubleList :
            for(int i = 0; i < size; i++){
                doubleList.push_back(rand() % size);
            };
            Form form = new Form("DoubleList", doubleList);
            return form; 
        return null;
}

template <typename T>
void benchmark(){
    Form form = getForm();
    


    int i = 0

}

