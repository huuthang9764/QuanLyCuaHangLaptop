#include "xuly.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <string>

    using namespace std;

#define FIX_CSTR(arr) arr[sizeof(arr) - 1] = '\0'

    // =================== TEMPLATE HỖ TRỢ MẢNG ===================

    template <typename List, typename DataType>
    void DocFileMang(const char* filename, List & list, int maxCapacity) {
        ifstream f(filename, ios::binary);
        if (f.is_open()) {
            int n; f.read((char*)&n, sizeof(int));
            if (n > maxCapacity) n = maxCapacity;
            list.soLuong = n;
            f.read((char*)list.ds, sizeof(DataType) * n);
            f.close();
        }
        else list.soLuong = 0;
    }

    template <typename List, typename DataType>
    void GhiFileMang(const char* filename, const List & list) {
        ofstream f(filename, ios::binary);
        if (f.is_open()) {
            f.write((char*)&list.soLuong, sizeof(int));
            f.write((char*)list.ds, sizeof(DataType) * list.soLuong);
            f.close();
        }
    }

    // =================== 1. ĐỌC / GHI FILE (ARRAY - COMPATIBLE MODE) ===================

    void DongBoHoaDonLong(DanhSachKhachHang & dskh, const DanhSachHoaDon & dsHD_ToanCuc);

    void GhiDuLieu(
        const DanhSachKhachHang & dskh, const DanhSachHoaDon & dsHD_ToanCuc,
        const DanhSachLaptop & dsls, const DanhSachNhanVien & dsnv,
        const DanhSachTaiKhoan & dstk, const DanhSachThuongHieu & dsth,
        const DanhSachLoai & dsl, const DanhSachBaoHanh & dsbh)
    {
        GhiFileMang<DanhSachLaptop, Laptop>("laptops.dat", dsls);
        GhiFileMang<DanhSachNhanVien, NhanVien>("nhanvien.dat", dsnv);
        GhiFileMang<DanhSachTaiKhoan, TaiKhoan>("taikhoan.dat", dstk);
        GhiFileMang<DanhSachThuongHieu, ThuongHieu>("thuonghieu.dat", dsth);
        GhiFileMang<DanhSachLoai, LoaiSanPham>("loai.dat", dsl);
        GhiFileMang<DanhSachBaoHanh, BaoHanh>("baohanh.dat", dsbh);

        ofstream f;

        // --- GHI KHACH HANG (Field-by-Field) ---
        f.open("khachhang.dat", ios::binary);
        if (f.is_open()) {
            f.write((char*)&dskh.soLuong, sizeof(int));
            for (int i = 0; i < dskh.soLuong; i++) {
                const KhachHang& kh = dskh.ds[i];
                f.write(kh.maKH, sizeof(kh.maKH));
                f.write(kh.tenKH, sizeof(kh.tenKH));
                f.write(kh.soDT, sizeof(kh.soDT));
                f.write(kh.email, sizeof(kh.email));
                f.write(kh.diaChi, sizeof(kh.diaChi));
            }
            f.close();
        }

        // --- GHI HOA DON (Field-by-Field) ---
        f.open("hoadon.dat", ios::binary);
        if (f.is_open()) {
            f.write((char*)&dsHD_ToanCuc.soLuong, sizeof(int));
            for (int i = 0; i < dsHD_ToanCuc.soLuong; i++) {
                const HoaDon& hd = dsHD_ToanCuc.ds[i];
                f.write(hd.maHD, sizeof(hd.maHD));
                f.write(hd.maKH, sizeof(hd.maKH));
                f.write(hd.maNV, sizeof(hd.maNV));
                f.write((char*)&hd.ngayLap, sizeof(Date));
                f.write((char*)&hd.tongTien, sizeof(long long));
                f.write((char*)&hd.trangThai, sizeof(int));
            }
            f.close();
        }
        cout << ">> Ghi file thanh cong (Array Mode).\n";
    }

    void DocDuLieu(
        DanhSachKhachHang & dskh, DanhSachHoaDon & dsHD_ToanCuc,
        DanhSachLaptop & dsls, DanhSachNhanVien & dsnv,
        DanhSachTaiKhoan & dstk, DanhSachThuongHieu & dsth,
        DanhSachLoai & dsl, DanhSachBaoHanh & dsbh)
    {
        // Đọc Laptop có fix lỗi chuỗi
        ifstream f("laptops.dat", ios::binary);
        if (f.is_open()) {
            int n; f.read((char*)&n, sizeof(int));
            if (n > MAX_LAPTOP) n = MAX_LAPTOP;
            dsls.soLuong = n;
            for (int i = 0; i < n; i++) {
                f.read((char*)&dsls.ds[i], sizeof(Laptop));
                FIX_CSTR(dsls.ds[i].maLaptop);
                FIX_CSTR(dsls.ds[i].tenLaptop);
            }
            f.close();
        }
        else dsls.soLuong = 0;

        DocFileMang<DanhSachNhanVien, NhanVien>("nhanvien.dat", dsnv, MAX_NHANVIEN);
        DocFileMang<DanhSachTaiKhoan, TaiKhoan>("taikhoan.dat", dstk, MAX_TAIKHOAN);
        DocFileMang<DanhSachThuongHieu, ThuongHieu>("thuonghieu.dat", dsth, MAX_THUONGHIEU);
        DocFileMang<DanhSachLoai, LoaiSanPham>("loai.dat", dsl, MAX_LOAI);
        DocFileMang<DanhSachBaoHanh, BaoHanh>("baohanh.dat", dsbh, MAX_BAOHANH);

        // --- ĐỌC KHACH HANG (Lẻ) ---
        f.open("khachhang.dat", ios::binary);
        if (f.is_open()) {
            int n; f.read((char*)&n, sizeof(int));
            if (n > MAX_KHACHHANG) n = MAX_KHACHHANG;
            dskh.soLuong = n;
            for (int i = 0; i < n; i++) {
                f.read(dskh.ds[i].maKH, sizeof(dskh.ds[i].maKH));   FIX_CSTR(dskh.ds[i].maKH);
                f.read(dskh.ds[i].tenKH, sizeof(dskh.ds[i].tenKH)); FIX_CSTR(dskh.ds[i].tenKH);
                f.read(dskh.ds[i].soDT, sizeof(dskh.ds[i].soDT));   FIX_CSTR(dskh.ds[i].soDT);
                f.read(dskh.ds[i].email, sizeof(dskh.ds[i].email)); FIX_CSTR(dskh.ds[i].email);
                f.read(dskh.ds[i].diaChi, sizeof(dskh.ds[i].diaChi)); FIX_CSTR(dskh.ds[i].diaChi);
                dskh.ds[i].dsHoaDon.soLuong = 0;
            }
            f.close();
        }
        else dskh.soLuong = 0;

        // --- ĐỌC HOA DON (Lẻ) ---
        f.open("hoadon.dat", ios::binary);
        if (f.is_open()) {
            int n; f.read((char*)&n, sizeof(int));
            if (n > MAX_HOADON) n = MAX_HOADON;
            dsHD_ToanCuc.soLuong = n;
            for (int i = 0; i < n; i++) {
                f.read(dsHD_ToanCuc.ds[i].maHD, sizeof(dsHD_ToanCuc.ds[i].maHD)); FIX_CSTR(dsHD_ToanCuc.ds[i].maHD);
                f.read(dsHD_ToanCuc.ds[i].maKH, sizeof(dsHD_ToanCuc.ds[i].maKH)); FIX_CSTR(dsHD_ToanCuc.ds[i].maKH);
                f.read(dsHD_ToanCuc.ds[i].maNV, sizeof(dsHD_ToanCuc.ds[i].maNV)); FIX_CSTR(dsHD_ToanCuc.ds[i].maNV);
                f.read((char*)&dsHD_ToanCuc.ds[i].ngayLap, sizeof(Date));
                f.read((char*)&dsHD_ToanCuc.ds[i].tongTien, sizeof(long long));
                f.read((char*)&dsHD_ToanCuc.ds[i].trangThai, sizeof(int));
                dsHD_ToanCuc.ds[i].dsChiTiet.soLuong = 0;
            }
            f.close();
        }
        else dsHD_ToanCuc.soLuong = 0;

        DongBoHoaDonLong(dskh, dsHD_ToanCuc);
    }

    KhachHang* TimKiemKhachHang(const DanhSachKhachHang & dskh, const char maKH[10]);

    void DongBoHoaDonLong(DanhSachKhachHang & dskh, const DanhSachHoaDon & dsHD_ToanCuc) {
        for (int i = 0; i < dskh.soLuong; i++) dskh.ds[i].dsHoaDon.soLuong = 0;
        for (int i = 0; i < dsHD_ToanCuc.soLuong; i++) {
            KhachHang* kh = TimKiemKhachHang(dskh, dsHD_ToanCuc.ds[i].maKH);
            if (kh && kh->dsHoaDon.soLuong < MAX_HOADON) {
                kh->dsHoaDon.ds[kh->dsHoaDon.soLuong++] = dsHD_ToanCuc.ds[i];
            }
        }
    }


