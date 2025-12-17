#include "laptop.h"
#include "danhmuc.h" 
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <chrono>
#include <cstring>
#include <string>
#include "benchmark.h"


using namespace std;

string LayChuoiRAM(LoaiRAM ram) {
    return to_string((int)ram) + "GB";
}

string LayChuoiSSD(LoaiSSD ssd) {
    return to_string((int)ssd) + "GB";
}

void XuatThongTinLaptop(const Laptop& lt) {
    cout << "| " << left << setw(10) << lt.maLaptop
        << "| " << left << setw(25) << lt.tenLaptop
        << "| " << left << setw(10) << lt.maThuongHieu
        << "| " << left << setw(10) << lt.maLoai
        << "| " << right << setw(15) << DinhDangTien(lt.giaBan)
        << "| " << right << setw(8) << lt.soLuongTon
        << "| " << left << setw(12) << (lt.trangThai == CON_HANG ? "  Con hang" : "  Het hang")
        << " |" << endl;
}

void XuatDanhSachLaptop(const DanhSachLaptop& dsls) {
    if (dsls.soLuong == 0) { 
        cout << "Danh sach Laptop rong.\n";
        return;
    }
    cout << "---------------------------------------------------------------------------------------------------\n";
    cout << "| " << left << setw(10) << "Ma LT"
        << "| " << left << setw(25) << "Ten Laptop"
        << "| " << left << setw(10) << "Hang"
        << "| " << left << setw(10) << "Loai"
        << "| " << right << setw(15) << "Gia Ban"
        << "| " << right << setw(8) << "SL Ton"
        << "| " << left << setw(12) << "Trang Thai" << " |\n";
    cout << "---------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < dsls.soLuong; i++) {
        XuatThongTinLaptop(dsls.ds[i]);
    }
    cout << "---------------------------------------------------------------------------------------------------\n";
}

void XuatCauHinhChiTiet(const Laptop& lt) {
    cout << "\n================ CHI TIET CAU HINH ================\n";
    cout << " [THONG TIN CHUNG]\n";
    cout << "  - Ma SP:        " << lt.maLaptop << endl;
    cout << "  - Ten SP:       " << lt.tenLaptop << endl;
    cout << "  - Thuong hieu:  " << lt.maThuongHieu << endl;
    cout << "  - Loai:         " << lt.maLoai << endl;
    cout << "  - Gia Ban:      " << DinhDangTien(lt.giaBan) << " VND\n";
    cout << "  - Ton Kho:      " << lt.soLuongTon << endl;
    cout << "  - Bao Hanh:     " << lt.thoiGianBaoHanh << " thang\n";

    cout << " [THONG SO KY THUAT]\n";
    cout << "  - CPU:          " << lt.cauHinh.CPU << endl;
    cout << "  - RAM:          " << LayChuoiRAM(lt.cauHinh.RAM) << endl;
    cout << "  - SSD:          " << LayChuoiSSD(lt.cauHinh.SSD) << endl;
    cout << "  - GPU:          " << lt.cauHinh.GPU << endl;
    cout << "  - Man Hinh:     " << lt.cauHinh.KichThuocManHinh << " inch\n";
    cout << "===================================================\n";
}

// =================== CÁC HÀM LỌC & XEM (FILTER) ===================

void XemLaptopTheoThuongHieu(const DanhSachLaptop& dsls, const char maTH[10]) {
    cout << "\n=== DANH SACH LAPTOP THUONG HIEU: " << maTH << " ===\n";
    bool found = false;
    cout << "---------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < dsls.soLuong; i++) {
        if (_stricmp(dsls.ds[i].maThuongHieu, maTH) == 0) {
            XuatThongTinLaptop(dsls.ds[i]);
            found = true;
        }
    }
    cout << "---------------------------------------------------------------------------------------------------\n";
    if (!found) cout << "Khong tim thay laptop thuoc thuong hieu nay.\n";
}

void XemLaptopTheoLoai(const DanhSachLaptop& dsls, const char maLoai[10]) {
    cout << "\n=== DANH SACH LAPTOP LOAI: " << maLoai << " ===\n";
    bool found = false;
    cout << "---------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < dsls.soLuong; i++) {
        if (_stricmp(dsls.ds[i].maLoai, maLoai) == 0) {
            XuatThongTinLaptop(dsls.ds[i]);
            found = true;
        }
    }
    cout << "---------------------------------------------------------------------------------------------------\n";
    if (!found) cout << "Khong tim thay laptop thuoc loai nay.\n";
}

