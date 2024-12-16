#include <Arduino.h>

const int potPin = 36;  // ขา 36 ของ ESP32 (ADC1)
const int ledPins[] = {23, 19, 18, 5, 17, 16, 4, 0};  // ขา 23, 19, 18, 5, 17, 16, 4, 0 สำหรับ LED

void setup() {
  // กำหนดขาของ LED ให้เป็น output
  for (int i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // เริ่มการเชื่อมต่อซีเรียล
  Serial.begin(115200);
}

void loop() {
  // อ่านค่า ADC จากพอตเทนชิออมิเตอร์ (P1) ที่เชื่อมต่อกับขา 36
  int sensorValue = analogRead(potPin);  
  float voltage = sensorValue * (3.3 / 4095.0);  // แปลงค่า ADC เป็นแรงดัน (0-3.3V)

  // แสดงค่าแรงดันบน serial monitor
  Serial.print("Voltage: ");
  Serial.println(voltage);

  // ควบคุมการเปิด/ปิด LED ตามค่าแรงดัน
  if (voltage >= 0.0 && voltage < 0.9) {
    // หมุน P1 ที่มีค่าแรงดัน 0-0.9V ให้ LED ทุกดวงดับ
    for (int i = 0; i < 8; i++) {
      digitalWrite(ledPins[i], LOW);
    }
  }
  else if (voltage >= 1.0 && voltage < 2.0) {
    // หมุน P1 ที่มีค่าแรงดัน 1-2V ให้ LED หลอดที่ 1-3 ติด
    for (int i = 0; i < 3; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
    // LED ที่เหลือดับ
    for (int i = 3; i < 8; i++) {
      digitalWrite(ledPins[i], LOW);
    }
  }
  else if (voltage >= 2.0 && voltage < 3.0) {
    // หมุน P1 ที่มีค่าแรงดัน 2-3V ให้ LED หลอดที่ 1-5 ติด
    for (int i = 0; i < 5; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
    // LED ที่เหลือดับ
    for (int i = 5; i < 8; i++) {
      digitalWrite(ledPins[i], LOW);
    }
  }
  else if (voltage >= 3.0) {
    // หมุน P1 ที่มีค่าแรงดัน 3V ขึ้นไปให้ LED ทุกดวงติด
    for (int i = 0; i < 8; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
  }

  delay(100);  // หน่วงเวลาเล็กน้อย เพื่อไม่ให้การอ่านค่ามีการเปลี่ยนแปลงเร็วเกินไป
}
