#include <iostream>
#include "linkedlist.h"
#include "dataset.h"
using namespace std;

int main(){
    linkedlist L;
    createList(L);
    address P1;
    for(int i=0; i<10; i++){
        P1 = alokasi(sample10[i]);
        insertFirst(L, P1);
    }
    cout << "Before Sorting: ";
    printInfo(L);
    bubbleSort(L);
    cout << endl;
    cout << "After Bubble Sort: ";
    printInfo(L);
    return 0;
}