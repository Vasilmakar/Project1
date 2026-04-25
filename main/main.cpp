#include "../Parameters.h"
#include <iostream>
// #include "../algorithms/quick_sort.h"
// #include "benchmark.hpp"
#include "../modes/singleMode.hpp"
using namespace std;

int main(int args, char* argv[]){
    

        if (Parameters::readParameters(args - 1, argv + 1) == -1) {
            return -1;
        }

    switch(Parameters::runMode){
        
        case Parameters::RunModes::singleFile:
            cout << "Run mode --singleFile\n"; 
            startSingleFileMode();
            break;

        case Parameters::RunModes::benchmark:
            cout << "Run mode --benchmark\n";
            // benchmark();
            break;

        case Parameters::RunModes::help:
            Parameters::help();
            break;

        default:
            std::cout << "W trakcie...\n";
            break;
    }

    return 0;
}