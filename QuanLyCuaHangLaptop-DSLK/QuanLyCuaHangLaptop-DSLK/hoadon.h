#pragma once
#ifndef UI_HOADON_H
#define UI_HOADON_H

#include "thuvien.h"
#include "xuly.h"

void MenuQuanLyHoaDon(
    DanhSachHoaDon& dsHD,
    DanhSachKhachHang& dsKH,
    DanhSachLaptop& dsLT,
    DanhSachBaoHanh& dsBH,
    TaiKhoan* tkCurrent
);

void LapHoaDonMoi(DanhSachHoaDon& dsHD, DanhSachKhachHang& dsKH, DanhSachLaptop& dsLT, DanhSachBaoHanh& dsBH, TaiKhoan* tkCurrent);
void XuatDanhSachHoaDon(const DanhSachHoaDon& dsHD);

#endif