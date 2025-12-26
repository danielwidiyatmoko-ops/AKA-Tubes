#include <iostream>
#include <chrono>
#include "linkedlist.h"
#include "dataset.h"
using namespace std;
using namespace std::chrono;

int main(){
    linkedlist L;
    createList(L);
    address P1;
    for(int i=0; i<10000; i++){
        P1 = alokasi(sample10000[i]);
        insertFirst(L, P1);
    }
    cout << "Before Sorting: ";
    printInfo(L);
    auto start = high_resolution_clock::now();
    mergeSort(L);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "After Merge Sort: ";   
    printInfo(L);
    cout << "Time taken by Merge Sort: " << duration.count() << " microseconds" << endl;
    return 0;
}