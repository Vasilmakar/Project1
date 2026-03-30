#pragma once
#include <iostream>

template <typename T>
struct SingleNode {
    T data;
    SingleNode* next;

    SingleNode(T val) {
        data = val;
        next = nullptr;
    }
};

template <typename T>
class SingleList {
public:
    SingleNode<T>* head;
    SingleList() {
        head = nullptr;
    }

    ~SingleList() {
        SingleNode<T>* current = head;
        while (current != nullptr) {
            SingleNode<T>* next = current->next;
            delete current; 
            current = next;
        }
    }

    void push_back(T val) {
        SingleNode<T>* newNode = new SingleNode<T>(val);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        SingleNode<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void print() {
        SingleNode<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "nullptr\n";
    }
};