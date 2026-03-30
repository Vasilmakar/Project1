#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "../data_generator/generate_random.hpp"
#include "../data/get_data.hpp"
#include "quick_sort.h"

using namespace std;

// wyszukiwanie pivota
int partition(std::vector<int>& A, int p, int r) {
    int x = A[p]; 
    int i = p - 1;
    int j = r + 1;
    while (true) {
        do { j--; } while (A[j] > x);
        do { i++; } while (A[i] < x);
        if (i < j) std::swap(A[i], A[j]);
        else return j;
    }
}

// rekurencyjna funkcja sortowania
void quickSort(std::vector<int>& A, int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        quickSort(A, p, q);
        quickSort(A, q + 1, r);
    }
}


int sorting(int count, std::string file) {

    generateData(count, file);

    vector<int> data1 = get_data(file);

    std::cout<<"Unsorted array look: ";
    for (int x : data1) std::cout << x << " ";
    std::cout<<"\n";
    if (!data1.empty()) {
        quickSort(data1, 0, data1.size() - 1);
        cout << "Success sorting comple!" << endl;
    } else {
        cout << "Error: No data to sort(file is unreached or empty)!" << endl;
    }
    
    std::cout << "Sorted array by Quick Sort: ";
    for (int x : data1) std::cout << x << " ";
    std::cout << std::endl;

    return 0;
}