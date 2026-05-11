#include "Parameters.h"
#include <iostream>
#include "modes/singleMode.hpp"
#include "modes/benchmark.hpp"
using namespace std;


// Główna funkcja wejściowa programu
int main(int args, char* argv[]){
    
        // Wczytywanie i parsowanie argumentów przekazanych z wiersza poleceń.
    // Pomijamy pierwszy argument (argv[0]), ponieważ jest to po prostu ścieżka do pliku wykonywalnego.
        if (Parameters::readParameters(args - 1, argv + 1) == -1) {
            return -1;
        }

        // Switch dla wyboru trybu programu podany w parametrach uruchamiania
    switch(Parameters::runMode){
        
        // Tryb sortowanie pojedynczego pliku wejściowego
        case Parameters::RunModes::singleFile:
            cout << "Run mode --singleFile\n"; 
            startSingleFileMode();
            break;

            //Tryb testów wydajności algorytmów i struktur
        case Parameters::RunModes::benchmark:
            cout << "Run mode --benchmark\n";
            startBenchmark();
            break;

            // Tryb informacyjny 
        case Parameters::RunModes::help:
            Parameters::help();
            break;

        default:
            std::cout << "Wybrany tryb jest jeszcze w trakcie implementacji...\n";
            break;
    }

    return 0;
}