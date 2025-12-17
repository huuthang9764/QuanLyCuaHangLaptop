#include "thongke.h"
#include <iostream>
#include <conio.h>
#include <iomanip>

using namespace std;

// =================== CÁC HÀM HỖ TRỢ TÍNH TOÁN ===================

double tinhLoiNhuanChiTietHoaDon(const DanhSachLaptop& dSLT, const ChiTietHoaDon& cTHD) {
    Laptop* pLaptop = TimKiemLaptop(dSLT, cTHD.maLaptop);
    if (pLaptop != NULL) {
        return (double)(cTHD.donGia - pLaptop->giaVon) * cTHD.soLuong;
    }
    return 0;
}

// =================== CÁC HÀM XUẤT BÁO CÁO DOANH THU ===================

void XuatBaoCaoDoanhThuNgay(Date ngayCanLoc, const DanhSachHoaDon& g_dsHoaDonToanCuc) {
    long long tongDoanhThu = 0;
    bool co = false;
    cout << "\n=== BAO CAO DOANH THU NGAY " << ngayCanLoc.ngay << "/" << ngayCanLoc.thang << "/" << ngayCanLoc.nam << " ===\n";
    cout << "--------------------------------------------------\n";
    cout << left << setw(10) << "Ma HD" << setw(15) << "Ma NV" << setw(20) << "Tong Tien" << endl;
    cout << "--------------------------------------------------\n";

    for (int i = 0; i < g_dsHoaDonToanCuc.soLuong; i++) {
        HoaDon hd = g_dsHoaDonToanCuc.ds[i];
        if (hd.ngayLap.ngay == ngayCanLoc.ngay && hd.ngayLap.thang == ngayCanLoc.thang && hd.ngayLap.nam == ngayCanLoc.nam) {
            co = true;
            cout << left << setw(10) << hd.maHD
                << setw(15) << hd.maNV
                << setw(20) << DinhDangTien(hd.tongTien) << endl;
            tongDoanhThu += hd.tongTien;
        }
    }
    cout << "--------------------------------------------------\n";
    if (!co) cout << "Khong co hoa don nao trong ngay nay.\n";
    else cout << ">> TONG DOANH THU: " << DinhDangTien(tongDoanhThu) << "\n";
}

void XuatBaoCaoDoanhThuThang(Date ngayCanLoc, const DanhSachHoaDon& g_dsHoaDonToanCuc) {
    long long tongDoanhThu = 0;
    bool co = false;
    cout << "\n=== BAO CAO DOANH THU THANG " << ngayCanLoc.thang << "/" << ngayCanLoc.nam << " ===\n";
    cout << "--------------------------------------------------\n";
    cout << left << setw(10) << "Ma HD" << setw(15) << "Ngay" << setw(20) << "Tong Tien" << endl;
    cout << "--------------------------------------------------\n";

    for (int i = 0; i < g_dsHoaDonToanCuc.soLuong; i++) {
        HoaDon hd = g_dsHoaDonToanCuc.ds[i];
        if (hd.ngayLap.thang == ngayCanLoc.thang && hd.ngayLap.nam == ngayCanLoc.nam) {
            co = true;
            cout << left << setw(10) << hd.maHD
                << hd.ngayLap.ngay << "/" << setw(2) << hd.ngayLap.thang
                << setw(8) << " "
                << setw(20) << DinhDangTien(hd.tongTien) << endl;
            tongDoanhThu += hd.tongTien;
        }
    }
    cout << "--------------------------------------------------\n";
    if (!co) cout << "Khong co hoa don nao trong thang nay.\n";
    else cout << ">> TONG DOANH THU: " << DinhDangTien(tongDoanhThu) << "\n";
}

void XuatBaoCaoDoanhThuNam(Date ngayCanLoc, const DanhSachHoaDon& g_dsHoaDonToanCuc) {
    long long tongDoanhThu = 0;
    bool co = false;
    cout << "\n=== BAO CAO DOANH THU NAM " << ngayCanLoc.nam << " ===\n";
    cout << "--------------------------------------------------\n";
    cout << left << setw(10) << "Ma HD" << setw(15) << "Thang" << setw(20) << "Tong Tien" << endl;
    cout << "--------------------------------------------------\n";

    for (int i = 0; i < g_dsHoaDonToanCuc.soLuong; i++) {
        HoaDon hd = g_dsHoaDonToanCuc.ds[i];
        if (hd.ngayLap.nam == ngayCanLoc.nam) {
            co = true;
            cout << left << setw(10) << hd.maHD
                << setw(2) << hd.ngayLap.thang << "/" << setw(12) << hd.ngayLap.nam
                << setw(20) << DinhDangTien(hd.tongTien) << endl;
            tongDoanhThu += hd.tongTien;
        }
    }
    cout << "--------------------------------------------------\n";
    if (!co) cout << "Khong co hoa don nao trong nam nay.\n";
    else cout << ">> TONG DOANH THU: " << DinhDangTien(tongDoanhThu) << " VND\n";
}

// =================== BÁO CÁO TỒN KHO ===================

void XuatBaoCaoTonKho(const DanhSachLaptop& g_dsLaptop) {
    cout << "\n================ BAO CAO TON KHO (ARRAY) ================\n";
    cout << left << setw(10) << "MaLT" << setw(30) << "Ten Laptop" << setw(10) << "SL Ton" << endl;
    cout << "-------------------------------------------------\n";

    long long tongSL = 0;

    for (int i = 0; i < g_dsLaptop.soLuong; i++) {
        Laptop lt = g_dsLaptop.ds[i];
        cout << left << setw(10) << lt.maLaptop
            << setw(30) << lt.tenLaptop
            << setw(10) << lt.soLuongTon << endl;
        tongSL += lt.soLuongTon;
    }
    cout << "-------------------------------------------------\n";
    cout << "Tong so luong may trong kho: " << tongSL << endl;
}

