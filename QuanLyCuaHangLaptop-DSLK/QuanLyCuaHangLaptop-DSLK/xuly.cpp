#include "xuly.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <string>

using namespace std;

// [MACRO AN TOÀN]: Tránh lỗi in ký tự lạ
#define FIX_CSTR(arr) arr[sizeof(arr) - 1] = '\0'

// =================== 0. HÀM HỖ TRỢ KHỞI TẠO ===================

template <typename T>
void KhoiTaoDS(T& ds) {
    ds.head = NULL; ds.tail = NULL; ds.soLuong = 0;
}

void KhoiTaoDanhSachLaptop(DanhSachLaptop& ds) { KhoiTaoDS(ds); }
void KhoiTaoDanhSachKhachHang(DanhSachKhachHang& ds) { KhoiTaoDS(ds); }
void KhoiTaoDanhSachHoaDon(DanhSachHoaDon& ds) { KhoiTaoDS(ds); }
void KhoiTaoDanhSachChiTiet(DanhSachChiTiet& ds) { KhoiTaoDS(ds); }

// =================== TẠO NODE (DSLK) ===================

NodeLaptop* TaoNodeLaptop(Laptop data) {
    NodeLaptop* p = new NodeLaptop; p->data = data; p->next = NULL; p->pre = NULL; return p;
}
NodeKhachHang* TaoNodeKhachHang(KhachHang data) {
    NodeKhachHang* p = new NodeKhachHang; p->data = data; p->next = NULL; p->pre = NULL;
    KhoiTaoDS(p->data.dsHoaDon); return p;
}
NodeHoaDon* TaoNodeHoaDon(HoaDon data) {
    NodeHoaDon* p = new NodeHoaDon; p->data = data; p->next = NULL; p->pre = NULL;
    KhoiTaoDS(p->data.dsChiTiet); return p;
}
NodeChiTiet* TaoNodeChiTiet(ChiTietHoaDon data) {
    NodeChiTiet* p = new NodeChiTiet; p->data = data; p->next = NULL; p->pre = NULL; return p;
}
NodeNhanVien* TaoNodeNhanVien(NhanVien data) {
    NodeNhanVien* p = new NodeNhanVien; p->data = data; p->next = NULL; p->pre = NULL; return p;
}
NodeTaiKhoan* TaoNodeTaiKhoan(TaiKhoan data) {
    NodeTaiKhoan* p = new NodeTaiKhoan; p->data = data; p->next = NULL; p->pre = NULL; return p;
}
NodeThuongHieu* TaoNodeThuongHieu(ThuongHieu data) {
    NodeThuongHieu* p = new NodeThuongHieu; p->data = data; p->next = NULL; p->pre = NULL; return p;
}
NodeLoai* TaoNodeLoai(LoaiSanPham data) {
    NodeLoai* p = new NodeLoai; p->data = data; p->next = NULL; p->pre = NULL; return p;
}
NodeBaoHanh* TaoNodeBaoHanh(BaoHanh data) {
    NodeBaoHanh* p = new NodeBaoHanh; p->data = data; p->next = NULL; p->pre = NULL; return p;
}

// =================== 1. ĐỌC / GHI FILE (LOGIC FIELD-BY-FIELD) ===================

template <typename DS, typename Node, typename Data>
void ThemVaoCuoi(DS& ds, Node* (*TaoNode)(Data), Data val) {
    Node* p = TaoNode(val);
    if (!ds.head) ds.head = ds.tail = p;
    else { ds.tail->next = p; p->pre = ds.tail; ds.tail = p; }
    ds.soLuong++;
}

void DongBoHoaDonLong(DanhSachKhachHang& dskh, const DanhSachHoaDon& dsHD_ToanCuc);

