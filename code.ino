#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define BMP280_ADDRESS 0x76
#define OLED_ADDRESS 0x3C

#define LED_PIN 12

unsigned long previousMillis = 0; 
unsigned long sensorInterval = 5000;
unsigned long animationInterval = 200;
unsigned long animationMillis = 0;
unsigned long ledPreviousMillis = 0;
unsigned long ledInterval = 0;

bool ledState = LOW;
float tempReadings[10];
int tempIndex = 0;
int animationFrame = 0;
int trendDirection = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  if (!bmp.begin(BMP280_ADDRESS)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  display.clearDisplay();

  for (int i = 0; i < 10; i++) {
    tempReadings[i] = 0.0;
  }
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= sensorInterval) {
    previousMillis = currentMillis;
    float currentTemp = bmp.readTemperature();

    tempReadings[tempIndex] = currentTemp;
    tempIndex = (tempIndex + 1) % 10;

    float tempSum = 0;
    bool tempChanged = false;
    for (int i = 0; i < 10; i++) {
      tempSum += tempReadings[i];
      if (i > 0 && tempReadings[i] != tempReadings[i - 1]) {
        tempChanged = true;
      }
    }
    float avgTemp = tempSum / 10.0;

    if (!tempChanged) {
      trendDirection = 0;
    } else if (currentTemp > avgTemp) {
      trendDirection = 1;
    } else if (currentTemp < avgTemp) {
      trendDirection = -1;
    }

    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    
    String tempString = String(currentTemp, 1);
    int16_t xTemp, yTemp;
    uint16_t wTemp, hTemp;
    display.getTextBounds(tempString, 0, 0, &xTemp, &yTemp, &wTemp, &hTemp);
    int16_t xPos = (SCREEN_WIDTH - wTemp) / 2;
    int16_t yPos = (SCREEN_HEIGHT - hTemp) / 2;
    display.setCursor(xPos, yPos);
    display.print(tempString);

    display.display();

    if (currentTemp >= 35.0) {
      digitalWrite(LED_PIN, HIGH);
    } else if (currentTemp >= 30.0 && currentTemp < 35.0) {
      ledInterval = map(currentTemp, 30, 35, 1000, 100);
      if (currentMillis - ledPreviousMillis >= ledInterval) {
        ledPreviousMillis = currentMillis;
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
      }
    } else {
      digitalWrite(LED_PIN, LOW);
    }
  }

  if (currentMillis - animationMillis >= animationInterval) {
    animationMillis = currentMillis;
    animationFrame = (animationFrame + 1) % 3;

    display.fillRect(SCREEN_WIDTH - 10, 0, 10, SCREEN_HEIGHT, SSD1306_BLACK);

    display.setTextSize(2);
    if (trendDirection == 1) {
      int arrowY = 20 - animationFrame * 10;
      display.setCursor(SCREEN_WIDTH - 10, arrowY);
      display.print("^");
    } else if (trendDirection == -1) {
      int arrowY = animationFrame * 10;
      display.setCursor(SCREEN_WIDTH - 10, arrowY);
      display.print("v");
    } else {
      display.setCursor(SCREEN_WIDTH - 10, SCREEN_HEIGHT / 2);
      display.print("-");
    }

    display.display();
  }
}
