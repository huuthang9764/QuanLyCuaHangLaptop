#pragma once
#ifndef TEST_DATA_H
#define TEST_DATA_H

#include "thuvien.h"

// Hàm khởi tạo dữ liệu mẫu cho toàn bộ hệ thống
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