// =================== TÍNH LỢI NHUẬN (Quan Trọng) ===================

double TinhLoiNhuanNgay(const DanhSachLaptop& dslt, const DanhSachHoaDon& dshd, Date ngayCanLoc) {
    double tong = 0;

    for (int i = 0; i < dshd.soLuong; i++) {
        HoaDon hd = dshd.ds[i];
        if (hd.ngayLap.ngay == ngayCanLoc.ngay && hd.ngayLap.thang == ngayCanLoc.thang && hd.ngayLap.nam == ngayCanLoc.nam) {

            for (int j = 0; j < hd.dsChiTiet.soLuong; j++) {
                tong += tinhLoiNhuanChiTietHoaDon(dslt, hd.dsChiTiet.ds[j]);
            }
        }
    }
    return tong;
}

double TinhLoiNhuanThang(const DanhSachLaptop& dslt, const DanhSachHoaDon& dshd, Date ngayCanLoc) {
    double tong = 0;
    for (int i = 0; i < dshd.soLuong; i++) {
        HoaDon hd = dshd.ds[i];
        if (hd.ngayLap.thang == ngayCanLoc.thang && hd.ngayLap.nam == ngayCanLoc.nam) {

            for (int j = 0; j < hd.dsChiTiet.soLuong; j++) {
                tong += tinhLoiNhuanChiTietHoaDon(dslt, hd.dsChiTiet.ds[j]);
            }
        }
    }
    return tong;
}

double TinhLoiNhuanNam(const DanhSachLaptop& dslt, const DanhSachHoaDon& dshd, Date ngayCanLoc) {
    double tong = 0;
    for (int i = 0; i < dshd.soLuong; i++) {
        HoaDon hd = dshd.ds[i];
        if (hd.ngayLap.nam == ngayCanLoc.nam) {

            for (int j = 0; j < hd.dsChiTiet.soLuong; j++) {
                tong += tinhLoiNhuanChiTietHoaDon(dslt, hd.dsChiTiet.ds[j]);
            }
        }
    }
    return tong;
}

// =================== MENU CON (Giữ nguyên logic) ===================

void MenuDoanhThu(const DanhSachHoaDon& dshd) {
    char subChon;
    cout << "\n--- BAO CAO DOANH THU ---\n";
    cout << "1. Theo Ngay\n2. Theo Thang\n3. Theo Nam\nChon: ";
    subChon = _getch();
    cout << subChon << endl;

    Date d;
    if (subChon == '1') {
        cout << "Nhap Ngay Thang Nam (vd 18 11 2025): "; cin >> d.ngay >> d.thang >> d.nam;
        XuatBaoCaoDoanhThuNgay(d, dshd);
    }
    else if (subChon == '2') {
        cout << "Nhap Thang Nam (vd 11 2025): "; cin >> d.thang >> d.nam;
        XuatBaoCaoDoanhThuThang(d, dshd);
    }
    else if (subChon == '3') {
        cout << "Nhap Nam (vd 2025): "; cin >> d.nam;
        XuatBaoCaoDoanhThuNam(d, dshd);
    }
    else {
        cout << "Lua chon khong hop le.\n";
    }
}

void MenuLoiNhuan(const DanhSachHoaDon& dshd, const DanhSachLaptop& dslt) {
    char subChon;
    cout << "\n--- BAO CAO LOI NHUAN ---\n";
    cout << "1. Theo Ngay\n2. Theo Thang\n3. Theo Nam\nChon: ";
    subChon = _getch();
    cout << subChon << endl;

    Date d;
    long long loiNhuan = 0;
    if (subChon == '1') {
        cout << "Nhap Ngay Thang Nam: "; cin >> d.ngay >> d.thang >> d.nam;
        loiNhuan = (long long)TinhLoiNhuanNgay(dslt, dshd, d);
    }
    else if (subChon == '2') {
        cout << "Nhap Thang Nam: "; cin >> d.thang >> d.nam;
        loiNhuan = (long long)TinhLoiNhuanThang(dslt, dshd, d);
    }
    else if (subChon == '3') {
        cout << "Nhap Nam: "; cin >> d.nam;
        loiNhuan = (long long)TinhLoiNhuanNam(dslt, dshd, d);
    }
    else {
        cout << "Lua chon khong hop le.\n";
        return;
    }
    cout << ">> TONG LOI NHUAN: " << DinhDangTien(loiNhuan) << "\n";
}

void MenuThongKe(DanhSachHoaDon& dshd, const DanhSachLaptop& dslt) {
    char chon;
    do {
        system("cls");
        cout << "===== THONG KE & BAO CAO (ARRAY) =====\n";
        cout << "1. Bao cao Doanh Thu\n";
        cout << "2. Bao cao Ton Kho\n";
        cout << "3. Bao cao Loi Nhuan\n";
        cout << "0. Quay lai\n";
        cout << "==============================\n";
        cout << "Chon: ";
        chon = _getch();

        system("cls");

        switch (chon) {
        case '1': MenuDoanhThu(dshd); break;
        case '2': XuatBaoCaoTonKho(dslt); break;
        case '3': MenuLoiNhuan(dshd, dslt); break;
        case '0': break;
        default: cout << "Chon sai!\n"; break;
        }
        if (chon != '0') system("pause");
    } while (chon != '0');
}