void GhiDuLieu(
    const DanhSachKhachHang& dskh, const DanhSachHoaDon& dsHD_ToanCuc,
    const DanhSachLaptop& dsls, const DanhSachNhanVien& dsnv,
    const DanhSachTaiKhoan& dstk, const DanhSachThuongHieu& dsth,
    const DanhSachLoai& dsl, const DanhSachBaoHanh& dsbh)
{
    ofstream f;

#define GHI_SIMPLE(FILENAME, LIST, TYPE, NODE) \
    f.open(FILENAME, ios::binary); \
    if (f.is_open()) { \
        f.write((char*)&LIST.soLuong, sizeof(int)); \
        for (NODE* k = LIST.head; k; k = k->next) f.write((char*)&k->data, sizeof(TYPE)); \
        f.close(); \
    }

    GHI_SIMPLE("laptops.dat", dsls, Laptop, NodeLaptop);
    GHI_SIMPLE("nhanvien.dat", dsnv, NhanVien, NodeNhanVien);
    GHI_SIMPLE("taikhoan.dat", dstk, TaiKhoan, NodeTaiKhoan);
    GHI_SIMPLE("thuonghieu.dat", dsth, ThuongHieu, NodeThuongHieu);
    GHI_SIMPLE("loai.dat", dsl, LoaiSanPham, NodeLoai);
    GHI_SIMPLE("baohanh.dat", dsbh, BaoHanh, NodeBaoHanh);

    // --- KHACH HANG (Ghi lẻ từng trường) ---
    f.open("khachhang.dat", ios::binary);
    if (f.is_open()) {
        f.write((char*)&dskh.soLuong, sizeof(int));
        for (NodeKhachHang* k = dskh.head; k; k = k->next) {
            const KhachHang& kh = k->data;
            f.write(kh.maKH, sizeof(kh.maKH));
            f.write(kh.tenKH, sizeof(kh.tenKH));
            f.write(kh.soDT, sizeof(kh.soDT));
            f.write(kh.email, sizeof(kh.email));
            f.write(kh.diaChi, sizeof(kh.diaChi));
        }
        f.close();
    }

    // --- HOA DON (Ghi lẻ từng trường) ---
    f.open("hoadon.dat", ios::binary);
    if (f.is_open()) {
        f.write((char*)&dsHD_ToanCuc.soLuong, sizeof(int));
        for (NodeHoaDon* k = dsHD_ToanCuc.head; k; k = k->next) {
            const HoaDon& hd = k->data;
            f.write(hd.maHD, sizeof(hd.maHD));
            f.write(hd.maKH, sizeof(hd.maKH));
            f.write(hd.maNV, sizeof(hd.maNV));
            f.write((char*)&hd.ngayLap, sizeof(Date));
            f.write((char*)&hd.tongTien, sizeof(long long));
            f.write((char*)&hd.trangThai, sizeof(int));
        }
        f.close();
    }
    cout << ">> Ghi file thanh cong (DSLK Mode).\n";
}

