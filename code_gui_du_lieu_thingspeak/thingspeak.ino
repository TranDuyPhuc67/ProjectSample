#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "HaiLong";
const char* password = "24112606";
const char* thingspeakKey = "U5LJ7SYIBMNIZNDW";
const char* server = "http://api.thingspeak.com/update";

#define CAM_BIEN_AM_THANH 34
#define CAM_BIEN_RUNG 35
#define TRIG_PIN 13
#define ECHO_PIN 12

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  WiFi.begin(ssid, password);
  Serial.print("Dang ket noi WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nDa ket noi WiFi!");
}

void loop() {
  int am_thanh = analogRead(CAM_BIEN_AM_THANH);
  int rung = analogRead(CAM_BIEN_RUNG);
  float kc = doKhoangCach();

  Serial.print("Am thanh: "); Serial.print(am_thanh);
  Serial.print(" | Rung: "); Serial.print(rung);
  Serial.print(" | Khoang cach: "); Serial.print(kc);
  Serial.println(" cm");

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) +
                 "?api_key=" + thingspeakKey +
                 "&field1=" + String(am_thanh) +
                 "&field2=" + String(rung) +
                 "&field3=" + String(kc, 2);  // lấy 2 chữ số thập phân

    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.println(" --> Du lieu da gui len ThingSpeak!");
    } else {
      Serial.print(" --> Loi khi gui. Ma loi: ");
      Serial.println(httpCode);
    }

    http.end();
  } else {
    Serial.println("Mat ket noi WiFi!");
  }

  delay(2000); 
}

float doKhoangCach() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2.0;
  return distance;
}
