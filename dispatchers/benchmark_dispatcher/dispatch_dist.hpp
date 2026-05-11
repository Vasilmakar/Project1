#pragma once
#include "dispatch_structure.hpp"
#include <iostream>
#include "Parameters.h"
#include "data_generator/generate_random.hpp"
#include "data_generator/generate_ascending.hpp"
#include "data_generator/generate_descending.hpp"
#include "data_generator/generate_half_sorted.hpp"
#include "dispatchers/singleMOde_dispatcher/dispatch_algorithm.hpp"
#include "data/saveBenchmarkResult.hpp"
#include <chrono>



// Funkcja odpowiedzialna za przeprowadzenie pełnego cyklu testowego dla tablic.
// Generuje dane o wybranym rozkładzie, uruchamia pomiar czasu dla zadanej liczby iteracji
// oraz loguje wyniki (zarówno dla każdej iteracji z osobna, jak i uśrednione podsumowanie).
template<typename T>
void dispatchArrayDistribution(){
    int size = Parameters::structureSize;
    double totalTimeMs = 0.0;
    double minTime = std::numeric_limits<double>::max(); 
    double maxTime = std::numeric_limits<double>::lowest();
    int iters = Parameters::iterations;
    
    // T* array = new T[size];
    // Główna pętla testowa
    // Tablica jest alokowana i wypełniana na nowo wewnątrz pętli,
    // dzięki temu mamy pewność, że algorytm za każdym razem pracuje na nowych 
    // danych, a nie na tablicy posortowanej w poprzednim kroku.
    for(int i = 0; i < Parameters::iterations; i++) {
         T* array = new T[size];

         // Wybór i generowanie odpowiedniego układu początkowego danych
        switch(Parameters::distribution) {
            case Parameters::Distribution::random:           
                generateRandomArray(array, Parameters::structureSize);  
                break;
            
            case Parameters::Distribution::ascending:
                generateAscendingArray(array, Parameters::structureSize);
                break;
                      
            case Parameters::Distribution::descending:
                generateDescendingArray(array, Parameters::structureSize);
                break;
 
            case Parameters::Distribution::ascending50Per:
                generateHalfSortedArray(array, Parameters::structureSize);
                break;

            default:
                std::cout << "Nieznany układ danych\n";
                break;
        }

        // Uruchomienie wybranego algorytmu dla tablicy i pobranie czasu
        double iterationTime = dispatchStructure<T>(array);
        // Zbieranie i aktualizacja statystyk czasowych
        totalTimeMs += iterationTime;
        if (iterationTime < minTime) minTime = iterationTime;
        if (iterationTime > maxTime) maxTime = iterationTime;
        // Zapis surowych wynikow dla bieżącej iteracji
        saveRawResult("Badanie", 
                      static_cast<int>(Parameters::algorithm), 
                      static_cast<int>(Parameters::structure), 
                      static_cast<int>(Parameters::dataType), 
                      static_cast<int>(Parameters::distribution), 
                      size, 
                      i + 1, 
                      iterationTime);

        delete[] array; //Zwolnienie pamięci po zakończeniu iteracji
    }

    // Obliczenie wartości średniej i zapis podsumowania z całej serii pomiarowej
    double avgTime = totalTimeMs / iters;
    saveAggregatedResult("Badanie", 
                         static_cast<int>(Parameters::algorithm), 
                         static_cast<int>(Parameters::structure), 
                         static_cast<int>(Parameters::dataType), 
                         static_cast<int>(Parameters::distribution), 
                         size, 
                         iters, 
                         avgTime, 
                         minTime, 
                         maxTime);

    }
    // double avgTime = totalTimeMs / Parameters::iterations;
    //     std::cout << "Avg time: " << avgTime << " ms\n";
    //     saveBenchmarkResult(
    //             "Badanie_A", 
    //             static_cast<int>(Parameters::algorithm),
    //             static_cast<int>(Parameters::structure),
    //             static_cast<int>(Parameters::dataType),
    //             static_cast<int>(Parameters::distribution),
    //             Parameters::structureSize,
    //             Parameters::iterations,
    //             avgTime,
    //             totalTimeMs
    //         );