void XemLaptopTheoKhoangGia(const DanhSachLaptop& dsls, long long giaMin, long long giaMax) {
    cout << "\n=== DANH SACH LAPTOP GIA TU: " << giaMin << " - " << giaMax << " ===\n";
    bool found = false;
    cout << "---------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < dsls.soLuong; i++) {
        if (dsls.ds[i].giaBan >= giaMin && dsls.ds[i].giaBan <= giaMax) {
            XuatThongTinLaptop(dsls.ds[i]);
            found = true;
        }
    }
    cout << "---------------------------------------------------------------------------------------------------\n";
    if (!found) cout << "Khong co laptop nao trong khoang gia nay.\n";
}

void XemChiTietCauHinh(const DanhSachLaptop& dsls) {
    char ma[10];
    cout << "Nhap Ma Laptop can xem chi tiet: ";
    cin.getline(ma, 10);

    Laptop* lt = TimKiemLaptop(dsls, ma);
    if (lt != NULL) {
        XuatCauHinhChiTiet(*lt);
    }
    else {
        cout << "Loi: Khong tim thay Laptop co ma '" << ma << "'.\n";
    }
}

void XemLaptopTheoCPU(const DanhSachLaptop& dsls) {
    char cpuCanTim[30];
    cout << "\n--- TIM KIEM THEO CPU ---\n";
    cout << "Nhap ten CPU (vd: i5, i7, Ryzen): ";
    cin.getline(cpuCanTim, 30);

    cout << "\n=== KET QUA TIM KIEM: " << cpuCanTim << " ===\n";
    cout << "---------------------------------------------------------------------------------------------------\n";
    bool found = false;

    for (int i = 0; i < dsls.soLuong; i++) {
        if (strstr(dsls.ds[i].cauHinh.CPU, cpuCanTim) != NULL) {
            XuatThongTinLaptop(dsls.ds[i]);
            found = true;
        }
    }
    cout << "---------------------------------------------------------------------------------------------------\n";
    if (!found) cout << "Khong tim thay laptop nao.\n";
}

void XemLaptopTheoRAM(const DanhSachLaptop& dsls) {
    cout << "\n--- CHON DUNG LUONG RAM ---\n";
    cout << "1. 4GB\n2. 8GB\n3. 16GB\n4. 32GB\n5. 64GB\n";
    int chon;
    cout << "Chon: "; cin >> chon;

    LoaiRAM ramCanTim;
    switch (chon) {
    case 1: ramCanTim = RAM_4GB; break;
    case 2: ramCanTim = RAM_8GB; break;
    case 3: ramCanTim = RAM_16GB; break;
    case 4: ramCanTim = RAM_32GB; break;
    case 5: ramCanTim = RAM_64GB; break;
    default: cout << "Lua chon khong hop le.\n"; return;
    }

    cout << "\n=== DANH SACH LAPTOP RAM " << LayChuoiRAM(ramCanTim) << " ===\n";
    cout << "---------------------------------------------------------------------------------------------------\n";
    bool found = false;

    for (int i = 0; i < dsls.soLuong; i++) {
        if (dsls.ds[i].cauHinh.RAM == ramCanTim) {
            XuatThongTinLaptop(dsls.ds[i]);
            found = true;
        }
    }
    cout << "---------------------------------------------------------------------------------------------------\n";
    if (!found) cout << "Khong co may nao.\n";
}

void XemLaptopTheoSSD(const DanhSachLaptop& dsls) {
    cout << "\n--- CHON DUNG LUONG SSD ---\n";
    cout << "1. 128GB\n2. 256GB\n3. 512GB\n4. 1TB (1024GB)\n5. 2TB (2048GB)\n";
    int chon;
    cout << "Chon: "; cin >> chon;

    LoaiSSD ssdCanTim;
    switch (chon) {
    case 1: ssdCanTim = SSD_128GB; break;
    case 2: ssdCanTim = SSD_256GB; break;
    case 3: ssdCanTim = SSD_512GB; break;
    case 4: ssdCanTim = SSD_1024GB; break;
    case 5: ssdCanTim = SSD_2048GB; break;
    default: cout << "Lua chon khong hop le.\n"; return;
    }

    cout << "\n=== DANH SACH LAPTOP SSD " << LayChuoiSSD(ssdCanTim) << " ===\n";
    cout << "---------------------------------------------------------------------------------------------------\n";
    bool found = false;

    for (int i = 0; i < dsls.soLuong; i++) {
        if (dsls.ds[i].cauHinh.SSD == ssdCanTim) {
            XuatThongTinLaptop(dsls.ds[i]);
            found = true;
        }
    }
    cout << "---------------------------------------------------------------------------------------------------\n";
    if (!found) cout << "Khong co may nao.\n";
}

