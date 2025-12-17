#include <iostream>
#include <conio.h> 
#include <cstring>
#include "thuvien.h" 
#include "xuly.h"   
#include "danhmuc.h"
#include "laptop.h"
#include "nhanvien.h"
#include "khachhang.h"
#include "hoadon.h"
#include "baohanh.h"
#include "thongke.h"


#include "test_data.h" 
#include "benchmark.h"

using namespace std;

// =================== KHAI BÁO BIẾN TOÀN CỤC (GLOBAL) ===================
DanhSachLaptop        g_dsLaptop;
DanhSachKhachHang     g_dsKhachHang;
DanhSachHoaDon        g_dsHoaDonToanCuc;
DanhSachNhanVien      g_dsNhanVien;
DanhSachTaiKhoan      g_dsTaiKhoan;
DanhSachThuongHieu    g_dsThuongHieu;
DanhSachLoai          g_dsLoai;
DanhSachBaoHanh       g_dsBaoHanh;

TaiKhoan* g_taiKhoanHienTai = NULL;

// =================== NGUYÊN MẪU HÀM ===================
void MenuChinh();
void MenuQuanLyCapCao();
void MenuNhanVien();
void XuLyDangNhap();

// =================== MAIN FUNCTION ===================
int main() {
    DocDuLieu(
        g_dsKhachHang, g_dsHoaDonToanCuc, g_dsLaptop,
        g_dsNhanVien, g_dsTaiKhoan, g_dsThuongHieu,
        g_dsLoai, g_dsBaoHanh
    );

    if (g_dsLaptop.soLuong == 0) {
        KhoiTaoDuLieuTuDong(
            g_dsLaptop, g_dsKhachHang, g_dsNhanVien,
            g_dsTaiKhoan, g_dsThuongHieu, g_dsLoai,
            g_dsHoaDonToanCuc, g_dsBaoHanh
        );
    }

    if (g_dsLaptop.soLuong != NULL) {
        cout << "\n=== BAT DAU BENCHMARK (ARRAY LIST VERSION) ===\n";
        RunFullBenchmark(g_dsLaptop);
        cout << "===============================================\n";
        cout << "Nhan phim bat ky de vao chuong trinh chinh...";
        _getch();
    }

    system("pause");
    while (true) {
        XuLyDangNhap();

        if (g_taiKhoanHienTai != NULL) {
            cout << "\nDang nhap thanh cong voi quyen: "
                << (g_taiKhoanHienTai->quyen == QUAN_LY ? "Quan Ly" : "Nhan Vien") << endl;
            system("pause");

            MenuChinh(); 
        }
        else {
            break; 
        }
    };

    cout << "\nDang luu du lieu xuong file..." << endl;
    GhiDuLieu(
        g_dsKhachHang, g_dsHoaDonToanCuc, g_dsLaptop,
        g_dsNhanVien, g_dsTaiKhoan, g_dsThuongHieu,
        g_dsLoai, g_dsBaoHanh
    );
    cout << "Da luu. Tam biet!" << endl;

    return 0;
}

// =================== CÁC HÀM MENU & LOGIC ===================

void MenuChinh() {
    if (g_taiKhoanHienTai == NULL) return;
    if (g_taiKhoanHienTai->quyen == QUAN_LY) MenuQuanLyCapCao();
    else MenuNhanVien();
}

void MenuQuanLyCapCao() {
    char luaChon;
    do {
        system("cls");
        cout << "======= MENU QUAN LY CAP CAO (ARRAY) =======" << endl;
        cout << "Hello, " << g_taiKhoanHienTai->tenDangNhap << "!" << endl;
        cout << "1. Quan ly Laptop & Kho" << endl;
        cout << "2. Quan ly Danh Muc" << endl;
        cout << "3. Quan ly Nhan Vien" << endl;
        cout << "4. Quan ly Khach Hang" << endl;
        cout << "5. Lap Hoa Don Ban Hang" << endl;
        cout << "6. Quan ly Bao Hanh" << endl;
        cout << "7. Thong ke & Bao cao" << endl;
        cout << "0. Dang xuat" << endl;
        cout << "Chon: ";
        luaChon = _getch();

        switch (luaChon) {
        case '1': MenuQuanLyLaptop(g_dsLaptop, g_dsThuongHieu, g_dsLoai); break;
        case '2': MenuQuanLyDanhMuc(g_dsThuongHieu, g_dsLoai); break;
        case '3': MenuQuanLyNhanVien(g_dsNhanVien, g_dsTaiKhoan); break;
        case '4': MenuQuanLyKhachHang(g_dsKhachHang); break;
        case '5': MenuQuanLyHoaDon(g_dsHoaDonToanCuc, g_dsKhachHang, g_dsLaptop, g_dsBaoHanh, g_taiKhoanHienTai); break;
        case '6': MenuQuanLyBaoHanh(g_dsBaoHanh); break;
        case '7': MenuThongKe(g_dsHoaDonToanCuc, g_dsLaptop); break;
        case '0': g_taiKhoanHienTai = NULL; break;
        default: cout << "Sai!\n"; break;
        }
    } while (luaChon != '0' && g_taiKhoanHienTai != NULL);
}