// template<typename T>
// void dispatchArrayDistribution(T* array){
//     double totalTimeMs = 0.0;
//     double avgTime = 0.0;

//     switch(Parameters::distribution) {
//         case Parameters::Distribution::random:
//         {
//             for(int i = 0; i < Parameters::iterations; i++){
//                 //generacja danych
//                 generateRandomArray(array, Parameters::structureSize);

//                 //zapis czasu startowego
//                 auto start = std::chrono::high_resolution_clock::now();

//                 //sortowanie
//                 dispatchAlgorithm(array, Parameters::structureSize); 

//                 //zapis czasu koncowego
//                 auto end = std::chrono::high_resolution_clock::now();

//                 std::chrono::duration<double, std::milli> elapsed = end - start;
//                 totalTimeMs += elapsed.count(); // milisekundy
//                 avgTime = totalTimeMs / Parameters::iterations;

//                 // wyczyszczenie pamieci
//                 delete[] array;
//             }
//             avgTime = totalTimeMs / Parameters::iterations;
//             std::cout<<"Average sorting of random array time for :"<<": "<<avgTime<<std::endl;
            
//             saveBenchmarkResult(
//                 "Badanie_A", 
//                 static_cast<int>(Parameters::algorithm),
//                 static_cast<int>(Parameters::structure),
//                 static_cast<int>(Parameters::dataType),
//                 static_cast<int>(Parameters::distribution),
//                 Parameters::structureSize,
//                 Parameters::iterations,
//                 avgTime,
//                 totalTimeMs
//             );
//             break;
//         }

//         case Parameters::Distribution::ascending:{
//             for(int i = 0; i < Parameters::iterations; i++){
//                 generateAscendingArray(array, Parameters::structureSize);
//                 auto start = std::chrono::high_resolution_clock::now();

//                 dispatchAlgorithm(array, Parameters::structureSize); 

//                 auto end = std::chrono::high_resolution_clock::now();

//                 std::chrono::duration<double, std::milli> elapsed = end - start;
//                 totalTimeMs += elapsed.count(); // Додаємо мілісекунди

//                 // wyczyszczenie pammieci
//                 delete[] array;
//             }
//             avgTime = totalTimeMs / Parameters::iterations;
//             std::cout<<"Average sorting of random array time for :"<<": "<<avgTime<<std::endl;
//             saveBenchmarkResult(
//                 "Badanie_A", 
//                 static_cast<int>(Parameters::algorithm),
//                 static_cast<int>(Parameters::structure),
//                 static_cast<int>(Parameters::dataType),
//                 static_cast<int>(Parameters::distribution),
//                 Parameters::structureSize,
//                 Parameters::iterations,
//                 avgTime,
//                 totalTimeMs
//             );
//             break;
//         }
           

//         case Parameters::Distribution::descending:{
//             for(int i = 0; i < Parameters::iterations; i++){
//                 generateDescendingArray(array, Parameters::structureSize);
//                 auto start = std::chrono::high_resolution_clock::now();

//                 dispatchAlgorithm(array, Parameters::structureSize); 

//                 auto end = std::chrono::high_resolution_clock::now();

//                 // wyliczamy czas
//                 std::chrono::duration<double, std::milli> elapsed = end - start;
//                 totalTimeMs += elapsed.count(); // Додаємо мілісекунди

//                 // wyczyszczamy pamiec
//                 delete[] array;
//             }
//             avgTime = totalTimeMs / Parameters::iterations;
//             std::cout<<"Average sorting of random array time for :"<<": "<<avgTime<<std::endl;
//             saveBenchmarkResult(
//                 "Badanie_A", 
//                 static_cast<int>(Parameters::algorithm),
//                 static_cast<int>(Parameters::structure),
//                 static_cast<int>(Parameters::dataType),
//                 static_cast<int>(Parameters::distribution),
//                 Parameters::structureSize,
//                 Parameters::iterations,
//                 avgTime,
//                 totalTimeMs
//             );
//             break;
//         }

//         case Parameters::Distribution::ascending50Per:{
//             for(int i = 0; i < Parameters::iterations; i++){
//                 generateHalfSortedArray(array, Parameters::structureSize);
//                 auto start = std::chrono::high_resolution_clock::now();