void DocDuLieu(
    DanhSachKhachHang& dskh, DanhSachHoaDon& dsHD_ToanCuc,
    DanhSachLaptop& dsls, DanhSachNhanVien& dsnv,
    DanhSachTaiKhoan& dstk, DanhSachThuongHieu& dsth,
    DanhSachLoai& dsl, DanhSachBaoHanh& dsbh)
{
    KhoiTaoDS(dskh); KhoiTaoDS(dsHD_ToanCuc); KhoiTaoDS(dsls);
    KhoiTaoDS(dsnv); KhoiTaoDS(dstk); KhoiTaoDS(dsth);
    KhoiTaoDS(dsl);  KhoiTaoDS(dsbh);

    ifstream f; int n;

#define DOC_SIMPLE(FILENAME, DS, TYPE, NODE_FUNC) \
    f.open(FILENAME, ios::binary); \
    if (f.is_open()) { \
        f.read((char*)&n, sizeof(int)); \
        for (int i = 0; i < n; i++) { \
            TYPE val; f.read((char*)&val, sizeof(TYPE)); \
            ThemVaoCuoi(DS, NODE_FUNC, val); \
        } \
        f.close(); \
    }

    // Đọc Laptop có fix chuỗi
    f.open("laptops.dat", ios::binary);
    if (f.is_open()) {
        f.read((char*)&n, sizeof(int));
        for (int i = 0; i < n; i++) {
            Laptop val; f.read((char*)&val, sizeof(Laptop));
            FIX_CSTR(val.maLaptop); FIX_CSTR(val.tenLaptop);
            ThemVaoCuoi(dsls, TaoNodeLaptop, val);
        }
        f.close();
    }

    DOC_SIMPLE("nhanvien.dat", dsnv, NhanVien, TaoNodeNhanVien);
    DOC_SIMPLE("taikhoan.dat", dstk, TaiKhoan, TaoNodeTaiKhoan);
    DOC_SIMPLE("thuonghieu.dat", dsth, ThuongHieu, TaoNodeThuongHieu);
    DOC_SIMPLE("loai.dat", dsl, LoaiSanPham, TaoNodeLoai);
    DOC_SIMPLE("baohanh.dat", dsbh, BaoHanh, TaoNodeBaoHanh);

    // --- KHACH HANG (Đọc lẻ) ---
    f.open("khachhang.dat", ios::binary);
    if (f.is_open()) {
        f.read((char*)&n, sizeof(int));
        for (int i = 0; i < n; i++) {
            KhachHang val{};
            f.read(val.maKH, sizeof(val.maKH));   FIX_CSTR(val.maKH);
            f.read(val.tenKH, sizeof(val.tenKH)); FIX_CSTR(val.tenKH);
            f.read(val.soDT, sizeof(val.soDT));   FIX_CSTR(val.soDT);
            f.read(val.email, sizeof(val.email)); FIX_CSTR(val.email);
            f.read(val.diaChi, sizeof(val.diaChi)); FIX_CSTR(val.diaChi);
            KhoiTaoDS(val.dsHoaDon);
            ThemVaoCuoi(dskh, TaoNodeKhachHang, val);
        }
        f.close();
    }

    // --- HOA DON (Đọc lẻ) ---
    f.open("hoadon.dat", ios::binary);
    if (f.is_open()) {
        f.read((char*)&n, sizeof(int));
        for (int i = 0; i < n; i++) {
            HoaDon val{};
            f.read(val.maHD, sizeof(val.maHD)); FIX_CSTR(val.maHD);
            f.read(val.maKH, sizeof(val.maKH)); FIX_CSTR(val.maKH);
            f.read(val.maNV, sizeof(val.maNV)); FIX_CSTR(val.maNV);
            f.read((char*)&val.ngayLap, sizeof(Date));
            f.read((char*)&val.tongTien, sizeof(long long));
            f.read((char*)&val.trangThai, sizeof(int));
            KhoiTaoDS(val.dsChiTiet);
            ThemVaoCuoi(dsHD_ToanCuc, TaoNodeHoaDon, val);
        }
        f.close();
    }

    DongBoHoaDonLong(dskh, dsHD_ToanCuc);
}

void DongBoHoaDonLong(DanhSachKhachHang& dskh, const DanhSachHoaDon& dsHD_ToanCuc) {
    for (NodeKhachHang* k = dskh.head; k; k = k->next) KhoiTaoDS(k->data.dsHoaDon);
    for (NodeHoaDon* h = dsHD_ToanCuc.head; h; h = h->next) {
        KhachHang* kh = TimKiemKhachHang(dskh, h->data.maKH);
        if (kh) {
            NodeHoaDon* p = TaoNodeHoaDon(h->data);
            DanhSachHoaDon& sub = kh->dsHoaDon;
            if (!sub.head) sub.head = sub.tail = p;
            else { sub.tail->next = p; p->pre = sub.tail; sub.tail = p; }
            sub.soLuong++;
        }
    }
}

// =================== 2. QUẢN LÝ HÓA ĐƠN ===================

HoaDon* TimKiemHoaDon(const DanhSachHoaDon& dsHD, const char maHD[10]) {
    NodeHoaDon* k = dsHD.head;
    while (k != NULL) {
        if (strcmp(k->data.maHD, maHD) == 0) return &k->data;
        k = k->next;
    };
    return NULL;
}