void MenuNhanVien() {
    char luaChon;
    do {
        system("cls");
        cout << "======= MENU NHAN VIEN (ARRAY) =======" << endl;
        cout << "1. Ban Hang (Lap Hoa Don)" << endl;
        cout << "2. Tra cuu Khach Hang" << endl;
        cout << "3. Tra cuu Bao Hanh" << endl;
        cout << "0. Dang xuat" << endl;
        cout << "Chon: ";
        luaChon = _getch();
        switch (luaChon) {
        case '1': MenuQuanLyHoaDon(g_dsHoaDonToanCuc, g_dsKhachHang, g_dsLaptop, g_dsBaoHanh, g_taiKhoanHienTai); break;
        case '2': MenuQuanLyKhachHang(g_dsKhachHang); break;
        case '3': MenuQuanLyBaoHanh(g_dsBaoHanh); break;
        case '0': g_taiKhoanHienTai = NULL; break;
        default: break;
        }
    } while (luaChon != '0' && g_taiKhoanHienTai != NULL);
}

void XuLyDangNhap() {
    // 1. KHOI TAO ADMIN MAC DINH 
    if (g_dsTaiKhoan.soLuong == 0) {
        NhanVien nv;
        strcpy_s(nv.maNV, "NV001");
        strcpy_s(nv.tenNV, "Super Admin");
        strcpy_s(nv.chucVu, "Quan Ly");
        strcpy_s(nv.soDT, "0909000000");
        strcpy_s(nv.email, "admin@shop.com");
        ThemNhanVien(g_dsNhanVien, nv);

        TaiKhoan tk;
        strcpy_s(tk.tenDangNhap, "admin");
        strcpy_s(tk.matKhau, "admin");
        strcpy_s(tk.maNV, "NV001");
        tk.quyen = QUAN_LY;
        tk.trangThai = TK_HOAT_DONG;
        ThemTaiKhoan(g_dsTaiKhoan, tk);
    }

    g_taiKhoanHienTai = NULL;

    // 2. MENU CHON PHUONG THUC
    system("cls");
    cout << "======= TUY CHON DANG NHAP =======\n";
    cout << "1. Dang nhap nhanh (Admin)\n";
    cout << "2. Nhap Ten Dang Nhap & Mat Khau thu cong\n";
    cout << "----------------------------------\n";
    cout << "Chon phuong thuc: ";

    char luaChon = _getch();

    if (luaChon == '1') {
        g_taiKhoanHienTai = DangNhap(g_dsTaiKhoan, "admin", "admin");

        if (g_taiKhoanHienTai != NULL) {
            return;
        }
        else {
            cout << "\n>> Dang nhap nhanh that bai. Vui long nhap tay.\n";
            system("pause");
        }
    }

    // 3. DANG NHAP THU CONG
    char ten[30];
    string pass;
    char ch;

    while (true) {
        system("cls");
        cout << "======= DANG NHAP HE THONG (ARRAY VERSION) =======" << endl;
        cout << "(Go '0' o Ten dang nhap de LUU VA THOAT)\n"; 
        cout << "--------------------------------------------------\n";

        cout << "Ten dang nhap: ";
        cin.getline(ten, 30);

        if (strcmp(ten, "0") == 0) {
            return;
        }

        cout << "Mat khau: ";
        pass = "";
        ch = _getch();
        while (ch != 13) {
            if (ch == 8) {
                if (!pass.empty()) {
                    pass.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                pass += ch;
                cout << '*';
            }
            ch = _getch();
        }
        cout << endl;

        g_taiKhoanHienTai = DangNhap(g_dsTaiKhoan, ten, pass.c_str());

        if (g_taiKhoanHienTai != NULL) {
            break;
        }
        else {
            cout << ">> Sai ten dang nhap hoac mat khau. Vui long thu lai.\n";
            system("pause");
        }
    }
}