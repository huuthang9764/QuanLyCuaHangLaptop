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

// =================== HÀM HỖ TRỢ (ARRAY) ===================

Laptop* LinearSearch_Name(const DanhSachLaptop& dsls, const char* name) {
    for (int i = 0; i < dsls.soLuong; i++) {
        if (strcmp(dsls.ds[i].tenLaptop, name) == 0) return (Laptop*)&dsls.ds[i];
    }
    return NULL;
}

Laptop* TimKiemNhiPhan_TheoMa(const DanhSachLaptop& dsls, const char* maCanTim) {
    int left = 0, right = dsls.soLuong - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int res = strcmp(dsls.ds[mid].maLaptop, maCanTim);
        if (res == 0) return (Laptop*)&dsls.ds[mid];
        if (res < 0) left = mid + 1;
        else right = mid - 1;
    }
    return NULL;
}

void SapXepLaptop_TheoMa(DanhSachLaptop& dsls) {
    for (int i = 0; i < dsls.soLuong - 1; i++) {
        for (int j = i + 1; j < dsls.soLuong; j++) {
            if (strcmp(dsls.ds[i].maLaptop, dsls.ds[j].maLaptop) > 0) {
                Laptop temp = dsls.ds[i];
                dsls.ds[i] = dsls.ds[j];
                dsls.ds[j] = temp;
            }
        }
    }
}

// =================== HÀM BENCHMARK CHÍNH ===================

void RunFullBenchmark(DanhSachLaptop& dsls) {
    if (dsls.soLuong == 0) {
        cout << ">> [BENCHMARK] Data empty!\n";
        return;
    }

    srand((unsigned int)time(NULL));

    cout << "\n================ KET QUA BENCHMARK (ARRAY) ================\n";
    cout << "So luong phan tu Laptop: " << dsls.soLuong << endl;
    cout << "-----------------------------------------------------------\n";

    // --- 1. GHI FILE ---
    DoBenchmark("  [1] Ghi File (Block Dump):       ", [&]() {
        ofstream f("bench_arr.dat", ios::binary);
        if (f.is_open()) {
            f.write((char*)&dsls.soLuong, sizeof(int));
            f.write((char*)dsls.ds, sizeof(Laptop) * dsls.soLuong);
            f.close();
        }
        });

    // --- 2. ĐỌC FILE ---
    DoBenchmark("  [2] Doc File (Block Load):       ", [&]() {
        DanhSachLaptop dsTemp;
        dsTemp.soLuong = 0;
        ifstream f("bench_arr.dat", ios::binary);
        if (f.is_open()) {
            f.read((char*)&dsTemp.soLuong, sizeof(int));
            if (dsTemp.soLuong <= MAX_LAPTOP) {
                f.read((char*)dsTemp.ds, sizeof(Laptop) * dsTemp.soLuong);
            }
            f.close();
        }
        });
    remove("bench_arr.dat");

    // --- 3. SẮP XẾP ---
    cout << "\n--- DO TOC DO SAP XEP ---\n";
    DoBenchmark("  [3a] Sort by Name (Selection Sort): ", [&]() {
        SapXepLaptop_TheoTen(dsls);
        });
    DoBenchmark("  [3b] Sort by Price (Selection Sort):", [&]() {
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
    cout << "\n------------------------------------------------------------------\n";

    // =======================================================
    // PHẦN 1: SO SÁNH TÌM KIẾM THEO TÊN (NAME)
    // =======================================================
    cout << "\n--- [ROUND 1] TIM KIEM THEO TEN ---\n";

    SapXepLaptop_TheoTen(dsls);

    // [1A] LINEAR SEARCH - NAME
    double time = 0;

    char tenCanTim[50];
    int currentTarget = 0;
    for (int k = 0; k < dsls.soLuong; k++) {
        if (currentTarget >= MAXTEST) break;
        if (k == indexTest[currentTarget]) {

            strcpy(tenCanTim, dsls.ds[k].tenLaptop);

            time +=DoBenchmark("  [A] Linear Search (Name): ", [&]() {
                LinearSearch_Name(dsls, tenCanTim);
                });

            while (currentTarget < MAXTEST && indexTest[currentTarget] == k) currentTarget++;
        }
    }
    cout << "\n Thoi gian trung binh cua 10 lan do " << (double)time / 10 <<" nanoseconds " << endl;
    long long t1_LinearName = DoBenchmark("  [A] Linear Search (Name): ", [&]() {
        char tenCanTim[50];
        int currentTarget = 0;
        for (int k = 0; k < dsls.soLuong; k++) {
            if (currentTarget >= MAXTEST) break;
            if (k == indexTest[currentTarget]) {

                strcpy(tenCanTim, dsls.ds[k].tenLaptop);

                LinearSearch_Name(dsls, tenCanTim);

                while (currentTarget < MAXTEST && indexTest[currentTarget] == k) currentTarget++;
            }
        }
        });

    // [1B] BINARY SEARCH - NAME
    long long t1_BinaryName = DoBenchmark("  [B] Binary Search (Name): ", [&]() {
        char tenCanTim[50];
        int currentTarget = 0;
        for (int k = 0; k < dsls.soLuong; k++) {
            if (currentTarget >= MAXTEST) break;
            if (k == indexTest[currentTarget]) {
                strcpy(tenCanTim, dsls.ds[k].tenLaptop);

                TimKiemNhiPhan_TheoTen(dsls, tenCanTim);

                while (currentTarget < MAXTEST && indexTest[currentTarget] == k) currentTarget++;
            }
        }
        });

    if (t1_BinaryName > 0)
        cout << "  >> Name Ratio (Linear/Binary): " << (double)t1_LinearName / t1_BinaryName << "x\n";


    // =======================================================
    // PHẦN 2: SO SÁNH TÌM KIẾM THEO MÃ (ID)
    // =======================================================
    cout << "\n--- [ROUND 2] TIM KIEM THEO MA (ID) ---\n";

    SapXepLaptop_TheoMa(dsls);

    // [2A] LINEAR SEARCH - ID
    long long t2_LinearID = DoBenchmark("  [C] Linear Search (ID):   ", [&]() {
        char maCanTim[20];
        int currentTarget = 0;
        for (int k = 0; k < dsls.soLuong; k++) {
            if (currentTarget >= MAXTEST) break;
            if (k == indexTest[currentTarget]) {
                strcpy(maCanTim, dsls.ds[k].maLaptop);

                TimKiemLaptop(dsls, maCanTim);

                while (currentTarget < MAXTEST && indexTest[currentTarget] == k) currentTarget++;
            }
        }
        });

    // [2B] BINARY SEARCH - ID
    long long t2_BinaryID = DoBenchmark("  [D] Binary Search (ID):   ", [&]() {
        char maCanTim[20];
        int currentTarget = 0;
        for (int k = 0; k < dsls.soLuong; k++) {
            if (currentTarget >= MAXTEST) break;
            if (k == indexTest[currentTarget]) {
                strcpy(maCanTim, dsls.ds[k].maLaptop);

                TimKiemNhiPhan_TheoMa(dsls, maCanTim);

                while (currentTarget < MAXTEST && indexTest[currentTarget] == k) currentTarget++;
            }
        }
        });

    if (t2_BinaryID > 0)
        cout << "  >> ID Ratio (Linear/Binary):   " << (double)t2_LinearID / t2_BinaryID << "x\n";

    delete[] indexTest;
    cout << "==================================================================\n\n";
}