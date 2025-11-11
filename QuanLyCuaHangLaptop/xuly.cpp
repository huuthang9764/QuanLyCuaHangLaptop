#include "xuly.h"
#include <iostream>
#include <fstream>  
#include <cstring>

using namespace std;


void DocDuLieu(
    DanhSachKhachHang& dskh,
    DanhSachHoaDon& dsHD_ToanCuc,
    DanhSachLaptop& dsls,
    DanhSachNhanVien& dsnv,
    DanhSachTaiKhoan& dstk,
    DanhSachThuongHieu& dsth,
    DanhSachLoai& dsl,
    DanhSachBaoHanh& dsbh){
    dskh.soLuong = 0;
    dsHD_ToanCuc.soLuong = 0;
    dsls.soLuong = 0;
    dsnv.soLuong = 0;
    dstk.soLuong = 0;
    dsth.soLuong = 0;
    dsl.soLuong = 0;
    dsbh.soLuong = 0;

    ifstream fileIn;
    
    // === 1. Đọc file Laptop (laptops.dat) ===
    fileIn.open("laptops.dat", ios::binary);
    if (fileIn.is_open()) {
        fileIn.read(reinterpret_cast<char*>(&dsls.soLuong), sizeof(int));
        fileIn.read(reinterpret_cast<char*>(dsls.ds), sizeof(Laptop) * dsls.soLuong);
        fileIn.close();
    }
    else {
        cout << "Thong bao: Khong tim thay file 'laptops.dat'." << endl;
    }

    // === 2. Đọc file Khách Hàng (khachhang.dat) ===
    fileIn.open("khachhang.dat", ios::binary);
    if (fileIn.is_open()) {
        fileIn.read(reinterpret_cast<char*>(&dskh.soLuong), sizeof(int));
        for (int i = 0; i < dskh.soLuong; i++) {
            fileIn.read(reinterpret_cast<char*>(&dskh.ds[i]), sizeof(KhachHang));
            dskh.ds[i].dsHoaDon.soLuong = 0; // Quan trọng
        }
        fileIn.close();
    }
    else {
        cout << "Thong bao: Khong tim thay file 'khachhang.dat'." << endl;
    }

    // === 3. Đọc file Hóa Đơn TOÀN CỤC (hoadon.dat) ===
    fileIn.open("hoadon.dat", ios::binary);
    if (fileIn.is_open()) {
        fileIn.read(reinterpret_cast<char*>(&dsHD_ToanCuc.soLuong), sizeof(int));
        fileIn.read(reinterpret_cast<char*>(dsHD_ToanCuc.ds), sizeof(HoaDon) * dsHD_ToanCuc.soLuong);
        fileIn.close();
    }
    else {
        cout << "Thong bao: Khong tim thay file 'hoadon.dat'." << endl;
    }

    // === 4. Đọc file Nhân Viên (nhanvien.dat) ===
    fileIn.open("nhanvien.dat", ios::binary);
    if (fileIn.is_open()) {
        fileIn.read(reinterpret_cast<char*>(&dsnv.soLuong), sizeof(int));
        fileIn.read(reinterpret_cast<char*>(dsnv.ds), sizeof(NhanVien) * dsnv.soLuong);
        fileIn.close();
    }
    else {
        cout << "Thong bao: Khong tim thay file 'nhanvien.dat'." << endl;
    }

    // === 5. Đọc file Tài Khoản (taikhoan.dat) ===
    fileIn.open("taikhoan.dat", ios::binary);
    if (fileIn.is_open()) {
        fileIn.read(reinterpret_cast<char*>(&dstk.soLuong), sizeof(int));
        fileIn.read(reinterpret_cast<char*>(dstk.ds), sizeof(TaiKhoan) * dstk.soLuong);
        fileIn.close();
    }
    else {
        cout << "Thong bao: Khong tim thay file 'taikhoan.dat'." << endl;
    }

    // === 6. Đọc file Thương Hiệu (thuonghieu.dat) ===
    fileIn.open("thuonghieu.dat", ios::binary);
    if (fileIn.is_open()) {
        fileIn.read(reinterpret_cast<char*>(&dsth.soLuong), sizeof(int));
        fileIn.read(reinterpret_cast<char*>(dsth.ds), sizeof(ThuongHieu) * dsth.soLuong);
        fileIn.close();
    }
    else {
        cout << "Thong bao: Khong tim thay file 'thuonghieu.dat'." << endl;
    }

    // === 7. Đọc file Loại SP (loai.dat) ===
    fileIn.open("loai.dat", ios::binary);
    if (fileIn.is_open()) {
        fileIn.read(reinterpret_cast<char*>(&dsl.soLuong), sizeof(int));
        fileIn.read(reinterpret_cast<char*>(dsl.ds), sizeof(LoaiSanPham) * dsl.soLuong);
        fileIn.close();
    }
    else {
        cout << "Thong bao: Khong tim thay file 'loai.dat'." << endl;
    }

    // === 8. Đọc file Bảo Hành (baohanh.dat) ===
    fileIn.open("baohanh.dat", ios::binary);
    if (fileIn.is_open()) {
        fileIn.read(reinterpret_cast<char*>(&dsbh.soLuong), sizeof(int));
        fileIn.read(reinterpret_cast<char*>(dsbh.ds), sizeof(BaoHanh) * dsbh.soLuong);
        fileIn.close();
    }
    else {
        cout << "Thong bao: Khong tim thay file 'baohanh.dat'." << endl;
    }

    // === BƯỚC QUAN TRỌNG NHẤT ===
    DongBoHoaDonLong(dskh, dsHD_ToanCuc);
    cout << "Da doc du lieu xong." << endl;
}

