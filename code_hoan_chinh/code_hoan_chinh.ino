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

  // Đọc và hiển thị theo chế độ
  man_hinh.clearDisplay();
  man_hinh.setCursor(0, 0);

  if (che_do == 0) {
    int gia_tri = analogRead(CAM_BIEN_AM_THANH);
    man_hinh.println("Cam bien am thanh:");
    man_hinh.print(gia_tri);
    man_hinh.println(" (ADC)");
    Serial.print("Am thanh: ");
    Serial.print(gia_tri);
    Serial.println(" (ADC)");
  } else if (che_do == 1) {
    int gia_tri = analogRead(CAM_BIEN_RUNG);
    man_hinh.println("Cam bien rung:");
    man_hinh.print(gia_tri);
    man_hinh.println(" (ADC)");
    Serial.print("Rung: ");
    Serial.print(gia_tri);
    Serial.println(" (ADC)");
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

    man_hinh.println("Cam bien sieu am:");
    man_hinh.print(distance);
    man_hinh.println(" cm");

    Serial.print("Cam bien sieu am: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  man_hinh.display();
  delay(300);
}
