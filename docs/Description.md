# Hệ thống quản lý bán hàng điện tử

Nhóm 19, môn Lập trình hướng đối tượng (OOP)



## Giới thiệu sơ lược

- Một hệ thống quản lý bán hàng điện tử cơ bản (list các shop, list các sản phẩm và list các order toàn cục) viết bằng C++, không có giao diện đồ họa
- Mục tiêu: hiểu rõ hơn và cố gắng áp dụng những khái niệm/mô hình lập trình trong OOP; tìm hiểu về hệ thống quản lý `git` và workflow xoay quanh `git`
- [GitHub repo](https://github.com/84436/LTHDT-18CLC6-Group17) (hiện tại đang `private`); kênh liên lạc chính của nhóm là nhóm Messenger và Discord



## Mô tả các đối tượng/chức năng

#### Đặc thù

- Mọi thứ sẽ quay quanh order (“người mua tạo order, người bán nhận và đồng ý/từ chối order, shipper nhận order và kiểm tra người mua đã nhận hàng chưa, người mua nhận hàng và cảm thấy hạnh phúc.”)
- Mỗi ngày sẽ có một transaction list giữ các order. Số lượng order trong cái list chỉ có thể tăng thêm (không có bất kì bên nào được quyền can thiệp/sửa vào list này; chỉ có admin có quyền xem list). List cũ sẽ được archived sau khi hết một ngày và list mới sẽ được tạo cho ngày hôm sau.



#### Lớp `Admin`

1. Tạo, sửa, xóa Buyer, Seller, Product, Shipper tùy ý

2. Tìm và xem lại transaction list của ngày hôm nay/một ngày nào đó

    

#### Lớp `Person` ("tài khoản" trong hệ thống này)

- Một superclass để có thể kế thừa ra `Buyer`, `Seller` và `Shipper`
- Thông tin cá nhân bao gồm:
  - ID
  - Họ và tên
  - Một object `Wallet` (để quản lý tín dụng)
  - Mật khẩu đăng nhập (không được bao gồm trong class)



#### Lớp `Wallet` (ví)

- Một ví tiền cơ bản, cho phép người sở hữu ví kiểm tra, nạp và tiêu dùng tín dụng



#### Lớp `Seller ` (người bán)

- Ngoài thông tin cá nhân từ `Person` ra, tài khoản này còn thêm:
	- Danh mục sản phẩm: tạo, edit (thông tin, tag, stock), xóa
	- Hành động xóa tài khoản
	
- Hoạt động đối với đơn hàng
	- Xử lí: chấp nhận đơn hàng/hủy đơn
		- Nếu chấp nhận đơn: sản phẩm sẽ đến tay shipper lập tức
		- Nếu hủy đơn: nêu rõ lý do
	- Giảm giá đơn hàng (nếu có)
	- Sửa tình trạng đơn hàng (sản phẩm đã đến tay Shipper): tự động sửa ngay khi chấp nhận đơn
	
	  
	

#### Lớp `Buyer` (người mua)

- Ngoài thông tin cá nhân từ `Person` ra, tài khoản này còn thêm:
	- Hành động xóa tài khoản
- Hoạt động đối với đơn hàng/sản phẩm
	- Tìm kiếm sản phẩm (theo tên, theo tag)
	
	- Tín dụng: check trước khi cho phép tạo đơn; chọn phương thức thanh toán (chuyển khoản/COD)
	
	- Kiểm tra độ uy tín của Buyer (người mua sau khi mua sẽ vote up hoặc down, sau đó chia tỉ lệ ra rate legit)
	
	- Hủy đơn (chỉ được phép hủy trước khi Seller chấp nhận)
	
	- Kiểm tra tình trạng đơn hàng
	
	    
	  
#### Lớp `Shipper` (người giao hàng)
- Ngoài thông tin cá nhân từ `Person` ra, tài khoản này còn thêm:
	- Hành động xóa tài khoản
- Hoạt động đối với đơn hàng
	- Xem thông tin: Seller, Buyer, giá (nếu ship COD), phí vận chuyển
	
	- Sửa tình trạng đơn hàng (sản phẩm đã tới tay Buyer chưa? Nếu đã tới, thông báo trừ tiền của Buyer)
	
    

#### Lớp `Product` (sản phẩm)

Thông tin sản phẩm bao gồm:

- ID sản phẩm, tên, loại
- Số lượng
- Miêu tả ngắn gọn
- Phí vận chuyển



#### Lớp `Order` (đơn hàng)

Một đơn hàng gồm có:

- ID order
- ID, tên sản phẩm, số lượng
- ID, thông tin cho: Seller, Buyer, Shipper
- Chi phí: phương thức thanh toán, phí vận chuyển, giá đã thỏa thuận (aka giá bán; Buyer-Seller)
- Tình trạng:
	- Seller: đang chờ chấp nhận đơn
	- Seller: đã hủy đơn (nêu rõ lý do)
	- Shipper: đang vận chuyển
	- Buyer: đã nhận

