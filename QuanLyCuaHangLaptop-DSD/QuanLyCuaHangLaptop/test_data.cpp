#include "test_data.h"
#include "xuly.h"
#include <iostream>
#include <cstdio>
#include <cstdlib> // Cho rand()
#include <ctime>   // Cho time()

using namespace std;

// =================== CẤU HÌNH SỐ LƯỢNG MUỐN TẠO ===================

const int SL_LAPTOP_GEN = 2000;
const int SL_KHACH_GEN = 1500;
const int SL_NHANVIEN_GEN = 50;
const int SL_HOADON_GEN = 500;

// =================== HÀM HỖ TRỢ RANDOM ===================
int Rand(int min, int max) {
    return min + rand() % (max - min + 1);
}

Date RandDate() {
    Date d;
    d.nam = Rand(2023, 2025);
    d.thang = Rand(1, 12);
    if (d.thang == 2) d.ngay = Rand(1, 28);
    else if (d.thang == 4 || d.thang == 6 || d.thang == 9 || d.thang == 11) d.ngay = Rand(1, 30);
    else d.ngay = Rand(1, 31);
    return d;
}

Date TinhHetHanFake(Date ngayMua, int thangBH) {
    Date d = ngayMua;
    d.thang += thangBH;
    while (d.thang > 12) {
        d.thang -= 12;
        d.nam++;
    }
    return d;
}

const char* HO[] = { "Nguyen", "Tran", "Le", "Pham", "Hoang", "Huynh", "Phan", "Vu", "Vo", "Dang" };
const char* TEN[] = { "An", "Binh", "Cuong", "Dung", "Em", "Giang", "Huy", "Khanh", "Lan", "Minh", "Nam", "Oanh", "Phat", "Quyen", "Tu", "Van", "Xuan", "Yen" };

void TaoTenNgauNhien(char* buffer) {
    int rHo = Rand(0, 9);
    int rTen = Rand(0, 17);
    sprintf_s(buffer, 50, "%s Van %s", HO[rHo], TEN[rTen]);
}

// =================== SINH DỮ LIỆU CHÍNH ===================

