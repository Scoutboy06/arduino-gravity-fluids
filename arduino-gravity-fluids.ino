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

#include <Adafruit_ADXL345_U.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include "particle.h"
#include "particle_manager.h"
#include "vec.h"

// -------- Global varialbes -------- //

#include "globals.h"

// -------- Setup -------- //

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");
  Serial.println(freeRam());

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (1)
      ;
  }

  Serial.println(freeRam());

  if (!accel.begin()) {
    Serial.println(F("ADXL345 allocation failed"));
    while (1)
      ;
  }

  Serial.println(freeRam());
  ParticleManager::GetInstance().spawnParticle(SCREEN_WIDTH / 2 - 10,
                                               SCREEN_HEIGHT / 2);
  Serial.println(freeRam());
  ParticleManager::GetInstance().spawnParticle(SCREEN_WIDTH / 2 + 10,
                                               SCREEN_HEIGHT / 2);
  Serial.println(freeRam());
}

void loop() {
  gravity = readAccelerometer();
  oled.clearDisplay();

  ParticleManager::GetInstance().updateParticles(timeStep);
  ParticleManager::GetInstance().renderParticles(oled);

  oled.display();
}

Vector2 readAccelerometer() {
  sensors_event_t event;
  accel.getEvent(&event);
  return Vector2(event.acceleration.x, -event.acceleration.y);
}

int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}