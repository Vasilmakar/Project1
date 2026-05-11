#pragma once
#include "generation_utils.hpp"
#include "generate_random.hpp"
#include <algorithm>


// Generuje tablicę z losowymi elementami, a następnie sortuje je malejąco.
// Zmiana kierunku sortowania odbywa się poprzez przekazanie komparatora std::greater<T>().
template <typename T>
void generateDescendingArray(T*& arr, int size) {
    generateRandomArray(arr, size);
    std::sort(arr, arr + size, std::greater<T>()); 
}


// Generowanie posortowanej malejąco listy jednokierunkowej.
// Najpierw tworzymy posortowaną tablicę pomocniczą, na jej podstawie buduje strukturę listy,
// potem zwalniamy zajętą przez tablicę pamięć  
template <typename T>
void generateDescendingSingleList(SingleNode<T>*& head, int size) {
    T* tempArr = nullptr;
    generateDescendingArray(tempArr, size);
    head = arrayToSingleList(tempArr, size);
    delete[] tempArr;
}

// Generowanie posortowanej malejąco listy dwukierunkowej, logika taka sama jak dla Single List
template <typename T>
void generateDescendingDoubleList(DoubleNode<T>*& head, int size) {
    T* tempArr = nullptr;
    generateDescendingArray(tempArr, size);
    head = arrayToDoubleList(tempArr, size);
    delete[] tempArr;
}