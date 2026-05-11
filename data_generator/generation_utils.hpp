#pragma once
#include <iostream>
#include "Structures/doubleNode.hpp"
#include "Structures/singleNode.hpp"
#include <random>
#include <string>
#include <type_traits>
#include <limits>
#include "Structures/queue.hpp"
#include "Structures/binaryTree.hpp"



// Funkcja generująca pojedynczą losową wartość dla zadanego typu T.
// Wykorzystuje mechanizm `if constexpr` (ewaluowany w czasie kompilacji), 
// aby dopasować odpowiednią dystrybucję do typu danych.
template <typename T>
T generateRandomValue(std::mt19937_64& gen) {
    
    // Obsługa string
    if constexpr (std::is_same_v<T, std::string>) {
        std::string text = "";
        std::uniform_int_distribution<int> letterDist('a', 'z'); 
        // Generujemy 5-literowe, proste słowa składające się z małych liter
        for (int i = 0; i < 5; i++) {
            text += static_cast<char>(letterDist(gen));
        }
        return text;
    } 
    
    // Obsługa char, unsigned char
    else if constexpr (std::is_same_v<T, char> || std::is_same_v<T, unsigned char>) {

        // Ograniczamy losowanie tylko do widocznych znaków ASCII (32 - 126),       
        std::uniform_int_distribution<int> dist(32, 126);
        return static_cast<T>(dist(gen));
    }
    
    // Obsługa liczb float, double
    else if constexpr (std::is_floating_point_v<T>) {

        // Używamy szerokiego, ale bezpiecznego zakresuIbiezpiecznego znaczy żeby uniknąć sytuacji 
        // z przepełnieniem lub nieskończonością
        std::uniform_real_distribution<T> dist(-1000000000.0, 1000000000.0);
        return dist(gen);
    } 
    
    // Obsługa liczb int, unsigned int, long 
    else if constexpr (std::is_integral_v<T>) {

        // Kompilator automatycznie podstawi pełen dostępny zakres dla danego typu    
        std::uniform_int_distribution<T> dist(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
        return dist(gen);
    }
    
    return T(); 
}




// Konwersja z surowej tablicy na listę jednokierunkową
template <typename T>
SingleNode<T>* arrayToSingleList(T* arr, int size) {
    if (size == 0) return nullptr;

    SingleNode<T>* head = new SingleNode<T>(arr[0]);
    SingleNode<T>* current = head;

    for (int i = 1; i < size; i++) {
        current->next = new SingleNode<T>(arr[i]);
        current = current->next;
    }
    return head;
}


// Konwersja z surowej tablicy na listę dwukierunkową
template <typename T>
DoubleNode<T>* arrayToDoubleList(T* arr, int size) {
    if (size == 0) return nullptr;

    DoubleNode<T>* head = new DoubleNode<T>(arr[0]);
    DoubleNode<T>* current = head;

    for (int i = 1; i < size; i++) {
        DoubleNode<T>* newNode = new DoubleNode<T>(arr[i]);
        current->next = newNode;
        newNode->prev = current;
        current = newNode;
    }
    return head;
}



// Konwersja z surowej tablicy na kolejkę
template <typename T>
CustomQueue<T>* arrayToQueue(T* arr, int size) {
    CustomQueue<T>* q = new CustomQueue<T>();
    for (int i = 0; i < size; i++) {
        q->push(arr[i]);
    }
    return q;
}

// Sortowanie przy użyciu drzewa (Tree Sort).
// Czas mierzymy od razu w tej funkcji, bo sortowanie dzieje się już w trakcie wstawiania (insert) elementów.
// Chcemy zmierzyć łączny czas tworzenia drzewa i przepisywania z niego gotowych danych.
template <typename T>
double dispatchTreeSort(T* arr, int size) {
    // Rozpoczęcie pomiaru czasu
    auto start = std::chrono::high_resolution_clock::now();

    BinaryTree<T>* tree = new BinaryTree<T>();
    // Budowa drzewa – elementy są automatycznie układane w odpowiednich gałęziach
    for(int i = 0; i < size; i++) {
        tree->insert(arr[i]);
    }
    
    // Odczyt posortowanych elementów  z powrotem do tablicy wyjściowej
    int index = 0;
    tree->inOrderToArray(tree->root, arr, index);

    // Zakończenie pomiaru czasu
    auto end = std::chrono::high_resolution_clock::now();
    delete tree;

    return std::chrono::duration<double, std::milli>(end - start).count();
};
