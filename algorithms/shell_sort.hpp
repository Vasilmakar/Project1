#pragma once
#include <iostream>
#include <algorithm>
#include "Structures/singleNode.hpp"
#include "Structures/doubleNode.hpp"
#include "Parameters.h"



// poszukiwanie poszatkowego gap w zaleznosci od wzoru
inline int getInitialGap(int n, Parameters::ShellParameters sequence) {
    if (sequence == Parameters::ShellParameters::option0) return n / 2;
    if (sequence == Parameters::ShellParameters ::option1) {
        int gap = 1;
        while (gap < n / 3) gap = 3 * gap + 1;
        return gap;
    }
    return n / 2;
}

// Wylicza kolejny, mniejszy odstęp na podstawie bieżącego kroku.
inline int getNextGap(int gap, Parameters::ShellParameters sequence) {
    if (sequence == Parameters::ShellParameters::option0) return gap / 2;
    if (sequence == Parameters::ShellParameters::option1) return (gap - 1) / 3;
    return gap / 2;
}

//Funckja dostaje wezel za indeksem(dla single oraz double list)
template <typename NodePtr>
NodePtr getNode(NodePtr head, int index) {
    NodePtr current = head;
    for (int i = 0; i < index && current != nullptr; i++) {
        current = current->next;
    }
    return current;
}

// obliczenie dlugości listy
template <typename NodePtr>
int getListLength(NodePtr head) {
    int length = 0;
    while (head != nullptr) {
        length++;
        head = head->next;
    }
    return length;
}


// Shell dla tablicy(array), opiera się na algorytmie sortowania przez wstawianie
template <typename T>
void shellSortArray(T* arr, int n, Parameters::ShellParameters sequence) {
    int gap = getInitialGap(n, sequence);

    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            T temp = arr[i];
            int j = i;
            
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
        gap = getNextGap(gap, sequence);
    }
}

// dla DoubleList
template <typename T>
void shellSortDoubleList(DoubleNode<T>* head, Parameters::ShellParameters sequence) {
    int n = getListLength(head);
    if (n <= 1) return;

    int gap = getInitialGap(n, sequence);

    while (gap > 0) {
        // Sortowanie przez wstawianie dla elementów odległych o aktualny 'gap'
        for (int i = gap; i < n; i++) {
            DoubleNode<T>* nodeI = getNode(head, i);
            T temp = nodeI->data;
            int j = i;
            
            // Wyszukiwanie odpowiednich węzłów za pomocą getNode()
            DoubleNode<T>* nodeJMinusGap = getNode(head, j - gap);
            DoubleNode<T>* nodeJ = nodeI;

            // Przesuwanie wartości większych wzdłuż przeskoku 'gap'
            while (j >= gap && nodeJMinusGap->data > temp) {
                nodeJ->data = nodeJMinusGap->data;
                j -= gap;
                nodeJ = nodeJMinusGap;
                if (j >= gap) nodeJMinusGap = getNode(head, j - gap);
            }
            nodeJ->data = temp;
        }
        gap = getNextGap(gap, sequence);
    }
}

//dla SingleList, logika działania jest identyczna jak dla listy dwukierunkowej
template <typename T>
void shellSortSingleList(SingleNode<T>* head, Parameters::ShellParameters sequence) {
    int n = getListLength(head);
    if (n <= 1) return;

    int gap = getInitialGap(n, sequence);

    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            SingleNode<T>* nodeI = getNode(head, i);
            T temp = nodeI->data;
            int j = i;
            
            SingleNode<T>* nodeJMinusGap = getNode(head, j - gap);
            SingleNode<T>* nodeJ = nodeI;

            while (j >= gap && nodeJMinusGap->data > temp) {
                nodeJ->data = nodeJMinusGap->data;
                j -= gap;
                nodeJ = nodeJMinusGap;
                if (j >= gap) nodeJMinusGap = getNode(head, j - gap);
            }
            nodeJ->data = temp;
        }
        gap = getNextGap(gap, sequence);
    }
}