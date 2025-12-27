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
    for(int i=0; i<10e5; i++){
        P1 = alokasi(rsample100k[i]);
        insertFirst(L, P1);
    }
    cout << "Before Sorting: ";
    cout << L.first->info <<", "<<L.first->next->info << " ... " <<L.last->prev->info << ", " << L.last->info << endl;
    auto start = high_resolution_clock::now();
    mergeSort(L);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "After Sort: ";   
    cout << L.first->info <<", "<<L.first->next->info << " ... " <<L.last->prev->info << ", " << L.last->info << endl;
    cout << "Time taken by Sort: " << duration.count() << " microseconds" << endl;
    return 0;
}