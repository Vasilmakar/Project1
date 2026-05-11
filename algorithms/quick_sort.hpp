#pragma once
#include <vector>
#include <iostream>
#include "Parameters.h"
#include "Structures/singleNode.hpp"
#include "Structures/doubleNode.hpp"
#include <algorithm>
#include <cstdlib>
#include "Structures/queue.hpp"


//(Dla Badania Alpha)


//Funckja poszukiwania węzła pewniącego rolę pivota 
template <typename NodePtr>
NodePtr getPivotNode(NodePtr low, NodePtr high, Parameters::Pivots type) {
    if (type == Parameters::Pivots::left) return low; 
    if (type == Parameters::Pivots::right || low == high) return high;

    int length = 0;
    NodePtr temp = low;
    while (temp != nullptr && temp != high->next) {
        length++;
        temp = temp->next;
    }

    int targetIndex = 0;
    if (type == Parameters::Pivots::middle) {
        targetIndex = length / 2;
    } else if (type == Parameters::Pivots::random) {
        targetIndex = rand() % length;
    }

    temp = low;
    for (int i = 0; i < targetIndex; i++) {
        temp = temp->next;
    }
    return temp;
}



//QuickSort dla tablicy

//Podział tablicy w zależności od Parameters::pivot
template <typename T>
int partitionArray(T* arr, int low, int high, Parameters::Pivots type) {
    // pivot
    int pivotIndex = high; // domyślnie prawy
    
    if (type == Parameters::Pivots::left) {
        pivotIndex = low;
    } else if (type == Parameters::Pivots::middle) {
        pivotIndex = low + (high - low) / 2;
    } else if (type == Parameters::Pivots::random) {
        pivotIndex = low + rand() % (high - low + 1);
    }

    std::swap(arr[pivotIndex], arr[high]);
    T pivot = arr[high];

   
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1; // Zwraca ostateczną pozycję pivota
}


template <typename T>
void quickSortRecursiveArray(T* arr, int low, int high, Parameters::Pivots type) {
    if (low < high) {
        int pi = partitionArray(arr, low, high, type);
        quickSortRecursiveArray(arr, low, pi - 1, type);
        quickSortRecursiveArray(arr, pi + 1, high, type);
    }
}

// Główna funkcja wywołująca QuickSort dla tablicy
template <typename T>
void quickSortArray(T* arr, int n, Parameters::Pivots type) {
    if (n > 1) {
        quickSortRecursiveArray(arr, 0, n - 1, type);
    }
}


//Quick Sort dla listy dwukierunkowej


// Podział listy dwukierunkowej na wzór schematu Lomuto.
// Zamianie ulegają wyłącznie wartości (data), dzięki czemu
// nie trzeba przepinać wskaźników (next, prev).
template <typename T>
DoubleNode<T>* partitionDouble(DoubleNode<T>* low, DoubleNode<T>* high, Parameters::Pivots type) {
    DoubleNode<T>* pivotNode = getPivotNode(low, high, type);
    std::swap(pivotNode->data, high->data);
    
    T pivot = high->data;
    DoubleNode<T>* i = low->prev;

    // Lomuto
    for (DoubleNode<T>* j = low; j != high; j = j->next) {
        if (j->data <= pivot) {
            i = (i == nullptr) ? low : i->next;
            std::swap(i->data, j->data);
        }
    }
    i = (i == nullptr) ? low : i->next;
    std::swap(i->data, high->data);
    return i;
}

template <typename T>
void quickSortRecursiveDouble(DoubleNode<T>* low, DoubleNode<T>* high, Parameters::Pivots type) {
    if (high != nullptr && low != high && low != high->next) {
        DoubleNode<T>* pi = partitionDouble(low, high, type);
        quickSortRecursiveDouble(low, pi->prev, type);
        quickSortRecursiveDouble(pi->next, high, type);
    }
}

// Główna funkcja wywołująca QuickSort dla listy dwukierunkowej
template <typename T>
void quickSortDoubleList(DoubleNode<T>* head, Parameters::Pivots type) {
    if (head == nullptr || head->next == nullptr) return;
    
    DoubleNode<T>* tail = head;
    while (tail->next != nullptr) tail = tail->next;
    
    quickSortRecursiveDouble(head, tail, type);
}


//Qiuck Sort dla listy jednokierunkowej

//Logika podobna do tej dla double list
template <typename T>
SingleNode<T>* partitionSingle(SingleNode<T>* low, SingleNode<T>* high, Parameters::Pivots type) {
    SingleNode<T>* pivotNode = getPivotNode(low, high, type);
    std::swap(pivotNode->data, high->data);

    T pivot = high->data;
    SingleNode<T>* i_node = low;

    // 2.podzial Lomuto
    for (SingleNode<T>* j = low; j != high; j = j->next) {
        if (j->data < pivot) {
            std::swap(i_node->data, j->data);
            i_node = i_node->next;
        }
    }
    std::swap(i_node->data, high->data);
    return i_node;
}

template <typename T>
void quickSortRecursiveSingle(SingleNode<T>* low, SingleNode<T>* high, Parameters::Pivots type) {
    if (low != high && low != nullptr && high != nullptr) {
        SingleNode<T>* pi = partitionSingle(low, high, type);
        
        // Sortujemy lewą część. Ponieważ w SingleList nie ma elementu prev, 
        // musimy znaleźć węzeł znajdujący się PRZED węzłem pivot, zaczynając od low
        if (pi != low) {
            SingleNode<T>* temp = low;
            while (temp->next != pi) {
                temp = temp->next;
            }
            quickSortRecursiveSingle(low, temp, type);
        }
        
        // sort prawa czesc
        if (pi != nullptr && pi != high) {
            quickSortRecursiveSingle(pi->next, high, type);
        }
    }
}

// Główna funkcja wywołująca QuickSort dla listy jednokierunkowej
template <typename T>
void quickSortSingleList(SingleNode<T>* head, Parameters::Pivots type) {
    if (head == nullptr || head->next == nullptr) return;
    
    SingleNode<T>* tail = head;
    while (tail->next != nullptr) tail = tail->next;
    
    quickSortRecursiveSingle(head, tail, type);
}


//Quick Sort dla kolejki

// Implementacja QuickSort przystosowana specjalnie dla struktury FIFO (kolejka).
// Ponieważ nie mamy dostępu do indeksów, zdejmujemy elementy z oryginalnej kolejki,
// rozdzielamy na dwie nowe , sortujemy je rekurencyjnie,
// a na koniec składamy z powrotem w całość.
template <typename T>
void quickSortQueue(CustomQueue<T>* q) {
    if (q->size <= 1) return;

    T pivot = q->pop(); 
    CustomQueue<T> leftQ;
    CustomQueue<T> rightQ;

    while (q->size > 0) {
        T val = q->pop();
        if (val < pivot) leftQ.push(val);
        else rightQ.push(val);
    }

    quickSortQueue(&leftQ);

    // Odtwarzanie posortowanej kolejki
    while (leftQ.size > 0) q->push(leftQ.pop());
    q->push(pivot);
    while (rightQ.size > 0) q->push(rightQ.pop());
};