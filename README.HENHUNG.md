# PROJECT II

## GIỚI THIỆU

__Đề bài__: Thiết kế và xây dựng thiết bị tích hợp cảm biến đo dao động cơ học, âm thanh và khoảng cách bằng siêu âm

__Sản phẩm:__
1. Đo cường độ âm thanh từ môi trường xung quanh bằng cảm biến âm thanh
2. Phát hiện rung động cơ học (va chạm, rung nhẹ) bằng cảm biến rung
3. Đo khoảng cách đến vật thể phía trước bằng cảm biến siêu âm
4. Hiển thị dữ liệu thời gian thực trên màn hình OLED
5. Chuyển chế độ hiển thị bằng nút bấm (âm thanh → rung → khoảng cách)
6. Gửi dữ liệu lên nền tảng IoT ThingSpeak để theo dõi từ xa qua internet
- Ảnh chụp minh họa:\
  ![Ảnh minh họa](https://soict.hust.edu.vn/wp-content/uploads/logo-soict-hust-1-1024x416.png)

## TÁC GIẢ

- Tên nhóm:......
- Thành viên trong nhóm
  |STT|Họ tên|MSSV|Công việc|
  |--:|--|--|--|
  |1|Nguyễn Hoàng Hải|20002987|hiện thị oled, hiệu ứng, và xử lý ngắt|

## MÔI TRƯỜNG HOẠT ĐỘNG

- Liệt kê module CPU/dev kit. Ví dụ ESP32 Dev Module, hoặc STM32F429-DISC.
- Liệt kê các kit, module được sử dụng: ví dụ: stm32 cảm biến...

## SO ĐỒ SCHEMATIC

_Cho biết cách nối dây, kết nối giữa các linh kiện_ 
Ví dụ có thể liệt kê dạng bảng
|STM32F429|Module ngoại vi|
|--|--|
|PA0|Nút bấm điều khiển trên board|
|PG13|Led báo trên board|
|PE2|MQ3 SCK|
|PE3|MQ3 SDA|

hoặc dạng ảnh:\
![image](https://github.com/user-attachments/assets/f15f7379-09bf-472a-b0d9-4de6d32a6ec0)

hoặc bất cứ dạng nào thể hiện được cách đấu nối giữa các linh kiện


### TÍCH HỢP HỆ THỐNG

- Mô tả các thành phần phần cứng và vai trò của chúng: máy chủ, máy trạm, thiết bị IoT, MQTT Server, module cảm biến IoT...
- Mô tả các thành phần phần mềm và vai trò của chúng, vị trí nằm trên phần cứng nào: Front-end, Back-end, Worker, Middleware...

### ĐẶC TẢ HÀM

- Giải thích một số hàm quan trọng: ý nghĩa của hàm, tham số vào, ra

  ```C
     /**
      *  Hàm tính ...
      *  @param  x  Tham số
      *  @param  y  Tham số
      */
     void abc(int x, int y = 2);
  ```
  
### KẾT QUẢ

- Các ảnh chụp với caption giải thích.
- Hoặc video sản phẩm
