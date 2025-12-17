#pragma once
#ifndef UI_NHANVIEN_H
#define UI_NHANVIEN_H

#include "xuly.h"

// Các hàm hiển thị menu và xử lý luồng nhập liệu
void MenuQuanLyNhanVien(DanhSachNhanVien& dsNV, DanhSachTaiKhoan& dsTK);
void MenuQuanLyTaiKhoan(DanhSachTaiKhoan& dsTK, DanhSachNhanVien& dsNV);

// Hàm nhập liệu
NhanVien NhapThongTinNhanVien();

// Hàm xuất danh sách (Phiên bản Mảng)
void XuatDanhSachNhanVien(const DanhSachNhanVien& dsNV);
void XuatDanhSachTaiKhoan(const DanhSachTaiKhoan& dsTK);

#endif