# Hệ thống quản lý bán hàng điện tử



## Thông tin nhóm

Nhóm 17 môn Lập trình Hướng Đối tượng, gồm `04` thành viên:

| MSSV     | Họ và tên         |
| -------- | ----------------- |
| 18127221 | Bùi Văn Thiện     |
| 18127185 | Bùi Vũ Hiếu Phụng |
| 18127080 | Kiều Vũ Minh Đức  |
| 18127164 | Huỳnh Thiện Nhân  |



## Sơ lược

#### *Vấn đề*

* Cuộc sống phát triển đi cùng với đó là nhu cầu kinh doanh, buôn bán ngày càng tăng cao với các hình thức kinh doanh khác nhau. Bên cạnh việc mở các cửa hàng kinh doanh theo kiểu truyền thống với lợi thế về mặt bằng, ngày càng có nhiều doanh nghiệp đi theo hướng phát triển hoạt động bán hàng trực tuyến, trong đó nổi bật nhất là bán hàng trực tuyến.
* Chính vì vậy, những sàn giao dịch điện tử đã ra đời như Shoppe, Lazada, Tiki,... Để hoạt động tốt, những trang thương mại này phụ thuộc nhiều vào việc lưu trữ và xử lí cơ sở dữ liệu. Đó là ý tưởng để nhóm em thực hiện đồ án này. 

#### *Giới thiệu*

