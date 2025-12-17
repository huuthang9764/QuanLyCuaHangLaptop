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
    cout << left << setw(12) << "Ma KH"
        << setw(25) << "Ten KH"
        << setw(15) << "So DT"
        << setw(25) << "Email"
        << setw(30) << "Dia chi" << endl;

    cout << string(110, '-') << endl;

    NodeKhachHang* p = dskh.head;
    while (p) {
        XuatMotKhachHang(p->data);
        p = p->next;
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
    do {
        system("cls");
        cout << "===== QUAN LY KHACH HANG (LINKED LIST) =====\n";
        cout << "1. Them Khach hang\n";
        cout << "2. Xoa Khach hang\n";
        cout << "3. Sua Khach hang\n";
        cout << "4. Tim Khach hang\n";
        cout << "5. In danh sach KH\n";
        cout << "6. Sap xep theo ten\n";
        cout << "0. Quay lai\n";
        cout << "Chon: ";
        chon = _getch();

        char ma[10];

        // [QUAN TRỌNG]: Không khai báo 'KhachHang kh;' ở đây nữa để tránh tràn Stack

        switch (chon) {
        case '1': {
            // Cấp phát động để tránh Stack Overflow
            KhachHang* khTam = new KhachHang;

            // [DSLK]: BẮT BUỘC khởi tạo danh sách lồng nhau bằng NULL
            khTam->dsHoaDon.head = NULL;
            khTam->dsHoaDon.tail = NULL;
            khTam->dsHoaDon.soLuong = 0;

            // Gọi hàm nhập (truyền con trỏ)
            NhapThongTinKhachHang(khTam);

            if (ThemKhachHang(dsKH, *khTam)) cout << "Them thanh cong!\n";
            else cout << "Ma KH da ton tai!\n";

            // Giải phóng bộ nhớ
            delete khTam;

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

            // Tìm kiếm trước
            KhachHang* found = TimKiemKhachHang(dsKH, ma);

            if (found) {
                KhachHang* khTam = new KhachHang;

                // [Logic Bảo Toàn Dữ Liệu]:
                // 1. Copy toàn bộ dữ liệu cũ (bao gồm cả danh sách hóa đơn) sang biến tạm
                *khTam = *found;

                // 2. Nhập thông tin cá nhân mới đè lên biến tạm
                // (Hàm nhập KHÔNG ĐƯỢC reset dsHoaDon.head = NULL)
                NhapThongTinKhachHang(khTam);

                // 3. Đảm bảo mã giữ nguyên (tránh người dùng nhập mã khác)
                strcpy(khTam->maKH, ma);

                if (SuaKhachHang(dsKH, *khTam)) cout << "Sua thanh cong!\n";

                delete khTam;
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
        default:
            cout << "Lua chon khong hop le!\n";
            break;
        }

    } while (chon != '0');
}