// =================== 2. QUẢN LÝ LAPTOP ===================

Laptop* TimKiemLaptop(const DanhSachLaptop& dsls, const char maLaptop[10]) {
    for (int i = 0; i < dsls.soLuong; i++) {
        if (_stricmp(dsls.ds[i].maLaptop, maLaptop) == 0) return (Laptop*)&dsls.ds[i];
    }
    return NULL;
}

Laptop* TimKiemNhiPhan_TheoTen(const DanhSachLaptop& dsls, const char tenCanTim[50]) {
    int left = 0;
    int right = dsls.soLuong - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        int res = strcmp(dsls.ds[mid].tenLaptop, tenCanTim);

        if (res == 0) {
            return (Laptop*)&dsls.ds[mid];
        }
        
        if (res < 0) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return NULL; 
}

bool ThemLaptop(DanhSachLaptop& dsls, Laptop ltMoi) {
    if (dsls.soLuong >= MAX_LAPTOP) return false; // Tràn mảng
    if (TimKiemLaptop(dsls, ltMoi.maLaptop) != NULL) return false; // Trùng mã

    dsls.ds[dsls.soLuong] = ltMoi;
    dsls.soLuong++;
    return true;
}

bool XoaLaptop(DanhSachLaptop& dsls, const char maLaptop[10]) {
    int viTri = -1;
    for (int i = 0; i < dsls.soLuong; i++) {
        if (_stricmp(dsls.ds[i].maLaptop, maLaptop) == 0) {
            viTri = i;
            break;
        }
    }

    if (viTri == -1) return false;

    // Dời mảng sang trái
    for (int i = viTri; i < dsls.soLuong - 1; i++) {
        dsls.ds[i] = dsls.ds[i + 1];
    }
    dsls.soLuong--;
    return true;
}

