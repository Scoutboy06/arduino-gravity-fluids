#include <Adafruit_ADXL345_U.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include "particle.h"
#include "vec.h"

// -------- OLED Screen -------- //

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// -------- Accelerometer -------- //

#define ACC_SCL A3
#define ACC_SDA A2

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

// -------- Fluid simulation -------- //

float timeStep = 1 / 60;

// -------- Setup -------- //

Vec ballPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (1)
      ;
  }

  // TODO: if(!accel.begin())
  if (!accel.begin()) {
    Serial.println(F("ADXL345 allocation failed"));
    while (1)
      ;
  }

  oled.clearDisplay();
  oled.setCursor(20, 20);
  oled.setTextColor(WHITE);
  oled.print("Hello there!");
  oled.display();

  pinMode(LED_BUILTIN, OUTPUT);
}

int r = 4;
int halfR = r / 2;

void loop() {
  Vec gravity = readAccelerometer();
  gravity.mult(0.5);
  ballPos.add(gravity);

  if (ballPos.x - halfR < 0) {
    ballPos.x = halfR;
  } else if (ballPos.x + halfR > SCREEN_WIDTH) {
    ballPos.x = SCREEN_WIDTH - halfR;
  }

  if (ballPos.y - halfR < 0) {
    ballPos.y = halfR;
  } else if (ballPos.y + halfR > SCREEN_HEIGHT) {
    ballPos.y = SCREEN_HEIGHT - halfR;
  }

  oled.clearDisplay();
  oled.fillCircle(ballPos.x, ballPos.y, r, WHITE);
  oled.display();
}

Vec readAccelerometer() {
  sensors_event_t event;
  accel.getEvent(&event);
  return Vec(event.acceleration.x, -event.acceleration.y, event.acceleration.z);
}