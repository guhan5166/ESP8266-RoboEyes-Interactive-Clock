#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <FluxGarage_RoboEyes.h>
#include <ESP8266WiFi.h>
#include <time.h>

// -------- OLED CONFIG --------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RoboEyes<Adafruit_SSD1306> roboEyes(display);

// -------- INPUTS --------
#define TOUCH_PIN  D6
#define BUTTON_PIN D5

// -------- STATE CONTROL --------
bool showClock = false;
unsigned long clockStartTime = 0;

// -------- MOOD --------
uint8_t moodIndex = 0;
bool lastTouchState = LOW;

// -------- TIME --------
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 19800;   // IST (India)
const int daylightOffset_sec = 0;

void setup() {
  Serial.begin(9600);

  pinMode(TOUCH_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1);
  }

  roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100);
  roboEyes.setAutoblinker(ON, 3, 2);
  roboEyes.setIdleMode(ON, 2, 2);

  // ---- WiFi ONLY for time ----
  WiFi.begin("Redmi", "9025817747");
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {

  // -------- BUTTON: CLOCK MODE --------
  if (digitalRead(BUTTON_PIN) == LOW && !showClock) {
    showClock = true;
    clockStartTime = millis();
    display.clearDisplay();
  }

  if (showClock) {
    showDateTime();

    if (millis() - clockStartTime >= 3000) {
      showClock = false;
      display.clearDisplay();
    }
    return;   // Skip pet mode while clock is showing
  }

  // -------- PET MODE --------
  roboEyes.update();

  bool touchState = digitalRead(TOUCH_PIN);

  if (touchState == HIGH && lastTouchState == LOW) {
    moodIndex = (moodIndex + 1) % 4;

    switch (moodIndex) {
      case 0:
        roboEyes.setMood(DEFAULT);
        break;
      case 1:
        roboEyes.setMood(HAPPY);
        roboEyes.anim_laugh();
        break;
      case 2:
        roboEyes.setMood(TIRED);
        break;
      case 3:
        roboEyes.setMood(ANGRY);
        roboEyes.anim_confused();
        break;
    }
  }

  lastTouchState = touchState;
}

// -------- CLOCK FUNCTION --------
void showDateTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return;

  int hour = timeinfo.tm_hour;
  bool isPM = false;

  if (hour >= 12) {
    isPM = true;
    if (hour > 12) hour -= 12;
  }
  if (hour == 0) hour = 12;

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // ---- TIME ----
  display.setTextSize(2);
  display.setCursor(16, 10);
  display.printf("%02d:%02d %s",
                 hour,
                 timeinfo.tm_min,
                 isPM ? "PM" : "AM");

  // ---- DATE ----
  display.setTextSize(2);
  display.setCursor(18, 40);
  display.printf("%02d-%02d-%02d",
                 timeinfo.tm_mday,
                 timeinfo.tm_mon + 1,
                 (timeinfo.tm_year + 1900) % 100);

  display.display();
}

