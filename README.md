# Temperature Trend OLED Display

This Arduino project displays real-time temperature data using a BMP280 sensor on an SSD1306 OLED display. It also shows a visual trend (up, down, or steady) based on the last 10 temperature measurements. An LED is used to signal different temperature ranges.

Arduino + SSD1306 + BMP280 + Status LED = Temperature Trend OLED Display with BMP280 Sensor

## Features

- Displays temperature on a 128x32 OLED display.
- Shows an animated arrow indicating the temperature trend.
- Controls an LED based on temperature thresholds (below 30°C, between 30°C-35°C, above 35°C).
- Simple and easy-to-understand code using the Adafruit libraries.

## Components

- **Arduino** (Any compatible board such as Uno, Nano, etc.)
- **BMP280 Temperature Sensor**
- **SSD1306 OLED Display** (128x32 pixels)
- **LED**
- **Resistor** (If needed for the LED)

## Libraries Required

- [Adafruit BMP280 Library](https://github.com/adafruit/Adafruit_BMP280_Library)
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit SSD1306 Library](https://github.com/adafruit/Adafruit_SSD1306)

Install these libraries via the Arduino Library Manager.

## Wiring

- **BMP280:**
  - VCC to 3.3V
  - GND to GND
  - SCL to A5 (or SCL pin on other Arduino boards)
  - SDA to A4 (or SDA pin on other Arduino boards)

- **SSD1306 OLED:**
  - VCC to 3.3V
  - GND to GND
  - SCL to A5 (or SCL pin)
  - SDA to A4 (or SDA pin)

- **LED:**
  - Anode to Pin 12
  - Cathode to GND (with an optional resistor)

## How It Works

- Every 5 seconds, the BMP280 sensor reads the temperature.
- The temperature is displayed on the OLED screen in large text.
- A trend arrow (up, down, or steady) is displayed based on the comparison of the current temperature to the average of the last 10 readings.
- The LED blinks faster or slower depending on the temperature, with specific behavior for different ranges.

## Code

See the `main.ino` file in this repository for the complete code.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contribution

Feel free to fork this project, make improvements, and open a pull request. Any contributions are welcome!