void GhiDuLieu(
    const DanhSachKhachHang& dskh,
    const DanhSachHoaDon& dsHD_ToanCuc,
    const DanhSachLaptop& dsls,
    const DanhSachNhanVien& dsnv,
    const DanhSachTaiKhoan& dstk,
    const DanhSachThuongHieu& dsth,
    const DanhSachLoai& dsl,
    const DanhSachBaoHanh& dsbh){
    ofstream fileOut; 

    // === 1. Ghi file Laptop (laptops.dat) ===
    fileOut.open("laptops.dat", ios::binary);
    if (fileOut.is_open()) {
        fileOut.write(reinterpret_cast<const char*>(&dsls.soLuong), sizeof(int));
        fileOut.write(reinterpret_cast<const char*>(dsls.ds), sizeof(Laptop) * dsls.soLuong);
        fileOut.close();
    }
    else {
        cout << "Loi: Khong mo duoc file 'laptops.dat' de ghi." << endl;
    }

    // === 2. Ghi file Khách Hàng (khachhang.dat) ===
    fileOut.open("khachhang.dat", ios::binary);
    if (fileOut.is_open()) {
        fileOut.write(reinterpret_cast<const char*>(&dskh.soLuong), sizeof(int));
        for (int i = 0; i < dskh.soLuong; i++) {
            fileOut.write(reinterpret_cast<const char*>(&dskh.ds[i]), sizeof(KhachHang));
        }
        fileOut.close();
    }
    else {
        cout << "Loi: Khong mo duoc file 'khachhang.dat' de ghi." << endl;
    }

    // === 3. Ghi file Hóa Đơn TOÀN CỤC (hoadon.dat) ===
    fileOut.open("hoadon.dat", ios::binary);
    if (fileOut.is_open()) {
        fileOut.write(reinterpret_cast<const char*>(&dsHD_ToanCuc.soLuong), sizeof(int));
        fileOut.write(reinterpret_cast<const char*>(dsHD_ToanCuc.ds), sizeof(HoaDon) * dsHD_ToanCuc.soLuong);
        fileOut.close();
    }
    else {
        cout << "Loi: Khong mo duoc file 'hoadon.dat' de ghi." << endl;
    }

    // === 4. Ghi file Nhân Viên (nhanvien.dat) ===
    fileOut.open("nhanvien.dat", ios::binary);
    if (fileOut.is_open()) {
        fileOut.write(reinterpret_cast<const char*>(&dsnv.soLuong), sizeof(int));
        fileOut.write(reinterpret_cast<const char*>(dsnv.ds), sizeof(NhanVien) * dsnv.soLuong);
        fileOut.close();
    }
    else {
        cout << "Loi: Khong mo duoc file 'nhanvien.dat' de ghi." << endl;
    }

    // === 5. Ghi file Tài Khoản (taikhoan.dat) ===
    fileOut.open("taikhoan.dat", ios::binary);
    if (fileOut.is_open()) {
        fileOut.write(reinterpret_cast<const char*>(&dstk.soLuong), sizeof(int));
        fileOut.write(reinterpret_cast<const char*>(dstk.ds), sizeof(TaiKhoan) * dstk.soLuong);
        fileOut.close();
    }
    else {
        cout << "Loi: Khong mo duoc file 'taikhoan.dat' de ghi." << endl;
    }

    // === 6. Ghi file Thương Hiệu (thuonghieu.dat) ===
    fileOut.open("thuonghieu.dat", ios::binary);
    if (fileOut.is_open()) {
        fileOut.write(reinterpret_cast<const char*>(&dsth.soLuong), sizeof(int));
        fileOut.write(reinterpret_cast<const char*>(dsth.ds), sizeof(ThuongHieu) * dsth.soLuong);
        fileOut.close();
    }
    else {
        cout << "Loi: Khong mo duoc file 'thuonghieu.dat' de ghi." << endl;
    }

    // === 7. Ghi file Loại SP (loai.dat) ===
    fileOut.open("loai.dat", ios::binary);
    if (fileOut.is_open()) {
        fileOut.write(reinterpret_cast<const char*>(&dsl.soLuong), sizeof(int));
        fileOut.write(reinterpret_cast<const char*>(dsl.ds), sizeof(LoaiSanPham) * dsl.soLuong);
        fileOut.close();
    }
    else {
        cout << "Loi: Khong mo duoc file 'loai.dat' de ghi." << endl;
    }

    // === 8. Ghi file Bảo Hành (baohanh.dat) ===
    fileOut.open("baohanh.dat", ios::binary);
    if (fileOut.is_open()) {
        fileOut.write(reinterpret_cast<const char*>(&dsbh.soLuong), sizeof(int));
        fileOut.write(reinterpret_cast<const char*>(dsbh.ds), sizeof(BaoHanh) * dsbh.soLuong);
        fileOut.close();
    }
    else {
        cout << "Loi: Khong mo duoc file 'baohanh.dat' de ghi." << endl;
    }
    cout << "Da ghi du lieu ra file thanh cong." << endl;
}
    