// =================== HÀM NHẬP LIỆU & NGHIỆP VỤ ===================

void ChonThuongHieuTuMenu(const DanhSachThuongHieu& dsth, char* maOut) {
    cout << "\n--- CHON THUONG HIEU ---\n";

    for (int i = 0; i < dsth.soLuong; i++) {
        cout << (i + 1) << ". " << dsth.ds[i].tenThuongHieu
            << " (" << dsth.ds[i].maThuongHieu << ")" << endl;
    }

    int chon;
    do {
        cout << "Chon so thu tu (1 - " << dsth.soLuong << "): ";
        cin >> chon;
        if (chon < 1 || chon > dsth.soLuong) {
            cout << "Lua chon khong hop le. Vui long chon lai!\n";
        }
    } while (chon < 1 || chon > dsth.soLuong);

    strcpy_s(maOut, 10, dsth.ds[chon - 1].maThuongHieu);
    cout << ">> Da chon: " << dsth.ds[chon - 1].tenThuongHieu << endl;
}

void ChonLoaiTuMenu(const DanhSachLoai& dsl, char* maOut) {
    cout << "\n--- CHON LOAI SAN PHAM ---\n";

    for (int i = 0; i < dsl.soLuong; i++) {
        cout << (i + 1) << ". " << dsl.ds[i].tenLoai
            << " (" << dsl.ds[i].maLoai << ")" << endl;
    }

    int chon;
    do {
        cout << "Chon so thu tu (1 - " << dsl.soLuong << "): ";
        cin >> chon;
        if (chon < 1 || chon > dsl.soLuong) {
            cout << "Lua chon khong hop le. Vui long chon lai!\n";
        }
    } while (chon < 1 || chon > dsl.soLuong);


    strcpy_s(maOut, 10, dsl.ds[chon - 1].maLoai);
    cout << ">> Da chon: " << dsl.ds[chon - 1].tenLoai << endl;
}

Laptop NhapThongTinLaptop(const DanhSachThuongHieu& dsth, const DanhSachLoai& dsl) {
    Laptop lt;
    char maTam[10];


    if (dsth.soLuong == 0 || dsl.soLuong == 0) {
        cout << "LOI: Can co it nhat 1 Thuong Hieu va 1 Loai SP de them Laptop.\n";
        strcpy_s(lt.maLaptop, "ERROR");
        return lt;
    }

    cout << "Nhap Ma Laptop (vd: LT001): ";
    cin.getline(lt.maLaptop, 10);

    cout << "Nhap Ten Laptop: ";
    cin.getline(lt.tenLaptop, 50);

    ChonThuongHieuTuMenu(dsth, maTam);
    strcpy_s(lt.maThuongHieu, maTam);

    ChonLoaiTuMenu(dsl, maTam);
    strcpy_s(lt.maLoai, maTam);

    cout << "Gia Von: "; cin >> lt.giaVon;
    cout << "Gia Ban: "; cin >> lt.giaBan;
    cout << "So Luong Ton: "; cin >> lt.soLuongTon;
    cout << "Bao Hanh (thang): "; cin >> lt.thoiGianBaoHanh;

    lt.trangThai = (lt.soLuongTon > 0) ? CON_HANG : HET_HANG;

    cin.ignore(1000, '\n');
    cout << "--- CAU HINH CHI TIET ---\n";
    cout << "CPU: "; cin.getline(lt.cauHinh.CPU, 30);

    int ram;
    cout << "RAM (4, 8, 16, 32...): "; cin >> ram;
    lt.cauHinh.RAM = static_cast<LoaiRAM>(ram);

    int ssd;
    cout << "SSD (128, 256, 512...): "; cin >> ssd;
    lt.cauHinh.SSD = static_cast<LoaiSSD>(ssd);

    cin.ignore(1000, '\n');
    cout << "GPU: "; cin.getline(lt.cauHinh.GPU, 30);
    cout << "Man Hinh (inch): "; cin >> lt.cauHinh.KichThuocManHinh;
    cin.ignore(1000, '\n');

    return lt;
}

