#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Structures/singleNode.hpp"
#include "Structures/doubleNode.hpp"


 

template <typename T>
void get_data(const std::string& path, T*& arr, int& size) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Błąd otwarcia pliku: " << path << std::endl;
        return;
    }

     // Odczyt oczekiwanego rozmiaru danych z początku pliku
    if (file >> size) {
        if (size <= 0) return;
        // Dynamiczna alokacja pamięci dla tablicy na podstawie odczytanego rozmiaru
         arr = new T[size];

         // Wczytywanie kolejnych elementów do tablicy
        for (int i = 0; i < size; ++i) {
            // Sprawdzamy czy to char czy unsigned char
            if constexpr (std::is_same_v<T, char> || std::is_same_v<T, unsigned char>) {
                int temp;
                if (file >> temp) {
                    arr[i] = static_cast<T>(temp);
                } else {
                    size = i; break;
                }
            } else {
                // Dla wszystkich innych typów (int, float, string) czytamy normalnie
                if (!(file >> arr[i])) {
                    size = i; break;
                }
            }
        }
    }
    file.close();
}


// Przeciążenie dla listy jednokierunkowej (SingleList)
template <typename T>
void get_data(const std::string& path, SingleList<T>& list, int& size) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Błąd otwarcia pliku:" << path << std::endl;
        return;
    }

    if (file >> size) {
        T value;
        for (int i = 0; i < size; ++i) {
           // Sprawdzamy czy char lub unsigned char
            if constexpr (std::is_same_v<T, char> || std::is_same_v<T, unsigned char>) {
                int temp;
                if (file >> temp) {
                    list.push_back(static_cast<T>(temp));
                } else {
                    size = i;
                    break;
                }
            }else {
                if (file >> value) {
                    list.push_back(value); 
                } else {
                    // Jeśli coś poszło nie tak
                    
                    if (file.eof()) {
                        size = i;
                        break;
                    } else if (file.fail()) {
                        std::cerr << "\n Błąd : Niezgodność typu danych w pliku!" << std::endl;
                        std::cerr << "Udało się wczytać tylko " << i << " z " << size << " elementów.\n" << std::endl;
                        
                        size = i;
                        break;
                    }
                }
            }
        }
    } else {
        std::cerr << "Błąd wczytywania rozmiaru z pliku." << std::endl;
    }
    file.close();
}


// Przeciążenie dla listy dwukierunkowej (DoubleList)
template <typename T>
void get_data(const std::string& path, DoubleList<T>& list, int& size) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Błąd otwarcia pliku: "<< path << std::endl;
        return;
    }

    if (file >> size) {
        T value;
        for (int i = 0; i < size; ++i) {
            // Sprawdzamy czy char lub unsigned char
            if constexpr (std::is_same_v<T, char> || std::is_same_v<T, unsigned char>) {
                int temp;
                if (file >> temp) {
                    list.push_back(static_cast<T>(temp));
                } else {
                    size = i;
                    break;
                }
            } else {
                // Dla wszystkich innych typów standartowo
                if (file >> value) {
                    list.push_back(value);
                } else {
                    size = i;
                    break;
                }
            }
        }
    }
    file.close();
}
