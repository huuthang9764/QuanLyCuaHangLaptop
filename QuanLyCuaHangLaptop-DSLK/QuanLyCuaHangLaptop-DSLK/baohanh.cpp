#include "baohanh.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <ctime>
#include <cstring>
#include <string> 
#include <cstdio> // Thêm để dùng sprintf_s

using namespace std;

const int TABLE_WIDTH = 110; // Tăng độ rộng bảng vì thêm cột Serial

// =================== HÀM HỖ TRỢ ===================

Date LayNgayHienTaiBH() {
    time_t t = time(0);
    struct tm* now = localtime(&t);
    Date d;
    d.ngay = now->tm_mday;
    d.thang = now->tm_mon + 1;
    d.nam = now->tm_year + 1900;
    return d;
}

const char* KiemTraTrangThaiBH(Date ngayHetHan) {
    Date homNay = LayNgayHienTaiBH();
    if (homNay.nam > ngayHetHan.nam) return "HET HAN";
    if (homNay.nam < ngayHetHan.nam) return "CON HAN";
    if (homNay.thang > ngayHetHan.thang) return "HET HAN";
    if (homNay.thang < ngayHetHan.thang) return "CON HAN";
    if (homNay.ngay > ngayHetHan.ngay) return "HET HAN";
    return "CON HAN";
}

void KeNgang(char kyTu = '-') {
    cout << string(TABLE_WIDTH, kyTu) << endl;
}

void InTieuDeBaoHanh() {
    KeNgang('=');
    cout << left << setw(10) << "Ma BH"
        << setw(10) << "Ma HD"
        << setw(12) << "Ma Laptop"
        << setw(12) << "Ma Khach"
        << setw(15) << "Serial"     // <--- CỘT MỚI
        << setw(18) << "Ngay Mua"
        << setw(18) << "Het Han"
        << setw(15) << "Trang Thai" << endl;
    KeNgang('-');
}

void InMotDongBaoHanh(const BaoHanh& bh) {
    char ngayMuaStr[15];
    sprintf_s(ngayMuaStr, "%02d/%02d/%04d", bh.ngayMua.ngay, bh.ngayMua.thang, bh.ngayMua.nam);

    char hetHanStr[15];
    sprintf_s(hetHanStr, "%02d/%02d/%04d", bh.ngayHetHan.ngay, bh.ngayHetHan.thang, bh.ngayHetHan.nam);

    cout << left
        << setw(10) << bh.maBH
        << setw(10) << bh.maHD
        << setw(12) << bh.maLaptop
        << setw(12) << bh.maKH
        << setw(15) << bh.serial  // <--- IN SERIAL
        << setw(18) << ngayMuaStr
        << setw(18) << hetHanStr
        << setw(15) << KiemTraTrangThaiBH(bh.ngayHetHan)
        << endl;
}

// =================== CHỨC NĂNG TRA CỨU ===================

void TraCuuBaoHanhTheoSerial(const DanhSachBaoHanh& dsBH) {
    char serial[20];
    cout << "Nhap So Serial can kiem tra (Check Legit): ";
    cin.ignore(); // Dọn dẹp bộ đệm
    cin.getline(serial, 20); // Dùng getline để nhập chuỗi

    cout << "\nKET QUA TRA CUU SERIAL: " << serial << "\n";
    InTieuDeBaoHanh();

    bool found = false;
    for (NodeBaoHanh* k = dsBH.head; k != NULL; k = k->next) {
        if (_stricmp(k->data.serial, serial) == 0) {
            InMotDongBaoHanh(k->data);
            found = true;
        }
    }
    KeNgang('=');

    if (found) {
        cout << ">> XAC NHAN: DAY LA SAN PHAM DO CUA HANG BAN RA.\n";
    }
    else {
        cout << ">> CANH BAO: Khong tim thay serial nay trong he thong!\n";
    }
}

void TraCuuBaoHanhTheoMaLaptop(const DanhSachBaoHanh& dsBH) {
    char maLT[10];
    cout << "Nhap Ma Laptop can kiem tra bao hanh: ";
    cin >> maLT;

    cout << "\nKET QUA TRA CUU:\n";
    InTieuDeBaoHanh();

    bool found = false;
    for (NodeBaoHanh* k = dsBH.head; k != NULL; k = k->next) {
        if (_stricmp(k->data.maLaptop, maLT) == 0) {
            InMotDongBaoHanh(k->data);
            found = true;
        }
    }
    KeNgang('=');

    if (!found) cout << "Khong co lich su bao hanh nao cho laptop nay.\n";
}

void TraCuuBaoHanhTheoKhachHang(const DanhSachBaoHanh& dsBH) {
    char maKH[10];
    cout << "Nhap Ma Khach Hang: ";
    cin >> maKH;

    cout << "\nCAC THIET BI DANG BAO HANH CUA KH '" << maKH << "':\n";
    InTieuDeBaoHanh();

    bool found = false;
    for (NodeBaoHanh* k = dsBH.head; k != NULL; k = k->next) {
        if (_stricmp(k->data.maKH, maKH) == 0) {
            InMotDongBaoHanh(k->data);
            found = true;
        }
    }
    KeNgang('=');

    if (!found) cout << "Khong tim thay.\n";
}

void XuatTatCaBaoHanh(const DanhSachBaoHanh& dsBH) {
    if (dsBH.head == NULL) {
        cout << "Chua co du lieu bao hanh nao trong he thong.\n";
        return;
    }
    cout << "\nDANH SACH TOAN BO PHIEU BAO HANH:\n";
    InTieuDeBaoHanh();
    for (NodeBaoHanh* k = dsBH.head; k != NULL; k = k->next) {
        InMotDongBaoHanh(k->data);
    }
    KeNgang('=');
    cout << "Tong so phieu: " << dsBH.soLuong << endl;
}

void MenuQuanLyBaoHanh(DanhSachBaoHanh& dsBH) {
    char luaChon;
    do {
        system("cls");
        cout << "======= QUAN LY BAO HANH =======\n";
        cout << "1. Tra cuu theo Serial (Chinh xac nhat)\n";
        cout << "2. Tra cuu theo Khach Hang (Lich su mua)\n";
        cout << "3. Xem lich su ban hang theo Dong May (Ma Laptop)\n";
        cout << "4. Xem toan bo danh sach Phieu Bao Hanh\n";
        cout << "0. Quay lai Menu Chinh\n";
        cout << "================================\n";
        cout << "Nhap lua chon: ";
        luaChon = _getch();

        system("cls");
        switch (luaChon) {
        case '1':
            TraCuuBaoHanhTheoSerial(dsBH); 
            break;
        case '2':
            TraCuuBaoHanhTheoKhachHang(dsBH);
            break;
        case '3':
            TraCuuBaoHanhTheoMaLaptop(dsBH); 
            break;
        case '4':
            XuatTatCaBaoHanh(dsBH);
            break;
        case '0': break;
        default: cout << "Lua chon khong hop le!\n"; break;
        }
        if (luaChon != '0') system("pause");
    } while (luaChon != '0');
}