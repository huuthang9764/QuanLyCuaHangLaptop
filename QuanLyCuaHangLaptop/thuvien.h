#pragma once
#define THUVIEN_H

#include <iostream>
#include <cstring>
using namespace std;

// =================== ENUM ===================
enum TrangThai { HET_HANG = 0, CON_HANG = 1 };
enum TrangThaiTK { TK_KHOA = 0, TK_HOAT_DONG = 1 };
enum Quyen { NHAN_VIEN = 0, QUAN_LY = 1 };

// =================== CONSTANTS ===================
const int MAX_CHITIET = 100;
const int MAX_HOADON = 100;
const int MAX_KHACHHANG = 100;
const int MAX_LAPTOP = 100;
const int MAX_THUONGHIEU = 50;
const int MAX_LOAI = 50;
const int MAX_NHANVIEN = 50;
const int MAX_TAIKHOAN = 50;
const int MAX_BAOHANH = 100;

// =================== CẤU TRÚC NGÀY ===================
struct Date {
    int ngay;
    int thang;
    int nam;
};

// =================== CHI TIẾT HÓA ĐƠN ===================
struct ChiTietHoaDon {
    char maLaptop[10];
    int soLuong;
    long donGia;
    long thanhTien;
};

struct DanhSachChiTiet {
    int soLuong;
    ChiTietHoaDon ds[MAX_CHITIET];
};

// =================== HÓA ĐƠN ===================
struct HoaDon {
    char maHD[10];
    char maKH[10];
    char maNV[10];
    Date ngayLap;
    long tongTien;
    int trangThai;
    DanhSachChiTiet dsChiTiet;
};

struct DanhSachHoaDon {
    int soLuong;
    HoaDon ds[MAX_HOADON];
};

// =================== KHÁCH HÀNG ===================
struct KhachHang {
    char maKH[10];
    char tenKH[50];
    char soDT[15];
    char email[50];
    char diaChi[100];
    DanhSachHoaDon dsHoaDon;
};

struct DanhSachKhachHang {
    int soLuong;
    KhachHang ds[MAX_KHACHHANG];
};

// =================== CẤU HÌNH LAPTOP ===================
struct CauHinh {
    char CPU[30];
    int RAM;
    int SSD;
    char GPU[30];
    float KichThuocManHinh;
};

// =================== LAPTOP ===================
struct Laptop {
    char maLaptop[10];
    char tenLaptop[50];
    char maThuongHieu[10];
    char maLoai[10];
    double giaVon;
    double giaBan;
    int soLuongTon;
    TrangThai trangThai;
    CauHinh cauHinh;
    int thoiGianBaoHanh; // tháng
};

struct DanhSachLaptop {
    int soLuong;
    Laptop ds[MAX_LAPTOP];
};

// =================== THƯƠNG HIỆU ===================
struct ThuongHieu {
    char maThuongHieu[10];
    char tenThuongHieu[50];
    char quocGia[30];
};

struct DanhSachThuongHieu {
    int soLuong;
    ThuongHieu ds[MAX_THUONGHIEU];
};

// =================== LOẠI SẢN PHẨM ===================
struct LoaiSanPham {
    char maLoai[10];
    char tenLoai[30];
};

struct DanhSachLoai {
    int soLuong;
    LoaiSanPham ds[MAX_LOAI];
};

// =================== NHÂN VIÊN ===================
struct NhanVien {
    char maNV[10];
    char tenNV[50];
    char chucVu[30];
    char soDT[15];
    char email[50];
};

struct DanhSachNhanVien {
    int soLuong;
    NhanVien ds[MAX_NHANVIEN];
};

// =================== TÀI KHOẢN ===================
struct TaiKhoan {
    char tenDangNhap[30];
    char matKhau[30];
    char maNV[10];
    Quyen quyen;
    TrangThaiTK trangThai;
};

struct DanhSachTaiKhoan {
    int soLuong;
    TaiKhoan ds[MAX_TAIKHOAN];
};

// =================== BẢO HÀNH ===================
struct BaoHanh {
    char maBH[10];
    char maKH[10];
    char maHD[10];
    char maLaptop[10];
    Date ngayMua;
    Date ngayHetHan;
    int trangThai; // 0: het han, 1: con han, 2: dang xu ly
};

struct DanhSachBaoHanh {
    int soLuong;
    BaoHanh ds[MAX_BAOHANH];
};

