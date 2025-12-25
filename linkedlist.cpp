#include <iostream>
#include "linkedlist.h"
using namespace std;

void createList(linkedlist &L){
    L.first = NULL;
    L.last = NULL;
}   
address alokasi(int x){
    address P = new data;
    P->info = x;
    P->next = NULL;
    P->prev = NULL;
    return P;
}
void insertFirst(linkedlist &L, address P){//insert at the beginning of the list
    if(L.first == NULL){
        L.first = P;
        L.last = P;
    } else {
        P->next = L.first;
        L.first->prev = P;
        L.first = P;
    }
}
void printInfo(linkedlist L){ //print from first to last in the list
    address P = L.first;
    while(P != NULL){
        cout << P->info << " ";
        P = P->next;
    }
    cout << endl;
}

void bubbleSort(linkedlist &L){
    if(L.first == NULL) return; //empty list
    bool swapped;
    do {
        swapped = false;
        address P = L.first;
        while(P->next != NULL){
            if(P->info > P->next->info){
                //swap info
                int temp = P->info;
                P->info = P->next->info;
                P->next->info = temp;
                swapped = true;
            }
            P = P->next;
        }
    } while(swapped);
}
void insertSort(linkedlist &L){
    if(L.first == NULL) return; //empty list
    address sorted = NULL;
    address current = L.first;
    while(current != NULL){
        address next = current->next;
        //insert current in sorted list
        if(sorted == NULL || sorted->info >= current->info){
            current->next = sorted;
            if(sorted != NULL) sorted->prev = current;
            sorted = current;
            sorted->prev = NULL;
        } else {
            address temp = sorted;
            while(temp->next != NULL && temp->next->info < current->info){
                temp = temp->next;
            }
            current->next = temp->next;
            if(temp->next != NULL) temp->next->prev = current;
            temp->next = current;
            current->prev = temp;
        }
        current = next;
    }
    L.first = sorted;
    //update last pointer
    address P = L.first;
    while(P->next != NULL){
        P = P->next;
    }
    L.last = P;
}
void selectSort(linkedlist &L){
    if(L.first == NULL) return; //empty list
    address P = L.first;
    while(P != NULL){
        address min = P;
        address Q = P->next;
        while(Q != NULL){
            if(Q->info < min->info){
                min = Q;
            }
            Q = Q->next;
        }
        //swap info
        if(min != P){
            int temp = P->info;
            P->info = min->info;
            min->info = temp;
        }
        P = P->next;
    }
}
void mergeSort(linkedlist &L){
    
}

