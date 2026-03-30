#pragma once
#include <iostream>

template <typename T>
struct DoubleNode {
    T data;
    DoubleNode* next;
    DoubleNode* prev;

    DoubleNode(T val) {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

template <typename T>
class DoubleList {
public:
    DoubleNode<T>* head;
    DoubleNode<T>* tail;

    DoubleList() {
        head = nullptr;
        tail = nullptr;
    }

    ~DoubleList() {
        DoubleNode<T>* current = head;
        while (current != nullptr) {
            DoubleNode<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    void push_back(T val) {
        DoubleNode<T>* newNode = new DoubleNode<T>(val);
        if (head == nullptr) {
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    void print() {
        DoubleNode<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " <-> ";
            temp = temp->next;
        }
        std::cout << "nullptr\n";
    }
};