//                 dispatchAlgorithm(array, Parameters::structureSize); 

//                 auto end = std::chrono::high_resolution_clock::now();

//                 std::chrono::duration<double, std::milli> elapsed = end - start;
//                 totalTimeMs += elapsed.count(); // milisekundy

//                 // Wyczyszczamy pamiec
//                 delete[] array;
//             }
//             avgTime = totalTimeMs / Parameters::iterations;
//             std::cout<<"Average sorting of random array time for :"<<": "<<avgTime<<std::endl;
//             saveBenchmarkResult(
//                 "Badanie_A", 
//                 static_cast<int>(Parameters::algorithm),
//                 static_cast<int>(Parameters::structure),
//                 static_cast<int>(Parameters::dataType),
//                 static_cast<int>(Parameters::distribution),
//                 Parameters::structureSize,
//                 Parameters::iterations,
//                 avgTime,
//                 totalTimeMs
//             );
//             break;
//         }
//     }

// }

// template<typename T>
// void dispatchSingleDistribution(SingleNode<T>* data){
//     double totalTimeMs = 0.0;
//     double avgTime = 0.0;
//     switch(Parameters::distribution){
//         case Parameters::Distribution::random:{
//             for(int i = 0; i < Parameters::iterations; i++){
//                 generateRandomSingleList(data, Parameters::structureSize);
                
//                 auto start = std::chrono::high_resolution_clock::now();

//                 dispatchAlgorithm(data, Parameters::structureSize); 

//                 auto end = std::chrono::high_resolution_clock::now();
//                 std::chrono::duration<double, std::milli> elapsed = end - start;
//                 totalTimeMs += elapsed.count();

//                 //Wyczyszczamy liste
//                 SingleNode<T>* current = data;
//                 while (current != nullptr) {
//                     SingleNode<T>* temp = current;
//                     current = current->next;
//                     delete temp; //usuwamy wezel
//                 }
//                 data = nullptr; 
//             }
//             avgTime = totalTimeMs / Parameters::iterations;
//             std::cout<<"Average sorting of random array time for :"<<": "<<avgTime<<std::endl;

//             saveBenchmarkResult(
//                 "Badanie_A", 
//                 static_cast<int>(Parameters::algorithm),
//                 static_cast<int>(Parameters::structure),
//                 static_cast<int>(Parameters::dataType),
//                 static_cast<int>(Parameters::distribution),
//                 Parameters::structureSize,
//                 Parameters::iterations,
//                 avgTime,
//                 totalTimeMs
//             );
//             break;
//         }
    
    

//         case Parameters::Distribution::ascending:{
//             for(int i = 0; i < Parameters::iterations; i++){
//                 generateAscendingSingleList(data, Parameters::structureSize);
                
//                 auto start = std::chrono::high_resolution_clock::now();

//                 dispatchAlgorithm(data, Parameters::structureSize); 

//                 auto end = std::chrono::high_resolution_clock::now();
//                 std::chrono::duration<double, std::milli> elapsed = end - start;
//                 totalTimeMs += elapsed.count();

//                 // Wyczyszczamy liste
//                 SingleNode<T>* current = data;
//                 while (current != nullptr) {
//                     SingleNode<T>* temp = current;
//                     current = current->next;
//                     delete temp; // usuwamy wezel
//                 }
//                 data = nullptr;
//             }
//             avgTime = totalTimeMs / Parameters::iterations;
//             std::cout<<"Average sorting of random array time for :"<<": "<<avgTime<<std::endl;

//             saveBenchmarkResult(
//                 "Badanie_A", 
//                 static_cast<int>(Parameters::algorithm),
//                 static_cast<int>(Parameters::structure),
//                 static_cast<int>(Parameters::dataType),
//                 static_cast<int>(Parameters::distribution),
//                 Parameters::structureSize,
//                 Parameters::iterations,
//                 avgTime,
//                 totalTimeMs
//             );
//             break;
//         }
    

//         case Parameters::Distribution::descending:{
//             for(int i = 0; i < Parameters::iterations; i++){
//                 generateDescendingSingleList(data, Parameters::structureSize);
                
