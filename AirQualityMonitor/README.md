# 🌫️ Air Quality Monitoring System

An IoT-based real-time air quality monitoring system using **NodeMCU ESP8266**, **SDS011 PM sensor**, **DHT11** temperature/humidity sensor, and a **0.96" OLED display**.

---

## 📷 Project Photos

| Hardware Setup | PM Sensor (SDS011) | OLED Display Output |
|---|---|---|
| NodeMCU on PCB | Nova PM Sensor | Live AQI Reading |

---

## 🔧 Hardware Components

| Component | Model | Purpose |
|---|---|---|
| Microcontroller | NodeMCU ESP8266 (ESP-12E) | Main controller + WiFi |
| PM Sensor | Nova SDS011 | Measures PM2.5 & PM10 |
| Temp/Humidity | DHT11 | Temperature & Humidity |
| Air Quality | MQ-135 | Gas/Air quality (analog) |
| Display | 0.96" OLED (I2C, SSD1306) | Shows live readings |
| PCB | Custom Air Quality Board | Sensor integration |

---

## 📌 Pin Connections

| Sensor | NodeMCU Pin |
|---|---|
| DHT11 Data | D4 |
| SDS011 TX → | D5 (RX) |
| SDS011 RX ← | D6 (TX) |
| MQ-135 Analog | A0 |
| OLED SDA | D2 |
| OLED SCL | D1 |

---

## 📚 Libraries Required

Install via Arduino Library Manager:

- `Adafruit SSD1306`
- `Adafruit GFX Library`
- `DHT sensor library` by Adafruit
- `SoftwareSerial` (built-in)

Board: **NodeMCU 1.0 (ESP-12E Module)** — Install ESP8266 board package in Arduino IDE.

---

## 🚀 How to Upload Code

1. Open `src/Air_quality_Monitering.ino` in Arduino IDE
2. Select board: **Tools → Board → NodeMCU 1.0 (ESP-12E Module)**
3. Select correct COM port
4. Install required libraries
5. Click **Upload**
6. Open Serial Monitor at **115200 baud** to view readings

---

## 📊 AQI Categories (based on PM2.5)

| PM2.5 (µg/m³) | AQI Status |
|---|---|
| 0 – 30 | 🟢 GOOD |
| 31 – 60 | 🟡 MODERATE |
| 61 – 90 | 🟠 POOR |
| 91 – 120 | 🔴 UNHEALTHY |
| > 120 | 🟣 HAZARDOUS |

---

## 📟 Sample Output (Serial Monitor)

```
--------------------
PM2.5 : 16.50
PM10  : 25.60
Temp  : 24.50
Hum   : 48.50
AQI   : GOOD
--------------------
PM2.5 : 15.60
PM10  : 26.00
Temp  : 24.50
Hum   : 48.40
AQI   : GOOD
```

---

## 📁 Project Structure

```
AirQualityMonitor/
├── src/
│   └── Air_quality_Monitering.ino   # Main Arduino sketch
├── docs/
│   └── Project_Report.docx          # Detailed project report
├── images/                          # Project photos
└── README.md
```

---

## 👨‍💻 Author

**[Your Name]**  
B.Tech / Diploma — [Your Branch]  
[Your College Name]  
Year: 2026

---

## 📄 License

This project is open-source under the [MIT License](LICENSE).
