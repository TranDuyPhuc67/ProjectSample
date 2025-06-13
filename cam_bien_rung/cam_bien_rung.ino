#define VIBRATION_SENSOR_PIN 34  // Chân đọc tín hiệu từ cảm biến rung

void setup() {
    Serial.begin(115200);  // Khởi động Serial với baudrate 115200
}

void loop() {
    int vibrationValue = analogRead(VIBRATION_SENSOR_PIN); // Đọc dữ liệu từ cảm biến rung
    Serial.println(vibrationValue); // Gửi dữ liệu lên Serial Plotter

    delay(10); // Độ trễ nhỏ để cập nhật dữ liệu nhanh
}