//                 auto start = std::chrono::high_resolution_clock::now();

//                 dispatchAlgorithm(data, Parameters::structureSize); 

//                 auto end = std::chrono::high_resolution_clock::now();
//                 std::chrono::duration<double, std::milli> elapsed = end - start;
//                 totalTimeMs += elapsed.count();

//                 // Wyczyszczamy liste 
//                 SingleNode<T>* current = data;
//                 while (current != nullptr) {
//                     SingleNode<T>* temp = current;
//                     current = current->next;
//                     delete temp; //usuwamy wezel
//                 }
//                 data = nullptr; 
//             }
//             avgTime = totalTimeMs / Parameters::iterations;
//             std::cout<<"Average sorting of random array time for :"<<": "<<avgTime<<std::endl;

//             saveBenchmarkResult(
//                 "Badanie_A", 
//                 static_cast<int>(Parameters::algorithm),
//                 static_cast<int>(Parameters::structure),
//                 static_cast<int>(Parameters::dataType),
//                 static_cast<int>(Parameters::distribution),
//                 Parameters::structureSize,
//                 Parameters::iterations,
//                 avgTime,
//                 totalTimeMs
//             );
//             break;
//         }
  

//         case Parameters::Distribution::ascending50Per:{
//             for(int i = 0; i < Parameters::iterations; i++){
//                 generateHalfSortedSingleList(data, Parameters::structureSize);
                
//                 auto start = std::chrono::high_resolution_clock::now();

//                 dispatchAlgorithm(data, Parameters::structureSize); 

//                 auto end = std::chrono::high_resolution_clock::now();
//                 std::chrono::duration<double, std::milli> elapsed = end - start;
//                 totalTimeMs += elapsed.count();

//                 // Wyczyszczamy liste wezel za wezlem
//                 SingleNode<T>* current = data;
//                 while (current != nullptr) {
//                     SingleNode<T>* temp = current;
//                     current = current->next;
//                     delete temp; // usuwamy wezel
//                 }
//                 data = nullptr; 
//             }
//             avgTime = totalTimeMs / Parameters::iterations;
//             std::cout<<"Average sorting of random array time for :"<<": "<<avg<<std::endl;
//             saveBenchmarkResult(
//                 "Badanie_A", 
//                 static_cast<int>(Parameters::algorithm),
//                 static_cast<int>(Parameters::structure),
//                 static_cast<int>(Parameters::dataType),
//                 static_cast<int>(Parameters::distribution),
//                 Parameters::structureSize,
//                 Parameters::iterations,
//                 avgTime,
//                 totalTimeMs
//             );
//             break;
//         }
//     }

// }

// template<typename T>
// void dispatchDoubleDistribution(DoubleNode<T>* data){
//     double totalTimeMs = 0.0;
//     double avgTime = 0.0;
//     switch(Parameters::distribution){
//         case Parameters::Distribution::random:{
//             for(int i = 0; i < Parameters::iterations; i++){
//                 generateRandomDoubleList(data, Parameters::structureSize);
                
//                 auto start = std::chrono::high_resolution_clock::now();

//                 dispatchAlgorithm(data, Parameters::structureSize); 

//                 auto end = std::chrono::high_resolution_clock::now();
//                 std::chrono::duration<double, std::milli> elapsed = end - start;
//                 totalTimeMs += elapsed.count();

//                 // Wyczyszczamy liste double
//                 DoubleNode<T>* current = data;
//                 while (current != nullptr) {
//                     DoubleNode<T>* temp = current;
//                     current = current->next;
//                     delete temp;
//                 }
//                 data = nullptr; 
//             }
            
//             // out
//             // double avgTime = totalTimeMs / Parameters::iterations;
//             std::cout << "Average sorting of random Double List time: " << avgTime << " ms\n";
//             saveBenchmarkResult(
//                 "Badanie_A", 
//                 static_cast<int>(Parameters::algorithm),
//                 static_cast<int>(Parameters::structure),
//                 static_cast<int>(Parameters::dataType),
//                 static_cast<int>(Parameters::distribution),
//                 Parameters::structureSize,
//                 Parameters::iterations,
//                 avgTime,
//                 totalTimeMs
//             );
//             break;
//         }

