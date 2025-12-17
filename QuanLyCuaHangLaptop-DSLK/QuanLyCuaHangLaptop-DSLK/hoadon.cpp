#define _CRT_SECURE_NO_WARNINGS
#include "hoadon.h"
#include "khachhang.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <ctime>
#include <cstdio>
#include <cstring>

using namespace std;

// =================== HÀM HỖ TRỢ ===================

Date LayNgayHienTai() {
    time_t t = time(0);
    struct tm* now = localtime(&t);
    Date d;
    d.ngay = now->tm_mday;
    d.thang = now->tm_mon + 1;
    d.nam = now->tm_year + 1900;
    return d;
}

Date TinhNgayHetHan(Date ngayMua, int thoiGianBaoHanhThang) {
    Date d = ngayMua;
    d.thang += thoiGianBaoHanhThang;
    while (d.thang > 12) {
        d.thang -= 12;
        d.nam++;
    }
    return d;
}

void InChiTietGioHang(const HoaDon& hd, DanhSachLaptop& dsLT) {
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << left << setw(5) << "STT"
        << setw(10) << "Ma LT"
        << setw(20) << "Ten Laptop"
        << setw(15) << "Serial"
        << setw(15) << "Don Gia" << endl;
    cout << "------------------------------------------------------------------------------------------------\n";

    int i = 1;

    for (NodeChiTiet* k = hd.dsChiTiet.head; k != NULL; k = k->next) {
        Laptop* lt = TimKiemLaptop(dsLT, k->data.maLaptop);
        cout << left << setw(5) << i++
            << setw(10) << k->data.maLaptop
            << setw(20) << (lt ? lt->tenLaptop : "N/A")
            << setw(15) << k->data.serial
            << setw(15) << DinhDangTien(k->data.thanhTien) << endl;
    }
    cout << right << setw(65) << "TONG CONG: " << DinhDangTien(hd.tongTien) << endl;
}

void XuatDanhSachHoaDon(const DanhSachHoaDon& dsHD) {
    if (dsHD.head == NULL) { cout << "Trong!\n"; return; }

    cout << "\n--- DANH SACH HOA DON ---\n";
    for (NodeHoaDon* k = dsHD.head; k != NULL; k = k->next) {
        cout << k->data.maHD << " - " << k->data.maKH
            << " - " << DinhDangTien(k->data.tongTien) << endl;
    }
}

// =================== CHỨC NĂNG LẬP HÓA ĐƠN ===================

