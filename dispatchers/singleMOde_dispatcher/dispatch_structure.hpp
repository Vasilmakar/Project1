#pragma once

#include <iostream>
#include "Parameters.h"
#include "dispatch_algorithm.hpp"
#include "data/save_data.hpp"


//Funkcje dla trybu singleFile
// Dla określonych w parametrach struktur wywoływana funkcja załadowania danych
//  z plików do odpowiednich struktur
// potem dane przekazywane kolejno do funkcji pełniących swoje role w programie
// potem posortowane dane zapisane zostają do pliku wyjściowego
template <typename T>
void dispatchStructure(const std::string& path) {
    int size = 0;
    double time = 0.0;  // Czas wykonania
    switch(Parameters::structure) {

        // Cykl życia dla surowej tablicy
        case Parameters::Structures::array: {
            T* array = nullptr;
            //Wczytanie danych z pliku. Wartość zmiennej size zostaje zaktualizowana 
            // wewnątrz funkcji get_data na podstawie rzeczywistej liczby elementów.
            get_data(path, array, size);
            for(int i = 0; i < 5; i++){
                std::cout<<array[i]<<", ";
            }
            //Właściwe sortowanie
            time = dispatchAlgorithm(array, size);

            // Eksport posortowanych wyników do pliku wskazanego w konfiguracji
            save_data_array(Parameters::outputFile, array, size);

            // Ręczne zwolnienie dynamicznie zaalokowanej pamięci tablicy
            delete[] array;
            break;
        }

        // Cykl życia dla listy jednokierunkowej
        case Parameters::Structures::singleList: {
            // Wykorzystujemy klasę SingleList, co upraszcza 
            // dynamiczne dodawanie elementów (push_back) podczas wczytywania.
            SingleList<T> list;
            get_data(path, list, size);
            
            // Ponieważ algorytm sortujący operuje na wskaźnikach do węzłów, 
            // przekazujemy mu bezpośrednio sam początek listy (head).
            time = dispatchAlgorithm(list.head, size); 
            // Pamięć jest zwalniana automatycznie w destruktorze obiektu 'list'
            save_data_single(Parameters::outputFile, list.head);
            break;
        }

        // Cykl życia dla listy dwukierunkowej
        case Parameters::Structures::doubleList: {
            DoubleList<T> list;
            get_data(path, list, size);
            time = dispatchAlgorithm(list.head, size);
            save_data_double(Parameters::outputFile, list.head);
            break;
        }
        default: 
        std::cerr << "Wybrana struktura danych nie jest obsługiwana w trybie wczytywania z pliku." << std::endl;
        break;
    }
}