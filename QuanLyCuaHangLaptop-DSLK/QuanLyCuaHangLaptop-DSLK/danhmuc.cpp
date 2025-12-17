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
    if (dsth.head == NULL) { cout << "Chua co Thuong Hieu nao trong danh sach.!\n"; return; }
    cout << "--- DANH SACH THUONG HIEU ---" << endl;
    cout << "| " << left << setw(10) << "Ma TH" << "| " << left << setw(20) << "Ten Thuong Hieu" << "| " << left << setw(15) << "Quoc Gia" << " |" << endl;
    cout << "------------------------------------------------------" << endl;
    for (NodeThuongHieu* k = dsth.head; k != NULL; k = k->next) {
        cout<< "| " << left << setw(10) << k->data.maThuongHieu
            << "| " << setw(20) << k->data.tenThuongHieu
            << "| " << setw(15) << k->data.quocGia << " |" << endl;
    }
    cout << "------------------------------------------------------" << endl;
}

void XuatDanhSachLoai(const DanhSachLoai& dsl) {
    if (dsl.head == NULL) { cout << "Chua co Loai San Pham nao trong danh sach.!\n"; return; }
    cout << "--- DANH SACH LOAI SAN PHAM ---" << endl;
    cout << "| " << left << setw(10) << "Ma Loai" << "| " << left << setw(30) << "Ten Loai" << " |" << endl;
    cout << "---------------------------------------------" << endl;
    for (NodeLoai* k = dsl.head; k != NULL; k = k->next) {
        cout << "| " << left << setw(10) << k->data.maLoai
             << "| " << setw(30) << k->data.tenLoai << " |" << endl;
    }
    cout << "------------------------------------------------------" << endl;
}
void MenuThuongHieu(DanhSachThuongHieu& dsth) {
    char luaChon;
    do {
        system("cls");
        cout << "======= QUAN LY THUONG HIEU =======" << endl;
        cout << "1. Them Thuong Hieu moi" << endl;
        cout << "2. Xoa Thuong Hieu" << endl;
        cout << "3. Sua Thuong Hieu" << endl;
        cout << "4. In danh sach Thuong Hieu" << endl;
        cout << "===================================" << endl;
        cout << "0. Quay lai Menu Danh Muc" << endl;
        cout << "Nhap lua chon: ";
        luaChon = _getch();
        system("cls");

        switch (luaChon) {
        case '1': {
            cout << "--- 1. Them Thuong Hieu moi ---" << endl;
            ThuongHieu thMoi;
            cout << "Nhap Ma Thuong Hieu (vd: DELL): ";
            cin.getline(thMoi.maThuongHieu, 10);
            cout << "Nhap Ten Thuong Hieu: ";
            cin.getline(thMoi.tenThuongHieu, 50);
            cout << "Nhap Quoc Gia: ";
            cin.getline(thMoi.quocGia, 30);

            if (ThemThuongHieu(dsth, thMoi)) {
                cout << "Them thanh cong!" << endl;
            }

            break;
        }
        case '2': {
            cout << "--- 2. Xoa Thuong Hieu ---" << endl;
            char maXoa[10];
            cout << "Nhap Ma Thuong Hieu can xoa: ";
            cin.getline(maXoa, 10);

            if (XoaThuongHieu(dsth, maXoa)) {
                cout << "Xoa thanh cong!" << endl;
            }
            break;
        }
        case '3': {
            cout << "--- 3. Sua Thuong Hieu ---" << endl;
            ThuongHieu thSua;
            cout << "Nhap Ma Thuong Hieu can sua: ";
            cin.getline(thSua.maThuongHieu, 10);

            if (TimKiemThuongHieu(dsth, thSua.maThuongHieu) == NULL) {
                cout << "Loi: Khong tim thay Thuong Hieu nay." << endl;
            }
            else {
                cout << "Nhap Ten Thuong Hieu moi: ";
                cin.getline(thSua.tenThuongHieu, 50);
                cout << "Nhap Quoc Gia moi: ";
                cin.getline(thSua.quocGia, 30);

                if (SuaThuongHieu(dsth, thSua)) {
                    cout << "Sua thanh cong!" << endl;
                }
            }
            break;
        }
        case '4': {
            cout << "--- 4. In danh sach Thuong Hieu ---" << endl;
            XuatDanhSachThuongHieu(dsth);
            break;
        }
        case '0':
            break;
        default:
            cout << "Lua chon khong hop le." << endl;
            break;
        }
        if (luaChon != '0') system("pause");
    } while (luaChon != '0');
}


void MenuLoai(DanhSachLoai& dsl) {

    char luaChon;
    do {
        system("cls");
        cout << "======= QUAN LY LOAI SAN PHAM =======" << endl;
        cout << "1. Them Loai moi" << endl;
        cout << "2. Xoa Loai" << endl;
        cout << "3. Sua Loai" << endl;
        cout << "4. In danh sach Loai" << endl;
        cout << "=====================================" << endl;
        cout << "0. Quay lai Menu Danh Muc" << endl;
        cout << "Nhap lua chon: ";
        luaChon = _getch();
        system("cls");

        switch (luaChon) {
        case '1': {
            cout << "--- 1. Them Loai moi ---" << endl;
            LoaiSanPham loaiMoi;
            cout << "Nhap Ma Loai (vd: GAMING): ";
            cin.getline(loaiMoi.maLoai, 10);
            cout << "Nhap Ten Loai: ";
            cin.getline(loaiMoi.tenLoai, 30);

            if (ThemLoai(dsl, loaiMoi)) {
                cout << "Them thanh cong!" << endl;
            }
            break;
        }
        case '2': {
            cout << "--- 2. Xoa Loai ---" << endl;
            char maXoa[10];
            cout << "Nhap Ma Loai can xoa: ";
            cin.getline(maXoa, 10);

            if (XoaLoai(dsl, maXoa)) {
                cout << "Xoa thanh cong!" << endl;
            }
            break;
        }
        case '3': {
            cout << "--- 3. Sua Loai ---" << endl;
            LoaiSanPham loaiSua;
            cout << "Nhap Ma Loai can sua: ";
            cin.getline(loaiSua.maLoai, 10);

            if (TimKiemLoai(dsl, loaiSua.maLoai) == NULL) {
                cout << "Loi: Khong tim thay Loai nay." << endl;
            }
            else {
                cout << "Nhap Ten Loai moi: ";
                cin.getline(loaiSua.tenLoai, 30);

                if (SuaLoai(dsl, loaiSua)) {
                    cout << "Sua thanh cong!" << endl;
                }
            }
            break;
        }
        case '4': {
            cout << "--- 4. In danh sach Loai ---" << endl;
            XuatDanhSachLoai(dsl);
            break;
        }
        case '0':
            break;
        default:
            cout << "Lua chon khong hop le." << endl;
            break;
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
        case '1':
            MenuThuongHieu(dsth);
            break;
        case '2':
            MenuLoai(dsl);
            break;
        case '0':
            break;
        default:
            cout << "Lua chon khong hop le." << endl;
            system("pause");
            break;
        }
    } while (luaChon != '0');
}