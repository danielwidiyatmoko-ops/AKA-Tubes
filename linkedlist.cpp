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
void insertLast(linkedlist &L, address P){//insert at the end of the list
    if(L.last == NULL){
        L.first = P;
        L.last = P;
    } else {
        L.last->next = P;
        P->prev = L.last;
        L.last = P;
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
    address P;
    if(L.first == NULL){//empty list
        // nothing to sort
    } else if (L.first == L.last){//only one element
        // nothing to sort
    } else { //more than one element aka something to sort
        bool swapped;
        do {
            swapped = false;
            P = L.first;
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
}
void insertSort(linkedlist &L){
    address P;
    address Q;
    if(L.first == NULL){  //empty list
        // nothing to sort
    }else if (L.first == L.last){ //only one element
        // nothing to sort
    } else { //more than one element aka something to sort
        P=L.first;
        while(P!= nullptr){
            Q = P->next;
            while(Q != nullptr){
                if(P->info > Q->info){
                    //swap info
                    int temp = P->info;
                    P->info = Q->info;
                    Q->info = temp;
                }
                Q = Q->next;
            }
            P = P->next;
        }
    }
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
// --- Helper Functions for Merge Sort --- //

// Merges two sorted lists (first node as a) and (first node as b)
address mergeLists(address a, address b) {
    // 1. Base cases
    if (a == NULL) return b;
    if (b == NULL) return a;

    address head = NULL;
    address tail = NULL;

    // 2. Pick the initial head
    if (a->info <= b->info) {
        head = a;
        a = a->next;
    } else {
        head = b;
        b = b->next;
    }
    
    // Maintain the double link structure
    head->prev = NULL;
    tail = head;

    // 3. Loop while both lists have data
    while (a != NULL && b != NULL) {
        if (a->info <= b->info) {
            tail->next = a;
            a->prev = tail; 
            tail = a;
            a = a->next;
        } else {
            tail->next = b;
            b->prev = tail; 
            tail = b;
            b = b->next;
        }
    }

    // 4. Attach the remaining part (if any)
    if (a != NULL) {
        tail->next = a;
        a->prev = tail;
    } else if (b != NULL) {
        tail->next = b;
        b->prev = tail;
    }

    return head;
}

// Splits the list into two halves
address getMiddle(address head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    address slow = head;
    address fast = head->next; 

    // Move fast by two and slow by one
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    return slow; 
}

// The recursive core function
address mergeSortRec(address head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    address middle = getMiddle(head);
    address nextToMiddle = middle->next;

    // Cut the list
    middle->next = NULL;
    if (nextToMiddle != NULL) {
        nextToMiddle->prev = NULL;
    }

    // Recursively sort both halves
    address left = mergeSortRec(head);
    address right = mergeSortRec(nextToMiddle);

    // Merge them back
    return mergeLists(left, right);
}

void mergeSort(linkedlist &L) {
    if (L.first == NULL || L.first->next == NULL) return;
    L.first = mergeSortRec(L.first);
    address P = L.first;
    while (P->next != NULL) {
        P = P->next;
    }
    L.last = P;
}
void swapData(address a, address b) {
    int temp = a->info;
    a->info = b->info;
    b->info = temp;
}
address partition(address low, address high) {
    int pivotValue = high->info;
    address i = low->prev; 
    
    for (address j = low; j != high; j = j->next) {
        if (j->info <= pivotValue) {
            if (i == NULL) i = low;
            else i = i->next;
            
            swapData(i, j);
        }
    }
    if (i == NULL) i = low;
    else i = i->next;
    
    swapData(i, high);
    return i; // return the pivot node
}

void quickSortRec(address low, address high) {
    if (high != NULL && low != high && low != high->next) {
        address p = partition(low, high);
        
        if (p->prev != NULL) {
             quickSortRec(low, p->prev);
        }
        
        if (p->next != NULL) {
            quickSortRec(p->next, high);
        }
    }
}

void quickSort(linkedlist &L) {
    if (L.first == NULL || L.first == L.last) return;
    quickSortRec(L.first, L.last);
}