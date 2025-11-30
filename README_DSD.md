💻 Hệ thống Quản lý Cửa hàng Laptop
📦 Phiên bản Danh sách Đặc – Đồ án Lập trình C++ (Console Application)

Hệ thống quản lý bán hàng được xây dựng bằng C++ thuần, sử dụng Mảng tĩnh (Static Array) làm nền tảng lưu trữ dữ liệu. Dự án mô phỏng quy trình kinh doanh thực tế tại một cửa hàng Laptop, đồng thời áp dụng mô hình 3-Layer Architecture để tách biệt dữ liệu – xử lý – giao diện.

📖 Tổng Quan

✔ Ứng dụng chạy trên console, đầy đủ tính năng quản lý cửa hàng.
✔ Dữ liệu được lưu trong mảng tĩnh, không sử dụng STL hay database.
✔ Tập trung vào tính chặt chẽ của dữ liệu, nghiệp vụ thực tế và phân quyền người dùng.

🛠️ Kiến trúc & Cấu trúc Dữ liệu

Hệ thống tuân theo mô hình 3 lớp (3-Layer Architecture):

```cpp
Data (thuvien.h)
Business Logic (xuly.cpp)
Presentation - UI (các module giao diện)
```

1️⃣ Tầng Dữ liệu (Data Structure – thuvien.h)
🔸 Mảng Tĩnh (Static Array)

Dữ liệu được lưu vào các mảng có kích thước cố định MAX_SIZE.

Quản lý bằng biến đếm soLuong.

Ví dụ cấu trúc danh sách:

```cpp
const int MAX_SIZE = 100;

struct DanhSachLaptop {
    int soLuong;
    Laptop ds[MAX_SIZE];
};
```

🔸 Cấu trúc Lồng nhau (Nested Structure)

KhachHang chứa mảng HoaDon.

HoaDon chứa mảng ChiTietHoaDon.

🔸 Enum Trạng thái

Sử dụng cho:

Trạng thái sản phẩm

Trạng thái tài khoản

Cấu hình (RAM, SSD)
2️⃣ Tầng Xử lý Logic (Business Logic – xuly.cpp)
Thuật toán chính:
➕ Thêm

Thêm vào cuối mảng rồi tăng biến đếm.

➖ Xóa

Dùng thuật toán Shift Left để dồn mảng.

🔍 Tìm kiếm

Tìm tuần tự (Linear Search) theo mã hoặc tên.

🔄 Sắp xếp

Interchange Sort

Selection Sort

💾 Lưu trữ

Đọc/Ghi toàn bộ mảng bằng file nhị phân .dat.

3️⃣ Tầng Giao diện (Presentation – UI)

Tách biệt hoàn toàn nhập/xuất khỏi logic xử lý.

Menu đa cấp, điều hướng bằng phím số.

Tương tác console đơn giản nhưng tối ưu trải nghiệm người dùng.

🚀 Chi Tiết Nhóm Chức Năng

Hệ thống gồm 7 nhóm nghiệp vụ chính:

1. 🔐 Quản trị Hệ thống
Đăng nhập & Bảo mật

Mật khẩu ẩn bằng ký tự *.

Tự tạo tài khoản Admin khi chạy lần đầu.

Phân quyền

Admin → toàn quyền

Nhân viên → giới hạn (Bán hàng, Tra cứu, Khách hàng)

2. 📦 Quản lý Kho & Sản phẩm
Danh mục

Thêm / xóa / sửa Hãng và Loại Laptop.

Quản lý Laptop

Nhập thông tin chi tiết cấu hình: CPU, RAM, SSD, GPU, màn hình.

Kiểm tra dữ liệu hợp lệ.

Restock sản phẩm có sẵn.

3. 🔍 Tra cứu & Tìm kiếm Nâng cao

Bộ lọc:

Hãng sản xuất

Loại sản phẩm

Khoảng giá

Dung lượng RAM

Dung lượng SSD

Tên CPU

4. 🧾 Nghiệp vụ Bán hàng (POS)
Quy trình lập hóa đơn

Tự sinh mã hóa đơn.

Chọn khách cũ hoặc tạo mới nhanh.

Kiểm tra tồn kho tức thời.

Nhập Serial Number để phục vụ bảo hành.

Xử lý giao dịch

Tự tính tổng tiền.

Tự trừ tồn kho sau bán.

Lưu lịch sử mua hàng vào khách hàng.

5. 🛡️ Quản lý Bảo hành & Hậu mãi
Tự động tạo phiếu bảo hành

Tính ngày hết hạn tự động.

Tra cứu

Theo Serial → kiểm tra hàng chính hãng.

Theo khách hàng → xem lịch sử.

Trạng thái

CON HAN hoặc HET HAN dựa vào ngày hiện tại.

6. 👥 Quản lý Con người
Nhân sự

Quản lý hồ sơ nhân viên.

Tài khoản

Cấp quyền

Khóa / Mở khóa

Đổi mật khẩu

Khách hàng (CRM)

Lưu thông tin liên lạc

Theo dõi lịch sử mua hàng

7. 📊 Báo cáo & Thống kê

Doanh thu theo Ngày / Tháng / Năm.

Báo cáo tồn kho.

Thống kê lợi nhuận dựa trên giá vốn – giá bán.

📂 Tổ chức File

```bash
QuanLyCuaHang/
├── Header Files/
│   ├── thuvien.h       # Struct, Enum, MAX_SIZE
│   ├── xuly.h          # Prototype hàm xử lý
│   ├── fake_data.h     # Prototype sinh dữ liệu mẫu
│   └── ... (UI header)
│
├── Source Files/
│   ├── main.cpp        # Menu điều hướng chính
│   ├── xuly.cpp        # Thuật toán xử lý mảng
│   ├── fake_data.cpp   # Logic sinh dữ liệu giả
│   ├── laptop.cpp      # UI quản lý Laptop
│   ├── hoadon.cpp      # UI Bán hàng
│   └── ... (mod khác)
│
└── Data Files/
    ├── laptops.dat
    ├── hoadon.dat
    └── ...

```