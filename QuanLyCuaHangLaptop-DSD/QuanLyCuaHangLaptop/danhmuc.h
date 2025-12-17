#pragma once
#ifndef UI_DANHMUC_H
#define UI_DANHMUC_H

#include "xuly.h"

void MenuQuanLyDanhMuc(DanhSachThuongHieu& dsth, DanhSachLoai& dsl);

void XuatDanhSachThuongHieu(const DanhSachThuongHieu& dsth);
void XuatDanhSachLoai(const DanhSachLoai& dsl);

ThuongHieu NhapThongTinThuongHieu();
LoaiSanPham NhapThongTinLoai();

#endif