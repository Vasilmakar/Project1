#include <iostream>
// #include "../data/get_data.hpp"
#include "../Parameters.h"
// #include "singleTest.hpp"
#include "singleMode.hpp"
#include "../dispatchers/singleMOde_dispatcher/dispatch_structure.hpp"
void startSingleFileMode() {
    std::string path = Parameters::inputFile;

    switch(Parameters::dataType) {
        case Parameters::DataTypes::typeInt: 
            std::cout<<"Hello 1\n";
            dispatchStructure<int>(path);
            break;
            
        case Parameters::DataTypes::typeFloat:
            dispatchStructure<float>(path); 
            break;
            
        case Parameters::DataTypes::typeDouble:
            dispatchStructure<double>(path);
            break;
            
        case Parameters::DataTypes::typeString:
            dispatchStructure<std::string>(path); 
            break;
            
        default:
            std::cout << "Blad\n";
            break;
    }
}