- Một hệ thống quản lý bán hàng điện tử cơ bản, được viết bằng C++, không có giao diện đồ họa. Hệ thống bao gồm những đối tượng cơ bản cần thiết như người bán/mua, sản phẩm, đơn hàng,...
-  Mục tiêu: Hiểu rõ và áp dụng những kiến thức cơ bản và nâng cao trong Lập trình Hướng Đối tượng. Đồng thời luyện tập tổ chức nhóm, tổ chức dự án, tìm hiểu về hệ thống quản lý `git` và workflow xoay quanh `git`.
- Mã nguồn của đồ án được lưu trên [repo GitHub riêng](https://github.com/84436/LTHDT-18CLC6-Group17); kênh liên lạc chính của nhóm là Messenger và Discord.



## Mô tả các đối tượng/chức năng

#### *Đặc thù*

- Mọi thứ sẽ quay quanh đơn hàng (*order*). Một workflow điển hình trong hệ thống này sẽ bao gồm:
  - Người mua tìm kiếm, xem thông tin sản phẩm, và tạo đơn hàng
  - Người bán nhận đơn của người mua và quyết định chấp nhận/từ chối đơn:
    - Nếu chấp nhận: người bán sẽ chọn shipper và chọn giảm giá (0 - 100%)
    - Nếu từ chối: đơn hàng được đánh dấu "Hủy bởi người bán"
  - Người mua nhận lại đơn từ người bán và quyết định chấp nhận/từ chối đơn:
    - Nếu chấp nhận: đơn hàng được chuyển cho shipper
    - Nếu từ chối: đơn hàng được đánh dấu "Hủy bởi người mua"
  - Shipper nhận đơn hàng, giao hàng, đánh dấu hoàn thành và rút tiền từ người mua (chia cho cả người bán và shipper)
  - Ở mỗi tháng, người bán có thể thống kê (dựa trên các mặt hàng người bán có) số lượng mua, tổng doanh thu cho mỗi mặt hàng và tổng doanh thu cho cả tháng. Shipper cũng có thể thống kê tổng số đơn hàng và tổng số tiền thu được từ phí ship trong mỗi tháng
- Toàn bộ dữ liệu của chương trình được lưu vào một file plain text có dạng `JSON`, bao gồm 6 khóa chính:
  - `HASHES` chứa các chuỗi băm (SHA-2 256-bit) mật khẩu tài khoản
  - `ACCOUNTS` chứa thông tin cá nhân các tài khoản
  - `PRODUCTS` chứa thông tin các sản phẩm
  - `ORDERS` chứa các đơn hàng
  - `CATEGORIES` chứa các danh mục mặt hàng cùng với phí ship tương ứng
  - `COUNTERS` chứa các bộ đếm dùng để hỗ trợ tạo ID cho `Account`/`Product`/`Order` mới
- Các đối tượng trong hệ thống sẽ được bố trí vào những "provider" tương ứng. Những provider này sẽ đọc khóa tương ứng trong tệp `JSON`. Cụ thể hơn:
  - `Login Provider`: cung cấp tính năng đăng nhập cơ bản; yêu cầu khóa `HASHES`
  - `Account Provider`: chứa thông tin các tài khoản trong hệ thống; yêu cầu khóa `ACCOUNTS` và ba khóa `BUYER`, `SELLER` và  `SHIPPER` trong `COUNTERS`
  - `Product Provider`: chứa toàn bộ các Product trong hệ thống; yêu cầu khóa `CATEGORIES` và `PRODUCTS`
  - `Order Provider`: chứa toàn bộ các Order trong hệ thống; yêu cầu khóa `ORDERS`

 

#### `Account` *("tài khoản" trong hệ thống này)*

- Một superclass được `Buyer`, `Seller` và `Shipper` kế thừa.
- Thông tin cá nhân bao gồm:
  - ID
  - Họ và tên
  - Ngày tháng năm sinh, địa chỉ, email, số điện thoại
  - Một object `Wallet` (để quản lý tiền)
  - Mật khẩu đăng nhập (không được bao gồm trong class)
- Các thao tác chung trên tài khoản bao gồm:
  - Sửa thông tin cá nhân, thay đổi mật khẩu



#### `Wallet` *(ví)*

- Một ví tiền cơ bản, cho phép người sở hữu ví kiểm tra, nạp tiền (chỉ cho `Buyer`) và rút tiền (chỉ cho `Seller` và `Shippper`)



#### `Buyer` *(người mua)*

- Hoạt động đối với sản phẩm:
  - Tìm kiếm sản phẩm (theo tên/danh mục chung chung, theo `Seller` ID)
    - Những mặt hàng mang tính nhạy cảm sẽ được lọc ra nếu người mua dưới 18 tuổi (xét ngày tháng năm sinh để biết tuổi)
  - Xem chi tiết một sản phẩm
- Hoạt động đối với đơn hàng:
  - Xem và lọc danh sách các order theo:
    - Bản thân Buyer
    - Trạng thái đang chờ của order
  - Xem chi tiết một đơn hàng
  - Tạo đơn hàng
    - Tiền: kiểm tra trước khi cho phép tạo đơn
  - Chấp nhận đơn hàng (sau khi Seller chấp nhận)
  - Hủy đơn hàng (trước khi Seller chấp nhận)
  - Từ chối đơn hàng (sau khi Seller chấp nhận)
  - Đánh giá đơn hàng



#### `Seller ` *(người bán)*

- Ngoài thông tin cá nhân từ `Account` ra, tài khoản này còn thêm:
	
	- Chỉ số đánh giá (rating)
	
- Hoạt động đối với sản phẩm:

  - Liệt kê các sản phẩm
  - Tạo, sửa thông tin sản phẩm
  - Tồn kho/dọn kho sản phẩm

- Hoạt động đối với đơn hàng:
	
	- Xem và lọc danh sách các order theo:
	  - Bản thân Buyer
	  - Trạng thái đang chờ của order
	- Xem chi tiết một đơn hàng
	
	- Chấp nhận đơn hàng (từ Buyer)
	  - Nếu chấp nhận: chọn shipper và chọn giảm giá đơn hàng (0-100%)
	- Từ chối đơn hàng (từ Buyer)
	- Xem thống kê theo tháng



#### `Shipper` *(người giao hàng)*

- Hoạt động đối với đơn hàng
	
	- Xem và lọc danh sách các order theo:
	  - Bản thân Shipper
	  - Trạng thái đang chờ của order
  - Xem chi tiết một đơn hàng
  
  - Đánh dấu hoàn thành đơn hàng
  - Xem thống kê theo tháng



#### `Product` *(sản phẩm)*

Thông tin sản phẩm bao gồm:

- ID sản phẩm, tên, loại
- Số lượng
- Miêu tả ngắn gọn
- Phí vận chuyển



#### `Order` *(đơn hàng)*

Một đơn hàng gồm có:

- ID order
- ID, tên sản phẩm, số lượng
- ID, thông tin cho: Seller, Buyer, Shipper
- Hệ số giá tiền (để giảm giá)
- Ngày tạo đơn hàng, ngày hoàn tất đơn hàng
- Chi phí: phương thức thanh toán, phí vận chuyển
- Tình trạng:
	- Seller: đang chờ chấp nhận đơn
	- Seller: đã hủy đơn
	- Buyer: đang chờ chấp nhận đơn
	- Buyer: đã hủy đơn
	- Shipper: đang giao hàng
	- Đã hoàn thành

