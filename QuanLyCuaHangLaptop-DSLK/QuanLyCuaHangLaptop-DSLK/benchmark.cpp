#define _CRT_SECURE_NO_WARNINGS
#include "benchmark.h"
#include "xuly.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Hàm tìm kiếm tuần tự
Laptop* LinearSearch_Name(const DanhSachLaptop& dsls, const char* name) {
    for (NodeLaptop* k = dsls.head; k != NULL; k = k->next) {
        if (strcmp(k->data.tenLaptop, name) == 0) return &k->data;
    }
    return NULL;
}


void SapXepLaptop_TheoMa(DanhSachLaptop& dsls) {
    for (NodeLaptop* i = dsls.head; i != NULL; i = i->next) {
        for (NodeLaptop* j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->data.maLaptop, j->data.maLaptop) > 0) {
                Laptop temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}


void RunFullBenchmark(DanhSachLaptop& dsls) {
    if (dsls.head == NULL) {
        cout << ">> [BENCHMARK] Data empty!\n";
        return;
    }

    srand((unsigned int)time(NULL));

    cout << "\n============= KET QUA BENCHMARK (LINKED LIST) =============\n";
    cout << "So luong phan tu Laptop: " << dsls.soLuong << endl;
    cout << "-----------------------------------------------------------\n";

    // --- 1. GHI FILE ---
    DoBenchmark("  [1] Ghi File (Linear Dump):      ", [&]() {
        ofstream f("bench_link.dat", ios::binary);
        if (f.is_open()) {
            f.write((char*)&dsls.soLuong, sizeof(int));
            for (NodeLaptop* k = dsls.head; k != NULL; k = k->next) {
                f.write((char*)&k->data, sizeof(Laptop));
            }
            f.close();
        }
        });

    // --- 2. DOC FILE ---
    DoBenchmark("  [2] Doc File (Node Allocation):  ", [&]() {
        DanhSachLaptop dsTemp;
        dsTemp.head = dsTemp.tail = NULL;

        ifstream f("bench_link.dat", ios::binary);
        if (f.is_open()) {
            int n;
            f.read((char*)&n, sizeof(int));
            for (int i = 0; i < n; i++) {
                Laptop val;
                f.read((char*)&val, sizeof(Laptop));

                NodeLaptop* p = new NodeLaptop;
                p->data = val; p->next = NULL; p->pre = dsTemp.tail;

                if (dsTemp.tail) dsTemp.tail->next = p;
                else dsTemp.head = p;
                dsTemp.tail = p;
            }
            f.close();
        }
        // Dọn dẹp
        while (dsTemp.head) {
            NodeLaptop* t = dsTemp.head;
            dsTemp.head = dsTemp.head->next;
            delete t;
        }
        });
    remove("bench_link.dat");

    // --- 3. SẮP XẾP ---
    cout << "\n--- DO TOC DO SAP XEP ---\n";
    DoBenchmark("  [3a] Sort by Name (String compare): ", [&]() {
        SapXepLaptop_TheoTen(dsls);
        });
    DoBenchmark("  [3b] Sort by Price (Int compare):   ", [&]() {
        SapXepLaptop_TheoGia(dsls);
        });

    // --- 4. SO SÁNH TÌM KIẾM ---
    cout << "\n---------------- SO SANH TIM KIEM ----------------\n";

    // --- 1. CHUẨN BỊ DỮ LIỆU TEST (INDEX SWEEP) ---
    int MAXTEST = 10;
    int* indexTest = new int[MAXTEST];

    for (int i = 0; i < MAXTEST; i++) {
        indexTest[i] = rand() % dsls.soLuong;
    }
    sort(indexTest, indexTest + MAXTEST);

    cout << "Muc tieu: Quét 10 vi tri ngau nhien: ";
    for (int i = 0; i < MAXTEST; i++) cout << indexTest[i] << " ";
    cout << "\n-------------------------------------------------------------\n";

    // =======================================================
    // PHẦN 1: SO SÁNH TÌM KIẾM THEO TÊN (NAME)
    // =======================================================
    cout << "\n--- [ROUND 1] TIM KIEM THEO TEN ---\n";

    SapXepLaptop_TheoTen(dsls);

    // [1A] LINEAR SEARCH - NAME
    /*DoBenchmark("  [A] Linear Search (Name): ", [&]() {
        char tenCanTim[50];
        int currentTarget = 0;
        int k = 0;

        for (NodeLaptop* p = dsls.head; p != NULL; p = p->next) {
            if (currentTarget >= MAXTEST) break;

            if (k == indexTest[currentTarget]) {
                strcpy(tenCanTim, p->data.tenLaptop);

                LinearSearch_Name(dsls, tenCanTim);

                while (currentTarget < MAXTEST && indexTest[currentTarget] == k) currentTarget++;
            }
            k++;
        }
        });*/

    char tenCanTim[50];
    int currentTarget = 0;
    int k = 0;
    double time = 0;
    for (NodeLaptop* p = dsls.head; p != NULL; p = p->next) {
        if (currentTarget >= MAXTEST) break;

        if (k == indexTest[currentTarget]) {
            strcpy(tenCanTim, p->data.tenLaptop);
            time += DoBenchmark("  [A] Linear Search (Name): ", [&]() {
                LinearSearch_Name(dsls, tenCanTim);  
               
            });


            while (currentTarget < MAXTEST && indexTest[currentTarget] == k) currentTarget++;
        }
        k++;
    }
    cout << "\n Thoi gian trung binh cua 10 lan do " << (double)time / 10 << endl;cout << (double)time/10;
    // [1B] BINARY SEARCH - NAME
    cout << "  [B] Binary Search (Name):   N/A (DSLK khong ho tro)\n";


    // =======================================================
    // PHẦN 2: SO SÁNH TÌM KIẾM THEO MÃ (ID)
    // =======================================================
    cout << "\n--- [ROUND 2] TIM KIEM THEO MA (ID) ---\n";

    SapXepLaptop_TheoMa(dsls); 

    // [2A] LINEAR SEARCH - ID
    DoBenchmark("  [C] Linear Search (ID):   ", [&]() {
        char maCanTim[20];
        int currentTarget = 0;
        int k = 0;

        for (NodeLaptop* p = dsls.head; p != NULL; p = p->next) {
            if (currentTarget >= MAXTEST) break;

            if (k == indexTest[currentTarget]) {
                strcpy(maCanTim, p->data.maLaptop);

                TimKiemLaptop(dsls, maCanTim);

                while (currentTarget < MAXTEST && indexTest[currentTarget] == k) currentTarget++;
            }
            k++;
        }
        });

    // [2B] BINARY SEARCH - ID
    cout << "  [D] Binary Search (ID):     N/A (DSLK khong ho tro)\n";

    delete[] indexTest; // Dọn dẹp
    cout << "=============================================================\n\n";
}