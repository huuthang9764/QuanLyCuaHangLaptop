#include "danhmuc.h"
#include <iostream>
#include <conio.h>  
#include <iomanip>  
#include <cstring>

using namespace std;

ThuongHieu NhapThongTinThuongHieu() {
    ThuongHieu th;
    cout << "Ma TH: "; cin >> th.maThuongHieu;
    cout << "Ten TH: "; cin.ignore(); cin.getline(th.tenThuongHieu, 50);
    cout << "Quoc gia: "; cin.getline(th.quocGia, 30);
    return th;
}

LoaiSanPham NhapThongTinLoai() {
    LoaiSanPham l;
    cout << "Ma Loai: "; cin >> l.maLoai;
    cout << "Ten Loai: "; cin.ignore(); cin.getline(l.tenLoai, 30);
    return l;
}

void XuatDanhSachThuongHieu(const DanhSachThuongHieu& dsth) {
    if (dsth.soLuong == 0) { cout << "Chua co Thuong Hieu nao trong danh sach.!\n"; return; }
    cout << "--- DANH SACH THUONG HIEU ---" << endl;
    cout << "| " << left << setw(10) << "Ma TH" << "| " << left << setw(20) << "Ten Thuong Hieu" << "| " << left << setw(15) << "Quoc Gia" << " |" << endl;
    cout << "------------------------------------------------------" << endl;

    for (int i = 0; i < dsth.soLuong; i++) {
        cout << "| " << left << setw(10) << dsth.ds[i].maThuongHieu
            << "| " << setw(20) << dsth.ds[i].tenThuongHieu
            << "| " << setw(15) << dsth.ds[i].quocGia << " |" << endl;
    }
    cout << "------------------------------------------------------" << endl;
}

void XuatDanhSachLoai(const DanhSachLoai& dsl) {
    if (dsl.soLuong == 0) { cout << "Chua co Loai San Pham nao trong danh sach.!\n"; return; }
    cout << "--- DANH SACH LOAI SAN PHAM ---" << endl;
    cout << "| " << left << setw(10) << "Ma Loai" << "| " << left << setw(30) << "Ten Loai" << " |" << endl;
    cout << "---------------------------------------------" << endl;

    for (int i = 0; i < dsl.soLuong; i++) {
        cout << "| " << left << setw(10) << dsl.ds[i].maLoai
            << "| " << setw(30) << dsl.ds[i].tenLoai << " |" << endl;
    }
    cout << "------------------------------------------------------" << endl;
}

void MenuThuongHieu(DanhSachThuongHieu& dsth) {
    char luaChon;
    do {
        system("cls");
        cout << "======= QUAN LY THUONG HIEU (ARRAY) =======" << endl;
        cout << "1. Them Thuong Hieu moi" << endl;
        cout << "2. Xoa Thuong Hieu" << endl;
        cout << "3. Sua Thuong Hieu" << endl;
        cout << "4. In danh sach Thuong Hieu" << endl;
        cout << "===========================================" << endl;
        cout << "0. Quay lai Menu Danh Muc" << endl;
        cout << "Nhap lua chon: ";
        luaChon = _getch();
        system("cls");

        switch (luaChon) {
        case '1': {
            ThuongHieu thMoi = NhapThongTinThuongHieu();
            if (ThemThuongHieu(dsth, thMoi)) cout << "Them thanh cong!" << endl;
            else cout << "Loi: Trung ma hoac danh sach day.\n";
            break;
        }
        case '2': {
            char maXoa[10]; cout << "Nhap Ma Thuong Hieu can xoa: "; cin >> maXoa;
            if (XoaThuongHieu(dsth, maXoa)) cout << "Xoa thanh cong!" << endl;
            else cout << "Khong tim thay!\n";
            break;
        }
        case '3': {
            char maSua[10]; cout << "Nhap Ma TH can sua: "; cin >> maSua;
            if (TimKiemThuongHieu(dsth, maSua) == NULL) cout << "Loi: Khong tim thay." << endl;
            else {
                ThuongHieu thSua;
                strcpy_s(thSua.maThuongHieu, maSua);
                cout << "Nhap Ten Thuong Hieu moi: "; cin.ignore(); cin.getline(thSua.tenThuongHieu, 50);
                cout << "Nhap Quoc Gia moi: "; cin.getline(thSua.quocGia, 30);
                SuaThuongHieu(dsth, thSua);
                cout << "Sua thanh cong!" << endl;
            }
            break;
        }
        case '4': XuatDanhSachThuongHieu(dsth); break;
        case '0': break;
        default: cout << "Lua chon khong hop le." << endl; break;
        }
        if (luaChon != '0') system("pause");
    } while (luaChon != '0');
}

void MenuLoai(DanhSachLoai& dsl) {
    char luaChon;
    do {
        system("cls");
        cout << "======= QUAN LY LOAI SAN PHAM (ARRAY) =======" << endl;
        cout << "1. Them Loai moi" << endl;
        cout << "2. Xoa Loai" << endl;
        cout << "3. Sua Loai" << endl;
        cout << "4. In danh sach Loai" << endl;
        cout << "=============================================" << endl;
        cout << "0. Quay lai Menu Danh Muc" << endl;
        cout << "Nhap lua chon: ";
        luaChon = _getch();
        system("cls");

        switch (luaChon) {
        case '1': {
            LoaiSanPham loaiMoi = NhapThongTinLoai();
            if (ThemLoai(dsl, loaiMoi)) cout << "Them thanh cong!" << endl;
            else cout << "Loi: Trung ma hoac day.\n";
            break;
        }
        case '2': {
            char maXoa[10]; cout << "Nhap Ma Loai can xoa: "; cin >> maXoa;
            if (XoaLoai(dsl, maXoa)) cout << "Xoa thanh cong!" << endl;
            else cout << "Khong tim thay!\n";
            break;
        }
        case '3': {
            char maSua[10]; cout << "Nhap Ma Loai can sua: "; cin >> maSua;
            if (TimKiemLoai(dsl, maSua) == NULL) cout << "Loi: Khong tim thay." << endl;
            else {
                LoaiSanPham loaiSua;
                strcpy_s(loaiSua.maLoai, maSua);
                cout << "Nhap Ten Loai moi: "; cin.ignore(); cin.getline(loaiSua.tenLoai, 30);
                SuaLoai(dsl, loaiSua);
                cout << "Sua thanh cong!" << endl;
            }
            break;
        }
        case '4': XuatDanhSachLoai(dsl); break;
        case '0': break;
        }
        if (luaChon != '0') system("pause");
    } while (luaChon != '0');
}

void MenuQuanLyDanhMuc(DanhSachThuongHieu& dsth, DanhSachLoai& dsl) {
    char luaChon;
    do {
        system("cls");
        cout << "======= QUAN LY DANH MUC =======" << endl;
        cout << "1. Quan ly Thuong Hieu" << endl;
        cout << "2. Quan ly Loai San Pham" << endl;
        cout << "================================" << endl;
        cout << "0. Quay lai Menu chinh" << endl;
        cout << "Nhap lua chon: ";
        luaChon = _getch();

        switch (luaChon) {
        case '1': MenuThuongHieu(dsth); break;
        case '2': MenuLoai(dsl); break;
        case '0': break;
        default: break;
        }
    } while (luaChon != '0');
}