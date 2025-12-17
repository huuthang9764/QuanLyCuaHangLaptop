#pragma once
#ifndef UI_THONGKE_H
#define UI_THONGKE_H

#include "xuly.h"
#include "thuvien.h"

// Menu chính Thống kê
void MenuThongKe(DanhSachHoaDon& dshd, const DanhSachLaptop& dslt);
void MenuDoanhThu(const DanhSachHoaDon& dshd);
void MenuLoiNhuan(const DanhSachHoaDon& dshd, const DanhSachLaptop& dslt);

// Các hàm xuất báo cáo
void XuatBaoCaoDoanhThuNgay(Date ngayCanLoc, const DanhSachHoaDon& dsHD);
void XuatBaoCaoDoanhThuThang(Date ngayCanLoc, const DanhSachHoaDon& dsHD);
void XuatBaoCaoDoanhThuNam(Date ngayCanLoc, const DanhSachHoaDon& dsHD);
void XuatBaoCaoTonKho(const DanhSachLaptop& dsLaptop);

// Các hàm tính toán lợi nhuận
double TinhLoiNhuanNgay(const DanhSachLaptop& dslt, const DanhSachHoaDon& dshd, Date ngayCanLoc);
double TinhLoiNhuanThang(const DanhSachLaptop& dslt, const DanhSachHoaDon& dshd, Date ngayCanLoc);
double TinhLoiNhuanNam(const DanhSachLaptop& dslt, const DanhSachHoaDon& dshd, Date ngayCanLoc);

#endif