void DongBoHoaDonLong(DanhSachKhachHang& dskh, const DanhSachHoaDon& dsHD_ToanCuc) {
    for (int i = 0; i < dskh.soLuong; i++) {
        dskh.ds[i].dsHoaDon.soLuong = 0;
    }
    for (int i = 0; i < dsHD_ToanCuc.soLuong; i++) {
        const HoaDon& hd = dsHD_ToanCuc.ds[i];
        KhachHang* kh = TimKiemKhachHang(dskh, hd.maKH); 
        if (kh != NULL) {
            DanhSachHoaDon& dsLong = kh->dsHoaDon;
            if (dsLong.soLuong < MAX_HOADON) {
                dsLong.ds[dsLong.soLuong] = hd;
                dsLong.soLuong++;
            }
        }
    }
}



int TimKiemViTriLaptop(DanhSachLaptop& dsls, const char maLaptop[10]) {
    for (int i = 0; i < dsls.soLuong; i++) {
        if (strcmp(dsls.ds[i].maLaptop, maLaptop) == 0) {
            return i;
        }
    }
    return -1;
}

Laptop* TimKiemLaptop(DanhSachLaptop& dsls, const char maLaptop[10]) {
    int viTri = TimKiemViTriLaptop(dsls, maLaptop);
    if (viTri == -1) return NULL;
    return &dsls.ds[viTri];
}

bool ThemLaptop(DanhSachLaptop& dsls, Laptop ltMoi) {
    if (dsls.soLuong >= MAX_LAPTOP) {
        cout << "Loi: Danh sach Laptop da day!" << endl;
        return false;
    }
    if (TimKiemViTriLaptop(dsls, ltMoi.maLaptop) != -1) {
        cout << "Loi: Ma Laptop '" << ltMoi.maLaptop << "' da ton tai!" << endl;
        return false;
    }
    dsls.ds[dsls.soLuong] = ltMoi;
    dsls.soLuong++;
    return true;
}

bool XoaLaptop(DanhSachLaptop& dsls, const char maLaptop[10]) {
    int viTriXoa = TimKiemViTriLaptop(dsls, maLaptop);
    if (viTriXoa == -1) {
        cout << "Loi: Khong tim thay Laptop voi ma '" << maLaptop << "' de xoa!" << endl;
        return false;
    }
    for (int i = viTriXoa; i < dsls.soLuong - 1; i++) {
        dsls.ds[i] = dsls.ds[i + 1];
    }
    dsls.soLuong--;
    return true;
}

