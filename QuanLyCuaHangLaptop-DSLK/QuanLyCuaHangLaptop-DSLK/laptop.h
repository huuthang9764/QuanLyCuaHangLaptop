#pragma once
#ifndef UI_LAPTOP_H
#define UI_LAPTOP_H

#include "xuly.h"

// =================== MENU CHÍNH ===================
void MenuQuanLyLaptop(DanhSachLaptop& dsls, const DanhSachThuongHieu& dsth, const DanhSachLoai& dsl);


// =================== CÁC HÀM HỖ TRỢ NHẬP/XUẤT ===================
Laptop NhapThongTinLaptop(const DanhSachThuongHieu& dsth, const DanhSachLoai& dsl);
void XuatDanhSachLaptop(const DanhSachLaptop& dsls);
void XuatThongTinLaptop(const Laptop& lt); 
void XuLyNhapKho(DanhSachLaptop& dsls);


// =================== CÁC HÀM LỌC & XEM (FILTER) ===================
void XemLaptopTheoThuongHieu(const DanhSachLaptop& dsls, const char maTH[10]);
void XemLaptopTheoLoai(const DanhSachLaptop& dsls, const char maLoai[10]);
void XemLaptopTheoKhoangGia(const DanhSachLaptop& dsls, long long giaMin, long long giaMax);
void XemLaptopTheoCPU(const DanhSachLaptop& dsls);
void XemChiTietCauHinh(const DanhSachLaptop& dsls);
void XemLaptopTheoRAM(const DanhSachLaptop& dsls);
void XemLaptopTheoSSD(const DanhSachLaptop& dsls);

#endif