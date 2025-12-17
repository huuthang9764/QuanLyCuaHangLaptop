#pragma once
#ifndef UI_NHANVIEN_H
#define UI_NHANVIEN_H

#include "xuly.h"

void MenuQuanLyNhanVien(DanhSachNhanVien& dsNV, DanhSachTaiKhoan& dsTK);
void MenuQuanLyTaiKhoan(DanhSachTaiKhoan& dsTK, DanhSachNhanVien& dsNV);
NhanVien NhapThongTinNhanVien();
void XuatDanhSachNhanVien(const DanhSachNhanVien& dsNV);
void XuatDanhSachTaiKhoan(const DanhSachTaiKhoan& dsTK);

#endif