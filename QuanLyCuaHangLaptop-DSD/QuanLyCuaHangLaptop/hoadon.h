#pragma once
#ifndef UI_HOADON_H
#define UI_HOADON_H

#include "xuly.h" // Đã bao gồm thuvien.h (phiên bản mảng)

// Menu chính quản lý hóa đơn (Bán hàng)
void MenuQuanLyHoaDon(
    DanhSachHoaDon& dsHD,
    DanhSachKhachHang& dsKH,
    DanhSachLaptop& dsLT,
    DanhSachBaoHanh& dsBH,
    TaiKhoan* tkCurrent
);

// Hàm lập hóa đơn mới
void LapHoaDonMoi(
    DanhSachHoaDon& dsHD,
    DanhSachKhachHang& dsKH,
    DanhSachLaptop& dsLT,
    DanhSachBaoHanh& dsBH,
    TaiKhoan* tkCurrent
);

// Hàm xuất danh sách hóa đơn (Duyệt mảng)
void XuatDanhSachHoaDon(const DanhSachHoaDon& dsHD);

#endif