//         case Parameters::Distribution::ascending:{
//             for(int i = 0; i < Parameters::iterations; i++){
//                generateAscendingDoubleList(data, Parameters::structureSize);
                
//                 auto start = std::chrono::high_resolution_clock::now();

//                 dispatchAlgorithm(data, Parameters::structureSize); 

//                 auto end = std::chrono::high_resolution_clock::now();
//                 std::chrono::duration<double, std::milli> elapsed = end - start;
//                 totalTimeMs += elapsed.count();

//                 // Wyczyszczamy liste double
//                 DoubleNode<T>* current = data;
//                 while (current != nullptr) {
//                     DoubleNode<T>* temp = current;
//                     current = current->next;
//                     delete temp;
//                 }
//                 data = nullptr;
//             }
            
//             // 6.out
//             avgTime = totalTimeMs / Parameters::iterations;
//             std::cout << "Average sorting of random Double List time: " << avgTime << " ms\n";
//             saveBenchmarkResult(
//                 "Badanie_A", 
//                 static_cast<int>(Parameters::algorithm),
//                 static_cast<int>(Parameters::structure),
//                 static_cast<int>(Parameters::dataType),
//                 static_cast<int>(Parameters::distribution),
//                 Parameters::structureSize,
//                 Parameters::iterations,
//                 avgTime,
//                 totalTimeMs
//             );
//             break;
//         }

//         case Parameters::Distribution::descending:{
//             for(int i = 0; i < Parameters::iterations; i++){
//                 generateDescendingDoubleList(data, Parameters::structureSize);
                
//                 auto start = std::chrono::high_resolution_clock::now();

//                 dispatchAlgorithm(data, Parameters::structureSize); 

//                 auto end = std::chrono::high_resolution_clock::now();
//                 std::chrono::duration<double, std::milli> elapsed = end - start;
//                 totalTimeMs += elapsed.count();

//                 //Wyczyszczamy liste double
//                 DoubleNode<T>* current = data;
//                 while (current != nullptr) {
//                     DoubleNode<T>* temp = current;
//                     current = current->next;
//                     delete temp;
//                 }
//                 data = nullptr; 
//             }
            
//             avgTime = totalTimeMs / Parameters::iterations;
//             std::cout << "Average sorting of random Double List time: " << avgTime << " ms\n";
//             saveBenchmarkResult(
//                 "Badanie_A", 
//                 static_cast<int>(Parameters::algorithm),
//                 static_cast<int>(Parameters::structure),
//                 static_cast<int>(Parameters::dataType),
//                 static_cast<int>(Parameters::distribution),
//                 Parameters::structureSize,
//                 Parameters::iterations,
//                 avgTime,
//                 totalTimeMs
//             );
//             break;
//         }

//         case Parameters::Distribution::ascending50Per:{
//             for(int i = 0; i < Parameters::iterations; i++){
//                 generateHalfSortedDoubleList(data, Parameters::structureSize);
                
//                 auto start = std::chrono::high_resolution_clock::now();

//                 dispatchAlgorithm(data, Parameters::structureSize); 

//                 auto end = std::chrono::high_resolution_clock::now();
//                 std::chrono::duration<double, std::milli> elapsed = end - start;
//                 totalTimeMs += elapsed.count();

//                 //  Wyczyszczamy liste double
//                 DoubleNode<T>* current = data;
//                 while (current != nullptr) {
//                     DoubleNode<T>* temp = current;
//                     current = current->next;
//                     delete temp;
//                 }
//                 data = nullptr;
//             }
            
//             // 6. out
//             avgTime = totalTimeMs / Parameters::iterations;
//             std::cout << "Average sorting of random Double List time: " << avgTime << " ms\n";
//             saveBenchmarkResult(
//                 "Badanie_A", 
//                 static_cast<int>(Parameters::algorithm),
//                 static_cast<int>(Parameters::structure),
//                 static_cast<int>(Parameters::dataType),
//                 static_cast<int>(Parameters::distribution),
//                 Parameters::structureSize,
//                 Parameters::iterations,
//                 avgTime,
//                 totalTimeMs
//             );
//             break;
//         }
//     }
// }
