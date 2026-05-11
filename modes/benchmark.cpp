#include <iostream>
#include "Parameters.h"
#include "dispatchers/benchmark_dispatcher/dispatch_dist.hpp"
#include "benchmark.hpp"
using namespace std;


// Inicjalizacja trybu benchmark
void startBenchmark() {

  // Na tym etapie określamy tym danych na których będziemy operować
     switch(Parameters::dataType) {
        // Typy standardowe (całkowitoliczbowe i zmiennoprzecinkowe)
        case Parameters::DataTypes::typeInt: 
            dispatchArrayDistribution<int>();
            break;
            
        case Parameters::DataTypes::typeFloat:
            dispatchArrayDistribution<float>(); 
            break;
            
        case Parameters::DataTypes::typeDouble:

            dispatchArrayDistribution<double>();
            break;
            
            // Typy tekstowe i znakowe
        case Parameters::DataTypes::typeString:
            dispatchArrayDistribution<std::string>(); 
            break;

        case Parameters::DataTypes::typeChar:
            dispatchArrayDistribution<char>(); 
            break;

        // Typy całkowitoliczbowe bez znaku (unsigned)
        case Parameters::DataTypes::tyleUnsignedInt:
            dispatchArrayDistribution<unsigned int>(); 
            break;
            
        case Parameters::DataTypes::typeUnsignedLong:

            dispatchArrayDistribution<unsigned long>();
            break;
            
        case Parameters::DataTypes::typeUnsignedChar:
            dispatchArrayDistribution<unsigned char>(); 
            break;
            
        default:
            std::cout << "Błąd: Nieobsługiwany typ danych do testowania!\n";
            break;
    }
}
