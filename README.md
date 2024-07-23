# Temperature Alert System

## Description
This project involves a temperature monitoring system that uses the DS18B20 sensor to measure the temperature and displays the current temperature on an OLED screen. When the temperature exceeds a predefined threshold, a red LED will light up and a buzzer will sound to alert the user. If the temperature is within the safe range, a green LED will be illuminated instead.

## Components
- ESP32 microcontroller
- DS18B20 temperature sensor
- OLED display (128x64)
- Red LED
- Green LED
- Buzzer
- 4.7kΩ resistor

## Wiring
- **DS18B20 Sensor**
  - VCC to 3.3V on ESP32
  - GND to GND on ESP32
  - DQ to GPIO 5 on ESP32
  - 4.7kΩ resistor between VCC and DQ

- **OLED Display**
  - VCC to 3.3V on ESP32
  - GND to GND on ESP32
  - SDA to GPIO 21 on ESP32
  - SCL to GPIO 22 on ESP32

- **Red LED**
  - Anode to GPIO 12 on ESP32
  - Cathode to GND

- **Green LED**
  - Anode to GPIO 2 on ESP32
  - Cathode to GND

- **Buzzer**
  - Positive pin to GPIO 13 on ESP32
  - Negative pin to GND

## Installation
1. Install the required libraries for the project:
   - Adafruit SSD1306
   - Adafruit GFX
   - Dallas Temperature
   - OneWire

2. Upload the provided code to your ESP32.

3. Connect the components as per the wiring diagram.

## Usage
The OLED display will show the current temperature. If the temperature exceeds 30°C, the red LED will light up and the buzzer will sound. If the temperature is within the safe range, the green LED will light up.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Wokwi Simulation
You can view and interact with the simulation of this project on Wokwi: [Temperature Alert System Simulation](https://wokwi.com/projects/404211434957239297)
