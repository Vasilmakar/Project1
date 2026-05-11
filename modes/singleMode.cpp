#include <iostream>
#include "Parameters.h"
#include "singleMode.hpp"
#include "dispatchers/singleMOde_dispatcher/dispatch_structure.hpp"

// inicjalizacja trybu singleFile
/// Etap definiowania trybu danych
void startSingleFileMode() {
    std::string path = Parameters::inputFile;

    switch(Parameters::dataType) {
        case Parameters::DataTypes::typeInt: 
            dispatchStructure<int>(path);
            break;
            
        case Parameters::DataTypes::typeFloat:
            dispatchStructure<float>(path); 
            break;
            
        case Parameters::DataTypes::typeDouble:

            dispatchStructure<double>(path);
            break;
            
        case Parameters::DataTypes::typeChar:        
            dispatchStructure<char>(path);
            break;

        case Parameters::DataTypes::typeString:       
            dispatchStructure<std::string>(path); 
            break;

        case Parameters::DataTypes::tyleUnsignedInt:
            dispatchStructure<unsigned int>(path); 
            break;

        case Parameters::DataTypes::typeUnsignedLong:  
            dispatchStructure<unsigned long>(path); 
            break;

        case Parameters::DataTypes::typeUnsignedChar: 
            dispatchStructure<unsigned char>(path); 
            break;
            
        default:
            std::cout << "Błąd: Nieznany typ danych\n";            
            break;
    }
}


