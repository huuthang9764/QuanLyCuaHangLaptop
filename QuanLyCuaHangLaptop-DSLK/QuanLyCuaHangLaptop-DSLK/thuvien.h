#define _CRT_SECURE_NO_WARNINGS
#pragma once
#ifndef THUVIEN_H
#define THUVIEN_H

#include <iostream>
#include <cstring>
using namespace std;

// =================== ENUM & HẰNG SỐ ===================
enum TrangThai { HET_HANG = 0, CON_HANG = 1 };
enum TrangThaiTK { TK_KHOA = 0, TK_HOAT_DONG = 1 };
enum Quyen { NHAN_VIEN = 0, QUAN_LY = 1 };
enum TrangThaiBH {
    BH_HET_HAN = 0,
    BH_CON_HAN = 1,
    BH_DANG_XU_LY = 2
};

// Enum cho cấu hình laptop
enum LoaiRAM {
    RAM_4GB = 4,
    RAM_8GB = 8,
    RAM_16GB = 16,
    RAM_32GB = 32,
    RAM_64GB = 64
};

enum LoaiSSD {
    SSD_128GB = 128,
    SSD_256GB = 256,
    SSD_512GB = 512,
    SSD_1024GB = 1024,
    SSD_2048GB = 2048
};

// =================== CẤU TRÚC CƠ BẢN ===================
struct Date {
    int ngay;
    int thang;
    int nam;
};

struct CauHinh {
    char CPU[30];
    LoaiRAM RAM; 
    LoaiSSD SSD; 
    char GPU[30];
    float KichThuocManHinh;
};

// =================== 1. CHI TIẾT HÓA ĐƠN (DSLK Cấp 3) ===================
struct ChiTietHoaDon {
    char maLaptop[10];
    char serial[20];// new
    int soLuong;
    long donGia;
    long thanhTien;
};

struct NodeChiTiet {
    ChiTietHoaDon data;
    NodeChiTiet* next;
    NodeChiTiet* pre;
};

struct DanhSachChiTiet {
    NodeChiTiet* head;
    NodeChiTiet* tail; 
    int soLuong;       
};

// =================== 2. HÓA ĐƠN (DSLK Cấp 2) ===================
struct HoaDon {
    char maHD[10];
    char maKH[10];
    char maNV[10];
    Date ngayLap;
    long tongTien;
    int trangThai;
    DanhSachChiTiet dsChiTiet;
};

struct NodeHoaDon {
    HoaDon data;
    NodeHoaDon* next;
    NodeHoaDon* pre;
};

struct DanhSachHoaDon {
    NodeHoaDon* head;
    NodeHoaDon* tail;
    int soLuong;
};

// =================== 3. KHÁCH HÀNG (DSLK Cấp 1) ===================
struct KhachHang {
    char maKH[10];
    char tenKH[50];
    char soDT[15];
    char email[50];
    char diaChi[100];
    DanhSachHoaDon dsHoaDon; 
};

struct NodeKhachHang {
    KhachHang data;
    NodeKhachHang* next;
    NodeKhachHang* pre;
};

struct DanhSachKhachHang {
    NodeKhachHang* head;
    NodeKhachHang* tail;
    int soLuong;
};

// =================== CÁC DANH SÁCH ĐỘC LẬP KHÁC ===================

// --- LAPTOP ---
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

struct NodeLaptop {
    Laptop data;
    NodeLaptop* next;
    NodeLaptop* pre;
};

struct DanhSachLaptop {
    NodeLaptop* head;
    NodeLaptop* tail;
    int soLuong;
};

// --- THƯƠNG HIỆU ---
struct ThuongHieu {
    char maThuongHieu[10];
    char tenThuongHieu[50];
    char quocGia[30];
};

struct NodeThuongHieu {
    ThuongHieu data;
    NodeThuongHieu* next;
    NodeThuongHieu* pre;
};

struct DanhSachThuongHieu {
    NodeThuongHieu* head;
    NodeThuongHieu* tail;
    int soLuong;
};

// --- LOẠI SẢN PHẨM ---
struct LoaiSanPham {
    char maLoai[10];
    char tenLoai[30];
};

struct NodeLoai {
    LoaiSanPham data;
    NodeLoai* next;
    NodeLoai* pre;
};

struct DanhSachLoai {
    NodeLoai* head;
    NodeLoai* tail;
    int soLuong;
};

// --- NHÂN VIÊN ---
struct NhanVien {
    char maNV[10];
    char tenNV[50];
    char chucVu[30];
    char soDT[15];
    char email[50];
};

struct NodeNhanVien {
    NhanVien data;
    NodeNhanVien* next;
    NodeNhanVien* pre;
};

struct DanhSachNhanVien {
    NodeNhanVien* head;
    NodeNhanVien* tail;
    int soLuong;
};

// --- TÀI KHOẢN ---
struct TaiKhoan {
    char tenDangNhap[30];
    char matKhau[30];
    char maNV[10];
    Quyen quyen;
    TrangThaiTK trangThai;
};

struct NodeTaiKhoan {
    TaiKhoan data;
    NodeTaiKhoan* next;
    NodeTaiKhoan* pre;
};

struct DanhSachTaiKhoan {
    NodeTaiKhoan* head;
    NodeTaiKhoan* tail;
    int soLuong;
};

// --- BẢO HÀNH ---
struct BaoHanh {
    char maBH[10];
    char maKH[10];
    char maHD[10];
    char maLaptop[10];
    char serial[20];
    Date ngayMua;
    Date ngayHetHan;
    TrangThaiBH trangThai; 
};

struct NodeBaoHanh {
    BaoHanh data;
    NodeBaoHanh* next;
    NodeBaoHanh* pre;
};

struct DanhSachBaoHanh {
    NodeBaoHanh* head;
    NodeBaoHanh* tail;
    int soLuong;
};

#endif