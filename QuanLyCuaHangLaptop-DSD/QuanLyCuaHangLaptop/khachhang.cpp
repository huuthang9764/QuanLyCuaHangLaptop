#include "khachhang.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstring>

using namespace std;

void XuatMotKhachHang(const KhachHang& kh) {
    cout << left << setw(12) << kh.maKH
        << setw(25) << kh.tenKH
        << setw(15) << kh.soDT
        << setw(25) << kh.email
        << setw(30) << kh.diaChi << endl;
}

void XuatDanhSachKhachHang(const DanhSachKhachHang& dskh) {
    if (dskh.soLuong == 0) {
        cout << "Danh sach khach hang rong!\n";
        return;
    }

    cout << left << setw(12) << "Ma KH"
        << setw(25) << "Ten KH"
        << setw(15) << "So DT"
        << setw(25) << "Email"
        << setw(30) << "Dia chi" << endl;

    cout << string(110, '-') << endl;

    for (int i = 0; i < dskh.soLuong; i++) {
        XuatMotKhachHang(dskh.ds[i]);
    }
}

void NhapThongTinKhachHang(KhachHang* kh) {

    cout << "Nhap Ma Khach Hang (vd: KH001): ";
    cin.getline(kh->maKH, 10);

    cout << "Nhap Ten Khach Hang: ";
    cin.getline(kh->tenKH, 50);

    cout << "Nhap So Dien Thoai: ";
    cin.getline(kh->soDT, 15);

    cout << "Nhap Email: ";
    cin.getline(kh->email, 50);

    cout << "Nhap Dia Chi: ";
    cin.getline(kh->diaChi, 100);
}

void MenuQuanLyKhachHang(DanhSachKhachHang& dsKH) {
    char chon;

    KhachHang* khTam = new KhachHang;
    char ma[10];

    do {
        system("cls");
        cout << "===== QUAN LY KHACH HANG (ARRAY) =====\n";
        cout << "1. Them Khach hang\n";
        cout << "2. Xoa Khach hang\n";
        cout << "3. Sua Khach hang\n";
        cout << "4. Tim Khach hang\n";
        cout << "5. In danh sach KH\n";
        cout << "6. Sap xep theo ten\n";
        cout << "0. Quay lai\n";
        cout << "Chon: ";
        chon = _getch();

        switch (chon) {
        case '1': {
            khTam->dsHoaDon.soLuong = 0;

            NhapThongTinKhachHang(khTam);

            if (ThemKhachHang(dsKH, *khTam)) cout << "Them thanh cong!\n";
            else cout << "Loi: Ma KH da ton tai hoac danh sach day!\n";

            system("pause");
            break;
        }
        case '2': {
            cout << "Nhap ma KH can xoa: ";
            cin.getline(ma, 10);
            if (XoaKhachHang(dsKH, ma)) cout << "Xoa thanh cong!\n";
            else cout << "Khong tim thay!\n";
            system("pause");
            break;
        }
        case '3': {
            cout << "Nhap ma KH can sua: ";
            cin.getline(ma, 10);
            KhachHang* found = TimKiemKhachHang(dsKH, ma);

            if (found) {
                *khTam = *found;

                NhapThongTinKhachHang(khTam);

                strcpy_s(khTam->maKH, ma);

                if (SuaKhachHang(dsKH, *khTam)) cout << "Sua thanh cong!\n";
            }
            else cout << "Khong tim thay!\n";
            system("pause");
            break;
        }
        case '4': {
            cout << "Nhap ma KH: ";
            cin.getline(ma, 10);
            KhachHang* found = TimKiemKhachHang(dsKH, ma);
            if (found) {
                XuatMotKhachHang(*found);
            }
            else cout << "Khong tim thay!\n";
            system("pause");
            break;
        }
        case '5': {
            XuatDanhSachKhachHang(dsKH);
            system("pause");
            break;
        }
        case '6': {
            SapXepKhachHang_TheoTen(dsKH);
            cout << "Da sap xep!\n";
            system("pause");
            break;
        }
        case '0': break;
        default: cout << "Lua chon khong hop le!\n"; break;
        }
    } while (chon != '0');


    delete khTam;
}