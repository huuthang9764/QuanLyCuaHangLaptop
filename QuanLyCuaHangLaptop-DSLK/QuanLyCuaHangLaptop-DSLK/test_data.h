#pragma once
#ifndef TEST_DATA_H
#define TEST_DATA_H

#include "thuvien.h" 
#include "xuly.h"

// Hàm sinh dữ liệu mẫu tự động cho DSLK
void KhoiTaoDuLieuTuDong(
    DanhSachLaptop& dsls,
    DanhSachKhachHang& dskh,
    DanhSachNhanVien& dsnv,
    DanhSachTaiKhoan& dstk,
    DanhSachThuongHieu& dsth,
    DanhSachLoai& dsl,
    DanhSachHoaDon& dshd,
    DanhSachBaoHanh& dsbh
);

#endif