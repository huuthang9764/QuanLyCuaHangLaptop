#pragma once
#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "thuvien.h"
#include <iostream>
#include <chrono>
#include <string>
#include <functional> 

using namespace std;
using namespace std::chrono;

// =================== HÀM TIỆN ÍCH ĐO THỜI GIAN CHUNG ===================

template <typename Func>
long long DoBenchmark(const char* label, Func func) {
    cout << label;
    cout.flush();  

    auto start = chrono::high_resolution_clock::now();
    func();        
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << duration << " nanoseconds\n";

    return duration;
}

// Các hàm chạy benchmark cũ
void RunFullBenchmark(DanhSachLaptop& dsls);

#endif