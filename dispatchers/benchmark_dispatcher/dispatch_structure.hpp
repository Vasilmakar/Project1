#pragma once
#include "dispatchers/singleMOde_dispatcher/dispatch_algorithm.hpp"
#include <iostream>
#include "data_generator/generate_ascending.hpp"
#include <chrono>
#include "Parameters.h"


// Funkcja otrzymuje wygenerowane dane w postaci tablicy, 
// i w zależności od Parameters:structure konwertuje je 
// na docelową strukturę, sortuje, mierzy czas i bezpiecznie zwalnia pamięć.
template<typename T>
double dispatchStructure(T* array) {
    int size = Parameters::structureSize;
    double iterationTime = 0.0;

    switch(Parameters::structure) {
        // Operacje bezpośrednio na surowej tablicy
        case Parameters::Structures::array: {
            iterationTime = dispatchAlgorithm(array, size);
            
            break;
        }

        // Konwersja i operacje na liście jednokierunkowej
        case Parameters::Structures::singleList: {
            SingleNode<T>* head = arrayToSingleList(array, size);

            iterationTime = dispatchAlgorithm(head, size); // Передаємо head!
        

            // Ręczne zwalnianie pamięci po każdym węźle
            SingleNode<T>* current = head;
            while (current != nullptr) {
                SingleNode<T>* temp = current;
                current = current->next;
                delete temp;
            }
            break;
        }

        // Konwersja i operacje na liście dwukierunkowej
        case Parameters::Structures::doubleList: {
            DoubleNode<T>* head = arrayToDoubleList(array, size);

            iterationTime = dispatchAlgorithm(head, size);
            

            // Bezpieczne usuwanie struktury węzeł po węźle
            DoubleNode<T>* current = head;
            while (current != nullptr) {
                DoubleNode<T>* temp = current;
                current = current->next;
                delete temp;
            }
            break;
        }

        // Konwersja i operacje na kolejce
        case Parameters::Structures::queue: {
            // Przepisanie danych z tablicy do struktury            
            CustomQueue<T>* queue = arrayToQueue(array, size);

            // Kompilator na podstawie przekazanego wskaźnika rozpozna i wywoła 
            // odpowiednie przeciążenie funkcji dispatchAlgorithm dla kolejki.
            iterationTime = dispatchAlgorithm<T>(queue, size);

            delete queue;
            break;
        }

        // Wypadek dla drzewa BST
        case Parameters::Structures::binaryTree: {
            // W odróżnieniu od innych struktur, dla drzewa wywołujemy dedykowaną funkcję.
            // Wynika to z faktu, że czas budowy drzewa jest równoznaczny z czasem sortowania,
            // więc mierzenie musi objąć sam etap alokacji i wstawiania węzłów.           
            iterationTime = dispatchAlgorithmTree(array, size);
            break;
        }
        
        default:
            std::cerr << "Wybrana struktura danych nie jest obsługiwana." << std::endl;
            break;
    }

    return iterationTime;
}










// --------------- Old version -------------------
// template<typename T>
// void dispatchStructure() {
//     // int size = 0;

//     switch(Parameters::structure) {
//         case Parameters::Structures::array: {
//             std::cout<<"Inside dispatchStructure for benchmark\n";
//             T* array = nullptr;
//             dispatchArrayDistribution(array);
//             break;
//         }
//         case Parameters::Structures::singleList: {
//             SingleList<T> list;
//             dispatchSingleDistribution(list.head);
//             break;
//         }
//         case Parameters::Structures::doubleList: {
//             DoubleList<T> list;
//              dispatchDoubleDistribution(list.head);
//             break;
//         }
//         default: 
//         std::cerr << "Not supported" << std::endl;
//         break;
//     }
// }