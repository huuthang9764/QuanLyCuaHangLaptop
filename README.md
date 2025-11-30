💻 Laptop Store Management System (C++)
Hệ thống Quản lý Cửa hàng Laptop - Phiên bản Danh sách Liên kết

Một đồ án C++ Console Application sử dụng cấu trúc dữ liệu nâng cao để quản lý quy trình bán hàng, kho bãi và nhân sự.

📖 Giới thiệu
Dự án này là một phần mềm quản lý toàn diện cho cửa hàng bán lẻ Laptop. Điểm đặc biệt về mặt kỹ thuật của dự án là việc loại bỏ hoàn toàn mảng (Array) và thay thế bằng cấu trúc Danh sách liên kết Kép (Doubly Linked List) kết hợp với Danh sách lồng nhau (Nested List) để tối ưu hóa việc quản lý bộ nhớ và thao tác dữ liệu động.

🚀 Tính năng Nổi bật
1. 🔐 Hệ thống & Bảo mật
Đăng nhập: Cơ chế bảo mật mật khẩu (hiển thị *), phân quyền Quản lý (Admin) và Nhân viên (Staff).

Tự động khởi tạo: Tự động tạo tài khoản Admin mặc định (admin/admin) khi chạy lần đầu.

Lưu trữ: Dữ liệu được lưu trữ bền vững (Persistence) qua hệ thống 8 file nhị phân (.dat).

2. 📦 Quản lý Kho & Sản phẩm
Danh mục: Quản lý Thương hiệu (Dell, Asus, Apple...) và Loại sản phẩm (Gaming, Ultrabook...).

Laptop:

CRUD (Thêm, Xóa, Sửa) Laptop.

Nhập kho: Cộng dồn số lượng tồn kho.

Cấu hình chi tiết: CPU, RAM, SSD, GPU, Màn hình (Sử dụng Enum).

Tra cứu nâng cao:

Lọc theo Hãng, Loại.

Lọc theo Khoảng giá (Min-Max).

Tìm kiếm theo Cấu hình (RAM, SSD, Tên CPU).

3. 🧾 Nghiệp vụ Bán hàng (POS)
Lập Hóa đơn:

Tự động sinh Mã hóa đơn.

Kiểm tra tồn kho tức thời.

Hỗ trợ Tạo nhanh Khách hàng ngay trong giao diện bán hàng.

Serial Number: Nhập số Serial cho từng máy bán ra để định danh duy nhất.

Xử lý tự động:

Tự động trừ kho khi thanh toán.

Tự động tạo Phiếu bảo hành kèm theo ngày hết hạn (tính toán theo chính sách bảo hành của từng máy).

4. 👥 Quản lý Con người
Nhân sự: Quản lý hồ sơ nhân viên. Khi xóa nhân viên, hệ thống tự động xóa tài khoản liên kết.

Khách hàng: Lưu trữ thông tin và Lịch sử mua hàng (Danh sách hóa đơn được lồng bên trong thông tin khách hàng).

5. 📊 Báo cáo & Thống kê
Doanh thu: Báo cáo chi tiết theo Ngày, Tháng, Năm.

Lợi nhuận: Tính toán lãi gộp dựa trên (Giá Bán - Giá Vốn).

Tồn kho: Báo cáo số lượng và giá trị hàng tồn.

Tra cứu Bảo hành: Kiểm tra hạn bảo hành theo Mã máy (Serial) hoặc Khách hàng.

🛠️ Kiến trúc Kỹ thuật (Technical Architecture)
Dự án áp dụng mô hình 3 Lớp (3-Layer Architecture) kết hợp Module hóa:

1. Cấu trúc Dữ liệu (thuvien.h)
Sử dụng Danh sách liên kết Kép (Doubly Linked List) với con trỏ head, tail, next, pre.

Cấu trúc Lồng nhau (Nested):

KhachHang chứa danh sách HoaDon.

HoaDon chứa danh sách ChiTietHoaDon.

Enum: Sử dụng Enum cho LoaiRAM, LoaiSSD, TrangThai để đảm bảo tính toàn vẹn dữ liệu.

2. Lớp Xử lý Logic (xuly.h / xuly.cpp)
Chứa toàn bộ thuật toán: Thêm, Xóa (tháo mắt xích DSLK), Tìm kiếm (Tuần tự), Sắp xếp (Interchange Sort trên Node).

Xử lý File I/O sử dụng Template để tái sử dụng code.

3. Lớp Giao diện UI (Modules)
Tách biệt code giao diện (cin/cout) ra khỏi logic xử lý.

main.cpp: Điều phối luồng chương trình.

laptop.cpp, hoadon.cpp, nhanvien.cpp...: Các module giao diện riêng biệt.

fake_data.cpp: Module sinh dữ liệu giả lập để test (Data Seeding).

📂 Cấu trúc Thư mục
QuanLyCuaHang/
├── Header Files/
│   ├── thuvien.h       # Định nghĩa Struct, Enum, Node
│   ├── xuly.h          # Khai báo hàm logic (API)
│   ├── fake_data.h     # Khai báo hàm sinh dữ liệu mẫu
│   ├── laptop.h        # UI Module Laptop
│   ├── danhmuc.h       # UI Module Danh mục
│   ├── hoadon.h        # UI Module Bán hàng
│   ├── nhanvien.h      # UI Module Nhân sự
│   ├── khachhang.h     # UI Module Khách hàng
│   ├── baohanh.h       # UI Module Bảo hành
│   └── thongke.h       # UI Module Thống kê
│
├── Source Files/
│   ├── main.cpp        # Hàm main(), Menu chính
│   ├── xuly.cpp        # Triển khai logic DSLK
│   ├── fake_data.cpp   # Logic sinh dữ liệu mẫu
│   ├── laptop.cpp      # Code giao diện Laptop
│   ├── hoadon.cpp      # Code giao diện Hóa đơn
│   └── ... (các file .cpp tương ứng với .h)
│
└── Data Files/ (Tự động tạo khi chạy)
    ├── laptops.dat
    ├── hoadon.dat
    └── ...
⚙️ Hướng dẫn Cài đặt & Chạy
Yêu cầu hệ thống
IDE: Visual Studio 2019/2022 (Khuyên dùng) hoặc Dev-C++.

Ngôn ngữ: C++11 trở lên.

Các bước thực hiện
Clone/Download toàn bộ source code.

Mở project trong Visual Studio.

Quan trọng: Vào thư mục chứa file .exe (thường là x64/Debug), XÓA TẤT CẢ các file có đuôi .dat cũ (nếu có) để tránh lỗi không tương thích dữ liệu.

Nhấn Build -> Rebuild Solution.

Chạy chương trình (F5).

Trong lần chạy đầu tiên, hệ thống sẽ tự động kích hoạt fake_data để sinh ra:

50 Laptop mẫu.

100 Khách hàng mẫu.

200 Hóa đơn giao dịch lịch sử.

Tài khoản Đăng nhập Mặc định
Admin (Quyền cao nhất):

User: admin

Pass: admin

Nhân viên:

User: user1

Pass: 123

📝 Ghi chú quan trọng
Để tránh lỗi trôi lệnh khi nhập chuỗi, chương trình sử dụng cin.ignore() một cách chiến lược và dùng _getch() cho các menu điều hướng.

Khi tìm kiếm, chương trình sử dụng _stricmp để so sánh chuỗi không phân biệt hoa thường (ví dụ: gõ "dell", "DELL", "Dell" đều được).