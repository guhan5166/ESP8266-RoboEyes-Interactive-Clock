# ESP8266 OLED Interactive Clock with RoboEyes

A compact and professional embedded systems project using **ESP8266**, **SSD1306 OLED**, **FluxGarage RoboEyes**, a **touch sensor**, and a **push button** to demonstrate interactive graphics, mood control, and time display.

This project showcases how user inputs dynamically affect OLED animations and system behavior.

---

## Key Features

* Animated OLED eyes using **FluxGarage RoboEyes**
* Touch-based **mood interaction**
* Push button to display **time and date**
* 12-hour time format with AM/PM
* Date format: **DD-MM-YY**
* Automatic return to animation mode
* Smooth rendering with correct screen alignment
* Optimized for ESP8266 performance

---

## Hardware Used

* ESP8266 (NodeMCU)
* 0.96″ OLED Display (SSD1306, 128×64, I2C)
* Touch Sensor (TTP223)
* 10kΩ Resistor
* Jumper Wires
* Breadboard

---

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

## Software & Libraries

**IDE:** Arduino IDE
**Board Package:** ESP8266 by Espressif

**Libraries Used:**

* Adafruit GFX
* Adafruit SSD1306
* FluxGarage RoboEyes

---

## System Behavior

### Default Mode

* RoboEyes animation runs continuously
* Auto blinking and idle movements enabled

### Touch Interaction

* Touch sensor changes **eye mood**
* Example moods:

  * HAPPY
  * TIRED
  * ANGRY
  * DEFAULT

### Button Interaction

* Press button to display clock
* Time and date shown for **3 seconds**
* System automatically returns to animation mode

---

## Display Format

```
10:59 AM
08-02-26
```

Optimized for 128×64 OLED with correct width, height, and alignment.

---

## Author

**Guhan R**

