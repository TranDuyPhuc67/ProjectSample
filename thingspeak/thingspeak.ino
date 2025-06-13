#include <WiFi.h>           // Thu vien de ket noi WiFi cho ESP32
#include <HTTPClient.h>     // Thu vien de gui yeu cau HTTP (GET/POST)

// Thong tin WiFi
const char* ssid = "Tdp";           // Ten mang WiFi
const char* password = "12345678a";      // Mat khau WiFi

// API key cua ThingSpeak de ghi du lieu
const char* thingspeakKey = "8J31HABKDOOBKO0T"; 

// Dia chi server ThingSpeak
const char* server = "http://api.thingspeak.com/update";

// Dinh nghia cac chan cam bien
#define CAM_BIEN_AM_THANH 34
#define CAM_BIEN_RUNG 35
#define TRIG_PIN 13
#define ECHO_PIN 12

void setup() {
  Serial.begin(115200); // Khoi dong cong Serial de debug

  pinMode(TRIG_PIN, OUTPUT);  // Chan TRIG cua cam bien sieu am la chan xuat
  pinMode(ECHO_PIN, INPUT);   // Chan ECHO la chan nhan

  // Ket noi WiFi
  WiFi.begin(ssid, password);
  Serial.print("Dang ket noi WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nDa ket noi WiFi!");
}

void loop() {
  // Doc du lieu tu cam bien
  int am_thanh = analogRead(CAM_BIEN_AM_THANH);  // Gia tri ADC cua cam bien am thanh
  int rung = analogRead(CAM_BIEN_RUNG);          // Gia tri ADC cua cam bien rung
  float kc = doKhoangCach();                     // Goi ham do khoang cach

  // Neu van ket noi WiFi thi gui du lieu len ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Tao URL voi cac truong du lieu field1, field2, field3
    String url = String(server) +
      "?api_key=" + thingspeakKey +
      "&field1=" + String(am_thanh) +
      "&field2=" + String(rung) +
      "&field3=" + String(kc);
      
    http.begin(url);                 // Khoi tao ket noi den server
    int httpCode = http.GET();      // Gui yeu cau GET
    if (httpCode > 0) {
      Serial.println("Du lieu da gui thanh cong!");
    } else {
      Serial.println("Loi khi gui!");
    }
    http.end();                     // Dong ket noi
  } else {
    Serial.println("Mat ket noi WiFi!");
  }

  delay(2000); // Cho 20 giay roi moi gui lan tiep theo (ThingSpeak gioi han 15s/lan)
}

// Ham do khoang cach bang cam bien sieu am
float doKhoangCach() {
  digitalWrite(TRIG_PIN, LOW);       // Tao xung bat dau
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);      // Gui xung cao 10us
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH); // Do thoi gian song phan xa quay ve
  float distance = duration * 0.034 / 2.0;  // Tinh khoang cach tu thoi gian (don vi: cm)
  return distance;
}