bool SuaLaptop(DanhSachLaptop& dsls, Laptop ltMoi) {
    Laptop* lt = TimKiemLaptop(dsls, ltMoi.maLaptop);
    if (lt == NULL) return false;
    *lt = ltMoi;
    return true;
}

void CapNhatSoLuongLaptop(DanhSachLaptop& dsls, const char maLaptop[10], int soLuongBan) {
    Laptop* lt = TimKiemLaptop(dsls, maLaptop);
    if (lt) {
        lt->soLuongTon -= soLuongBan;
        lt->trangThai = (lt->soLuongTon > 0) ? CON_HANG : HET_HANG;
    }
}

// =================== 3. QUẢN LÝ KHÁCH HÀNG ===================

KhachHang* TimKiemKhachHang(const DanhSachKhachHang& dskh, const char maKH[10]) {
    for (int i = 0; i < dskh.soLuong; i++) {
        if (_stricmp(dskh.ds[i].maKH, maKH) == 0) return (KhachHang*)&dskh.ds[i];
    }
    return NULL;
}

bool ThemKhachHang(DanhSachKhachHang& dskh, KhachHang khMoi) {
    if (dskh.soLuong >= MAX_KHACHHANG) return false;
    if (TimKiemKhachHang(dskh, khMoi.maKH)) return false;

    khMoi.dsHoaDon.soLuong = 0; // Khởi tạo danh sách hóa đơn rỗng
    dskh.ds[dskh.soLuong] = khMoi;
    dskh.soLuong++;
    return true;
}

