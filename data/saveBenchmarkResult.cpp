#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <iostream>
#include "Parameters.h"
#include "saveBenchmarkResult.hpp"


// Funkcja pomocnicza pobierająca aktualny czas systemowy, postaci "YYYY-MM-DD HH:MM:SS"
std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_c);
    char timeBuffer[20];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", now_tm);
    return std::string(timeBuffer);
}

// Zapisuje "surowe" wyniki pojedynczej iteracji testu, dane dopisywane do pliku csv z wynikami
void saveRawResult(const std::string& badanieName, 
                   int algorithm, int structure, int dataType, int distribution, 
                   int size, int iterationNo, double iterationTimeMs) {
               
    // Ustalenie parametru, w zależnności od wybranego algorytmu(dla qucik sort parametry dla pivota, dla Shell Sort - parametr odstępu) 
    int algParam = (algorithm == static_cast<int>(Parameters::Algorithms::quick)) ? static_cast<int>(Parameters::pivot) : 
                   (algorithm == static_cast<int>(Parameters::Algorithms::shell)) ? static_cast<int>(Parameters::shellParameter) : 0;

    // Sprawdzanie, czy plik z wynikami jest pusty lub nie istnieje, 
    // aby wiedzieć, czy konieczne jest dopisanie nagłówka kolumn
    std::ifstream checkFile(Parameters::resultsFile);
    bool isNewFile = checkFile.peek() == std::ifstream::traits_type::eof() || !checkFile.is_open();
    checkFile.close();


    //Otwieramy plik w trybie dopisywania
    std::ofstream file(Parameters::resultsFile, std::ios::app);
    if (file.is_open()) {
        if (isNewFile) file << "Timestamp,Badanie,Alg,Param,Struct,Type,Dist,Size,Iter_No,Time_ms\n";
        
        file << getCurrentTime() << "," << badanieName << "," << algorithm << "," << algParam << ","
             << structure << "," << dataType << "," << distribution << "," << size << ","
             << iterationNo << "," << iterationTimeMs << "\n";
        file.close();
    }
}

//Zapisuje zagregowane statystyki z całej serii testów
// Zamiast pojedynczych czasów, zapisuje średnią, wartość minimalną i maksymalną
void saveAggregatedResult(const std::string& badanieName, 
                          int algorithm, int structure, int dataType, int distribution, 
                          int size, int iterations, double avgTime, double minTime, double maxTime) {
                          
  int algParam = (algorithm == static_cast<int>(Parameters::Algorithms::quick)) ? static_cast<int>(Parameters::pivot) : 
                   (algorithm == static_cast<int>(Parameters::Algorithms::shell)) ? static_cast<int>(Parameters::shellParameter) : 0;
    
    //Dynamiczne generowanie nazwy pliku dla wyników uśrednionych.
    std::string summaryFileName = Parameters::resultsFile;
    size_t dotPos = summaryFileName.find_last_of('.');
    if (dotPos != std::string::npos) {
        summaryFileName.insert(dotPos, "_usrednione");
    } else {
        summaryFileName += "_usrednione.csv";
    }

    std::ifstream checkFile(summaryFileName);
    bool isNewFile = checkFile.peek() == std::ifstream::traits_type::eof() || !checkFile.is_open();
    checkFile.close();

    std::ofstream file(summaryFileName, std::ios::app);
    if (file.is_open()) {
        if (isNewFile) file << "Timestamp,Badanie,Alg,Param,Struct,Type,Dist,Size,Iterations,AvgTime_ms,MinTime_ms,MaxTime_ms\n";
        
        file << getCurrentTime() << "," << badanieName << "," << algorithm << "," << algParam << ","
             << structure << "," << dataType << "," << distribution << "," << size << ","
             << iterations << "," << avgTime << "," << minTime << "," << maxTime << "\n";
        file.close();
    }
}