void XuLyNhapKho(DanhSachLaptop& dsls) {
    char ma[10];
    cout << "Nhap Ma Laptop can nhap kho: ";
    cin.getline(ma, 10);

    Laptop* lt = TimKiemLaptop(dsls, ma);
    if (lt == NULL) {
        cout << "Loi: Khong tim thay Laptop.\n";
        return;
    }

    cout << "Tim thay: " << lt->tenLaptop << " | Ton kho hien tai: " << lt->soLuongTon << endl;
    int slThem;
    cout << "Nhap so luong muon them: ";
    cin >> slThem;

    if (slThem > 0) {
        lt->soLuongTon += slThem;
        if (lt->soLuongTon > 0) lt->trangThai = CON_HANG;
        cout << ">> Da cap nhat! Ton kho moi: " << lt->soLuongTon << endl;
    }
    else {
        cout << "Huy bo.\n";
    }
    cin.ignore(1000, '\n');
}

// =================== MENU CHÍNH CỦA MODULE ===================

void MenuQuanLyLaptop(DanhSachLaptop& dsls, const DanhSachThuongHieu& dsth, const DanhSachLoai& dsl) {
    char chon;
    do {
        system("cls");
        cout << "======= QUAN LY LAPTOP & KHO (Array Version) =======\n";
        cout << "1. Them Laptop moi\n";
        cout << "2. Xoa Laptop\n";
        cout << "3. Sua thong tin Laptop\n";
        cout << "4. Tim kiem Laptop (theo Ma)\n";
        cout << "5. In danh sach Laptop\n";
        cout << "6. Sap xep Laptop (theo Ten/Gia)\n";
        cout << "7. Nhap Kho (Cong don so luong)\n";
        cout << "8. Xem Laptop theo Hang\n";
        cout << "9. Xem Laptop theo Loai\n";
        cout << "a. Xem Laptop theo Khoang Gia\n";
        cout << "b. Xem Laptop theo CPU\n";
        cout << "c. Xem Chi Tiet Cau Hinh (Theo Ma)\n";
        cout << "d. Loc theo RAM\n";
        cout << "e. Loc theo SSD\n";
        cout << "0. Quay lai\n";
        cout << "====================================================\n";
        cout << "Chon: ";
        chon = _getch();

        system("cls");

        switch (chon) {
        case '1': {
            cout << "--- 1. Them Laptop ---\n";
            Laptop lt = NhapThongTinLaptop(dsth, dsl);

            if (strcmp(lt.maLaptop, "ERROR") != 0) {
                bool ketQuaThem = false;

                DoBenchmark("Thoi gian them: ", [&]() {
                    ketQuaThem = ThemLaptop(dsls, lt);
                    });

                if (ketQuaThem) cout << "Them thanh cong!\n";
                else cout << "Loi: Khong them duoc (Da day hoac trung ma)!\n";
            }
            break;
        }
        case '2': {
            cout << "--- 2. Xoa Laptop ---\n";
            char ma[10];
            cout << "Nhap ma can xoa: "; cin.getline(ma, 10);

            bool ketQuaXoa = false;

            DoBenchmark("Thoi gian xoa: ", [&]() {
                ketQuaXoa = XoaLaptop(dsls, ma);
                });

            if (ketQuaXoa) cout << "Da xoa!\n";
            else cout << "Khong tim thay!\n";
            break;
        }
        case '3': {
            cout << "--- 3. Sua Laptop ---\n";
            char ma[10];
            cout << "Nhap ma can sua: "; cin.getline(ma, 10);


            if (TimKiemLaptop(dsls, ma) == NULL) {
                cout << "Khong tim thay!\n";
            }
            else {
                cout << "Nhap thong tin moi:\n";
                Laptop ltMoi = NhapThongTinLaptop(dsth, dsl);
                strcpy_s(ltMoi.maLaptop, ma); 

                bool ketQuaSua = false;

                DoBenchmark("Thoi gian cap nhat: ", [&]() {
                    ketQuaSua = SuaLaptop(dsls, ltMoi);
                    });

                if (ketQuaSua) cout << "Da cap nhat!\n";
            }
            break;
        }
        case '4': {
            cout << "\n--- 4. Tim kiem Laptop (ARRAY) ---\n";
            char ma[10];
            cout << "Nhap ma can tim: ";
            cin.getline(ma, 10);

            Laptop* ketQua = nullptr;

            DoBenchmark("Thoi gian tim kiem: ", [&]() {
                ketQua = TimKiemLaptop(dsls, ma);
                });

            if (ketQua) {
                cout << ">> TIM THAY:\n";
                XuatThongTinLaptop(*ketQua);
            }
            else {
                cout << ">> Khong tim thay!\n";
            }
            break;
        }
        case '5': {

            DoBenchmark("Thoi gian hien thi toan bo: ", [&]() {
                XuatDanhSachLaptop(dsls);
                });
            break;
        }
        case '6': {
            char subChon;
            cout << "\n--- SAP XEP DANH SACH LAPTOP ---\n";
            cout << "1. Sap xep theo Ten (A-Z)\n";
            cout << "2. Sap xep theo Gia Ban (Tang dan)\n";
            cout << "Chon: ";
            subChon = _getch();

            if (subChon == '1') {
                DoBenchmark("Thoi gian sap xep Ten: ", [&]() {
                    SapXepLaptop_TheoTen(dsls);
                    });
                cout << "\n>> Da sap xep theo Ten!\n";
            }
            else if (subChon == '2') {
                DoBenchmark("Thoi gian sap xep Gia: ", [&]() {
                    SapXepLaptop_TheoGia(dsls);
                    });
                cout << "\n>> Da sap xep theo Gia!\n";
            }
            else {
                cout << "\n>> Huy sap xep.\n";
            }
            XuatDanhSachLaptop(dsls);
            break;
        }
        case '7': {
            XuLyNhapKho(dsls);
            break;
        }
        case '8': {
            for (int i = 0; i < dsth.soLuong; i++) {
                cout << dsth.ds[i].maThuongHieu << ": " << dsth.ds[i].tenThuongHieu << ", ";
            }
            cout << endl;
            char ma[10]; cout << "Nhap Ma Thuong Hieu: "; cin.getline(ma, 10);

            
            DoBenchmark("Thoi gian loc theo Hang: ", [&]() {
                XemLaptopTheoThuongHieu(dsls, ma);
                });
            break;
        }
        case '9': {
            for (int i = 0; i < dsl.soLuong; i++) {
                cout << dsl.ds[i].maLoai << ": " << dsl.ds[i].tenLoai << ", ";
            }
            cout << endl;
            char ma[10]; cout << "Nhap Ma Loai: "; cin.getline(ma, 10);

            DoBenchmark("Thoi gian loc theo Loai: ", [&]() {
                XemLaptopTheoLoai(dsls, ma);
                });
            break;
        }
        case 'a':
        case 'A': {
            long long min, max;
            cout << "Nhap gia min: "; cin >> min;
            cout << "Nhap gia max: "; cin >> max;
            cin.ignore(1000, '\n');

            DoBenchmark("Thoi gian loc khoang gia: ", [&]() {
                XemLaptopTheoKhoangGia(dsls, min, max);
                });
            break;
        }
        case 'b':
        case 'B': {

            char cpuCanTim[30];
            cout << "\n--- TIM KIEM THEO CPU ---\n";
            cout << "Nhap ten CPU (vd: i5, i7, Ryzen): ";
            cin.getline(cpuCanTim, 30);


            DoBenchmark("Thoi gian tim CPU: ", [&]() {
                cout << "\n=== KET QUA TIM KIEM: " << cpuCanTim << " ===\n";

                bool found = false;
                for (int i = 0; i < dsls.soLuong; i++) {
                    if (strstr(dsls.ds[i].cauHinh.CPU, cpuCanTim) != NULL) {
                        XuatThongTinLaptop(dsls.ds[i]);
                        found = true;
                    }
                }
                if (!found) cout << "Khong tim thay.\n";
                });
            break;
        }
        case 'c':
        case 'C': {
            char ma[10];
            cout << "Nhap Ma Laptop can xem chi tiet: ";
            cin.getline(ma, 10);

            Laptop* lt = nullptr;
            DoBenchmark("Thoi gian tim & hien thi: ", [&]() {
                lt = TimKiemLaptop(dsls, ma);
                if (lt != NULL) {
                    XuatCauHinhChiTiet(*lt);
                }
                });
            if (lt == NULL) cout << "Loi: Khong tim thay Laptop.\n";
            break;
        }
        case 'd':
        case 'D': {
           
            DoBenchmark("Thoi gian Loc RAM (gom input): ", [&]() {
                XemLaptopTheoRAM(dsls);
                });
            cin.ignore(1000, '\n');
            break;
        }
        case 'e':
        case 'E': {
            DoBenchmark("Thoi gian Loc SSD (gom input): ", [&]() {
                XemLaptopTheoSSD(dsls);
                });
            cin.ignore(1000, '\n');
            break;
        }
        case '0': break;
        default: cout << "Chon sai!\n"; break;
        }
        if (chon != '0') system("pause");
    } while (chon != '0');
}