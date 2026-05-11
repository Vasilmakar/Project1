#pragma once
#include <iostream>


//Struktura listy jednokierunkowej, elementy przechowują wskaźnik na kolejny element
template <typename T>
struct SingleNode {
    T data;
    SingleNode* next;

    // Konstruktor inicjalizujący węzeł
    SingleNode(T val) {
        data = val;
        next = nullptr;
    }
};

template <typename T>
class SingleList {
public:
    SingleNode<T>* head; // Wskaźnik na początek listy
    SingleList() {
        head = nullptr;
    }

    // Destruktow
    // Automatycznie zwalnia pamięć zaalokowaną dla węzłów w momencie usunięcia obiektu listy
    ~SingleList() {
        SingleNode<T>* current = head;
        while (current != nullptr) {
            SingleNode<T>* next = current->next;
            delete current; 
            current = next;
        }
    }

    //dodawanie elementu na koniec, 
    // algorytm musi za każdym razem przejść przez wszystkie elementy, 
    // aby znaleźć przedostatni węzeł i dopiąć do niego nowy element (Złożoność: O(n)).
    void push_back(T val) {
        SingleNode<T>* newNode = new SingleNode<T>(val);
        if (head == nullptr) {
            head = newNode;
            return;
        }

        // Iterowanie do samego końca listy
        SingleNode<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        // Dopięcie nowego węzła na samym końcu
        temp->next = newNode;
    }
\
    // Wyświetlanie listy, dla debagowania
    void print() {
        SingleNode<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "nullptr\n";
    }
};