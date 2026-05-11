#pragma once
#include "generation_utils.hpp"
#include "generate_random.hpp"
#include <algorithm>


// Generuje tablicę z losowymi elementami, w której tylko pierwsza połowa 
// zostaje posortowana rosnąco. Druga połowa pozostaje całkowicie losowa.
template <typename T>
void generateHalfSortedArray(T*& arr, int size) {
    generateRandomArray(arr, size);
    std::sort(arr, arr + (size / 2)); 
}


// Generowanie w połowie posortowanej listy jednokierunkowej.
// Podobnie jak w poprzednich plikach, stosujemy podejście z tablicą tymczasową
template <typename T>
void generateHalfSortedSingleList(SingleNode<T>*& head, int size) {
    T* tempArr = nullptr;
    generateHalfSortedArray(tempArr, size);
    head = arrayToSingleList(tempArr, size);
    delete[] tempArr;
}

// Generowanie w połowie posortowanej listy dwukierunkowej, logika taka sama jak dla Single List

template <typename T>
void generateHalfSortedDoubleList(DoubleNode<T>*& head, int size) {
    T* tempArr = nullptr;
    generateHalfSortedArray(tempArr, size);
    head = arrayToDoubleList(tempArr, size);
    delete[] tempArr;
}