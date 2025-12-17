#pragma once
#ifndef UI_KHACHHANG_H
#define UI_KHACHHANG_H

#include "xuly.h" 

// Menu chính quản lý khách hàng
void MenuQuanLyKhachHang(DanhSachKhachHang& dsKH);

// Hàm hỗ trợ nhập liệu
void NhapThongTinKhachHang(KhachHang* kh);

// Hàm xuất danh sách (Duyệt mảng)
void XuatDanhSachKhachHang(const DanhSachKhachHang& dsKH);

#endif