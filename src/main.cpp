#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DS18B20 temperature sensor settings
#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// LED and Buzzer settings
#define LED_RED_PIN 12
#define LED_GRIN_PIN 2
#define BUZZER_PIN 13
#define TEMPERATURE_THRESHOLD 30.0 // Temperature threshold for alert

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);

  // Initialize OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Halt if the display fails to initialize
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println(F("Temperature Sensor"));
  display.display();

  // Initialize temperature sensor
  sensors.begin();

  // Check if the sensor is detected
  if (sensors.getDeviceCount() == 0) {
    Serial.println(F("No DS18B20 temperature sensors are connected"));
    display.clearDisplay();
    display.setCursor(0,0);
    display.println(F("No Sensor Found"));
    display.display();
    while (true) {} // Halt if no sensor is found
  }

  // Initialize LED and Buzzer pins
  pinMode(LED_GRIN_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Request temperature reading
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);

  // Check if the reading is valid
  if (temperatureC == DEVICE_DISCONNECTED_C) {
    Serial.println(F("Error: Could not read temperature data"));
    display.clearDisplay();
    display.setCursor(0,0);
    display.println(F("Read Error"));
    display.display();
    digitalWrite(LED_RED_PIN, LOW);  // Turn off the red LED
    digitalWrite(LED_GRIN_PIN, LOW); // Turn off the green LED
    noTone(BUZZER_PIN);              // Turn off the buzzer
  } else {
    // Display temperature on OLED
    display.clearDisplay();
    display.setCursor(0,0);
    display.println(F("Temperature: "));
    display.print(temperatureC);
    display.println(F(" C"));
    display.display();

    // Check if the temperature exceeds the threshold
    if (temperatureC > TEMPERATURE_THRESHOLD) {
      digitalWrite(LED_RED_PIN, HIGH);  // Turn on the red LED
      digitalWrite(LED_GRIN_PIN, LOW);  // Turn off the green LED
      tone(BUZZER_PIN, 1000);           // Turn on the buzzer
    } else {
      digitalWrite(LED_GRIN_PIN, HIGH); // Turn on the green LED
      digitalWrite(LED_RED_PIN, LOW);   // Turn off the red LED
      noTone(BUZZER_PIN);               // Turn off the buzzer
    }
  }

  delay(1000); // Wait for 1 second before the next reading
}
