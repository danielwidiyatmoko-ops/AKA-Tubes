#include <iostream>
#include <chrono>
#include <random>
#include "linkedlist.h"
#include "dataset.h" // Pastikan file ini ada di folder yang sama

using namespace std;
using namespace std::chrono;
// FUNGSI UNTUK MEMBERSIHKAN LINKED LIST AGAR TIDAK ADA MEMORY LEAK
void freeLinkedList(linkedlist &L) {
    address P = L.first;
    address temp;

    while (P != NULL) {
        temp = P;
        P = P->next;
        delete temp;
    }

    L.first = NULL;
    L.last = NULL;
}
// ======================================================================================
// FUNGSI UTAMA UNTUK MENJALANKAN BENCHMARK DENGAN LIST YANG SUDAH DIISI (dari dataset.h)
// ======================================================================================
microseconds runBenchmark(linkedlist &L, int algorithmChoice, int arr[], int n, string namaDataset) {
    createList(L);
    address P;

    // 1. Memasukkan data dari array dataset ke Linked List
    for(int i = 0; i < n; i++){
        P = alokasi(arr[i]);
        insertFirst(L, P);
    }

    cout << "\n--------------------------------------------------" << endl;
    cout << "  Pengujian: " << namaDataset << " (N = " << n << ")" << endl;
    cout << "--------------------------------------------------" << endl;

    // Tampilkan cuplikan data (agar nggak lama nunggu print semua terutama untuk dataset besar)
    if(L.first != NULL && L.first->next != NULL) {
        cout << "Before Sorting (Head...Tail): " 
             << L.first->info << ", " << L.first->next->info 
             << " ... " 
             << L.last->prev->info << ", " << L.last->info << endl;
    }

    // 2. Mulai hitung waktu
    auto start = high_resolution_clock::now();
    
    switch (algorithmChoice)
    {
    case 1:
        bubbleSort(L);
        break;
    case 2:
        insertSort(L);
        break;
    case 3:
        selectSort(L);
        break;
    case 4:
        mergeSort(L);
        break;
    case 5:
        quickSort(L);
        break;
    default:
        break;
    }
    
    auto end = high_resolution_clock::now();
    // 3. Selesai hitung waktu

    // Tampilkan cuplikan hasil
    if(L.first != NULL && L.first->next != NULL) {
        cout << "After Sorting (Head...Tail):  " 
             << L.first->info << ", " << L.first->next->info 
             << " ... " 
             << L.last->prev->info << ", " << L.last->info << endl;
    }

    auto duration = duration_cast<microseconds>(end - start);
    cout << ">> Time taken by Sort: " << duration.count() << " microseconds" << endl;
    freeLinkedList(L); // Bersihkan list setelah setiap benchmark
    return duration;
}


// ==========================================================
// FUNGSI KHUSUS GENERATE RANDOM ON-THE-FLY
// ==========================================================

