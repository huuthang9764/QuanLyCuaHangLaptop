#pragma once
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
void DongBoHoaDonLong(DanhSachKhachHang& dskh, const DanhSachHoaDon& dsHD_ToanCuc);

int TimKiemViTriKhachHang(DanhSachKhachHang& dskh, const char maKH[10]);
KhachHang* TimKiemKhachHang(DanhSachKhachHang& dskh, const char maKH[10]);


bool ThemLaptop(DanhSachLaptop& dsls, Laptop ltMoi);
bool XoaLaptop(DanhSachLaptop& dsls, const char maLaptop[10]);
bool SuaLaptop(DanhSachLaptop& dsls, Laptop ltMoi);
Laptop* TimKiemLaptop(DanhSachLaptop& dsls, const char maLaptop[10]);
int TimKiemViTriLaptop(DanhSachLaptop& dsls, const char maLaptop[10]);
void CapNhatSoLuongLaptop(DanhSachLaptop& dsls, const char maLaptop[10], int soLuongBan);


bool ThemNhanVien(DanhSachNhanVien& dsnv, NhanVien nvMoi);
bool SuaNhanVien(DanhSachNhanVien& dsnv, NhanVien nvMoi);
NhanVien* TimKiemNhanVien(DanhSachNhanVien& dsnv, const char maNV[10]);
int TimKiemViTriNhanVien(DanhSachNhanVien& dsnv, const char maNV[10]);
bool XoaNhanVien(DanhSachNhanVien& dsnv, DanhSachTaiKhoan& dstk, const char maNV[10]);

bool ThemTaiKhoan(DanhSachTaiKhoan& dstk, TaiKhoan tkMoi);
bool XoaTaiKhoan(DanhSachTaiKhoan& dstk, const char tenDangNhap[30]);
bool SuaTaiKhoan(DanhSachTaiKhoan& dstk, TaiKhoan tkMoi);
TaiKhoan* TimKiemTaiKhoan(DanhSachTaiKhoan& dstk, const char tenDangNhap[30]);
int TimKiemViTriTaiKhoan(DanhSachTaiKhoan& dstk, const char tenDangNhap[30]);

TaiKhoan* DangNhap(DanhSachTaiKhoan& dstk, const char user[30], const char pass[30]);
bool DoiMatKhau(DanhSachTaiKhoan& dstk, const char tenDangNhap[30], const char passMoi[30]);

bool ThemThuongHieu(DanhSachThuongHieu& dsth, ThuongHieu thMoi);
bool XoaThuongHieu(DanhSachThuongHieu& dsth, const char maTH[10]);
bool SuaThuongHieu(DanhSachThuongHieu& dsth, ThuongHieu thMoi);
ThuongHieu* TimKiemThuongHieu(DanhSachThuongHieu& dsth, const char maTH[10]);
int TimKiemViTriThuongHieu(DanhSachThuongHieu& dsth, const char maTH[10]);


bool ThemLoai(DanhSachLoai& dsl, LoaiSanPham loaiMoi);
bool XoaLoai(DanhSachLoai& dsl, const char maLoai[10]);
bool SuaLoai(DanhSachLoai& dsl, LoaiSanPham loaiMoi);
LoaiSanPham* TimKiemLoai(DanhSachLoai& dsl, const char maLoai[10]);
int TimKiemViTriLoai(DanhSachLoai& dsl, const char maLoai[10]);
