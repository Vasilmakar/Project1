#include <iostream>
#include "../algorithms/quick_sort.h"


namespace Generation{

    template <typename T>
    void descending(int size){
        T *tab = generate(size);
        quick_sort(tab) 


    }

    void ascending(){}

    void partial(){}

    template <typename T>
    T* generate(T* tab, int size){
        srand(time(0));
        int i = 0;
        while(i<size){
            tab[i] = rand() % size;
            i++;
        }
        return tab;

    }
}