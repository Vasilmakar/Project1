#pragma once
#include "../Structures/singleNode.hpp"
#include "../Structures/doubleNode.hpp"
#include <cstdlib>

template<typename T>
T* generateArray(int length, int typeSorted) {
    T* array = new T[length];
    for(int i = 0; i < length; i++) {
        array[i] = static_cast<T>(rand() % length);
    }
    return array;
}

template<typename T>
SingleList<T> generateSingleList(int length, int typeSorted) {
    SingleList<T> list;
    for(int i = 0; i < length; i++) {
        list.push_back(static_cast<T>(rand() % length));
    }
    return list;
}

template<typename T>
DoubleList<T> generateDoubleList(int length, int typeSorted) {
    DoubleList<T> list;
    for(int i = 0; i < length; i++) {
        list.push_back(static_cast<T>(rand() % length));
    }
    return list;
}