bool XoaKhachHang(DanhSachKhachHang& dskh, const char maKH[10]) {
    int viTri = -1;
    for (int i = 0; i < dskh.soLuong; i++) {
        if (_stricmp(dskh.ds[i].maKH, maKH) == 0) {
            viTri = i; break;
        }
    }
    if (viTri == -1) return false;

    for (int i = viTri; i < dskh.soLuong - 1; i++) {
        dskh.ds[i] = dskh.ds[i + 1];
    }
    dskh.soLuong--;
    return true;
}

bool SuaKhachHang(DanhSachKhachHang& dskh, KhachHang khMoi) {
    KhachHang* kh = TimKiemKhachHang(dskh, khMoi.maKH);
    if (!kh) return false;
    // Giữ lại danh sách hóa đơn cũ
    DanhSachHoaDon hdCu = kh->dsHoaDon;
    *kh = khMoi;
    kh->dsHoaDon = hdCu;
    return true;
}

// =================== 4. QUẢN LÝ HÓA ĐƠN ===================

HoaDon* TimKiemHoaDon(const DanhSachHoaDon& dsHD, const char maHD[10]) {
    for (int i = 0; i < dsHD.soLuong; i++) {
        if (_stricmp(dsHD.ds[i].maHD, maHD) == 0) return (HoaDon*)&dsHD.ds[i];
    }
    return NULL;
}

bool ThemHoaDon(DanhSachHoaDon& dsHD_ToanCuc, DanhSachKhachHang& dskh, HoaDon hdMoi) {
    if (dsHD_ToanCuc.soLuong >= MAX_HOADON) return false;
    if (TimKiemHoaDon(dsHD_ToanCuc, hdMoi.maHD)) return false;

    // 1. Thêm vào danh sách toàn cục
    dsHD_ToanCuc.ds[dsHD_ToanCuc.soLuong++] = hdMoi;

    // 2. Thêm vào danh sách con của Khách Hàng
    KhachHang* kh = TimKiemKhachHang(dskh, hdMoi.maKH);
    if (kh) {
        if (kh->dsHoaDon.soLuong < MAX_HOADON) {
            kh->dsHoaDon.ds[kh->dsHoaDon.soLuong++] = hdMoi;
        }
    }
    return true;
}

bool ThemChiTietVaoHoaDon(HoaDon& hd, ChiTietHoaDon ctMoi) {
    if (hd.dsChiTiet.soLuong >= MAX_CHITIET) return false;
    hd.dsChiTiet.ds[hd.dsChiTiet.soLuong++] = ctMoi;
    hd.tongTien += ctMoi.thanhTien;
    return true;
}

// =================== 5. NHÂN VIÊN & TÀI KHOẢN ===================

// --- Nhân viên ---
NhanVien* TimKiemNhanVien(const DanhSachNhanVien& dsnv, const char maNV[10]) {
    for (int i = 0; i < dsnv.soLuong; i++)
        if (_stricmp(dsnv.ds[i].maNV, maNV) == 0) return (NhanVien*)&dsnv.ds[i];
    return NULL;
}

bool ThemNhanVien(DanhSachNhanVien& dsnv, NhanVien nv) {
    if (dsnv.soLuong >= MAX_NHANVIEN || TimKiemNhanVien(dsnv, nv.maNV)) return false;
    dsnv.ds[dsnv.soLuong++] = nv;
    return true;
}

bool XoaNhanVien(DanhSachNhanVien& dsnv, DanhSachTaiKhoan& dstk, const char maNV[10]) {
    // Xóa tài khoản trước
    for (int i = 0; i < dstk.soLuong; i++) {
        if (_stricmp(dstk.ds[i].maNV, maNV) == 0) {
            XoaTaiKhoan(dstk, dstk.ds[i].tenDangNhap);
            i--; // Lùi chỉ số vì mảng đã dồn
        }
    }

    int viTri = -1;
    for (int i = 0; i < dsnv.soLuong; i++) if (_stricmp(dsnv.ds[i].maNV, maNV) == 0) viTri = i;
    if (viTri == -1) return false;

    for (int i = viTri; i < dsnv.soLuong - 1; i++) dsnv.ds[i] = dsnv.ds[i + 1];
    dsnv.soLuong--;
    return true;
}

bool SuaNhanVien(DanhSachNhanVien& dsnv, NhanVien nvMoi) {
    NhanVien* nv = TimKiemNhanVien(dsnv, nvMoi.maNV);
    if (nv) { *nv = nvMoi; return true; }
    return false;
}