bool ThemHoaDon(DanhSachHoaDon& dsHD, DanhSachKhachHang& dskh, HoaDon hdMoi) {
    if (TimKiemHoaDon(dsHD, hdMoi.maHD) != NULL) {
        cout << "Loi: Trung ma hoa don!\n"; return false;
    }

    NodeHoaDon* pGlobal = TaoNodeHoaDon(hdMoi);
    if (dsHD.head == NULL) dsHD.head = dsHD.tail = pGlobal;
    else { dsHD.tail->next = pGlobal; pGlobal->pre = dsHD.tail; dsHD.tail = pGlobal; }
    dsHD.soLuong++;

    KhachHang* kh = TimKiemKhachHang(dskh, hdMoi.maKH);
    if (kh != NULL) {
        NodeHoaDon* pSub = TaoNodeHoaDon(hdMoi);
        if (kh->dsHoaDon.head == NULL) kh->dsHoaDon.head = kh->dsHoaDon.tail = pSub;
        else { kh->dsHoaDon.tail->next = pSub; pSub->pre = kh->dsHoaDon.tail; kh->dsHoaDon.tail = pSub; }
        kh->dsHoaDon.soLuong++;
    }
    return true;
}


bool ThemChiTietVaoHoaDon(HoaDon& hd, ChiTietHoaDon ctMoi) {
    NodeChiTiet* p = TaoNodeChiTiet(ctMoi);

    if (hd.dsChiTiet.head == NULL) {
        hd.dsChiTiet.head = hd.dsChiTiet.tail = p;
    }
    else {
        hd.dsChiTiet.tail->next = p;
        p->pre = hd.dsChiTiet.tail; 
        hd.dsChiTiet.tail = p;  
    }

    hd.dsChiTiet.soLuong++;
    hd.tongTien += ctMoi.thanhTien;
    return true;
}


// =================== 3. QUẢN LÝ KHÁCH HÀNG ===================

KhachHang* TimKiemKhachHang(const DanhSachKhachHang& dskh, const char maKH[10]) {
    for (NodeKhachHang* k = dskh.head; k != NULL; k = k->next) {
        if (strcmp(k->data.maKH, maKH) == 0) return &k->data;
    }
    return NULL;
}

bool ThemKhachHang(DanhSachKhachHang& dskh, KhachHang khMoi) {
    if (TimKiemKhachHang(dskh, khMoi.maKH) != NULL) {
        cout << "Loi: Trung ma khach hang!\n"; return false;
    }
    NodeKhachHang* p = TaoNodeKhachHang(khMoi);
    if (dskh.head == NULL) dskh.head = dskh.tail = p;
    else { dskh.tail->next = p; p->pre = dskh.tail; dskh.tail = p; }
    dskh.soLuong++;
    return true;
}

bool XoaKhachHang(DanhSachKhachHang& dskh, const char maKH[10]) {
    if (dskh.head == NULL) return false;

    NodeKhachHang* p = dskh.head;
    while (p != NULL) {
        if (strcmp(p->data.maKH, maKH) == 0) {

            if (p == dskh.head) {
                dskh.head = p->next;
                if (dskh.head) dskh.head->pre = NULL;
            }
            else {
                p->pre->next = p->next;
            }

            if (p == dskh.tail) {
                dskh.tail = p->pre;
                if (dskh.tail) dskh.tail->next = NULL;
            }
            else {
                p->next->pre = p->pre;
            }

            delete p;
            dskh.soLuong--;
            return true;
        }
        p = p->next;
    }
    return false;
}

bool SuaKhachHang(DanhSachKhachHang& dskh, KhachHang khMoi) {
    KhachHang* kh = TimKiemKhachHang(dskh, khMoi.maKH);
    if (kh == NULL) return false;
    strcpy_s(kh->tenKH, khMoi.tenKH);
    strcpy_s(kh->soDT, khMoi.soDT);
    strcpy_s(kh->email, khMoi.email);
    strcpy_s(kh->diaChi, khMoi.diaChi);
    return true;
}


// =================== 4. QUẢN LÝ LAPTOP ===================