bool SuaLaptop(DanhSachLaptop& dsls, Laptop ltMoi) {
    int viTriSua = TimKiemViTriLaptop(dsls, ltMoi.maLaptop);
    if (viTriSua == -1) {
        cout << "Loi: Khong tim thay Laptop voi ma '" << ltMoi.maLaptop << "' de sua!" << endl;
        return false;
    }
    dsls.ds[viTriSua] = ltMoi;
    return true;
}



int TimKiemViTriNhanVien(DanhSachNhanVien& dsnv, const char maNV[10]) {
    for (int i = 0; i < dsnv.soLuong; i++) {
        if (strcmp(dsnv.ds[i].maNV, maNV) == 0) {
            return i;
        }
    }
    return -1;
}

NhanVien* TimKiemNhanVien(DanhSachNhanVien& dsnv, const char maNV[10]) {
    int viTri = TimKiemViTriNhanVien(dsnv, maNV);
    if (viTri == -1) return NULL;
    return &dsnv.ds[viTri];
}

bool ThemNhanVien(DanhSachNhanVien& dsnv, NhanVien nvMoi) {
    if (dsnv.soLuong >= MAX_NHANVIEN) {
        cout << "Loi: Danh sach Nhan Vien da day!" << endl;
        return false;
    }
    if (TimKiemViTriNhanVien(dsnv, nvMoi.maNV) != -1) {
        cout << "Loi: Ma Nhan Vien '" << nvMoi.maNV << "' da ton tai!" << endl;
        return false;
    }
    dsnv.ds[dsnv.soLuong] = nvMoi;
    dsnv.soLuong++;
    return true;
}


int TimKiemViTriTaiKhoan(DanhSachTaiKhoan& dstk, const char tenDangNhap[30]) {
    for (int i = 0; i < dstk.soLuong; i++) {
        if (strcmp(dstk.ds[i].tenDangNhap, tenDangNhap) == 0) {
            return i;
        }
    }
    return -1;
}

TaiKhoan* TimKiemTaiKhoan(DanhSachTaiKhoan& dstk, const char tenDangNhap[30]) {
    int viTri = TimKiemViTriTaiKhoan(dstk, tenDangNhap);
    if (viTri == -1) return NULL;
    return &dstk.ds[viTri];
}

bool ThemTaiKhoan(DanhSachTaiKhoan& dstk, TaiKhoan tkMoi) {
    if (dstk.soLuong >= MAX_TAIKHOAN) {
        cout << "Loi: Danh sach Tai Khoan da day!" << endl;
        return false;
    }
    if (TimKiemViTriTaiKhoan(dstk, tkMoi.tenDangNhap) != -1) {
        cout << "Loi: Ten dang nhap '" << tkMoi.tenDangNhap << "' da ton tai!" << endl;
        return false;
    }
    dstk.ds[dstk.soLuong] = tkMoi;
    dstk.soLuong++;
    return true;
}





TaiKhoan* DangNhap(DanhSachTaiKhoan& dstk, const char user[30], const char pass[30]) {
    TaiKhoan* tk = TimKiemTaiKhoan(dstk, user);
    if (tk == NULL) return NULL;
    if (strcmp(tk->matKhau, pass) == 0) {
        if (tk->trangThai == TK_HOAT_DONG) {
            return tk;
        }
        else {
            cout << "Loi: Tai khoan nay dang bi khoa." << endl;
            return NULL;
        }
    }

    cout << "Loi: Sai ten dang nhap hoac mat khau." << endl;
    return NULL;
}


int TimKiemViTriThuongHieu(DanhSachThuongHieu& dsth, const char maTH[10]) {
    for (int i = 0; i < dsth.soLuong; i++) {
        if (strcmp(dsth.ds[i].maThuongHieu, maTH) == 0) {
            return i;
        }
    }
    return -1;
}

ThuongHieu* TimKiemThuongHieu(DanhSachThuongHieu& dsth, const char maTH[10]) {
    int viTri = TimKiemViTriThuongHieu(dsth, maTH);
    if (viTri == -1) return NULL;
    return &dsth.ds[viTri];
}