// --- Tài khoản ---
TaiKhoan* TimKiemTaiKhoan(const DanhSachTaiKhoan& dstk, const char user[30]) {
    for (int i = 0; i < dstk.soLuong; i++)
        if (strcmp(dstk.ds[i].tenDangNhap, user) == 0) return (TaiKhoan*)&dstk.ds[i];
    return NULL;
}

bool ThemTaiKhoan(DanhSachTaiKhoan& dstk, TaiKhoan tk) {
    if (dstk.soLuong >= MAX_TAIKHOAN || TimKiemTaiKhoan(dstk, tk.tenDangNhap)) return false;
    dstk.ds[dstk.soLuong++] = tk;
    return true;
}

bool XoaTaiKhoan(DanhSachTaiKhoan& dstk, const char user[30]) {
    int viTri = -1;
    for (int i = 0; i < dstk.soLuong; i++) if (strcmp(dstk.ds[i].tenDangNhap, user) == 0) viTri = i;
    if (viTri == -1) return false;

    for (int i = viTri; i < dstk.soLuong - 1; i++) dstk.ds[i] = dstk.ds[i + 1];
    dstk.soLuong--;
    return true;
}

bool SuaTaiKhoan(DanhSachTaiKhoan& dstk, TaiKhoan tkMoi) {
    TaiKhoan* tk = TimKiemTaiKhoan(dstk, tkMoi.tenDangNhap);
    if (tk) { tk->quyen = tkMoi.quyen; tk->trangThai = tkMoi.trangThai; return true; }
    return false;
}

TaiKhoan* DangNhap(const DanhSachTaiKhoan& dstk, const char user[30], const char pass[30]) {
    TaiKhoan* tk = TimKiemTaiKhoan(dstk, user);
    if (tk && strcmp(tk->matKhau, pass) == 0) {
        if (tk->trangThai == TK_HOAT_DONG) return tk;
    }
    return NULL;
}

bool DoiMatKhau(DanhSachTaiKhoan& dstk, const char user[30], const char passMoi[30]) {
    TaiKhoan* tk = TimKiemTaiKhoan(dstk, user);
    if (tk) { strcpy(tk->matKhau, passMoi); return true; }
    return false;
}

// =================== 6. QUẢN LÝ DANH MỤC ===================

// --- Thương hiệu ---
ThuongHieu* TimKiemThuongHieu(const DanhSachThuongHieu& dsth, const char maTH[10]) {
    for (int i = 0; i < dsth.soLuong; i++) if (_stricmp(dsth.ds[i].maThuongHieu, maTH) == 0) return (ThuongHieu*)&dsth.ds[i];
    return NULL;
}
bool ThemThuongHieu(DanhSachThuongHieu& dsth, ThuongHieu th) {
    if (dsth.soLuong >= MAX_THUONGHIEU || TimKiemThuongHieu(dsth, th.maThuongHieu)) return false;
    dsth.ds[dsth.soLuong++] = th;
    return true;
}
bool XoaThuongHieu(DanhSachThuongHieu& dsth, const char maTH[10]) {
    int pos = -1; for (int i = 0; i < dsth.soLuong; i++) if (_stricmp(dsth.ds[i].maThuongHieu, maTH) == 0) pos = i;
    if (pos == -1) return false;
    for (int i = pos; i < dsth.soLuong - 1; i++) dsth.ds[i] = dsth.ds[i + 1];
    dsth.soLuong--; return true;
}
bool SuaThuongHieu(DanhSachThuongHieu& dsth, ThuongHieu th) {
    ThuongHieu* ptr = TimKiemThuongHieu(dsth, th.maThuongHieu);
    if (ptr) { *ptr = th; return true; } return false;
}