Laptop* TimKiemLaptop(const DanhSachLaptop& dsls, const char maLaptop[10]) {
    for (NodeLaptop* k = dsls.head; k != NULL; k = k->next) {
        if (strcmp(k->data.maLaptop, maLaptop) == 0) return &k->data;
    }
    return NULL;
}

bool ThemLaptop(DanhSachLaptop& dsls, Laptop ltMoi) {
    if (TimKiemLaptop(dsls, ltMoi.maLaptop) != NULL) {
        cout << "Loi: Trung ma Laptop!\n"; return false;
    }
    NodeLaptop* p = TaoNodeLaptop(ltMoi);
    if (dsls.head == NULL) dsls.head = dsls.tail = p;
    else { dsls.tail->next = p; p->pre = dsls.tail; dsls.tail = p; }
    dsls.soLuong++;
    return true;
}

bool XoaLaptop(DanhSachLaptop& dsls, const char maLaptop[10]) {
    if (dsls.head == NULL) return false;
    NodeLaptop* p = dsls.head;
    while (p != NULL) {
        if (strcmp(p->data.maLaptop, maLaptop) == 0) {
            if (p == dsls.head) {
                dsls.head = p->next;
                if (dsls.head) dsls.head->pre = NULL;
            }
            else {
                p->pre->next = p->next;
            }

            if (p == dsls.tail) {
                dsls.tail = p->pre;
                if (dsls.tail) dsls.tail->next = NULL;
            }
            else {
                p->next->pre = p->pre;
            }

            delete p;
            dsls.soLuong--;
            return true;
        }
        p = p->next;
    }
    return false;
}

bool SuaLaptop(DanhSachLaptop& dsls, Laptop ltMoi) {
    Laptop* lt = TimKiemLaptop(dsls, ltMoi.maLaptop);
    if (lt == NULL) return false;
    *lt = ltMoi;
    return true;
}

void CapNhatSoLuongLaptop(DanhSachLaptop& dsls, const char maLaptop[10], int soLuongBan) {
    Laptop* lt = TimKiemLaptop(dsls, maLaptop);
    if (lt != NULL) {
        lt->soLuongTon -= soLuongBan;
        lt->trangThai = (lt->soLuongTon > 0) ? CON_HANG : HET_HANG;
    }
}


// =================== 5. QUẢN LÝ NHÂN VIÊN & TÀI KHOẢN ===================

NhanVien* TimKiemNhanVien(const DanhSachNhanVien& dsnv, const char maNV[10]) {
    for (NodeNhanVien* k = dsnv.head; k != NULL; k = k->next) {
        if (strcmp(k->data.maNV, maNV) == 0) return &k->data;
    }
    return NULL;
}

bool ThemNhanVien(DanhSachNhanVien& dsnv, NhanVien nvMoi) {
    if (TimKiemNhanVien(dsnv, nvMoi.maNV) != NULL) return false;
    NodeNhanVien* p = TaoNodeNhanVien(nvMoi);
    if (dsnv.head == NULL) dsnv.head = dsnv.tail = p;
    else { dsnv.tail->next = p; p->pre = dsnv.tail; dsnv.tail = p; }
    dsnv.soLuong++;
    return true;
}

bool SuaNhanVien(DanhSachNhanVien& dsnv, NhanVien nvMoi) {
    NhanVien* nv = TimKiemNhanVien(dsnv, nvMoi.maNV);
    if (nv == NULL) return false;
    *nv = nvMoi;
    return true;
}

TaiKhoan* TimKiemTaiKhoan(const DanhSachTaiKhoan& dstk, const char user[30]) {
    for (NodeTaiKhoan* k = dstk.head; k != NULL; k = k->next) {
        if (strcmp(k->data.tenDangNhap, user) == 0) return &k->data;
    }
    return NULL;
}

bool ThemTaiKhoan(DanhSachTaiKhoan& dstk, TaiKhoan tkMoi) {
    if (TimKiemTaiKhoan(dstk, tkMoi.tenDangNhap) != NULL) return false;
    NodeTaiKhoan* p = TaoNodeTaiKhoan(tkMoi);
    if (dstk.head == NULL) dstk.head = dstk.tail = p;
    else { dstk.tail->next = p; p->pre = dstk.tail; dstk.tail = p; }
    dstk.soLuong++;
    return true;
}

