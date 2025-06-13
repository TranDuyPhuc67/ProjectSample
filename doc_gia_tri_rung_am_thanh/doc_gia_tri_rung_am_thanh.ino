#define CAM_BIEN_AM_THANH 35
#define CAM_BIEN_RUNG     34

void setup() {
  Serial.begin(115200);
}

void loop() {
  int gia_tri_am_thanh = analogRead(CAM_BIEN_AM_THANH);
  int gia_tri_rung     = analogRead(CAM_BIEN_RUNG);

  Serial.print("Am thanh: ");
  Serial.print(gia_tri_am_thanh);
  Serial.print(" | Rung: ");
  Serial.println(gia_tri_rung);

  delay(100); // Đọc mỗi 100ms
}
