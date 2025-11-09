/*******************************************************
 *  Project: IoT-Based IV Bag Monitoring and Alert System
 *  Hardware: ESP32 + HX711 + LCD + Servo + Buzzer
 *  Cloud: Blynk IoT Cloud
 *  Author: [Your Name]
 *  Description:
 *   - Monitors IV fluid level using a load cell (HX711)
 *   - Displays weight & volume on LCD
 *   - Sends alerts via Blynk Cloud when fluid is low
 *   - Activates buzzer and servo indicator locally
 *******************************************************/
// fill your blynk cloud credentials
#define BLYNK_TEMPLATE_ID   "************"
#define BLYNK_TEMPLATE_NAME "************"
#define BLYNK_AUTH_TOKEN    "************"

#define BLYNK_PRINT Serial

#include <ESP32Servo.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin Configuration 
#define LOADCELL_DOUT_PIN  19
#define LOADCELL_SCK_PIN   18
#define BUZZER_PIN         23
#define SERVO_PIN          14
#define LCD_ADDR           0x27


LiquidCrystal_I2C lcd(LCD_ADDR, 16, 2);
HX711 scale(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
Servo servo1;

 
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "************";//enter password and wifi name
char pass[] = "************";


float calibration_factor = 118.542;

int servoClosed = 180;
int servoOpen   = 0;


void setup() {
  Serial.begin(9600);
  Wire.begin(21, 22);

  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Welcome");
  lcd.setCursor(2, 1);
  lcd.print("ESP32 Ready!");
  delay(1000);
  lcd.clear();

  pinMode(BUZZER_PIN, OUTPUT);
  servo1.attach(SERVO_PIN);

  scale.set_scale(calibration_factor);
  scale.tare();  // Reset to zero

  Blynk.begin(auth, ssid, pass);
  Serial.println("Setup complete. Monitoring started...");
}


void loop() {
  Blynk.run();
  measureWeight();
}


void measureWeight() {
  int value = scale.get_units();
  int percent = map(value, 0, 600, 0, 100);
  percent = constrain(percent, 0, 100);

  Serial.print("Weight: ");
  Serial.print(value);
  Serial.print(" g | Level: ");
  Serial.print(percent);
  Serial.println("%");

  String line  = "LEVEL: " + String(value) + "ml";
  String line2 = "IS: " + String(value) + "ml";

  // --- Error handling for negative readings ---
  if (value < 0) {
    scale.tare();
    return;
  }

  // --- Empty Bottle Condition ---
  if (value < 10) {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("PLACE THE");
    lcd.setCursor(4, 1);
    lcd.print("BOTTLE");
    servo1.write(servoClosed);
  }

  // --- 25% Level Alert ---
  else if (value > 90 && value < 120) {
    Blynk.logEvent("iv_alert", "IV Bottle is too LOW");
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("ALERT!! BOTTLE");
    lcd.setCursor(1, 1);
    lcd.print(line);

    digitalWrite(BUZZER_PIN, HIGH);
    delay(1000);
    digitalWrite(BUZZER_PIN, LOW);
    delay(1000);

    Serial.println("Bottle running low (25%)");
    servo1.write(servoOpen);
  }

  // --- 50% Level ---
  else if (value > 200 && value < 320) {
    Blynk.logEvent("iv_alert", "IV Bottle is 30%");
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Bottle Level");
    lcd.setCursor(4, 1);
    lcd.print(line2);
    servo1.write(servoClosed);
  }

  // --- 75% Level ---
  else if (value > 330 && value < 420) {
    Blynk.logEvent("iv_alert", "IV Bottle is 60%");
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Bottle Level");
    lcd.setCursor(4, 1);
    lcd.print(line2);
    servo1.write(servoClosed);
  }

  // --- Send data to Blynk Dashboard ---
  Blynk.virtualWrite(V0, value);   // Send raw weight
  Blynk.virtualWrite(V1, percent); // Send level percentage

  delay(1000);
  lcd.clear();
}
