#pragma once
#include <string>

// Deklaracja funkcji zapisującej surowe wyniki dla każdej pojedynczej iteracji
void saveRawResult(const std::string& badanieName,
                   int algorithm, 
                   int structure, 
                   int dataType, 
                   int distribution, 
                   int size, 
                   int iterationNo, 
                   double iterationTimeMs);

// Deklaracja funkcji zapisującej zagregowane statystyki po wykonaniu całej serii testów
void saveAggregatedResult(const std::string& badanieName, 
                          int algorithm, 
                          int structure, 
                          int dataType, 
                          int distribution, 
                          int size, 
                          int iterations, 
                          double avgTime, 
                          double minTime, 
                          double maxTime);