bool ThemThuongHieu(DanhSachThuongHieu& dsth, ThuongHieu thMoi) {
    if (dsth.soLuong >= MAX_THUONGHIEU) {
        cout << "Loi: Danh sach Thuong Hieu da day!" << endl;
        return false;
    }
    if (TimKiemViTriThuongHieu(dsth, thMoi.maThuongHieu) != -1) {
        cout << "Loi: Ma Thuong Hieu '" << thMoi.maThuongHieu << "' da ton tai!" << endl;
        return false;
    }
    dsth.ds[dsth.soLuong] = thMoi;
    dsth.soLuong++;
    return true;
}

bool XoaThuongHieu(DanhSachThuongHieu& dsth, const char maTH[10]) {
    int viTriXoa = TimKiemViTriThuongHieu(dsth, maTH);
    if (viTriXoa == -1) {
        cout << "Loi: Khong tim thay ma Thuong Hieu '" << maTH << "' de xoa!" << endl;
        return false;
    }
    for (int i = viTriXoa; i < dsth.soLuong - 1; i++) {
        dsth.ds[i] = dsth.ds[i + 1];
    }
    dsth.soLuong--;
    return true;
}

bool SuaThuongHieu(DanhSachThuongHieu& dsth, ThuongHieu thMoi) {
    int viTriSua = TimKiemViTriThuongHieu(dsth, thMoi.maThuongHieu);
    if (viTriSua == -1) {
        cout << "Loi: Khong tim thay ma Thuong Hieu '" << thMoi.maThuongHieu << "' de sua!" << endl;
        return false;
    }
    dsth.ds[viTriSua] = thMoi;
    return true;
}

// --- Loại Sản Phẩm ---
int TimKiemViTriLoai(DanhSachLoai& dsl, const char maLoai[10]) {
    for (int i = 0; i < dsl.soLuong; i++) {
        if (strcmp(dsl.ds[i].maLoai, maLoai) == 0) {
            return i;
        }
    }
    return -1;
}

LoaiSanPham* TimKiemLoai(DanhSachLoai& dsl, const char maLoai[10]) {
    int viTri = TimKiemViTriLoai(dsl, maLoai);
    if (viTri == -1) return NULL;
    return &dsl.ds[viTri];
}

bool ThemLoai(DanhSachLoai& dsl, LoaiSanPham loaiMoi) {
    if (dsl.soLuong >= MAX_LOAI) {
        cout << "Loi: Danh sach Loai San Pham da day!" << endl;
        return false;
    }
    if (TimKiemViTriLoai(dsl, loaiMoi.maLoai) != -1) {
        cout << "Loi: Ma Loai '" << loaiMoi.maLoai << "' da ton tai!" << endl;
        return false;
    }
    dsl.ds[dsl.soLuong] = loaiMoi;
    dsl.soLuong++;
    return true;
}

bool XoaLoai(DanhSachLoai& dsl, const char maLoai[10]) {
    int viTriXoa = TimKiemViTriLoai(dsl, maLoai);
    if (viTriXoa == -1) {
        cout << "Loi: Khong tim thay ma Loai '" << maLoai << "' de xoa!" << endl;
        return false;
    }
    for (int i = viTriXoa; i < dsl.soLuong - 1; i++) {
        dsl.ds[i] = dsl.ds[i + 1];
    }
    dsl.soLuong--;
    return true;
}

bool SuaLoai(DanhSachLoai& dsl, LoaiSanPham loaiMoi) {
    int viTriSua = TimKiemViTriLoai(dsl, loaiMoi.maLoai);
    if (viTriSua == -1) {
        cout << "Loi: Khong tim thay ma Loai '" << loaiMoi.maLoai << "' de sua!" << endl;
        return false;
    }
    dsl.ds[viTriSua] = loaiMoi;
    return true;
}

int TimKiemViTriKhachHang(DanhSachKhachHang& dskh, const char maKH[10]) {
    for (int i = 0; i < dskh.soLuong; i++) {
        if (strcmp(dskh.ds[i].maKH, maKH) == 0) {
            return i;
        }
    }
    return -1;
}

KhachHang* TimKiemKhachHang(DanhSachKhachHang& dskh, const char maKH[10]) {
    int viTri = TimKiemViTriKhachHang(dskh, maKH);
    if (viTri == -1) return NULL;
    return &dskh.ds[viTri];
}