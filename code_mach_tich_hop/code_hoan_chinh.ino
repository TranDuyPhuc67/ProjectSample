#include <Wire.h>                    // Giao tiep I2C
#include <Adafruit_GFX.h>            // Dieu khien man hinh OLED
#include <Adafruit_SSD1306.h>

#define NUT_BAM 18
#define CAM_BIEN_AM_THANH 34
#define CAM_BIEN_RUNG 35
#define TRIG_PIN 13
#define ECHO_PIN 12

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 man_hinh(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int che_do = -1; // -1: chưa chọn, 0: âm thanh, 1: rung, 2: khoảng cách

#define SO_DONG 5  // Số dòng cuộn được
String lich_su[SO_DONG];  // Mảng lưu các giá trị gần đây
int so_dong = 0;

void setup() {
  Serial.begin(115200);
  pinMode(NUT_BAM, INPUT_PULLUP);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  if (!man_hinh.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Khong tim thay OLED");
    while (true);
  }

  man_hinh.clearDisplay();
  man_hinh.setTextSize(1);
  man_hinh.setTextColor(SSD1306_WHITE);
  man_hinh.setCursor(0, 0);
  man_hinh.println("Khoi dong...");
  man_hinh.display();
}

void loop() {
  static bool da_nhan = false;

  // Nếu bấm nút lần đầu thì bắt đầu vào chế độ 0
  if (digitalRead(NUT_BAM) == LOW && !da_nhan) {
    if (che_do == -1) che_do = 0;        // Nếu đang ở màn hình khởi động thì chuyển sang chế độ đầu tiên
    else che_do = (che_do + 1) % 3;      // Nếu đã chọn thì chuyển tiếp chế độ
    da_nhan = true;
  }

  if (digitalRead(NUT_BAM) == HIGH) {
    da_nhan = false;
  }

  if (che_do == -1) {
    // Đang ở màn hình "Khoi dong...", không làm gì thêm
    delay(100);
    return;
  }

  // Đọc cảm biến tương ứng
  String tieu_de;
  String gia_tri_moi;


  if (che_do == 0) {
   int gia_tri = analogRead(CAM_BIEN_AM_THANH);
    tieu_de = "Cam bien am thanh";
    gia_tri_moi = String(gia_tri) + " (ADC)";
    Serial.println(gia_tri);
  } else if (che_do == 1) {
    int gia_tri = analogRead(CAM_BIEN_RUNG);
    tieu_de = "Cam bien rung";
    gia_tri_moi = String(gia_tri) + " (ADC)";
    Serial.println(gia_tri);
  } else if (che_do == 2) {
    long duration;
    float distance;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);
    distance = duration * 0.034 / 2;

    tieu_de = "Cam bien sieu am";
    gia_tri_moi = String(distance, 1) + " cm";
    Serial.println(distance);
  }

// Cập nhật dữ liệu cuộn
  if (so_dong < SO_DONG) {
    lich_su[so_dong++] = gia_tri_moi;
  } else {
    for (int i = 0; i < SO_DONG - 1; i++) {
      lich_su[i] = lich_su[i + 1];
    }
    lich_su[SO_DONG - 1] = gia_tri_moi;
  }

  // Hiển thị lên màn hình
  man_hinh.clearDisplay();
  man_hinh.setCursor(0, 0);
  man_hinh.println(tieu_de);
  // man_hinh.setCursor(0, 16);  // xuống dòng thứ 2 (16px)
  // man_hinh.println(gia_tri_moi);
  for (int i = 0; i < so_dong; i++) {
    man_hinh.setCursor(0, (i + 1) * 10);
    man_hinh.println(lich_su[i]);
  }
  man_hinh.display();
  delay(300);
}
