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
    printInfo(L); // Output: 5
    return 0;
}