// --- Loại ---
LoaiSanPham* TimKiemLoai(const DanhSachLoai& dsl, const char maLoai[10]) {
    for (int i = 0; i < dsl.soLuong; i++) if (_stricmp(dsl.ds[i].maLoai, maLoai) == 0) return (LoaiSanPham*)&dsl.ds[i];
    return NULL;
}
bool ThemLoai(DanhSachLoai& dsl, LoaiSanPham l) {
    if (dsl.soLuong >= MAX_LOAI || TimKiemLoai(dsl, l.maLoai)) return false;
    dsl.ds[dsl.soLuong++] = l; return true;
}
bool XoaLoai(DanhSachLoai& dsl, const char maLoai[10]) {
    int pos = -1; for (int i = 0; i < dsl.soLuong; i++) if (_stricmp(dsl.ds[i].maLoai, maLoai) == 0) pos = i;
    if (pos == -1) return false;
    for (int i = pos; i < dsl.soLuong - 1; i++) dsl.ds[i] = dsl.ds[i + 1];
    dsl.soLuong--; return true;
}
bool SuaLoai(DanhSachLoai& dsl, LoaiSanPham l) {
    LoaiSanPham* ptr = TimKiemLoai(dsl, l.maLoai);
    if (ptr) { *ptr = l; return true; } return false;
}

// =================== 7. BẢO HÀNH ===================
bool ThemBaoHanh(DanhSachBaoHanh& dsbh, BaoHanh bh) {
    if (dsbh.soLuong >= MAX_BAOHANH) return false;
    dsbh.ds[dsbh.soLuong++] = bh;
    return true;
}

// =================== 8. SẮP XẾP (SELECTION SORT - ARRAY) ===================

template <typename T>
void Swap(T& a, T& b) { T temp = a; a = b; b = temp; }

// --- Laptop ---
void SapXepLaptop_TheoTen(DanhSachLaptop& dsls) {
    for (int i = 0; i < dsls.soLuong - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < dsls.soLuong; j++) {
            // Tìm phần tử nhỏ nhất
            if (strcmp(dsls.ds[j].tenLaptop, dsls.ds[minIdx].tenLaptop) < 0)
                minIdx = j;
        }
        // Chỉ swap 1 lần nếu tìm thấy phần tử nhỏ hơn
        if (minIdx != i) Swap(dsls.ds[i], dsls.ds[minIdx]);
    }
}

void SapXepLaptop_TheoGia(DanhSachLaptop& dsls) {
    for (int i = 0; i < dsls.soLuong - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < dsls.soLuong; j++) {
            if (dsls.ds[j].giaBan < dsls.ds[minIdx].giaBan)
                minIdx = j;
        }
        if (minIdx != i) Swap(dsls.ds[i], dsls.ds[minIdx]);
    }
}

// --- Khách Hàng ---
void SapXepKhachHang_TheoTen(DanhSachKhachHang& dskh) {
    for (int i = 0; i < dskh.soLuong - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < dskh.soLuong; j++) {
            if (strcmp(dskh.ds[j].tenKH, dskh.ds[minIdx].tenKH) < 0)
                minIdx = j;
        }
        if (minIdx != i) Swap(dskh.ds[i], dskh.ds[minIdx]);
    }
}

// --- Hóa Đơn ---
int SoSanhNgay(Date a, Date b) {
    if (a.nam != b.nam) return a.nam - b.nam;
    if (a.thang != b.thang) return a.thang - b.thang;
    return a.ngay - b.ngay;
}

void SapXepHoaDon_TheoNgay(DanhSachHoaDon& dsHD) {
    for (int i = 0; i < dsHD.soLuong - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < dsHD.soLuong; j++) {
            if (SoSanhNgay(dsHD.ds[j].ngayLap, dsHD.ds[minIdx].ngayLap) < 0)
                minIdx = j;
        }
        if (minIdx != i) Swap(dsHD.ds[i], dsHD.ds[minIdx]);
    }
}

void SapXepHoaDon_TheoTongTien(DanhSachHoaDon& dsHD) {
    for (int i = 0; i < dsHD.soLuong - 1; i++) {
        int maxIdx = i; // Sắp xếp giảm dần (Tiền nhiều lên đầu)
        for (int j = i + 1; j < dsHD.soLuong; j++) {
            if (dsHD.ds[j].tongTien > dsHD.ds[maxIdx].tongTien)
                maxIdx = j;
        }
        if (maxIdx != i) Swap(dsHD.ds[i], dsHD.ds[maxIdx]);
    }
}
string DinhDangTien(long long tien) {
    string s = to_string(tien);
    int n = s.length() - 3;
    while (n > 0) {
        s.insert(n, ",");
        n -= 3;
    }
    return s + " VND";
}