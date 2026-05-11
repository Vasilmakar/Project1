#include <fstream>
#include <iostream>
#include <string>
#include "Structures/doubleNode.hpp"
#include "Structures/singleNode.hpp"
template <typename T>

// W pierwszej linii zapisywana jest liczba elementów, a w kolejnych same dane.

// Przeciążenie dla tablicy
void save_data_array(const std::string& path, T* arr, int size) {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "Błąd otwarcia pliku do zapisu: " << path << std::endl;
        return;
    }

    // Zapisujemy znany z góry rozmiar tablicy
    file << size << "\n"; 

    // Zapisujemy kolejne elementy
    for (int i = 0; i < size; ++i) {
        file << arr[i] << "\n";
    }
    
    file.close();
}


// Przeciążenie dla listy jednokierunkowej
template <typename T>
void save_data_single(const std::string& path, SingleNode<T>* head) {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "Błąd otwarcia pliku do zapisu: " << path << std::endl;
        return;
    }

    // Ponieważ przekazujemy tylko wskaźnik na początek listy, 
    // musimy wykonać pierwsze przejście, aby policzyć wszystkie elementy.
    int count = 0;
    SingleNode<T>* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }

    // Zapisujemy wyliczoną liczbę elementów
    file << count << "\n";

 
    // Drugie przejście przez listę w celu właściwego zapisu danych
    temp = head;
    while (temp != nullptr) {
        file << temp->data << "\n";
        temp = temp->next;
    }

    file.close();
}



// Przeciążenie dla listy dwukierunkowej, logika taka sama jak dla Single List
template <typename T>
void save_data_double(const std::string& path, DoubleNode<T>* head) {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "Blad" << path << std::endl;
        return;
    }

    // Pierwsze przejście: zliczanie węzłów
    int count = 0;
    DoubleNode<T>* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    file << count << "\n";

    // Drugie przejście: zapisywanie wartości
    temp = head;
    while (temp != nullptr) {
        file << temp->data << "\n";
        temp = temp->next;
    }

    file.close();
}