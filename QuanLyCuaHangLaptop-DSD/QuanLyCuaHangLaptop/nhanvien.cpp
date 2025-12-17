#include "nhanvien.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstring>

using namespace std;

// =================== HELPER: IN DANH SÁCH (DÙNG MẢNG) ===================

void XuatDanhSachNhanVien(const DanhSachNhanVien& dsNV) {
    if (dsNV.soLuong == 0) {
        cout << "Danh sach nhan vien rong.\n";
        return;
    }
    cout << "-----------------------------------------------------------------------------------\n";
    cout << "| " << left << setw(10) << "Ma NV"
        << "| " << left << setw(25) << "Ten Nhan Vien"
        << "| " << left << setw(15) << "Chuc Vu"
        << "| " << left << setw(15) << "SDT"
        << "| " << left << setw(20) << "Email" << " |\n";
    cout << "-----------------------------------------------------------------------------------\n";

    // [THAY ĐỔI]: Duyệt mảng
    for (int i = 0; i < dsNV.soLuong; i++) {
        cout << "| " << left << setw(10) << dsNV.ds[i].maNV
            << "| " << left << setw(25) << dsNV.ds[i].tenNV
            << "| " << left << setw(15) << dsNV.ds[i].chucVu
            << "| " << left << setw(15) << dsNV.ds[i].soDT
            << "| " << left << setw(20) << dsNV.ds[i].email << " |\n";
    }
    cout << "-----------------------------------------------------------------------------------\n";
}

void XuatDanhSachTaiKhoan(const DanhSachTaiKhoan& dsTK) {
    if (dsTK.soLuong == 0) {
        cout << "Danh sach tai khoan rong.\n";
        return;
    }
    cout << "-------------------------------------------------------------\n";
    cout << "| " << left << setw(20) << "Ten Dang Nhap"
        << "| " << left << setw(10) << "Ma NV"
        << "| " << left << setw(10) << "Quyen"
        << "| " << left << setw(15) << "Trang Thai" << " |\n";
    cout << "-------------------------------------------------------------\n";

    for (int i = 0; i < dsTK.soLuong; i++) {
        cout << "| " << left << setw(20) << dsTK.ds[i].tenDangNhap
            << "| " << left << setw(10) << dsTK.ds[i].maNV
            << "| " << left << setw(10) << (dsTK.ds[i].quyen == QUAN_LY ? "Quan Ly" : "Nhan Vien")
            << "| " << left << setw(15) << (dsTK.ds[i].trangThai == TK_HOAT_DONG ? "Hoat Dong" : "DA KHOA") << " |\n";
    }
    cout << "-------------------------------------------------------------\n";
}

NhanVien NhapThongTinNhanVien() {
    NhanVien nv;
    cout << "Nhap Ma NV: "; cin >> nv.maNV;
    cout << "Nhap Ten NV: "; cin.ignore(); cin.getline(nv.tenNV, 50);
    cout << "Nhap Chuc Vu: "; cin.getline(nv.chucVu, 30);
    cout << "Nhap SDT: "; cin.getline(nv.soDT, 15);
    cout << "Nhap Email: "; cin.getline(nv.email, 50);
    return nv;
}

// =================== MENU TÀI KHOẢN ===================

