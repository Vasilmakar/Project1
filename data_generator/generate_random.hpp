#pragma once
#include "generation_utils.hpp"
#include <random>


// Generuje tablicę o zadanym rozmiarze i wypełnia ją losowymi wartościami.
// Wykorzystuje 64-bitowy generator Mersenne Twister (std::mt19937_64) zainicjowany 
// ziarnem z std::random_device, co gwarantuje wysokiej jakości pseudolosowość.
template <typename T>
void generateRandomArray(T*& arr, int size) {
    arr = new T[size];
    std::mt19937_64 gen(std::random_device{}()); // 64 bitowy generator
    for (int i = 0; i < size; ++i) {
        arr[i] = generateRandomValue<T>(gen);
    }
}


// Generowanie listy jednokierunkowej z losowymi danymi, tak samo korzystamy z tablicy pomocniczej
template <typename T>
void generateRandomSingleList(SingleNode<T>*& head, int size) {
    T* tempArr = nullptr;
    generateRandomArray(tempArr, size);
    head = arrayToSingleList(tempArr, size);
    delete[] tempArr;
}


// Generowanie listy dwukierunkowej z losowymi danymi, logika taka sama jak dla Single List
template <typename T>
void generateRandomDoubleList(DoubleNode<T>*& head, int size) {
    T* tempArr = nullptr;
    generateRandomArray(tempArr, size);
    head = arrayToDoubleList(tempArr, size);
    delete[] tempArr;
}