bool XoaTaiKhoan(DanhSachTaiKhoan& dstk, const char user[30]) {
    if (dstk.head == NULL) return false;
    NodeTaiKhoan* p = dstk.head;
    while (p != NULL) {
        if (strcmp(p->data.tenDangNhap, user) == 0) {
            if (p == dstk.head) {
                dstk.head = p->next;
                if (dstk.head) dstk.head->pre = NULL;
            }
            else {
                p->pre->next = p->next;
            }

            if (p == dstk.tail) {
                dstk.tail = p->pre;
                if (dstk.tail) dstk.tail->next = NULL;
            }
            else {
                p->next->pre = p->pre;
            }
            delete p;
            dstk.soLuong--;
            return true;
        }
        p = p->next;
    }
    return false;
}

bool XoaNhanVien(DanhSachNhanVien& dsnv, DanhSachTaiKhoan& dstk, const char maNV[10]) {
    for (NodeTaiKhoan* k = dstk.head; k != NULL; k = k->next) {
        if (strcmp(k->data.maNV, maNV) == 0) {
            XoaTaiKhoan(dstk, k->data.tenDangNhap);
            break;
        }
    }

    if (dsnv.head == NULL) return false;
    NodeNhanVien* p = dsnv.head;
    while (p != NULL) {
        if (strcmp(p->data.maNV, maNV) == 0) {
            if (p == dsnv.head) {
                dsnv.head = p->next;
                if (dsnv.head) dsnv.head->pre = NULL;
            }
            else {
                p->pre->next = p->next;
            }

            if (p == dsnv.tail) {
                dsnv.tail = p->pre;
                if (dsnv.tail) dsnv.tail->next = NULL;
            }
            else {
                p->next->pre = p->pre;
            }
            delete p;
            dsnv.soLuong--;
            return true;
        }
        p = p->next;
    }
    return false;
}

bool SuaTaiKhoan(DanhSachTaiKhoan& dstk, TaiKhoan tkMoi) {
    TaiKhoan* tk = TimKiemTaiKhoan(dstk, tkMoi.tenDangNhap);
    if (tk == NULL) return false;
    tk->quyen = tkMoi.quyen;
    tk->trangThai = tkMoi.trangThai;
    return true;
}

TaiKhoan* DangNhap(const DanhSachTaiKhoan& dstk, const char user[30], const char pass[30]) {
    TaiKhoan* tk = TimKiemTaiKhoan(dstk, user);
    if (tk != NULL && strcmp(tk->matKhau, pass) == 0) {
        if (tk->trangThai == TK_HOAT_DONG) return tk;
        else {
            cout << "Tai khoan da bi khoa!\n"; return NULL;
        }
    }
    return NULL;
}

bool DoiMatKhau(DanhSachTaiKhoan& dstk, const char user[30], const char passMoi[30]) {
    TaiKhoan* tk = TimKiemTaiKhoan(dstk, user);
    if (tk) { strcpy_s(tk->matKhau, passMoi); return true; }
    return false;
}


// =================== 6. DANH MỤC ===================

ThuongHieu* TimKiemThuongHieu(const DanhSachThuongHieu& dsth, const char maTH[10]) {
    for (NodeThuongHieu* k = dsth.head; k != NULL; k = k->next) {
        if (strcmp(k->data.maThuongHieu, maTH) == 0) return &k->data;
    }
    return NULL;
}

bool ThemThuongHieu(DanhSachThuongHieu& dsth, ThuongHieu th) {
    if (TimKiemThuongHieu(dsth, th.maThuongHieu)) return false;
    NodeThuongHieu* p = TaoNodeThuongHieu(th);
    if (!dsth.head) dsth.head = dsth.tail = p;
    else { dsth.tail->next = p; p->pre = dsth.tail; dsth.tail = p; }
    dsth.soLuong++;
    return true;
}

