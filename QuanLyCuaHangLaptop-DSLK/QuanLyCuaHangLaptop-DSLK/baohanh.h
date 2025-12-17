#pragma once
#ifndef UI_BAOHANH_H
#define UI_BAOHANH_H

#include "thuvien.h"
#include "xuly.h"

void MenuQuanLyBaoHanh(DanhSachBaoHanh& dsBH);
void TraCuuBaoHanhTheoMaLaptop(const DanhSachBaoHanh& dsBH);
void TraCuuBaoHanhTheoKhachHang(const DanhSachBaoHanh& dsBH);
void XuatTatCaBaoHanh(const DanhSachBaoHanh& dsBH);
const char* KiemTraTrangThaiBH(Date ngayHetHan);

#endif