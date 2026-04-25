#pragma once
#include <iostream>
#include "../Structures/doubleNode.hpp"
#include "../Structures/singleNode.hpp"
#include <string>



template <typename NodePtr>
int getListLengthBucket(NodePtr head) {
    int length = 0;
    while (head != nullptr) {
        length++;
        head = head->next;
    }
    return length;
}

// main funk dla array
template <typename T>
void bucketArraySort(T* arr, int n) {
    if (n <= 1) return;

    T min_val = arr[0];
    T max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
    }
    if (min_val == max_val) return; 

    int bucketCount = n;
    
    // Tworze buckets recznie(tablica wskaznikow na SingleNode)
    SingleNode<T>** buckets = new SingleNode<T>*[bucketCount];
    for (int i = 0; i < bucketCount; i++) {
        buckets[i] = nullptr; 
    }
    double range = static_cast<double>(max_val - min_val);
    
    // KOrzystamy z sortowania Insertion Sort
    for (int i = 0; i < n; i++) {
        double normalized = static_cast<double>(arr[i] - min_val) / range;
        int bIndex = static_cast<int>(normalized * (bucketCount - 1));

        SingleNode<T>* newNode = new SingleNode<T>(arr[i]);

        // jesli bucket pusty lub nowy element mniejszy za pierwszy
        if (buckets[bIndex] == nullptr || buckets[bIndex]->data >= arr[i]) {
            newNode->next = buckets[bIndex];
            buckets[bIndex] = newNode;
        } else {
            // szukanie miejsca dla wstawienia
            SingleNode<T>* current = buckets[bIndex];
            while (current->next != nullptr && current->next->data < arr[i]) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    // zbieramy odsortowane dane i zwalniamy pamiec dodatkowo zajeta
    int index = 0;
    for (int i = 0; i < bucketCount; i++) {
        SingleNode<T>* current = buckets[i];
        while (current != nullptr) {
            arr[index++] = current->data;
            SingleNode<T>* temp = current;
            current = current->next;
            delete temp;
        }
    }
    
    delete[] buckets;
}

// main funk dla double list
template <typename T>
void bucketDoubleListSort(DoubleNode<T>* head) {
    int n = getListLengthBucket(head);
    if (n <= 1) return;

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
    
    // recznie alokowane buckets
    SingleNode<T>** buckets = new SingleNode<T>*[bucketCount];
    for (int i = 0; i < bucketCount; i++) buckets[i] = nullptr;

    double range = static_cast<double>(max_val - min_val);
    
    currentList = head;
    while (currentList != nullptr) {
        double normalized = static_cast<double>(currentList->data - min_val) / range;
        int bIndex = static_cast<int>(normalized * (bucketCount - 1));

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

    // zbieramy dane i wyczyszczamy
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

// dla single list
template <typename T>
void bucketSingleListSort(SingleNode<T>* head) {
    std::cout<<"Hello\n";
    int n = getListLengthBucket(head);
    if (n <= 1) return;

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
    
    // allokacja recza
    SingleNode<T>** buckets = new SingleNode<T>*[bucketCount];
    for (int i = 0; i < bucketCount; i++) buckets[i] = nullptr;

    double range = static_cast<double>(max_val - min_val);
    
    currentList = head;
    while (currentList != nullptr) {
        double normalized = static_cast<double>(currentList->data - min_val) / range;
        int bIndex = static_cast<int>(normalized * (bucketCount - 1));

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

    // zbior i oczyszczenie
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
inline void bucketSingleListSort(SingleNode<std::string>* head) {
    int n = getListLengthBucket(head);
    if (n <= 1) return;

    int bucketCount = 256;
    SingleNode<std::string>** buckets = new SingleNode<std::string>*[bucketCount];
    for (int i = 0; i < bucketCount; i++) buckets[i] = nullptr;

    SingleNode<std::string>* currentList = head;
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
            currentList->data = currBucket->data;
            currentList = currentList->next;
            
            SingleNode<std::string>* temp = currBucket;
            currBucket = currBucket->next;
            delete temp;
        }
    }
    delete[] buckets;
}

inline void bucketArraySort(std::string* arr, int n) {
    if (n <= 1) return;

    int bucketCount = 256; // 256 koszykow dla ASCII symboli
    SingleNode<std::string>** buckets = new SingleNode<std::string>*[bucketCount];
    for (int i = 0; i < bucketCount; i++) buckets[i] = nullptr;

    for (int i = 0; i < n; i++) {
        // jesli row pusty, dajemy do bucket 0, inaczej bierzemy kod pierwszej litery
        int bIndex = arr[i].empty() ? 0 : static_cast<unsigned char>(arr[i][0]);

        SingleNode<std::string>* newNode = new SingleNode<std::string>(arr[i]);

        // wstawianie z sortowaniem
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
            // przepis danych, struct zostaje ta sama
            // Перезаписуємо тільки дані, структура (next, prev) залишається цілою!
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