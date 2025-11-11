#include <iostream>
#include <conio.h> 
#include "thuvien.h" 
#include "xuly.h"   
#include "danhmuc.h"


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
    DocDuLieu(
        g_dsKhachHang,
        g_dsHoaDonToanCuc,
        g_dsLaptop,
        g_dsNhanVien,
        g_dsTaiKhoan,
        g_dsThuongHieu,
        g_dsLoai,
        g_dsBaoHanh
    );

    XuLyDangNhap();

    if (g_taiKhoanHienTai != NULL) {
        cout << "Dang nhap thanh cong voi quyen: "
            << (g_taiKhoanHienTai->quyen == QUAN_LY ? "Quan Ly" : "Nhan Vien") << endl;
        system("pause");


        MenuChinh();
    }
    else {
        cout << "Dang nhap that bai!" << endl;
    }

    cout << "Dang luu du lieu..." << endl;
    GhiDuLieu(
        g_dsKhachHang,
        g_dsHoaDonToanCuc,
        g_dsLaptop,
        g_dsNhanVien,
        g_dsTaiKhoan,
        g_dsThuongHieu,
        g_dsLoai,
        g_dsBaoHanh
    );
    cout << "Da luu. Tam biet!" << endl;

    return 0;
}


void MenuChinh() {
    if (g_taiKhoanHienTai == NULL) return; 
    if (g_taiKhoanHienTai->quyen == QUAN_LY) {
        MenuQuanLyCapCao();
    }
    else {
        MenuNhanVien();
    }
}

void MenuQuanLyCapCao() {
    char luaChon;
    do {
        system("cls");
        cout << "======= MENU QUAN LY CAP CAO =======" << endl;
        cout << "1. Quan ly Laptop & Kho" << endl;
        cout << "2. Quan ly Danh Muc (Thuong hieu, Loai)" << endl;
        cout << "3. Quan ly Nhan Vien & Tai Khoan" << endl;
        cout << "4. Quan ly Khach Hang" << endl;
        cout << "5. Lap Hoa Don Ban Hang" << endl;
        cout << "6. Quan ly Bao Hanh" << endl;
        cout << "7. Thong ke & Bao cao" << endl;
        cout << "====================================" << endl;
        cout << "0. Dang xuat va Thoat" << endl;
        cout << "Nhap lua chon cua ban: ";
        luaChon = _getch();

        switch (luaChon) {
        case '1': 
            cout << "Chuc nang [QL Laptop] dang duoc xay dung..." << endl;
            break;
        case '2': 
            MenuQuanLyDanhMuc(g_dsThuongHieu, g_dsLoai);
            break;
        case '3': 
            cout << "Chuc nang [QL Nhan Vien] dang duoc xay dung..." << endl;
            break;
        case '4': 
            cout << "Chuc nang [QL Khach Hang] dang duoc xay dung..." << endl;
            break;
        case '5': 
            cout << "Chuc nang [Lap Hoa Don] dang duoc xay dung..." << endl;
            break;
        case '6': 
            cout << "Chuc nang [QL Bao Hanh] dang duoc xay dung..." << endl;
            break;
        case '7': 
            cout << "Chuc nang [Thong Ke] dang duoc xay dung..." << endl;
            break;
        case '0':
            cout << "Dang xuat..." << endl;
            break;
        default:
            cout << "Lua chon khong hop le." << endl;
            break;
        }
        if (luaChon != '0') system("pause");
    } while (luaChon != '0');
}


void MenuNhanVien() {

    system("cls");
    cout << "Chuc nang [Menu Nhan Vien] dang duoc xay dung..." << endl;
    system("pause");
}


void XuLyDangNhap() {

    if (g_dsTaiKhoan.soLuong == 0) {
        NhanVien nvAdmin;
        strcpy_s(nvAdmin.maNV, "NV001"); 
        strcpy_s(nvAdmin.tenNV, "Admin");
        ThemNhanVien(g_dsNhanVien, nvAdmin);

        TaiKhoan tkAdmin;
        strcpy_s(tkAdmin.tenDangNhap, "admin");
        strcpy_s(tkAdmin.matKhau, "admin");
        strcpy_s(tkAdmin.maNV, "NV001");
        tkAdmin.quyen = QUAN_LY;
        tkAdmin.trangThai = TK_HOAT_DONG;
        ThemTaiKhoan(g_dsTaiKhoan, tkAdmin);
    }

    g_taiKhoanHienTai = DangNhap(g_dsTaiKhoan, "admin", "admin");
}

//void XuLyDangNhap() {
//    if (g_dsTaiKhoan.soLuong == 0) {
//        NhanVien nvAdmin;
//        strcpy_s(nvAdmin.maNV, "NV001");
//        strcpy_s(nvAdmin.tenNV, "Admin");
//        ThemNhanVien(g_dsNhanVien, nvAdmin);
//
//        TaiKhoan tkAdmin;
//        strcpy_s(tkAdmin.tenDangNhap, "admin");
//        strcpy_s(tkAdmin.matKhau, "admin");
//        strcpy_s(tkAdmin.maNV, "NV001");
//        tkAdmin.quyen = QUAN_LY;
//        tkAdmin.trangThai = TK_HOAT_DONG;
//        ThemTaiKhoan(g_dsTaiKhoan, tkAdmin);
//    }
//
//
//    char ten[30];
//    string pass; 
//    char ch;
//
//    while (true) {
//        system("cls");
//        cout << "======= DANG NHAP HE THONG =======" << endl;
//
//        pass = ""; 
//
//        cout << "Ten dang nhap: ";
//        cin.getline(ten, 30);
//
//        cout << "Mat khau: ";
//        ch = _getch(); 
//
//        while (ch != 13) { 
//            if (ch == 8) { 
//                if (pass.length() > 0) {
//                    pass.pop_back();    
//                    cout << "\b \b";    
//                }
//            }
//            else {
//                pass += ch; 
//                cout << '*';  
//            }
//            ch = _getch();
//        }
//        cout << endl; 
//
//    
//        g_taiKhoanHienTai = DangNhap(g_dsTaiKhoan, ten, pass.c_str());
//
//
//        if (g_taiKhoanHienTai != NULL) {
//
//            break;
//        }
//        else {
//           
//            system("pause");
//        }
//    }
//}