void LapHoaDonMoi(DanhSachHoaDon& dsHD, DanhSachKhachHang& dsKH, DanhSachLaptop& dsLT, DanhSachBaoHanh& dsBH, TaiKhoan* tkCurrent) {
    system("cls");
    cout << "=========== LAP HOA DON BAN HANG (LINKED LIST) ===========\n";
    cout << "(Go 'huy' o bat cu buoc nhap lieu nao de thoat)\n";

    // 1. KHỞI TẠO
    HoaDon hdMoi;
    KhoiTaoDanhSachChiTiet(hdMoi.dsChiTiet); 
    hdMoi.tongTien = 0;
    hdMoi.trangThai = 1;
    hdMoi.ngayLap = LayNgayHienTai();
    strcpy_s(hdMoi.maNV, tkCurrent->maNV);
    sprintf_s(hdMoi.maHD, "HD%03d", dsHD.soLuong + 1);

    cout << "Ma Hoa Don: " << hdMoi.maHD << endl;
    cout << "Nhan Vien: " << hdMoi.maNV << endl;
    cout << "Ngay Lap: " << hdMoi.ngayLap.ngay << "/" << hdMoi.ngayLap.thang << "/" << hdMoi.ngayLap.nam << endl;

    // 2. CHỌN KHÁCH
    char maKH[10];
    KhachHang* kh = NULL;
    do {
        cout << "Nhap Ma Khach Hang (go '0' xem DS, 'huy' de thoat): ";
        cin >> maKH;

        if (_stricmp(maKH, "huy") == 0) { cout << ">> Da huy.\n"; return; }
        if (strcmp(maKH, "0") == 0) { XuatDanhSachKhachHang(dsKH); continue; }

        kh = TimKiemKhachHang(dsKH, maKH);
        if (kh == NULL) {
            cout << "Khong tim thay KH!\n";
            char chonTao;
            cout << "Tao moi? (y/n): "; cin >> chonTao;
            cin.ignore(1000, '\n');

            if (chonTao == 'y' || chonTao == 'Y') {

                KhachHang* khTam = new KhachHang;

                khTam->dsHoaDon.head = NULL;
                khTam->dsHoaDon.tail = NULL;
                khTam->dsHoaDon.soLuong = 0;

                // Nhập thông tin (Hàm void nhận con trỏ)
                NhapThongTinKhachHang(khTam);

                if (strlen(khTam->maKH) > 0 && ThemKhachHang(dsKH, *khTam)) {
                    cout << ">> Tao thanh cong!\n";

                    if (dsKH.tail != NULL) {
                        kh = &dsKH.tail->data;
                        strcpy_s(maKH, kh->maKH);
                    }
                }
                else {
                    cout << "Loi tao moi.\n";
                }

                // Dọn dẹp Heap
                delete khTam;
            }
        }
    } while (kh == NULL);

    strcpy_s(hdMoi.maKH, kh->maKH);
    cout << ">> Chon KH: " << kh->tenKH << endl;

    // 3. CHỌN HÀNG & NHẬP SERIAL
    while (true) {
        char maLT[10];
        cout << "\nNhap Ma Laptop (go 'end' de thanh toan, 'huy' de huy): ";
        cin >> maLT;

        if (_stricmp(maLT, "huy") == 0) { cout << ">> Huy don.\n"; return; }
        if (_stricmp(maLT, "end") == 0) break;

        Laptop* lt = TimKiemLaptop(dsLT, maLT);
        if (!lt) { cout << "Khong tim thay!\n"; continue; }
        if (lt->trangThai == HET_HANG || lt->soLuongTon <= 0) { cout << "Het hang!\n"; continue; }

        cout << ">> SP: " << lt->tenLaptop << " (Gia: " << DinhDangTien(lt->giaBan) << ")\n";

        ChiTietHoaDon ct;
        strcpy_s(ct.maLaptop, maLT);

        cout << "Nhap So Serial (S/N) cua may: ";
        cin.ignore();
        cin.getline(ct.serial, 20);

        ct.soLuong = 1;
        ct.donGia = (long)lt->giaBan;
        ct.thanhTien = ct.donGia;

        ThemChiTietVaoHoaDon(hdMoi, ct);
        cout << "Da them may Serial [" << ct.serial << "] vao gio! Tong: " << DinhDangTien(hdMoi.tongTien) << "\n";
    }

    // 4. THANH TOÁN
    if (hdMoi.dsChiTiet.soLuong == 0) { cout << "Gio rong.\n"; return; }

    system("cls");
    cout << "--- XAC NHAN HOA DON ---\n";
    cout << "Khach hang: " << kh->tenKH << endl;
    InChiTietGioHang(hdMoi, dsLT);

    char xacNhan; cout << "\nXac nhan thanh toan? (y/n): "; cin >> xacNhan;
    if (xacNhan == 'y' || xacNhan == 'Y') {

        for (NodeChiTiet* k = hdMoi.dsChiTiet.head; k != NULL; k = k->next) {
            // Trừ kho
            CapNhatSoLuongLaptop(dsLT, k->data.maLaptop, 1);

            // Tạo bảo hành
            Laptop* lt = TimKiemLaptop(dsLT, k->data.maLaptop);
            BaoHanh bh;
            sprintf_s(bh.maBH, "BH%03d", dsBH.soLuong + 1);
            strcpy_s(bh.maHD, hdMoi.maHD);
            strcpy_s(bh.maKH, hdMoi.maKH);
            strcpy_s(bh.maLaptop, k->data.maLaptop);
            strcpy_s(bh.serial, k->data.serial);

            bh.ngayMua = hdMoi.ngayLap;
            if (lt) bh.ngayHetHan = TinhNgayHetHan(bh.ngayMua, lt->thoiGianBaoHanh);
            else bh.ngayHetHan = bh.ngayMua;

            bh.trangThai = BH_CON_HAN;
            ThemBaoHanh(dsBH, bh);
        }

        if (ThemHoaDon(dsHD, dsKH, hdMoi)) {
            cout << "THANH CONG! Da luu hoa don va tao phieu bao hanh.\n";
        }
    }
    else cout << "Da huy.\n";
}

void MenuQuanLyHoaDon(DanhSachHoaDon& dsHD, DanhSachKhachHang& dsKH, DanhSachLaptop& dsLT, DanhSachBaoHanh& dsBH, TaiKhoan* tkCurrent) {
    char luaChon;
    do {
        system("cls");
        cout << "======= QUAN LY BAN HANG (LINKED LIST) =======\n";
        cout << "1. Lap Hoa Don Moi\n";
        cout << "2. Xem Danh Sach Hoa Don\n";
        cout << "0. Quay lai\n";
        cout << "Chon: ";
        luaChon = _getch();
        switch (luaChon) {
        case '1': LapHoaDonMoi(dsHD, dsKH, dsLT, dsBH, tkCurrent); break;
        case '2': system("cls"); XuatDanhSachHoaDon(dsHD); break;
        case '0': break;
        default: cout << "Sai!\n"; break;
        }
        if (luaChon != '0') system("pause");
    } while (luaChon != '0');
}