void runRandomBenchmark(linkedlist &L, int algorithmChoice, int n) {
    // Setup mesin pengacak
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 10000); // Angka acak 1 - 10.000

    createList(L);
    address P;

    // Generate dan masukkan angka acak baru
    cout << "\n[PROSES] Generating " << n << " random numbers..." << endl;
    for(int i = 0; i < n; i++){
        int angkaAcak = distrib(gen); // Ambil angka baru
        P = alokasi(angkaAcak);
        insertFirst(L, P);
    }

    // Benchmark
    auto start = high_resolution_clock::now();
    switch (algorithmChoice)
    {
    case 1:
        bubbleSort(L);
        break;
    case 2:
        insertSort(L);
        break;
    case 3:
        selectSort(L);
        break;
    case 4:
        mergeSort(L);
        break;
    case 5:
        quickSort(L);
        break;
    default:
        break;
    }
    auto end = high_resolution_clock::now();
    
    auto duration = duration_cast<microseconds>(end - start);
    cout << ">> Time taken (Random Generated): " << duration.count() << " microseconds" << endl;
    
}
// ==========================================================
// FUNGSI UNTUK MENJALANKAN SEMUA BENCHMARK DAN MENABULASIKANNYA
// ==========================================================
void runAllBenchmarksandTabulate(linkedlist &L, microseconds results[5][6]) {
    for(int i = 4; i >=0; i--){
        switch(i){
            case 0:
                cout << "\n================== BUBBLE SORT BENCHMARK ==================" << endl;
                break;
            case 1:
                cout << "\n================== INSERTION SORT BENCHMARK ==================" << endl;
                break;  
            case 2:
                cout << "\n================== SELECTION SORT BENCHMARK ==================" << endl;
                break;
            case 3:
                cout << "\n================== MERGE SORT BENCHMARK ==================" << endl;
                break;  
            case 4:
                cout << "\n================== QUICK SORT BENCHMARK ==================" << endl;
                break;
        }
        for(int j = 5; j >=0; j--){
            switch(j){
                case 0:
                    results[i][j] = runBenchmark(L, i+1, rsample10, 10, "rsample10");
                    break;
                case 1:
                    results[i][j] = runBenchmark(L, i+1, rsample100, 100, "rsample100");
                    break;  
                case 2:
                    results[i][j] = runBenchmark(L, i+1, rsample1k, 1000, "rsample1k");
                    break;
                case 3:
                    results[i][j] = runBenchmark(L, i+1, rsample10k, 10000, "rsample10k");
                    break;  
                case 4:
                    results[i][j] = runBenchmark(L, i+1, rsample100k, 100000, "rsample100k");
                    break;
                case 5:
                    if (i < 3){results[i][j] = microseconds(-1); break;} //takes too long for bubble, insertion, selection sort. not bothering to run; just trust me on this
                    else{results[i][j] = runBenchmark(L, i+1, rsample1m, 1000000, "rsample1m");
                    break;}
            }
        }
    }
    cout << "\n================== BENCHMARK RESULTS ==================" << endl;
    printf("%-18s| %-12s | %-12s | %-12s | %-12s | %-12s | %-12s |\n", "Algoritma\\Dataset", "rsample10", "rsample100", "rsample1k", "rsample10k", "rsample100k", "rsample1m");
    cout << "-----------------------------------------------------------------------------------------" << endl;
    string algNames[5] = {"Bubble Sort", "Insertion Sort", "Selection Sort", "Merge Sort", "Quick Sort"};
    for(int i = 0; i < 5; i++){
        printf("%-18s|", algNames[i].c_str());
        for(int j = 0; j < 6; j++){
            printf(" %-10lldus |", results[i][j].count());
        }
        cout << endl;
    }
}
// ==========================================================
// FUNGSI MENU SELECTION DATASET SIZE
// ==========================================================
void selectDatasetSize(linkedlist &L, int algorithmChoice) {
    int pilihan;
    bool jalan = true;

    while (jalan) {
        cout << "\n===========================================" << endl;
        cout << "   DATASET SIZE SELECTION (10-1.000.000)   " << endl;
        cout << "===========================================" << endl;
        cout << "Pilih Dataset:" << endl;
        cout << "1. rsample10     (10 data)" << endl;
        cout << "2. rsample100    (100 data)" << endl;
        cout << "3. rsample1k     (1.000 data)" << endl;
        cout << "4. rsample10k    (10.000 data)" << endl;
        cout << "5. rsample100k   (100.000 data)" << endl;
        cout << "6. rsample1m   (1.000.000 data)" << endl;
        cout << "7. Random Generator (Input Manual)" << endl;
        cout << "0. Back" << endl;
        cout << "===========================================" << endl;
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: runBenchmark(L, algorithmChoice, rsample10, 10, "rsample10"); break;
            case 2: runBenchmark(L, algorithmChoice, rsample100, 100, "rsample100"); break;
            case 3: runBenchmark(L, algorithmChoice, rsample1k, 1000, "rsample1k"); break;
            case 4: runBenchmark(L, algorithmChoice, rsample10k, 10000, "rsample10k"); break;
            case 5: runBenchmark(L, algorithmChoice, rsample100k, 100000, "rsample100k"); break;
            case 6: runBenchmark(L, algorithmChoice, rsample1m, 1000000, "rsample1m"); break;
            case 7: 
                int size;
                cout << "Masukkan jumlah data yang diinginkan: ";
                cin >> size;
                runRandomBenchmark(L, algorithmChoice, size);
                break;
                case 8: //do something here;
            case 0: 
                cout << "Terima kasih!" << endl;
                jalan = false; 
                break;
            default: cout << "Pilihan tidak valid!" << endl;
        }
        
    }
}
// ==========================================================
// FUNGSI MENU SELECTION SORTING ALGORITHM
// ==========================================================
void selectSortingAlgorithm(linkedlist &L, microseconds results[5][6]) {
    int pilihan;
    bool jalan = true;

    while (jalan) {
        cout << "\n===========================================" << endl;
        cout << "   BENCHMARK SORTING ALGOS (LINKED LIST)   " << endl;
        cout << "===========================================" << endl;
        cout << "Pilih Sorting Algorithm:" << endl;
        cout << "1. Bubble Sort" << endl;                           //select one algorithm to run on different dataset sizes; no recording of results needed
        cout << "2. Insertion Sort" << endl;
        cout << "3. SelectionSort" << endl;
        cout << "4. Merge Sort" << endl;
        cout << "5. Quick Sort" << endl;
        cout << "9. Run All Benchmarks and Tabulate" << endl;       //run all algorithms and record results
        cout << "0. Keluar" << endl;
        cout << "===========================================" << endl;
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: selectDatasetSize(L,1); break;
            case 2: selectDatasetSize(L,2); break;
            case 3: selectDatasetSize(L,3); break;
            case 4: selectDatasetSize(L,4); break;
            case 5: selectDatasetSize(L,5); break;
            case 9: runAllBenchmarksandTabulate(L, results); break;
            case 0: 
                cout << "Terima kasih!" << endl;
                jalan = false; 
                break;
            default: cout << "Pilihan tidak valid!" << endl;
        }
    }
}


// ==========================================================
// MAIN PROGRAM UNTUK MENJALANKAN SEMUA FUNGSI DI ATAS DAN SEBAGAI WADAH VARIABEL
// ==========================================================
int main() {
    microseconds resultsArray[5][6]; // Menyimpan hasil benchmark
    linkedlist L;
    selectSortingAlgorithm(L,resultsArray);
    return 0;
}