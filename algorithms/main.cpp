#include "../AiZO-P1-sortingAlgorithms/Parameters.h"
#include <iostream>
#include "../algorithms/quick_sort.h"
#include "benchmark.hpp"
using namespace std;

int main(int args, char* argv[]){
    

        if (Parameters::readParameters(args - 1, argv + 1) == -1) {
            return -1;
        }

    switch(Parameters::runMode){
        
        case Parameters::RunModes::singleFile:
            cout << "Run mode --singleFile\n"; 
            sorting(Parameters::structureSize, Parameters::inputFile);
            break;

        case Parameters::RunModes::benchmark:
            cout << "Run mode --benchmark\n";
            benchmark();
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