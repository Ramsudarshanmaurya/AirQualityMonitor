/*
  ============================================================
  Air Quality Monitoring System
  ============================================================
  Hardware   : NodeMCU ESP8266 (ESP-12E)
  Sensors    : SDS011 (PM2.5 / PM10), DHT11 (Temperature/Humidity),
               MQ-135 (Air Quality / Gas)
  Display    : 0.96" OLED (I2C, SSD1306)

  Description:
  Reads particulate matter (PM2.5, PM10), temperature, humidity
  and gas concentration in real time, calculates an AQI status
  based on CPCB PM2.5 standards, and displays the results on
  an OLED screen as well as the Serial Monitor.

  Author     : Ramsudarshan Maurya
  Branch     : Electronics & Communication Engineering (ECE)
  Trained at : Uniconverge Technologies Pvt. Ltd., Noida
  Date       : June 2026
  ============================================================
*/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <SoftwareSerial.h>

// -------- Pin Definitions --------
#define DHTPIN     D4       // DHT11 Data Pin
#define DHTTYPE    DHT11
#define SDS_RX     D5       // SDS011 TX -> NodeMCU RX
#define SDS_TX     D6       // SDS011 RX -> NodeMCU TX
#define MQ135_PIN  A0       // MQ-135 Analog Pin

// -------- OLED Config --------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET   -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// -------- Sensor Objects --------
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial sdsSerial(SDS_RX, SDS_TX);

// -------- Global Variables --------
float pm25 = 0, pm10 = 0;
float temp = 0, hum = 0;
int   airQualityRaw = 0;
String aqiStatus = "GOOD";

// -------- AQI Calculation (based on CPCB PM2.5 standards) --------
String getAQIStatus(float pm25Val) {
  if (pm25Val <= 30.0)       return "GOOD";
  else if (pm25Val <= 60.0)  return "MODERATE";
  else if (pm25Val <= 90.0)  return "POOR";
  else if (pm25Val <= 120.0) return "UNHEALTHY";
  else                       return "HAZARDOUS";
}

// -------- Read SDS011 (PM2.5 / PM10) --------
// Data frame: 10 bytes | Header 0xAA ... Tail 0xAB
bool readSDS011() {
  byte buf[10];
  if (sdsSerial.available() >= 10) {
    if (sdsSerial.read() == 0xAA) {
      buf[0] = 0xAA;
      for (int i = 1; i < 10; i++) buf[i] = sdsSerial.read();
      if (buf[9] == 0xAB) {
        pm25 = ((buf[3] * 256) + buf[2]) / 10.0;
        pm10 = ((buf[5] * 256) + buf[4]) / 10.0;
        return true;
      }
    }
  }
  return false;
}

// -------- Display Data on OLED --------
void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("PM2.5 :"); display.print(pm25, 1); display.println(" ug");

  display.setCursor(0, 12);
  display.print("PM10  :"); display.print(pm10, 1); display.println(" ug");

  display.setCursor(0, 24);
  display.print("Temp  :"); display.print(temp, 1); display.print(" C");

  display.setCursor(0, 36);
  display.print("Hum   :"); display.print(hum, 1); display.print(" %");

  display.setCursor(0, 52);
  display.print("AQI   :"); display.print(aqiStatus);

  display.display();
}

// -------- Print to Serial Monitor --------
void printSerial() {
  Serial.println("--------------------");
  Serial.print("PM2.5 : "); Serial.println(pm25);
  Serial.print("PM10  : "); Serial.println(pm10);
  Serial.print("Temp  : "); Serial.println(temp);
  Serial.print("Hum   : "); Serial.println(hum);
  Serial.print("AQI   : "); Serial.println(aqiStatus);
}

// -------- Setup --------
void setup() {
  Serial.begin(115200);
  sdsSerial.begin(9600);
  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found!");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 20);
  display.println("Air Quality Monitor");
  display.println("   Initializing...");
  display.display();
  delay(2000);
}

// -------- Main Loop --------
void loop() {
  // Read DHT11
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (!isnan(t)) temp = t;
  if (!isnan(h)) hum  = h;

  // Read SDS011
  readSDS011();

  // Read MQ-135
  airQualityRaw = analogRead(MQ135_PIN);

  // Calculate AQI Status
  aqiStatus = getAQIStatus(pm25);

  // Update Display & Serial
  updateDisplay();
  printSerial();

  delay(2000);
}