bool XoaThuongHieu(DanhSachThuongHieu& dsth, const char maTH[10]) {
    if (!dsth.head) return false;
    NodeThuongHieu* p = dsth.head;
    while (p) {
        if (strcmp(p->data.maThuongHieu, maTH) == 0) {
            if (p == dsth.head) {
                dsth.head = p->next;
                if (dsth.head) dsth.head->pre = NULL;
                if (!dsth.head) dsth.tail = NULL;
            }
            else {
                p->pre->next = p->next;
            }

            if (p == dsth.tail) {
                dsth.tail = p->pre;
                if (dsth.tail) dsth.tail->next = NULL;
            }
            else {
                p->next->pre = p->pre;
            }
            delete p;
            dsth.soLuong--;
            return true;
        }
        p = p->next;
    }
    return false;
}

bool SuaThuongHieu(DanhSachThuongHieu& dsth, ThuongHieu thMoi) {
    ThuongHieu* th = TimKiemThuongHieu(dsth, thMoi.maThuongHieu);
    if (th) { *th = thMoi; return true; }
    return false;
}

LoaiSanPham* TimKiemLoai(const DanhSachLoai& dsl, const char maLoai[10]) {
    for (NodeLoai* k = dsl.head; k != NULL; k = k->next) {
        if (strcmp(k->data.maLoai, maLoai) == 0) return &k->data;
    }
    return NULL;
}

bool ThemLoai(DanhSachLoai& dsl, LoaiSanPham loai) {
    if (TimKiemLoai(dsl, loai.maLoai)) return false;
    NodeLoai* p = TaoNodeLoai(loai);
    if (!dsl.head) dsl.head = dsl.tail = p;
    else { dsl.tail->next = p; p->pre = dsl.tail; dsl.tail = p; }
    dsl.soLuong++;
    return true;
}

bool XoaLoai(DanhSachLoai& dsl, const char maLoai[10]) {
    if (!dsl.head) return false;
    NodeLoai* p = dsl.head;
    while (p) {
        if (strcmp(p->data.maLoai, maLoai) == 0) {
            if (p == dsl.head) {
                dsl.head = p->next;
                if (dsl.head) dsl.head->pre = NULL;
                if (!dsl.head) dsl.tail = NULL;
            }
            else {
                p->pre->next = p->next;
            }
            if (p == dsl.tail) {
                dsl.tail = p->pre;
                if (dsl.tail) dsl.tail->next = NULL;
            }
            else {
                p->next->pre = p->pre;
            }
            delete p;
            dsl.soLuong--;
            return true;
        }
        p = p->next;
    }
    return false;
}

bool SuaLoai(DanhSachLoai& dsl, LoaiSanPham loaiMoi) {
    LoaiSanPham* l = TimKiemLoai(dsl, loaiMoi.maLoai);
    if (l) { *l = loaiMoi; return true; }
    return false;
}


// =================== 7. SẮP XẾP ===================
// =================== 7. SẮP XẾP (SELECTION SORT - LINKED LIST) ===================

template <typename T>
void SwapData(T& a, T& b) { T temp = a; a = b; b = temp; }

void SapXepLaptop_TheoID(DanhSachLaptop& dsls) {
    for (NodeLaptop* p = dsls.head;p != NULL;p=p->next) {
        NodeLaptop* minNode = p;
        for (NodeLaptop* q = p->next; q != NULL;q = q->next) {
            if (strcmp(q->data.maLaptop, minNode->data.maLaptop) < 0) {
                minNode = q;
            }
        }
        if (minNode != p) SwapData(p->data, minNode->data);
    }
}
// --- Laptop ---
void SapXepLaptop_TheoTen(DanhSachLaptop& dsls) {
    for (NodeLaptop* p = dsls.head; p != NULL; p = p->next) {
        NodeLaptop* minNode = p;
        // Duyệt tìm Node nhỏ nhất trong phần còn lại
        for (NodeLaptop* q = p->next; q != NULL; q = q->next) {
            if (strcmp(q->data.tenLaptop, minNode->data.tenLaptop) < 0) {
                minNode = q;
            }
        }
        // Hoán đổi dữ liệu nếu tìm thấy
        if (minNode != p) SwapData(p->data, minNode->data);
    }
}

