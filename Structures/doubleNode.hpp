#pragma once
#include <iostream>


// Struktura listy dwukierunkowej 
// W odróżnieniu od listy jednokierunkowej, każdy węzeł przechowuje 
// wskaźnik zarówno na następny (next), jak i poprzedni (prev) element.
template <typename T>
struct DoubleNode {
    T data;
    DoubleNode* next;
    DoubleNode* prev;

    // Konstruktor
    DoubleNode(T val) {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

template <typename T>
class DoubleList {
public:
    DoubleNode<T>* head; // Wskaźnik na pierwszy element listy
    DoubleNode<T>* tail; // Wskaźnik na ostatni element listy


    
    DoubleList() {
        head = nullptr;
        tail = nullptr;
    }

    // Destruktor
    ~DoubleList() {
        DoubleNode<T>* current = head;
        while (current != nullptr) {
            DoubleNode<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    // Dodawanie nowego elementu na koniec list
    void push_back(T val) {
        DoubleNode<T>* newNode = new DoubleNode<T>(val);
        if (head == nullptr) {
            head = tail = newNode;
            return;
        }

        // wstawianie na koniec 
        // Ostatni element wskazuje na nowy węzeł jako na następnika.
        // Nowy węzeł wskazuje na obecny tail jako na poprzednika.
        // Ogon  zostaje zaktualizowany na nowy węzeł.
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    // Funkcja pomocnicza do debugowania
    void print() {
        DoubleNode<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " <-> ";
            temp = temp->next;
        }
        std::cout << "nullptr\n";
    }
};