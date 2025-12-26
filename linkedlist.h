#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

typedef struct data *address; 

struct data{
    int info;
    address next;
    address prev;
};

struct linkedlist{
    address first;
    address last;
};

//basic operation
void createList(linkedlist &L);
address alokasi(int x);
void insertFirst(linkedlist &L, address P);
void insertLast(linkedlist &L, address P);

//sorting operation
void bubbleSort(linkedlist &L);
void insertSort(linkedlist &L);
void selectSort(linkedlist &L);
void mergeSort(linkedlist &L);
void quickSort(linkedlist &L);
//output operation
void printInfo(linkedlist L);//print from first to last in the list;
#endif // LINKEDLIST_H_INCLUDED
