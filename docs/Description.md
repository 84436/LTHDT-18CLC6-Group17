# Hệ thống quản lý bán hàng điện tử

-- Nhóm 19 OOP



## Mục tiêu chính

- Mọi thứ sẽ quay quanh order (“người mua tạo order, người bán nhận và đồng ý/từ chối order, shipper nhận order và kiểm tra người mua đã nhận hàng chưa, người mua nhận hàng và cảm thấy hạnh phúc.”)
	
- Mỗi ngày sẽ có một transaction list giữ các order. Số lượng order trong cái list chỉ có thể tăng thêm (không có bất kì bên nào được quyền can thiệp/sửa vào list này; chỉ có admin có quyền xem list). List cũ sẽ được archived sau khi hết một ngày và list mới sẽ được tạo cho ngày hôm sau.

    

## Giao diện

```
Giao diện dòng lệnh; đăng nhập/đăng xuất; hiện menu tương ứng cho từng role
```



## ADMIN

1. Tạo, sửa, xóa Buyer, Seller, Product, Shipper tùy ý

2. Tìm và xem lại transaction list của ngày hôm nay/một ngày nào đó

    

## SELLER

- Tài khoản (người bán)
	- ID
	- Thông tin cá nhân: edit
	- Tín dụng (xiền): kiểm tra
	- Sản phẩm: tạo, edit (thông tin, tag, stock), xóa
	- Ngừng bán (xóa tài khoản + đốt xiền)
	
- Đơn hàng (nhận đơn hàng)
	- Xử lí: chấp nhận đơn hàng/hủy đơn
		- Nếu chấp nhận đơn: sản phẩm sẽ đến tay shipper lập tức
		- Nếu hủy đơn: nêu rõ lý do
	- Giảm giá đơn hàng (nếu có s a l e s)
	- Sửa tình trạng đơn hàng (sản phẩm đã đến tay Shipper): tự động sửa ngay khi chấp nhận đơn
	
- Set up sale (hmmm)

    

## BUYER

- Tài khoản (người mua)
	- ID
	- Thông tin cá nhân: edit
	- Tín dụng (xiền): kiểm tra, bơm thêm
	- Ngừng mua (xóa tài khoản + đốt xiền)
- Đơn hàng (tạo đơn hàng)
	- Note: 1 sản phẩm x số lượng = 1 đơn hàng; tín dụng chỉ bị trừ sau khi đã nhận hàng (“cháo múc rồi tiền mới trao”)
	
	- Tìm kiếm sản phẩm (theo tên, theo tag)
	
	- Tín dụng: check trước khi cho phép tạo đơn; chọn phương thức thanh toán (chuyển khoản/COD)
	
	- Kiểm tra độ uy tín của Buyer (người mua sau khi mua sẽ vote up hoặc down, sau đó chia tỉ lệ ra rate legit)
	
	- Hủy đơn (chỉ được phép hủy trước khi Seller chấp nhận)
	
	- Kiểm tra tình trạng đơn hàng
	
	    
	  
## SHIPPER
- Tài khoản (người vận chuyển)
	- ID
	- Thông tin cá nhân
	- Không muốn phận làm shipper nữa (xóa tài khoản)
- Đơn hàng
	- Xem thông tin đơn hàng: Seller, Buyer, giá (nếu ship COD), phí vận chuyển
	
	- Sửa tình trạng đơn hàng (sản phẩm đã tới tay Buyer chưa?)
	
    

## PRODUCT

- ID sản phẩm, tên, loại

- Số lượng

- Miêu tả ngắn gọn

- Phí vận chuyển

  

## `-->` ORDER `<--`
- ID order
- ID, tên sản phẩm
- ID, thông tin cho: Seller, Buyer, Shipper
- Chi phí: phương thức thanh toán, phí vận chuyển, giá đã thỏa thuận (aka giá bán; Buyer-Seller)
- Tình trạng:
	- Seller: đang chờ chấp nhận đơn
	- Seller: đã hủy đơn (nêu rõ lý do)
	- Shipper: đang vận chuyển
	- Buyer: đã nhận

