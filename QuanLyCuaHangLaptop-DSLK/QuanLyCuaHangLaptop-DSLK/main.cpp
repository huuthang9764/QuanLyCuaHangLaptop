#include <iostream>
#include <conio.h> 
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


DanhSachLaptop        g_dsLaptop;
DanhSachKhachHang     g_dsKhachHang;
DanhSachHoaDon        g_dsHoaDonToanCuc;
DanhSachNhanVien      g_dsNhanVien;
DanhSachTaiKhoan      g_dsTaiKhoan;
DanhSachThuongHieu    g_dsThuongHieu;
DanhSachLoai          g_dsLoai;
DanhSachBaoHanh       g_dsBaoHanh;

TaiKhoan* g_taiKhoanHienTai = NULL;

void MenuChinh();
void MenuQuanLyCapCao();
void MenuNhanVien();
void XuLyDangNhap();

int main() {
    // 1. Đọc dữ liệu từ file (Nếu có)
    DocDuLieu(
        g_dsKhachHang, g_dsHoaDonToanCuc, g_dsLaptop,
        g_dsNhanVien, g_dsTaiKhoan, g_dsThuongHieu,
        g_dsLoai, g_dsBaoHanh
    );

    // 2. Nếu dữ liệu rỗng (Lần đầu chạy), tự động sinh dữ liệu mẫu
    if (g_dsLaptop.head == NULL) {
        KhoiTaoDuLieuTuDong(
            g_dsLaptop, g_dsKhachHang, g_dsNhanVien,
            g_dsTaiKhoan, g_dsThuongHieu, g_dsLoai,
            g_dsHoaDonToanCuc, g_dsBaoHanh
        );
    }

    // 3. CHẠY BENCHMARK (Đo hiệu năng DSLK)
    // [QUAN TRỌNG] Chỉ chạy khi có dữ liệu
    if (g_dsLaptop.head != NULL) {
        cout << "\n=== BAT DAU BENCHMARK (LINKED LIST VERSION) ===\n";
        RunFullBenchmark(g_dsLaptop);
        cout << "===============================================\n";
        cout << "Nhan phim bat ky de vao chuong trinh chinh...";
        _getch();
    }

    while (true) {
        XuLyDangNhap();
        if (g_taiKhoanHienTai != NULL) {
            cout << "Dang nhap thanh cong voi quyen: "
                << (g_taiKhoanHienTai->quyen == QUAN_LY ? "Quan Ly" : "Nhan Vien") << endl;
            system("pause");

            MenuChinh();
        }
        else {
            break;
        }
    };

    cout << "Dang luu du lieu..." << endl;
    GhiDuLieu(
        g_dsKhachHang, g_dsHoaDonToanCuc, g_dsLaptop,
        g_dsNhanVien, g_dsTaiKhoan, g_dsThuongHieu,
        g_dsLoai, g_dsBaoHanh
    );
    cout << "Da luu. Tam biet!" << endl;

    return 0;
}

void MenuChinh() {
    if (g_taiKhoanHienTai == NULL) return;
    if (g_taiKhoanHienTai->quyen == QUAN_LY) MenuQuanLyCapCao();
    else MenuNhanVien();
}

void MenuQuanLyCapCao() {
    char luaChon;
    do {
        system("cls");
        cout << "======= MENU QUAN LY CAP CAO =======" << endl;
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
        case '0': break;
        default: cout << "Sai!\n";
        }
        if (luaChon != '0') system("pause");
    } while (luaChon != '0');
}

void MenuNhanVien() {
    char luaChon;
    do {
        system("cls");
        cout << "======= MENU NHAN VIEN =======" << endl;
        cout << "1. Ban Hang" << endl;
        cout << "2. Khach Hang" << endl;
        cout << "3. Bao Hanh" << endl;
        cout << "0. Dang xuat" << endl;
        cout << "Chon: ";
        luaChon = _getch();
        switch (luaChon) {
        case '1': MenuQuanLyHoaDon(g_dsHoaDonToanCuc, g_dsKhachHang, g_dsLaptop, g_dsBaoHanh, g_taiKhoanHienTai); break;
        case '2': MenuQuanLyKhachHang(g_dsKhachHang); break;
        case '3': MenuQuanLyBaoHanh(g_dsBaoHanh); break;
        case '0': g_taiKhoanHienTai = NULL; break;
        }
        if (luaChon != '0') system("pause");
    } while (luaChon != '0');
}

void XuLyDangNhap() {
    if (g_dsTaiKhoan.head == NULL) {
        NhanVien nv;
        strcpy_s(nv.maNV, "NV001");
        strcpy_s(nv.tenNV, "Super Admin");
        strcpy_s(nv.chucVu, "Quan Ly");
        strcpy_s(nv.soDT, "0909000000");
        strcpy_s(nv.email, "admin@shop.com");
        ThemNhanVien(g_dsNhanVien, nv);

        TaiKhoan tk;
        strcpy_s(tk.tenDangNhap, "admin");
        strcpy_s(tk.matKhau, "admin"); // Pass mac dinh
        strcpy_s(tk.maNV, "NV001");
        tk.quyen = QUAN_LY;
        tk.trangThai = TK_HOAT_DONG;
        ThemTaiKhoan(g_dsTaiKhoan, tk);
    }

    g_taiKhoanHienTai = NULL;

    // 2. MENU CHON PHUONG THUC
    system("cls");
    cout << "======= TUY CHON DANG NHAP (DSLK) =======\n";
    cout << "1. Dang nhap nhanh (Admin)\n";
    cout << "2. Nhap Ten Dang Nhap & Mat Khau thu cong\n";
    cout << "-----------------------------------------\n";
    cout << "Chon phuong thuc: ";

    char luaChon = _getch();

    if (luaChon == '1') {
        g_taiKhoanHienTai = DangNhap(g_dsTaiKhoan, "admin", "admin");
        if (g_taiKhoanHienTai != NULL) return;
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
        cout << "======= DANG NHAP HE THONG (LINKED LIST) =======" << endl;
        cout << "(Go '0' o Ten dang nhap de LUU VA THOAT)\n";
        cout << "------------------------------------------------\n";

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
                if (!pass.empty()) { pass.pop_back(); cout << "\b \b"; }
            }
            else { pass += ch; cout << '*'; }
            ch = _getch();
        }
        cout << endl;

        g_taiKhoanHienTai = DangNhap(g_dsTaiKhoan, ten, pass.c_str());

        if (g_taiKhoanHienTai != NULL) break;
        else {
            cout << ">> Sai ten dang nhap hoac mat khau. Vui long thu lai.\n";
            system("pause");
        }
    }
}