void KhoiTaoDuLieuTuDong(
    DanhSachLaptop& dsls, DanhSachKhachHang& dskh, DanhSachNhanVien& dsnv,
    DanhSachTaiKhoan& dstk, DanhSachThuongHieu& dsth, DanhSachLoai& dsl,
    DanhSachHoaDon& dsHD, DanhSachBaoHanh& dsBH)
{
    // Kiểm tra nếu có dữ liệu rồi thì thôi
    if (dsls.soLuong > 0) return;

    srand((unsigned int)time(NULL));
    cout << ">> Dang sinh du lieu mau (Array Version - Large Data)... \n";

    // --- 1. DANH MỤC ---
    const char* MA_TH[] = { "DELL", "ASUS", "HP", "MAC", "MSI", "ACER", "LENOVO" };
    const char* TEN_TH[] = { "Dell Inc", "Asus Tek", "HP Inc", "Apple", "MSI Gaming", "Acer Corp", "Lenovo Group" };
    for (int i = 0; i < 7; i++) {
        ThuongHieu th;
        strcpy_s(th.maThuongHieu, MA_TH[i]);
        strcpy_s(th.tenThuongHieu, TEN_TH[i]);
        strcpy_s(th.quocGia, (i == 3) ? "USA" : "Taiwan");
        ThemThuongHieu(dsth, th);
    }

    const char* MA_LOAI[] = { "GAME", "OFFICE", "WORK", "ULTR" };
    const char* TEN_LOAI[] = { "Gaming Laptop", "Van Phong", "Workstation", "Ultrabook" };
    for (int i = 0; i < 4; i++) {
        LoaiSanPham l;
        strcpy_s(l.maLoai, MA_LOAI[i]);
        strcpy_s(l.tenLoai, TEN_LOAI[i]);
        ThemLoai(dsl, l);
    }

    // --- 2. LAPTOP ---
    Laptop* arrLaptop[MAX_LAPTOP];
    int countLT = 0;

    const char* CPU_LIST[] = { "Core i5 12400H", "Core i7 13700K", "Core i9 13900HX", "Ryzen 5 5600H", "Ryzen 7 7735HS", "M1 Pro", "M2 Max" };
    const char* GPU_LIST[] = { "RTX 3050", "RTX 4060", "RTX 4090", "GTX 1650", "Intel Iris Xe", "Radeon 680M" };

    for (int i = 1; i <= SL_LAPTOP_GEN; i++) {

        if (dsls.soLuong >= MAX_LAPTOP) break;

        Laptop lt;
        sprintf_s(lt.maLaptop, "LT%04d", i);

        int rTH = Rand(0, 6);
        int rLoai = Rand(0, 3);
        strcpy_s(lt.maThuongHieu, MA_TH[rTH]);
        strcpy_s(lt.maLoai, MA_LOAI[rLoai]);
        sprintf_s(lt.tenLaptop, "%s %s %d", MA_TH[rTH], MA_LOAI[rLoai], Rand(100, 999));

        lt.giaVon = Rand(10, 40) * 1000000;
        lt.giaBan = lt.giaVon + Rand(2, 8) * 1000000;
        lt.soLuongTon = Rand(50, 200);
        lt.thoiGianBaoHanh = (Rand(0, 1) == 0) ? 12 : 24;
        lt.trangThai = CON_HANG;

        // Cấu hình
        strcpy_s(lt.cauHinh.CPU, CPU_LIST[Rand(0, 6)]);
        strcpy_s(lt.cauHinh.GPU, GPU_LIST[Rand(0, 5)]);
        int valsRAM[] = { 4, 8, 16, 32, 64 };
        lt.cauHinh.RAM = static_cast<LoaiRAM>(valsRAM[Rand(0, 4)]);
        int valsSSD[] = { 128, 256, 512, 1024, 2048 };
        lt.cauHinh.SSD = static_cast<LoaiSSD>(valsSSD[Rand(0, 4)]);
        lt.cauHinh.KichThuocManHinh = (Rand(0, 1) == 0) ? 15.6f : 14.0f;

        ThemLaptop(dsls, lt);

        arrLaptop[countLT++] = &dsls.ds[dsls.soLuong - 1];
    }

    // --- 3. NHÂN VIÊN & TÀI KHOẢN ---
    NhanVien* arrNV[100];
    int countNV = 0;

    // Admin
    NhanVien admin; strcpy_s(admin.maNV, "NV001"); strcpy_s(admin.tenNV, "Administrator");
    strcpy_s(admin.chucVu, "Quan Ly"); strcpy_s(admin.soDT, "000"); strcpy_s(admin.email, "admin@store.com");
    ThemNhanVien(dsnv, admin);
    TaiKhoan tkAdmin; strcpy_s(tkAdmin.tenDangNhap, "admin"); strcpy_s(tkAdmin.matKhau, "admin");
    strcpy_s(tkAdmin.maNV, "NV001"); tkAdmin.quyen = QUAN_LY; tkAdmin.trangThai = TK_HOAT_DONG;
    ThemTaiKhoan(dstk, tkAdmin);

    arrNV[countNV++] = &dsnv.ds[dsnv.soLuong - 1];

    // Nhân viên
    for (int i = 2; i <= SL_NHANVIEN_GEN + 1; i++) {
        if (dsnv.soLuong >= MAX_NHANVIEN) break;

        NhanVien nv;
        sprintf_s(nv.maNV, "NV%03d", i);
        TaoTenNgauNhien(nv.tenNV);
        strcpy_s(nv.chucVu, "Ban Hang");
        sprintf_s(nv.soDT, "09%08d", Rand(10000000, 99999999));
        sprintf_s(nv.email, "user%d@store.com", i);
        ThemNhanVien(dsnv, nv);

        TaiKhoan tk;
        sprintf_s(tk.tenDangNhap, "user%d", i);
        strcpy_s(tk.matKhau, "123");
        strcpy_s(tk.maNV, nv.maNV);
        tk.quyen = NHAN_VIEN;
        tk.trangThai = TK_HOAT_DONG;
        ThemTaiKhoan(dstk, tk);

        arrNV[countNV++] = &dsnv.ds[dsnv.soLuong - 1];
    }

    // --- 4. KHÁCH HÀNG ---
    KhachHang* arrKH[MAX_KHACHHANG];
    int countKH = 0;

    for (int i = 1; i <= SL_KHACH_GEN; i++) {
        if (dskh.soLuong >= MAX_KHACHHANG) {
            cout << "Canh bao: Mang Khach Hang da day (" << MAX_KHACHHANG << "). Dung tao KH.\n";
            break;
        }

        KhachHang kh;
        sprintf_s(kh.maKH, "KH%03d", i);
        TaoTenNgauNhien(kh.tenKH);
        sprintf_s(kh.soDT, "09%08d", Rand(10000000, 99999999));
        sprintf_s(kh.email, "khach%d@gmail.com", i);
        strcpy_s(kh.diaChi, "Ho Chi Minh City");

        ThemKhachHang(dskh, kh);
        arrKH[countKH++] = &dskh.ds[dskh.soLuong - 1];
    }

    // --- 5. GIẢ LẬP GIAO DỊCH (Hóa đơn + Bảo hành) ---
    cout << ">> Dang tao hoa don giao dich...\n";
    for (int i = 1; i <= SL_HOADON_GEN; i++) {
        if (dsHD.soLuong >= MAX_HOADON) {
            cout << "Canh bao: Mang Hoa Don da day. Dung tao HD.\n";
            break;
        }

        HoaDon hd;
        sprintf_s(hd.maHD, "HD%03d", i);

        // Random người mua và người bán
        if (countKH == 0 || countNV == 0) break;
        KhachHang* khMua = arrKH[Rand(0, countKH - 1)];
        NhanVien* nvBan = arrNV[Rand(0, countNV - 1)];

        strcpy_s(hd.maKH, khMua->maKH);
        strcpy_s(hd.maNV, nvBan->maNV);
        hd.ngayLap = RandDate();
        hd.trangThai = 1;
        hd.tongTien = 0;

        hd.dsChiTiet.soLuong = 0;

        // Mua 1-3 món
        int slMon = Rand(1, 3);
        for (int j = 0; j < slMon; j++) {
            if (countLT == 0) break;
            Laptop* ltMua = arrLaptop[Rand(0, countLT - 1)];

            if (ltMua->soLuongTon <= 0) continue;

            ChiTietHoaDon ct;
            strcpy_s(ct.maLaptop, ltMua->maLaptop);

            // Sinh Serial
            sprintf_s(ct.serial, "%s-%d-%d", ltMua->maLaptop, i, j);

            ct.soLuong = 1;
            ct.donGia = (long)ltMua->giaBan;
            ct.thanhTien = ct.donGia;

            ltMua->soLuongTon--;

            // Thêm vào mảng chi tiết
            ThemChiTietVaoHoaDon(hd, ct);

            // Tạo Bảo hành
            if (dsBH.soLuong < MAX_BAOHANH) {
                BaoHanh bh;
                sprintf_s(bh.maBH, "BH%04d%d", i, j);
                strcpy_s(bh.maHD, hd.maHD);
                strcpy_s(bh.maKH, hd.maKH);
                strcpy_s(bh.maLaptop, ct.maLaptop);
                strcpy_s(bh.serial, ct.serial);

                bh.ngayMua = hd.ngayLap;
                bh.ngayHetHan = TinhHetHanFake(bh.ngayMua, ltMua->thoiGianBaoHanh);
                bh.trangThai = BH_CON_HAN;

                ThemBaoHanh(dsBH, bh);
            }
        }

        // Lưu Hóa đơn (Chỉ lưu nếu có mua hàng)
        if (hd.dsChiTiet.soLuong > 0) {
            ThemHoaDon(dsHD, dskh, hd);
        }
    }

    cout << "Xong! Da tao du lieu mau.\n";
}