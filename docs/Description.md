# Hệ thống quản lý bán hàng điện tử

## Thông tin nhóm

* Nhóm 19 môn Lập trình Hướng Đối tượng
* Thành viên:
  * 18127221 - Bùi Văn Thiện
  * 18127185 - Bùi Vũ Hiếu Phụng
  * 18127080 - Kiều Vũ Minh Đức
  * 18127164 - Huỳnh Thiện Nhân

## Sơ lược

### Vấn đề

* Cuộc sống phát triển đi cùng với đó là nhu cầu kinh doanh, buôn bán ngày càng tăng cao với các hình thức kinh doanh khác nhau. Bên cạnh việc mở các cửa hàng kinh doanh theo kiểu truyền thống với lợi thế về mặt bằng, ngày càng có nhiều doanh nghiệp đi theo hướng phát triển hoạt động bán hàng trực tuyến, trong đó nổi bật nhất là bán hàng trực tuyến.
* Chính vì vậy, những sàn giao dịch điện tử đã ra đời như Shoppe, Lazada, Tiki,... Để hoạt động tốt, những trang thương mại này phụ thuộc nhiều vào việc lưu trữ và xử lí cơ sở dữ liệu. Đó là ý tưởng để nhóm em thực hiện đồ án này. 

### Giới thiệu

- Một hệ thống quản lý bán hàng điện tử cơ bản, được viết bằng C++, không có giao diện đồ họa. Hệ thống bao gồm những đối tượng cơ bản cần thiết như cửa hàng, sản phẩm, đơn hàng,...
- Mục tiêu: Hiểu rõ và áp dụng những kiến thức cơ bản và nâng cao trong Lập trình Hướng Đối tượng. Đồng thời luyện tập tổ chức nhóm, tổ chức dự án, tìm hiểu về hệ thống quản lý `git` và workflow xoay quanh `git`.
- [GitHub repo](https://github.com/84436/LTHDT-18CLC6-Group17) (hiện tại đang `private`); kênh liên lạc chính của nhóm là nhóm Messenger và Discord.



## Mô tả các đối tượng/chức năng

#### Đặc thù

Mọi thứ sẽ quay quanh đơn hàng (*order*) (“người mua tạo đơn hàng, người bán nhận và đồng ý/từ chối đơn, shipper nhận đơn và kiểm tra người mua đã nhận hàng chưa, người mua nhận hàng.”)

 

#### `Person` ("tài khoản" trong hệ thống này)

- Một superclass được `Buyer`, `Seller` và `Shipper` kế thừa.
- Thông tin cá nhân bao gồm:
  - ID
  - Họ và tên
  - Ngày tháng năm sinh, địa chỉ, email, số điện thoại
  - Một object `Wallet` (để quản lý tiền)
  - Mật khẩu đăng nhập (không được bao gồm trong class)
- Các thao tác chung trên tài khoản bao gồm:
  - Sửa thông tin cá nhân, thay đổi mật khẩu và xóa tài khoản
  - Xem và lọc danh sách các order theo:
    - Bản thân Seller/Buyer/Shipper (VD: nếu Seller chọn xem danh sách order, chỉ có những order có liên quan đến Seller nói trên sẽ được list ra)
    - (Tùy chọn) Trạng thái đơn hàng hoặc ngày tạo đơn hàng
    - Danh sách order sau khi được lọc sẽ được lưu vào một vector tạm (để bản thân Buyer/Seller/Shipper có thể chọn ra order cần thiết để thao tác trên nó)



#### `Admin`

Một tài khoản đặc biệt kế thừa từ `Person`, có thông tin cá nhân hạn chế (VD: không ví, không ngày tháng năm sinh, v.v.) và có quyền:

- Tạo, sửa, xóa `Buyer` và `Seller`
- Xem và xóa `Product`
- Xem *tất cả* các đơn hàng trong hệ thống và lọc theo ngày



#### `Wallet` (ví)

- Một ví tiền cơ bản, cho phép người sở hữu ví kiểm tra, nạp và tiêu dùng tiền



#### `Seller ` (người bán)

- Ngoài thông tin cá nhân từ `Person` ra, tài khoản này còn thêm:
	
	- Danh sách các `Shipper` và hành động tạo, xóa shipper
	- Chỉ số đánh giá (rating)
	
- Hoạt động đối với sản phẩm:

  - Tạo, sửa thông tin và xóa sản phẩm

- Hoạt động đối với đơn hàng:
	- Chấp nhận/từ chối đơn hàng
		- Nếu chấp nhận: trạng thái của đơn hàng sẽ được thay đổi thành "chờ `Shipper` giao hàng"
		- Nếu từ chối: ghi lại lý do
	- Giảm giá đơn hàng (nếu có)
	
	  
	

#### `Buyer` (người mua)

- Hoạt động đối với sản phẩm:
	
	- Tìm kiếm sản phẩm (theo tên, theo danh mục)
	  - Những mặt hàng mang tính nhạy cảm sẽ được lọc ra nếu người mua dưới 18 tuổi (xét ngày tháng năm sinh để biết tuổi)
	
- Hoạt động đối với đơn hàng:
	
	- Tạo đơn hàng
		
		- Tiền: kiểm tra trước khi cho phép tạo đơn; chọn phương thức thanh toán (chuyển khoản/COD)
		
	- Kiểm tra độ uy tín của Buyer (người mua sau khi mua sẽ vote up hoặc down, sau đó chia tỉ lệ ra độ uy tín)
	
	- Hủy đơn (chỉ được phép hủy trước khi Seller chấp nhận)
	
	- Kiểm tra tình trạng đơn hàng
	
	    
	
#### `Shipper` (người giao hàng)
- Hoạt động đối với đơn hàng
	- Xem thông tin: Seller, Buyer, giá (nếu ship COD), phí vận chuyển
	
	- Sửa tình trạng đơn hàng (sản phẩm đã tới tay Buyer chưa? Nếu đã tới, thông báo trừ tiền của Buyer)
	
    

#### `Product` (sản phẩm)

Thông tin sản phẩm bao gồm:

- ID sản phẩm, tên, loại
- Số lượng
- Miêu tả ngắn gọn
- Phí vận chuyển



#### `Order` (đơn hàng)

Một đơn hàng gồm có:

- ID order
- ID, tên sản phẩm, số lượng
- ID, thông tin cho: Seller, Buyer, Shipper
- Hệ số giá tiền (để giảm giá)
- Ngày tạo đơn hàng, ngày hoàn tất đơn hàng
- Chi phí: phương thức thanh toán, phí vận chuyển
- Tình trạng:
	- Seller: đang chờ chấp nhận đơn
	- Seller: đã hủy đơn (+ lý do)
	- Shipper: đang vận chuyển
	- Buyer: đã nhận

