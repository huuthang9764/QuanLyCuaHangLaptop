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

// =================== 2. QUẢN LÝ HÓA ĐƠN ===================
bool ThemHoaDon(DanhSachHoaDon& dsHD_ToanCuc, DanhSachKhachHang& dskh, HoaDon hdMoi);
bool XoaHoaDon(DanhSachHoaDon& dsHD_ToanCuc, DanhSachKhachHang& dskh, const char maHD[10]);
bool SuaHoaDon(DanhSachHoaDon& dsHD_ToanCuc, DanhSachKhachHang& dskh, HoaDon hdMoi);
HoaDon* TimKiemHoaDon(DanhSachHoaDon& dsHD_ToanCuc, const char maHD[10]);
int TimKiemViTriHoaDon(DanhSachHoaDon& dsHD_ToanCuc, const char maHD[10]);
bool ThemChiTietVaoHoaDon(HoaDon& hd, ChiTietHoaDon ctMoi);

// =================== 3. QUẢN LÝ KHÁCH HÀNG ===================
bool ThemKhachHang(DanhSachKhachHang& dskh, KhachHang khMoi);
bool XoaKhachHang(DanhSachKhachHang& dskh, const char maKH[10]);
bool SuaKhachHang(DanhSachKhachHang& dskh, KhachHang khMoi);
KhachHang* TimKiemKhachHang(DanhSachKhachHang& dskh, const char maKH[10]);
int TimKiemViTriKhachHang(DanhSachKhachHang& dskh, const char maKH[10]);

// =================== 4. QUẢN LÝ LAPTOP ===================
bool ThemLaptop(DanhSachLaptop& dsls, Laptop ltMoi);
bool XoaLaptop(DanhSachLaptop& dsls, const char maLaptop[10]);
bool SuaLaptop(DanhSachLaptop& dsls, Laptop ltMoi);
Laptop* TimKiemLaptop(DanhSachLaptop& dsls, const char maLaptop[10]);
int TimKiemViTriLaptop(DanhSachLaptop& dsls, const char maLaptop[10]);
void CapNhatSoLuongLaptop(DanhSachLaptop& dsls, const char maLaptop[10], int soLuongBan);

// =================== 5. QUẢN LÝ NHÂN VIÊN & TÀI KHOẢN ===================
// --- Nhân Viên ---
bool ThemNhanVien(DanhSachNhanVien& dsnv, NhanVien nvMoi);
bool SuaNhanVien(DanhSachNhanVien& dsnv, NhanVien nvMoi);
NhanVien* TimKiemNhanVien(DanhSachNhanVien& dsnv, const char maNV[10]);
int TimKiemViTriNhanVien(DanhSachNhanVien& dsnv, const char maNV[10]);
bool XoaNhanVien(DanhSachNhanVien& dsnv, DanhSachTaiKhoan& dstk, const char maNV[10]);
// --- Tài Khoản ---
bool ThemTaiKhoan(DanhSachTaiKhoan& dstk, TaiKhoan tkMoi);
bool XoaTaiKhoan(DanhSachTaiKhoan& dstk, const char tenDangNhap[30]);
bool SuaTaiKhoan(DanhSachTaiKhoan& dstk, TaiKhoan tkMoi);
TaiKhoan* TimKiemTaiKhoan(DanhSachTaiKhoan& dstk, const char tenDangNhap[30]);
int TimKiemViTriTaiKhoan(DanhSachTaiKhoan& dstk, const char tenDangNhap[30]);
// --- Nghiệp vụ ---
TaiKhoan* DangNhap(DanhSachTaiKhoan& dstk, const char user[30], const char pass[30]);
bool DoiMatKhau(DanhSachTaiKhoan& dstk, const char tenDangNhap[30], const char passMoi[30]);

// =================== 6. QUẢN LÝ DANH MỤC (Thương Hiệu, Loại) ===================
// --- Thương Hiệu ---
bool ThemThuongHieu(DanhSachThuongHieu& dsth, ThuongHieu thMoi);
bool XoaThuongHieu(DanhSachThuongHieu& dsth, const char maTH[10]);
bool SuaThuongHieu(DanhSachThuongHieu& dsth, ThuongHieu thMoi);
ThuongHieu* TimKiemThuongHieu(DanhSachThuongHieu& dsth, const char maTH[10]);
int TimKiemViTriThuongHieu(DanhSachThuongHieu& dsth, const char maTH[10]);
// --- Loại Sản Phẩm ---
bool ThemLoai(DanhSachLoai& dsl, LoaiSanPham loaiMoi);
bool XoaLoai(DanhSachLoai& dsl, const char maLoai[10]);
bool SuaLoai(DanhSachLoai& dsl, LoaiSanPham loaiMoi);
LoaiSanPham* TimKiemLoai(DanhSachLoai& dsl, const char maLoai[10]);
int TimKiemViTriLoai(DanhSachLoai& dsl, const char maLoai[10]);

// =================== 7. SẮP XẾP ===================
void SapXepLaptop_TheoTen(DanhSachLaptop& dsls);
void SapXepLaptop_TheoGia(DanhSachLaptop& dsls);
void SapXepKhachHang_TheoTen(DanhSachKhachHang& dskh);
void SapXepHoaDon_TheoNgay(DanhSachHoaDon& dsHD_ToanCuc);
void SapXepHoaDon_TheoTongTien(DanhSachHoaDon& dsHD_ToanCuc);