void SapXepLaptop_TheoGia(DanhSachLaptop& dsls) {
    for (NodeLaptop* p = dsls.head; p != NULL; p = p->next) {
        NodeLaptop* minNode = p;
        for (NodeLaptop* q = p->next; q != NULL; q = q->next) {
            if (q->data.giaBan < minNode->data.giaBan) {
                minNode = q;
            }
        }
        if (minNode != p) SwapData(p->data, minNode->data);
    }
}

// --- Khách Hàng ---
void SapXepKhachHang_TheoTen(DanhSachKhachHang& dskh) {
    for (NodeKhachHang* p = dskh.head; p != NULL; p = p->next) {
        NodeKhachHang* minNode = p;
        for (NodeKhachHang* q = p->next; q != NULL; q = q->next) {
            if (strcmp(q->data.tenKH, minNode->data.tenKH) < 0) {
                minNode = q;
            }
        }
        if (minNode != p) SwapData(p->data, minNode->data);
    }
}

// --- Hóa Đơn ---
int SoSanhNgay(Date a, Date b) {
    if (a.nam != b.nam) return a.nam - b.nam;
    if (a.thang != b.thang) return a.thang - b.thang;
    return a.ngay - b.ngay;
}

void SapXepHoaDon_TheoNgay(DanhSachHoaDon& dsHD) {
    for (NodeHoaDon* p = dsHD.head; p != NULL; p = p->next) {
        NodeHoaDon* minNode = p;
        for (NodeHoaDon* q = p->next; q != NULL; q = q->next) {
            if (SoSanhNgay(q->data.ngayLap, minNode->data.ngayLap) < 0) {
                minNode = q;
            }
        }
        if (minNode != p) SwapData(p->data, minNode->data);
    }
}

void SapXepHoaDon_TheoTongTien(DanhSachHoaDon& dsHD) {
    for (NodeHoaDon* p = dsHD.head; p != NULL; p = p->next) {
        NodeHoaDon* maxNode = p; // Giảm dần
        for (NodeHoaDon* q = p->next; q != NULL; q = q->next) {
            if (q->data.tongTien > maxNode->data.tongTien) {
                maxNode = q;
            }
        }
        if (maxNode != p) SwapData(p->data, maxNode->data);
    }
}

// =================== 8. BẢO HÀNH ===================

bool ThemBaoHanh(DanhSachBaoHanh& dsBH, BaoHanh bhMoi) {
    NodeBaoHanh* p = TaoNodeBaoHanh(bhMoi);
    if (dsBH.head == NULL) dsBH.head = dsBH.tail = p;
    else { dsBH.tail->next = p; p->pre = dsBH.tail; dsBH.tail = p; }
    dsBH.soLuong++;
    return true;
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

NodeLaptop* LayNodeTaiViTri(const DanhSachLaptop& dsls, int index) {
    if (index < 0 || index >= dsls.soLuong) return NULL;

    // Tối ưu nhẹ: Nếu index ở nửa đầu thì đi từ Head, nửa sau thì đi từ Tail
    // (Vì là DSLK đôi)
    if (index < dsls.soLuong / 2) {
        NodeLaptop* k = dsls.head;
        for (int i = 0; i < index; i++) k = k->next;
        return k;
    }
    else {
        NodeLaptop* k = dsls.tail;
        for (int i = dsls.soLuong - 1; i > index; i--) k = k->pre;
        return k;
    }
}

// Thuật toán Binary Search trên DSLK
Laptop* TimKiemNhiPhan_TheoTen(const DanhSachLaptop& dsls, const char tenCanTim[50]) {
    int left = 0;
    int right = dsls.soLuong - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        // [CHẬM] Phải duyệt tìm node mid thay vì truy cập tức thì
        NodeLaptop* midNode = LayNodeTaiViTri(dsls, mid);

        if (midNode == NULL) break;

        int res = strcmp(midNode->data.tenLaptop, tenCanTim);

        if (res == 0) {
            return &midNode->data; // Tìm thấy
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

