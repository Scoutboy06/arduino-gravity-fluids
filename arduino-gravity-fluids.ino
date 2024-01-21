/*

  /$$$$$$                                /$$   /$$
 /$$__  $$                              |__/  | $$
| $$  \__/  /$$$$$$  /$$$$$$  /$$    /$$ /$$ /$$$$$$   /$$   /$$
| $$ /$$$$ /$$__  $$|____  $$|  $$  /$$/| $$|_  $$_/  | $$  | $$
| $$|_  $$| $$  \__/ /$$$$$$$ \  $$/$$/ | $$  | $$    | $$  | $$
| $$  \ $$| $$      /$$__  $$  \  $$$/  | $$  | $$ /$$| $$  | $$
|  $$$$$$/| $$     |  $$$$$$$   \  $/   | $$  |  $$$$/|  $$$$$$$
 \______/ |__/      \_______/    \_/    |__/   \___/   \____  $$
                                                       /$$  | $$
                                                      |  $$$$$$/
                                                       \______/
 /$$$$$$$$ /$$           /$$       /$$
| $$_____/| $$          |__/      | $$
| $$      | $$ /$$   /$$ /$$  /$$$$$$$  /$$$$$$$
| $$$$$   | $$| $$  | $$| $$ /$$__  $$ /$$_____/
| $$__/   | $$| $$  | $$| $$| $$  | $$|  $$$$$$
| $$      | $$| $$  | $$| $$| $$  | $$ \____  $$
| $$      | $$|  $$$$$$/| $$|  $$$$$$$ /$$$$$$$/
|__/      |__/ \______/ |__/ \_______/|_______/


A fluid simulation that responds to motion (gravity).

Resources:

  [Mån13] Daniel Månsson. Interactive 2D Particle-based Fluid Simulation for
  Mobile Devices. Bachelor's Thesis, KTH, 2013

  [GHJV95] Erich Gamma, Richard Helm, Ralph Johnsson, John Vlissides. Design
  Patterns: Elements of Reusable Object-Oriented Software. Addison-Wesley, 1995.

*/

#pragma once

#include <Adafruit_ADXL345_U.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include "particle.h"
#include "particle_manager.h"
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
#define NUM_PARTICLES 512

// Variables described in [Mån13], 3.1.3, List 3

const float radius = 1.0;  // Maximum distance particles effect each other.
const float collisionRadius =
    1.0;                // The distance from a wall that counts as a collision.
const float p_0 = 1.0;  // Rest density
const float sigma = 1.0;  // The viscosity's linear dependence on the velocity
const float beta = 1.0;  // The viscosity's quadratic dependence on the velocity
const float k = 1.0;     // Stiffness used in DoubleDensityRelaxation
const float k_near = 1.0;  // Near-stiffness used in DoubleDensityRelaxation
Vec gravity;               // The global gravity acceleration

// -------- Setup -------- //

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

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  gravity = readAccelerometer();
  oled.clearDisplay();

  ParticleManager::GetInstance().updateParticles(timeStep);
  ParticleManager::GetInstance().renderParticles();

  oled.display();
}

Vec readAccelerometer() {
  sensors_event_t event;
  accel.getEvent(&event);
  return Vec(event.acceleration.x, -event.acceleration.y, event.acceleration.z);
}