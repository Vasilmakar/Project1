#pragma once
#include <iostream>
#include "Structures/doubleNode.hpp"
#include "Structures/singleNode.hpp"
#include <string>


// Pomocnicza funkcja do obliczania długości listy wiązanej
template <typename NodePtr>
int getListLengthBucket(NodePtr head) {
    int length = 0;
    while (head != nullptr) {
        length++;
        head = head->next;
    }
    return length;
}

// Główna funkcja sortowania kubełkowego dla tablic (typy generyczne)
template <typename T>
void bucketArraySort(T* arr, int n) {
    if (n <= 1) return;

    //Znajdowanie wartości ekstremalnych w celu ustalenia zakresu danych
    T min_val = arr[0];
    T max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
    }
    if (min_val == max_val) return; 

    // Inicjalizacja kubełków (używamy tablicy wskaźników na listy jednokierunkowe)
    int bucketCount = n;
    SingleNode<T>** buckets = new SingleNode<T>*[bucketCount];
    for (int i = 0; i < bucketCount; i++) {
        buckets[i] = nullptr; 
    }
    
    // Obliczanie zakresu z zabezpieczeniem przed dzieleniem przez zero
    double d_max = static_cast<double>(max_val);
    double d_min = static_cast<double>(min_val);
    double range = d_max - d_min;
    if (range == 0.0) range = 1.0; // ubiezpieczenie od dzielenia przez 0
    
    // Rozmieszczanie elementów w kubełkach
    for (int i = 0; i < n; i++) {
        // Normalizacja wartości do przedziału <0, 1> i wyliczenie indeksu
        double normalized = (static_cast<double>(arr[i]) - d_min) / range;
        int bIndex = static_cast<int>(normalized * (bucketCount - 1));

        // ubiezpieczenie od przekroczenia granicy tablicy
        if (bIndex >= bucketCount) bIndex = bucketCount - 1;
        else if (bIndex < 0) bIndex = 0;
    // ---------------------------------------

        SingleNode<T>* newNode = new SingleNode<T>(arr[i]);

        // Wstawianie elementu do kubełka z zachowaniem kolejności rosnącej (wstawianie posortowane)
        if (buckets[bIndex] == nullptr || buckets[bIndex]->data >= arr[i]) {
            newNode->next = buckets[bIndex];
            buckets[bIndex] = newNode;
        } else {
            SingleNode<T>* current = buckets[bIndex];
            while (current->next != nullptr && current->next->data < arr[i]) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    // Łączenie posortowanych danych z kubełków z powrotem do tablicy wyjściowej
    int index = 0;
    for (int i = 0; i < bucketCount; i++) {
        SingleNode<T>* current = buckets[i];
        while (current != nullptr) {
            arr[index++] = current->data;
            SingleNode<T>* temp = current;
            current = current->next;
            delete temp; // Czyszczenie pamięci po węzłach kubełka
        }
    }
    
    delete[] buckets;
}


// Sortowanie kubełkowe dla listy dwukierunkowej
template <typename T>
void bucketDoubleListSort(DoubleNode<T>* head) {
    int n = getListLengthBucket(head);
    if (n <= 1) return;

    // Ustalanie zakresu wartości w liście
    T min_val = head->data;
    T max_val = head->data;
    DoubleNode<T>* currentList = head->next;
    while (currentList != nullptr) {
        if (currentList->data < min_val) min_val = currentList->data;
        if (currentList->data > max_val) max_val = currentList->data;
        currentList = currentList->next;
    }
    if (min_val == max_val) return;

    int bucketCount = n;
    SingleNode<T>** buckets = new SingleNode<T>*[bucketCount];
    for (int i = 0; i < bucketCount; i++) buckets[i] = nullptr;

   
    double d_max = static_cast<double>(max_val);
    double d_min = static_cast<double>(min_val);
    double range = d_max - d_min;
    if (range == 0.0) range = 1.0;
    
    currentList = head;
    while (currentList != nullptr) {
        // Dystrybucja węzłów listy do kubełków w oparciu o znormalizowaną wartość
        double normalized = (static_cast<double>(currentList->data) - d_min) / range;
        int bIndex = static_cast<int>(normalized * (bucketCount - 1));

        if (bIndex >= bucketCount) bIndex = bucketCount - 1;
        else if (bIndex < 0) bIndex = 0;
    // ---------------------------------------

        SingleNode<T>* newNode = new SingleNode<T>(currentList->data);

        // Sortowanie przez wstawianie wewnątrz danego kubełka
        if (buckets[bIndex] == nullptr || buckets[bIndex]->data >= currentList->data) {
            newNode->next = buckets[bIndex];
            buckets[bIndex] = newNode;
        } else {
            SingleNode<T>* currBucket = buckets[bIndex];
            while (currBucket->next != nullptr && currBucket->next->data < currentList->data) {
                currBucket = currBucket->next;
            }
            newNode->next = currBucket->next;
            currBucket->next = newNode;
        }
        currentList = currentList->next;
    }

    // Przepisywanie wyników do oryginalnej listy
    // Zmieniamy tylko wartości (data), oryginalna struktura wskaźników listy pozostaje nienaruszona
    currentList = head;
    for (int i = 0; i < bucketCount; i++) {
        SingleNode<T>* currBucket = buckets[i];
        while (currBucket != nullptr) {
            currentList->data = currBucket->data;
            currentList = currentList->next;
            
            SingleNode<T>* temp = currBucket;
            currBucket = currBucket->next;
            delete temp;
        }
    }
    
    delete[] buckets;
}


// Sortowanie kubełkowe dla listy jednokierunkowej
template <typename T>
void bucketSingleListSort(SingleNode<T>* head) {
    int n = getListLengthBucket(head);
    if (n <= 1) return;

    //Taka sama logika jak dla DoubleList
    T min_val = head->data;
    T max_val = head->data;
    SingleNode<T>* currentList = head->next;
    while (currentList != nullptr) {
        if (currentList->data < min_val) min_val = currentList->data;
        if (currentList->data > max_val) max_val = currentList->data;
        currentList = currentList->next;
    }
    if (min_val == max_val) return;

    int bucketCount = n;
    SingleNode<T>** buckets = new SingleNode<T>*[bucketCount];
    for (int i = 0; i < bucketCount; i++) buckets[i] = nullptr;

    double d_max = static_cast<double>(max_val);
    double d_min = static_cast<double>(min_val);
    double range = d_max - d_min;
    if (range == 0.0) range = 1.0;
    
    currentList = head;
    while (currentList != nullptr) {
        double normalized = (static_cast<double>(currentList->data) - d_min) / range;
        int bIndex = static_cast<int>(normalized * (bucketCount - 1));

        if (bIndex >= bucketCount) bIndex = bucketCount - 1;
        else if (bIndex < 0) bIndex = 0;
    // ---------------------------------------

        SingleNode<T>* newNode = new SingleNode<T>(currentList->data);

        if (buckets[bIndex] == nullptr || buckets[bIndex]->data >= currentList->data) {
            newNode->next = buckets[bIndex];
            buckets[bIndex] = newNode;
        } else {
            SingleNode<T>* currBucket = buckets[bIndex];
            while (currBucket->next != nullptr && currBucket->next->data < currentList->data) {
                currBucket = currBucket->next;
            }
            newNode->next = currBucket->next;
            currBucket->next = newNode;
        }
        currentList = currentList->next;
    }

    currentList = head;
    for (int i = 0; i < bucketCount; i++) {
        SingleNode<T>* currBucket = buckets[i];
        while (currBucket != nullptr) {
            currentList->data = currBucket->data;
            currentList = currentList->next;
            
            SingleNode<T>* temp = currBucket;
            currBucket = currBucket->next;
            delete temp;
        }
    }
    
    delete[] buckets;
}
    //wersje dla danych w postaci string
    //Kategoryzowanie łańcuchów znaków na podstawie pierwszego znaku (ASCII)

    //Dla jednokierunkowej listy stringów
inline void bucketSingleListSort(SingleNode<std::string>* head) {
    int n = getListLengthBucket(head);
    if (n <= 1) return;

    // 256 kubełków odpowiadających wszystkim możliwym wartościom ASCII
    int bucketCount = 256;
    SingleNode<std::string>** buckets = new SingleNode<std::string>*[bucketCount];
    for (int i = 0; i < bucketCount; i++) buckets[i] = nullptr;

    SingleNode<std::string>* currentList = head;
    while (currentList != nullptr) {
        // Puste stringi trafiają do kubełka 0, pozostałe w zależności od kodu ASCII pierwszej litery
        int bIndex = currentList->data.empty() ? 0 : static_cast<unsigned char>(currentList->data[0]);

        SingleNode<std::string>* newNode = new SingleNode<std::string>(currentList->data);

        if (buckets[bIndex] == nullptr || buckets[bIndex]->data >= currentList->data) {
            newNode->next = buckets[bIndex];
            buckets[bIndex] = newNode;
        } else {
            SingleNode<std::string>* currBucket = buckets[bIndex];
            while (currBucket->next != nullptr && currBucket->next->data < currentList->data) {
                currBucket = currBucket->next;
            }
            newNode->next = currBucket->next;
            currBucket->next = newNode;
        }
        currentList = currentList->next;
    }


    // Przepisanie posortowanych stringów z powrotem do listy
    currentList = head;
    for (int i = 0; i < bucketCount; i++) {
        SingleNode<std::string>* currBucket = buckets[i];
        while (currBucket != nullptr) {
            currentList->data = currBucket->data;
            currentList = currentList->next;
            
            SingleNode<std::string>* temp = currBucket;
            currBucket = currBucket->next;
            delete temp;
        }
    }
    delete[] buckets;
}

// Specjalizacja dla tablicy stringów
inline void bucketArraySort(std::string* arr, int n) {
    if (n <= 1) return;

    int bucketCount = 256; // 256 koszykow dla ASCII symboli
    SingleNode<std::string>** buckets = new SingleNode<std::string>*[bucketCount];
    for (int i = 0; i < bucketCount; i++) buckets[i] = nullptr;

    for (int i = 0; i < n; i++) {
        // jesli row pusty, dajemy do bucket 0, inaczej bierzemy kod pierwszej litery
        int bIndex = arr[i].empty() ? 0 : static_cast<unsigned char>(arr[i][0]);

        SingleNode<std::string>* newNode = new SingleNode<std::string>(arr[i]);

        // Wstawianie stringa do odpowiedniego kubełka w posortowanej kolejności
        if (buckets[bIndex] == nullptr || buckets[bIndex]->data >= arr[i]) {
            newNode->next = buckets[bIndex];
            buckets[bIndex] = newNode;
        } else {
            SingleNode<std::string>* current = buckets[bIndex];
            while (current->next != nullptr && current->next->data < arr[i]) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    // zbieramy 
    int index = 0;
    for (int i = 0; i < bucketCount; i++) {
        SingleNode<std::string>* current = buckets[i];
        while (current != nullptr) {
            arr[index++] = current->data;
            SingleNode<std::string>* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] buckets;
}


// Specjalizacja dla dwukierunkowej listy stringów
inline void bucketDoubleListSort(DoubleNode<std::string>* head) {
    int n = getListLengthBucket(head);
    if (n <= 1) return;

    int bucketCount = 256;
    // tymczasowe koszyki dla single node
    SingleNode<std::string>** buckets = new SingleNode<std::string>*[bucketCount];
    for (int i = 0; i < bucketCount; i++) buckets[i] = nullptr;

    // idziemy po pierwatnej liscie double list
    DoubleNode<std::string>* currentList = head;
    while (currentList != nullptr) {
        int bIndex = currentList->data.empty() ? 0 : static_cast<unsigned char>(currentList->data[0]);

        SingleNode<std::string>* newNode = new SingleNode<std::string>(currentList->data);

    
        if (buckets[bIndex] == nullptr || buckets[bIndex]->data >= currentList->data) {
            newNode->next = buckets[bIndex];
            buckets[bIndex] = newNode;
        } else {
            SingleNode<std::string>* currBucket = buckets[bIndex];
            while (currBucket->next != nullptr && currBucket->next->data < currentList->data) {
                currBucket = currBucket->next;
            }
            newNode->next = currBucket->next;
            currBucket->next = newNode;
        }
        currentList = currentList->next;
    }


    currentList = head;
    for (int i = 0; i < bucketCount; i++) {
        SingleNode<std::string>* currBucket = buckets[i];
        while (currBucket != nullptr) {
            // Nadpisujemy tylko dane łańcuchowe (data), a wskaźniki (next, prev) listy dwukierunkowej zostają nietknięte
            currentList->data = currBucket->data;
            currentList->data = currBucket->data;
            currentList = currentList->next;
            
            // wyczyszczenie
            SingleNode<std::string>* temp = currBucket;
            currBucket = currBucket->next;
            delete temp;
        }
    }
    delete[] buckets;
}