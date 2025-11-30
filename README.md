📖 Giới thiệu

Dự án này là một phần mềm quản lý bán lẻ Laptop được xây dựng hoàn toàn bằng C++.
Điểm đặc biệt của đồ án là không sử dụng mảng (Array) mà thay thế bằng:

Danh sách liên kết kép (Doubly Linked List)

Danh sách lồng nhau (Nested Linked List)

Mục tiêu là tối ưu hóa bộ nhớ, tăng khả năng thêm/xóa động và mô phỏng các nghiệp vụ thực tế của một cửa hàng máy tính.

🚀 Tính năng Nổi bật
1. 🔐 Hệ thống & Bảo mật

Đăng nhập với cơ chế ẩn mật khẩu (hiển thị *)

Phân quyền Quản lý (Admin) & Nhân viên (Staff)

Tự tạo tài khoản Admin mặc định (admin/admin) khi khởi động lần đầu

Dữ liệu lưu trữ bền vững qua 8 file nhị phân (.dat)

2. 📦 Quản lý Kho & Sản phẩm

Quản lý Thương hiệu (Dell, Asus, Apple, MSI...)

Quản lý Loại Laptop (Gaming, Ultrabook, Văn phòng,...)

Chức năng Laptop:

CRUD: Thêm / Xóa / Sửa

Nhập kho: Cộng dồn số lượng

Cấu hình chi tiết (CPU, RAM, SSD, GPU, Display)

Tra cứu nâng cao:

Lọc theo hãng, loại

Lọc theo khoảng giá

Tìm theo cấu hình (RAM, SSD, CPU)

3. 🧾 Nghiệp vụ Bán hàng (POS)

Tự sinh Mã hóa đơn

Kiểm tra tồn kho tức thời

Hỗ trợ tạo nhanh khách hàng mới tại POS

Nhập Serial Number cho từng máy bán ra

Xử lý tự động:

Trừ kho khi thanh toán

Sinh phiếu bảo hành gắn theo từng máy, có ngày hết hạn theo chính sách

4. 👥 Quản lý Con người

Nhân viên: Quản lý hồ sơ, khi xóa nhân viên → tự động xóa tài khoản

Khách hàng:

Lưu thông tin cá nhân

Lịch sử mua hàng (Danh sách Hóa đơn lồng bên trong Khách hàng)

5. 📊 Báo cáo & Thống kê

Doanh thu theo ngày / tháng / năm

Lợi nhuận (Giá bán – Giá vốn)

Tồn kho theo số lượng & giá trị

Tra cứu bảo hành theo:

Mã Serial

Khách hàng

🛠️ Kiến trúc Kỹ thuật (Technical Architecture)
1. Cấu trúc Dữ liệu (thuvien.h)

Doubly Linked List: head, tail, next, pre

Nested list:

KhachHang → danh sách HoaDon

HoaDon → danh sách ChiTietHoaDon

Enum:

RAM / SSD / Loại sản phẩm

Trạng thái hệ thống

2. Lớp Logic xử lý (xuly.h / xuly.cpp)

Chứa toàn bộ thuật toán:

Thêm – Xóa node (unlink DSLK)

Tìm kiếm tuần tự

Sắp xếp Interchange Sort trực tiếp trên Node

File I/O bằng Template để tái sử dụng tối đa

3. Lớp Giao diện (UI Modules)

Tách toàn bộ cin/cout khỏi logic xử lý

Các module:

laptop.cpp

danhmuc.cpp

hoadon.cpp

khachhang.cpp

nhanvien.cpp

baohanh.cpp

thongke.cpp

main.cpp điều phối chương trình

fake_data.cpp sinh dữ liệu mẫu

📂 Cấu trúc Thư mục
QuanLyCuaHang/
├── Header Files/
│   ├── thuvien.h
│   ├── xuly.h
│   ├── fake_data.h
│   ├── laptop.h
│   ├── danhmuc.h
│   ├── hoadon.h
│   ├── nhanvien.h
│   ├── khachhang.h
│   ├── baohanh.h
│   └── thongke.h
│
├── Source Files/
│   ├── main.cpp
│   ├── xuly.cpp
│   ├── fake_data.cpp
│   ├── laptop.cpp
│   ├── hoadon.cpp
│   └── ... (các file còn lại)
│
└── Data Files/ (tự động tạo khi chạy)
    ├── laptops.dat
    ├── hoadon.dat
    └── ...

⚙️ Hướng dẫn Cài đặt & Chạy
Yêu cầu

Windows + Visual Studio 2019/2022 (khuyên dùng)

C++11 trở lên

Cách chạy

Clone/Download source code

Mở project bằng Visual Studio

Xóa tất cả file .dat cũ trong thư mục chứa file .exe
(thường là x64/Debug)

Build → Rebuild Solution

Chạy chương trình (F5)

Lần chạy đầu tiên hệ thống sẽ tự động tạo:

50 Laptop mẫu

100 Khách hàng mẫu

200 Hóa đơn lịch sử

🔑 Tài khoản Đăng nhập Mặc định
Admin
```cpp
User: admin
Pass: admin
```


Nhân viên
```cpp
User: user1
Pass: 123
```



📝 Ghi chú quan trọng

Dùng cin.ignore() để tránh trôi lệnh khi nhập chuỗi

Menu điều hướng sử dụng _getch()

Tìm kiếm chuỗi không phân biệt hoa thường (_stricmp)
