#pragma once
#include "generation_utils.hpp"
#include "generate_random.hpp"
#include <algorithm>


// Generuje tablicę z losowymi elementami, a następnie sortuje je rosnąco, stosując funkcji std::sort
template <typename T>
void generateAscendingArray(T*& arr, int size) {
    generateRandomArray(arr, size);
    std::sort(arr, arr + size);
}


// Funkcja generacji posortowanej rosnąco listy jednokierunkowej
// Najpierw tworzymy posortowaną tablicę pomocniczą, na jej podstawie buduje strukturę listy,
// potem zwalniamy zajętą przez tablicę pamięć
template <typename T>
void generateAscendingSingleList(SingleNode<T>*& head, int size) {
    T* tempArr = nullptr;
    generateAscendingArray(tempArr, size);
    head = arrayToSingleList(tempArr, size);
    delete[] tempArr; // Czyszczenie pamięci po strukturze tymczasowej
}


// Generowanie posortowanej rosnąco listy dwukierunkowej, logika taka sama jak dla Single List
template <typename T>
void generateAscendingDoubleList(DoubleNode<T>*& head, int size) {
    T* tempArr = nullptr;
    generateAscendingArray(tempArr, size);
    head = arrayToDoubleList(tempArr, size);
    delete[] tempArr;
}