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
// Hàm nhận vào:
// 1. label: Chuỗi văn bản hiển thị (vd: "[1] Ghi File...")
// 2. func: Một hàm hoặc đoạn code (lambda) cần thực thi
// Trả về: Thời gian chạy (microseconds)
template <typename Func>
long long DoBenchmark(const char* label, Func func) {
    cout << label;
    cout.flush();  // Ngăn cout dính vào thời gian đo

    auto start = chrono::high_resolution_clock::now();
    func();                    // ❗ CHỈ chứa thuật toán cần đo
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << duration << " nanoseconds\n";

    return duration;
}

// Các hàm chạy benchmark cũ
void RunFullBenchmark(DanhSachLaptop& dsls);

#endif