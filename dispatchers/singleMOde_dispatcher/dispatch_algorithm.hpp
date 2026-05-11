#pragma once

#include <iostream>
#include "Parameters.h"
#include "algorithms/quick_sort.hpp"
#include "algorithms/shell_sort.hpp"
#include "algorithms/bucket_sort.hpp"
#include "Structures/singleNode.hpp"
#include "Structures/doubleNode.hpp"
#include <chrono>
#include "Structures/queue.hpp"
#include "Structures/binaryTree.hpp"



// Funkcje do uruchamianie algorytmów sortowania i mierzenia czasu
// Dla każdej struktury realizowana jest logika wyboru algorytmu w zależności 
// od wskazanych parametrów

// Funckja dla tablicy
template <typename T>
double dispatchAlgorithm(T* data, int size) {
    double iterationTime = 0.0;
auto start = std::chrono::high_resolution_clock::now();
auto end = start;    
switch(Parameters::algorithm) {
        case Parameters::Algorithms::quick:

             start = std::chrono::high_resolution_clock::now();

            quickSortArray(data, size, Parameters::pivot);

            end = std::chrono::high_resolution_clock::now();
            

            break;

        case Parameters::Algorithms::shell:

            start = std::chrono::high_resolution_clock::now();

            shellSortArray(data, size, Parameters::shellParameter);

            end = std::chrono::high_resolution_clock::now();

            break;

        case Parameters::Algorithms::bucket:

            start = std::chrono::high_resolution_clock::now();

            bucketArraySort(data, size);

            end = std::chrono::high_resolution_clock::now();

            break;

        default: 
            std::cerr << "Algorytm nie jest wspierany dla tablicy!" << std::endl;
            break;
    }
    std::chrono::duration<double, std::milli> elapsed = end - start;
    iterationTime = elapsed.count();
     return iterationTime;
}


// Przeciążenie dla listy jednokierunkowej
template <typename T>
double dispatchAlgorithm(SingleNode<T>* data, int size) {
    double iterationTime = 0.0;
auto start = std::chrono::high_resolution_clock::now();
auto end = start;    switch(Parameters::algorithm) {
        case Parameters::Algorithms::quick:

            start = std::chrono::high_resolution_clock::now();

            quickSortSingleList(data, Parameters::pivot);

            end = std::chrono::high_resolution_clock::now();

            break;

        case Parameters::Algorithms::shell:

            start = std::chrono::high_resolution_clock::now();

            shellSortSingleList(data, Parameters::shellParameter);

            end = std::chrono::high_resolution_clock::now();

            break;

        case Parameters::Algorithms::bucket:

            start = std::chrono::high_resolution_clock::now();

            bucketSingleListSort(data); 

            end = std::chrono::high_resolution_clock::now();

            break;

        default: 
            std::cerr << "Algorytm nie jest wspierany dla listy jednokierunkowej!" << std::endl;
            break;
    }
    std::chrono::duration<double, std::milli> elapsed = end - start;
    iterationTime = elapsed.count();
     return iterationTime;
}


// Przeciążenie dla listy dwukierunkowej
template <typename T>
double dispatchAlgorithm(DoubleNode<T>* data, int size) {
    double iterationTime = 0.0;
auto start = std::chrono::high_resolution_clock::now();
auto end = start;    
switch(Parameters::algorithm) {
        case Parameters::Algorithms::quick:

            start = std::chrono::high_resolution_clock::now();

            quickSortDoubleList(data, Parameters::pivot);

            end = std::chrono::high_resolution_clock::now();
    
            break;

        case Parameters::Algorithms::shell:

            start = std::chrono::high_resolution_clock::now();

            shellSortDoubleList(data, Parameters::shellParameter);

            end = std::chrono::high_resolution_clock::now();
            
        
            break;

        case Parameters::Algorithms::bucket:

            start = std::chrono::high_resolution_clock::now();

            bucketDoubleListSort(data); 

            end = std::chrono::high_resolution_clock::now();
            

            break;

        default: 
            std::cerr << "Algorytm nie jest wspierany dla listy dwukierunkowej!" << std::endl;
            break;
    }
    std::chrono::duration<double, std::milli> elapsed = end - start;
    iterationTime = elapsed.count();
     return iterationTime;
}

// Przeciążenie dla struktury kolejki, implementacja tzlko dla Quick Sort
// ze względu na specyfike dostępu do elementów
template <typename T>
double dispatchAlgorithm(CustomQueue<T>* data, int size) {
    double iterationTime = 0.0;
auto start = std::chrono::high_resolution_clock::now();
auto end = start;    
    switch(Parameters::algorithm) {
        case Parameters::Algorithms::quick:
            start = std::chrono::high_resolution_clock::now();

            quickSortQueue(data);

            end = std::chrono::high_resolution_clock::now();
            break;

        default: 
            std::cerr << "Ten algorytm nie jest wspierany dla kolejki!" << std::endl;
            break;
    }
    
    std::chrono::duration<double, std::milli> elapsed = end - start;
    iterationTime = elapsed.count();
    return iterationTime;
};


// Funckja sortowania dla struktury Binary Tree
// W przypadku tej struktury ignorujemy Parameters::algorithm,
// ponieważ to struktura, sortowanie której następuje w momencie tworzenia
template <typename T>
double dispatchAlgorithmTree(T* data, int size) {
    double iterationTime = 0.0;
auto start = std::chrono::high_resolution_clock::now();
auto end = start;
    
    start = std::chrono::high_resolution_clock::now();

    // Inicjalizacja pustego drzewa
    BinaryTree<T> tree;
    
    // Sortowanie odbywa się w tle podczas wstawiania kolejnych elementów
    for(int i = 0; i < size; i++) {
        tree.insert(data[i]);
    }
    
    // Odczyt posortowanych elementów nadpisanie początkowej tablicy
    int index = 0;
    tree.inOrderToArray(tree.root, data, index);

    end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = end - start;
    iterationTime = elapsed.count();
    return iterationTime;
};