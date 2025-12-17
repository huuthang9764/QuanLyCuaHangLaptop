#pragma once
#ifndef XULY_H
#define XULY_H

#include "thuvien.h"

// =================== 1. ĐỌC / GHI FILE ===================
void DocDuLieu(
    DanhSachKhachHang& dskh,
    DanhSachHoaDon& dsHD_ToanCuc,
    DanhSachLaptop& dsls,
    DanhSachNhanVien& dsnv,
    DanhSachTaiKhoan& dstk,
    DanhSachThuongHieu& dsth,
    DanhSachLoai& dsl,
    DanhSachBaoHanh& dsbh
);

void GhiDuLieu(
    const DanhSachKhachHang& dskh,
    const DanhSachHoaDon& dsHD_ToanCuc,
    const DanhSachLaptop& dsls,
    const DanhSachNhanVien& dsnv,
    const DanhSachTaiKhoan& dstk,
    const DanhSachThuongHieu& dsth,
    const DanhSachLoai& dsl,
    const DanhSachBaoHanh& dsbh
);

// =================== 2. QUẢN LÝ LAPTOP ===================
bool ThemLaptop(DanhSachLaptop& dsls, Laptop ltMoi);
bool XoaLaptop(DanhSachLaptop& dsls, const char maLaptop[10]);
bool SuaLaptop(DanhSachLaptop& dsls, Laptop ltMoi);
Laptop* TimKiemLaptop(const DanhSachLaptop& dsls, const char maLaptop[10]); 
Laptop* TimKiemNhiPhan_TheoTen(const DanhSachLaptop& dsls, const char tenCanTim[50]);
void CapNhatSoLuongLaptop(DanhSachLaptop& dsls, const char maLaptop[10], int soLuongBan);

// =================== 3. QUẢN LÝ KHÁCH HÀNG ===================
bool ThemKhachHang(DanhSachKhachHang& dskh, KhachHang khMoi);
bool XoaKhachHang(DanhSachKhachHang& dskh, const char maKH[10]);
bool SuaKhachHang(DanhSachKhachHang& dskh, KhachHang khMoi);
KhachHang* TimKiemKhachHang(const DanhSachKhachHang& dskh, const char maKH[10]);

// =================== 4. QUẢN LÝ HÓA ĐƠN ===================
bool ThemHoaDon(DanhSachHoaDon& dsHD_ToanCuc, DanhSachKhachHang& dskh, HoaDon hdMoi);
HoaDon* TimKiemHoaDon(const DanhSachHoaDon& dsHD_ToanCuc, const char maHD[10]);
bool ThemChiTietVaoHoaDon(HoaDon& hd, ChiTietHoaDon ctMoi);

// =================== 5. QUẢN LÝ NHÂN VIÊN & TÀI KHOẢN ===================
bool ThemNhanVien(DanhSachNhanVien& dsnv, NhanVien nvMoi);
bool XoaNhanVien(DanhSachNhanVien& dsnv, DanhSachTaiKhoan& dstk, const char maNV[10]);
bool SuaNhanVien(DanhSachNhanVien& dsnv, NhanVien nvMoi);
NhanVien* TimKiemNhanVien(const DanhSachNhanVien& dsnv, const char maNV[10]);

bool ThemTaiKhoan(DanhSachTaiKhoan& dstk, TaiKhoan tkMoi);
bool XoaTaiKhoan(DanhSachTaiKhoan& dstk, const char tenDangNhap[30]);
bool SuaTaiKhoan(DanhSachTaiKhoan& dstk, TaiKhoan tkMoi);
TaiKhoan* TimKiemTaiKhoan(const DanhSachTaiKhoan& dstk, const char tenDangNhap[30]);
TaiKhoan* DangNhap(const DanhSachTaiKhoan& dstk, const char user[30], const char pass[30]);
bool DoiMatKhau(DanhSachTaiKhoan& dstk, const char tenDangNhap[30], const char passMoi[30]);

// =================== 6. QUẢN LÝ DANH MỤC ===================
bool ThemThuongHieu(DanhSachThuongHieu& dsth, ThuongHieu th);
bool XoaThuongHieu(DanhSachThuongHieu& dsth, const char maTH[10]);
bool SuaThuongHieu(DanhSachThuongHieu& dsth, ThuongHieu thMoi);
ThuongHieu* TimKiemThuongHieu(const DanhSachThuongHieu& dsth, const char maTH[10]);

bool ThemLoai(DanhSachLoai& dsl, LoaiSanPham loai);
bool XoaLoai(DanhSachLoai& dsl, const char maLoai[10]);
bool SuaLoai(DanhSachLoai& dsl, LoaiSanPham loaiMoi);
LoaiSanPham* TimKiemLoai(const DanhSachLoai& dsl, const char maLoai[10]);

// =================== 7. BẢO HÀNH ===================
bool ThemBaoHanh(DanhSachBaoHanh& dsbh, BaoHanh bh);

// =================== 8. SẮP XẾP ===================
void SapXepLaptop_TheoTen(DanhSachLaptop& dsls);
void SapXepLaptop_TheoGia(DanhSachLaptop& dsls);
void SapXepKhachHang_TheoTen(DanhSachKhachHang& dskh);

string DinhDangTien(long long tien);

#endif