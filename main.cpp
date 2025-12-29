#include <iostream>
#include <chrono>
#include <random>
#include "linkedlist.h"
#include "dataset.h" // Pastikan file ini ada di folder yang sama

using namespace std;
using namespace std::chrono;

// ==========================================================
// FUNGSI UTAMA UNTUK MENJALANKAN BENCHMARK
// ==========================================================
void runBenchmark(int arr[], int n, string namaDataset) {
    linkedlist L;
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

    // Tampilkan cuplikan data (Cek apakah list kosong/sedikit)
    if(L.first != NULL && L.first->next != NULL) {
        cout << "Before Sorting (Head...Tail): " 
             << L.first->info << ", " << L.first->next->info 
             << " ... " 
             << L.last->prev->info << ", " << L.last->info << endl;
    }

    // 2. Mulai hitung waktu
    auto start = high_resolution_clock::now();
    
    mergeSort(L); // Panggil algoritma sorting kamu
    
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
}

// ==========================================================
// FUNGSI KHUSUS GENERATE RANDOM ON-THE-FLY
// ==========================================================
void runRandomBenchmark(int n) {
    // Setup mesin pengacak
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 10000); // Angka acak 1 - 10.000

    linkedlist L;
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
    mergeSort(L);
    auto end = high_resolution_clock::now();
    
    auto duration = duration_cast<microseconds>(end - start);
    cout << ">> Time taken (Random Generated): " << duration.count() << " microseconds" << endl;
}

// ==========================================================
// MAIN PROGRAM (UI/MENU)
// ==========================================================
int main() {
    int pilihan;
    bool jalan = true;

    while (jalan) {
        cout << "\n========================================" << endl;
        cout << "   BENCHMARK MERGE SORT (LINKED LIST)   " << endl;
        cout << "========================================" << endl;
        cout << "Pilih Dataset:" << endl;
        cout << "1. rsample10     (10 data)" << endl;
        cout << "2. rsample100    (100 data)" << endl;
        cout << "3. rsample1k     (1.000 data)" << endl;
        cout << "4. rsample10k    (10.000 data)" << endl;
        cout << "5. rsample100k   (100.000 data)" << endl;
        cout << "6. Random Generator (Input Manual)" << endl;
        cout << "0. Keluar" << endl;
        cout << "========================================" << endl;
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: runBenchmark(rsample10, 10, "rsample10"); break;
            case 2: runBenchmark(rsample100, 100, "rsample100"); break;
            case 3: runBenchmark(rsample1k, 1000, "rsample1k"); break;
            case 4: runBenchmark(rsample10k, 10000, "rsample10k"); break;
            case 5: runBenchmark(rsample100k, 100000, "rsample100k"); break;
            case 6: 
                int size;
                cout << "Masukkan jumlah data yang diinginkan: ";
                cin >> size;
                runRandomBenchmark(size);
                break;
            case 0: 
                cout << "Terima kasih!" << endl;
                jalan = false; 
                break;
            default: cout << "Pilihan tidak valid!" << endl;
        }
    }
    return 0;
}