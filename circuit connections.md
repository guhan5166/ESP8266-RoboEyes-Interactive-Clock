## Circuit Connections

### OLED Display (I2C)

| OLED Pin | ESP8266 Pin |
| -------- | ----------- |
| VCC      | 3.3V        |
| GND      | GND         |
| SDA      | D2 (GPIO4)  |
| SCL      | D1 (GPIO5)  |

---

### Touch Sensor

| Touch Sensor Pin | ESP8266 Pin |
| ---------------- | ----------- |
| VCC              | 3.3V        |
| GND              | GND         |
| OUT              | D6 (GPIO12) |

---

### Push Button

| Button Pin | ESP8266 Pin                |
| ---------- | -------------------------- |
| One Side   | D3 (GPIO0)                 |
| Other Side | GND (with pull-up enabled) |

> Internal pull-up is recommended for stable operation.

---