void MenuQuanLyTaiKhoan(DanhSachTaiKhoan& dsTK, DanhSachNhanVien& dsNV) {
    char chon;
    do {
        system("cls");
        cout << "===== QUAN LY TAI KHOAN (ARRAY) =====\n";
        cout << "1. Them Tai Khoan moi\n";
        cout << "2. Xoa Tai Khoan\n";
        cout << "3. Doi Mat Khau\n";
        cout << "4. Khoa / Mo Khoa Tai Khoan\n";
        cout << "5. Xem danh sach Tai Khoan\n";
        cout << "0. Quay lai\n";
        cout << "Chon: ";
        chon = _getch();
        system("cls");

        switch (chon) {
        case '1': {
            cout << "--- 1. Them Tai Khoan ---\n";
            TaiKhoan tk;
            cout << "Nhap Ten Dang Nhap: "; cin >> tk.tenDangNhap;
            cout << "Nhap Mat Khau: "; cin >> tk.matKhau;
            XuatDanhSachNhanVien(dsNV);
            cout << "Nhap Ma NV so huu: "; cin >> tk.maNV;

            if (TimKiemNhanVien(dsNV, tk.maNV) == NULL) {
                cout << "Loi: Ma NV khong ton tai.\n";
            }
            else {
                int q;
                cout << "Chon Quyen (0: NV, 1: QL): "; cin >> q;
                tk.quyen = (q == 1) ? QUAN_LY : NHAN_VIEN;
                tk.trangThai = TK_HOAT_DONG;
                if (ThemTaiKhoan(dsTK, tk)) cout << "Them thanh cong!\n";
                else cout << "Loi: Danh sach day hoac trung User.\n";
            }
            break;
        }
        case '2': {
            cout << "--- 2. Xoa Tai Khoan ---\n";
            char user[30];
            cout << "Nhap Ten Dang Nhap: "; cin >> user;
            if (XoaTaiKhoan(dsTK, user)) cout << "Da xoa!\n";
            else cout << "Khong tim thay!\n";
            break;
        }
        case '3': {
            cout << "--- 3. Doi Mat Khau ---\n";
            char user[30], pass[30];
            cout << "User: "; cin >> user;
            cout << "New Pass: "; cin >> pass;
            if (DoiMatKhau(dsTK, user, pass)) cout << "Thanh cong!\n";
            else cout << "Loi: Khong tim thay user.\n";
            break;
        }
        case '4': {
            cout << "--- 4. Khoa/Mo Khoa ---\n";
            char user[30];
            cout << "User: "; cin >> user;
            TaiKhoan* tk = TimKiemTaiKhoan(dsTK, user);
            if (tk) {
                tk->trangThai = (tk->trangThai == TK_HOAT_DONG) ? TK_KHOA : TK_HOAT_DONG;
                cout << "Da doi trang thai!\n";
            }
            else cout << "Khong tim thay!\n";
            break;
        }
        case '5': XuatDanhSachTaiKhoan(dsTK); break;
        case '0': break;
        }
        if (chon != '0') system("pause");
    } while (chon != '0');
}

// =================== MENU NHÂN VIÊN ===================

void MenuQuanLyNhanVien(DanhSachNhanVien& dsNV, DanhSachTaiKhoan& dsTK) {
    char chon;
    do {
        system("cls");
        cout << "===== QUAN LY NHAN SU (ARRAY) =====\n";
        cout << "1. Them Nhan Vien\n";
        cout << "2. Xoa Nhan Vien (Xoa ca TK)\n";
        cout << "3. Sua Nhan Vien\n";
        cout << "4. Tim Kiem Nhan Vien\n";
        cout << "5. Xuat Danh Sach\n";
        cout << "6. Quan Ly Tai Khoan\n";
        cout << "0. Quay lai\n";
        cout << "Chon: ";
        chon = _getch();
        system("cls");

        switch (chon) {
        case '1': {
            NhanVien nv = NhapThongTinNhanVien();
            if (ThemNhanVien(dsNV, nv)) cout << "Them thanh cong!\n";
            else cout << "Loi: Danh sach day hoac trung Ma NV.\n";
            break;
        }
        case '2': {
            char ma[10];
            cout << "Nhap Ma NV xoa: "; cin >> ma;
            char yn; cout << "Xoa NV se xoa luon Tai khoan. Tiep tuc? (y/n): "; cin >> yn;
            if (yn == 'y' || yn == 'Y') {
                if (XoaNhanVien(dsNV, dsTK, ma)) cout << "Da xoa NV & TK!\n";
                else cout << "Khong tim thay!\n";
            }
            break;
        }
        case '3': {
            char ma[10];
            cout << "Nhap Ma NV sua: "; cin >> ma;
            NhanVien* nv = TimKiemNhanVien(dsNV, ma);
            if (nv) {
                NhanVien moi = NhapThongTinNhanVien();
                strcpy_s(moi.maNV, ma);
                SuaNhanVien(dsNV, moi);
                cout << "Sua thanh cong!\n";
            }
            else cout << "Khong tim thay!\n";
            break;
        }
        case '4': {
            char ma[10];
            cout << "Nhap Ma NV: "; cin >> ma;
            NhanVien* nv = TimKiemNhanVien(dsNV, ma);
            if (nv) cout << "Tim thay: " << nv->tenNV << " - " << nv->chucVu << endl;
            else cout << "Khong tim thay!\n";
            break;
        }
        case '5': XuatDanhSachNhanVien(dsNV); break;
        case '6': MenuQuanLyTaiKhoan(dsTK, dsNV); break;
        case '0': break;
        }
        if (chon != '0') system("pause");
    } while (chon != '0');
}