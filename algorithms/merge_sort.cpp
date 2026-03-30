#include <vector>
#include <iostream>

using namespace std;

template <typename T>
void mergeHalfs(std::vector<T>& A, T left, int mid, T right){
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);
    for(int i = 0; i < n1; i++) L[i] = A[left+i];
    for(int j = 0; j < n2; j++) R[j] = A[mid+1+j];

    int i = 0 , j = 0, k = left;
    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            A[k++] = L[i++];
        }else{
            A[k++] = R[j++];
        }
    }

    while(i < n1) A[k++] = L[i++];
    while(j < n2) A[k++] = R[j++];
}

template <typename T>
void mergeSort(std::vector<T>& A, T left, T right) {
    if(left < right){
        int mid = left + (right - left) / 2;
        mergeSort(A, left, mid);
        mergeSort(A, mid+1, right);
        mergeHalfs(A, left, mid, right);
    }

}
