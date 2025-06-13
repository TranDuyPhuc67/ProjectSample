#define SOUND_SENSOR_PIN 35  // Chân đọc tín hiệu từ cảm biến âm thanh

void setup() {
    Serial.begin(115200);  // Khởi động Serial với baudrate 115200
}

void loop() {
    int soundValue = analogRead(SOUND_SENSOR_PIN); // Đọc dữ liệu từ cảm biến âm thanh
    Serial.println(soundValue); // Gửi dữ liệu lên Serial Plotter

    delay(10); // Độ trễ nhỏ để cập nhật dữ liệu nhanh
}
