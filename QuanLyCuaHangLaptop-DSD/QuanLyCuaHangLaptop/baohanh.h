#pragma once
#ifndef UI_BAOHANH_H
#define UI_BAOHANH_H

#include "xuly.h" 
void MenuQuanLyBaoHanh(DanhSachBaoHanh& dsBH);

// Các hàm tra cứu
void TraCuuBaoHanhTheoMaLaptop(const DanhSachBaoHanh& dsBH);
void TraCuuBaoHanhTheoKhachHang(const DanhSachBaoHanh& dsBH);
void TraCuuBaoHanhTheoSerial(const DanhSachBaoHanh& dsBH);

// Hàm xuất
void XuatTatCaBaoHanh(const DanhSachBaoHanh& dsBH);
const char* KiemTraTrangThaiBH(Date ngayHetHan);

#endif