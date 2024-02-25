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
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include "particle.h"
#include "particle_manager.h"
#include "ssd1306_128x64_i2c.h"
#include "vec.h"

// -------- Global varialbes -------- //

#include "globals.h"

// -------- Setup -------- //

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");
  Serial.println(freeRam());

  oled.init(SSD1306_CMD_SWITCHCAPVCC, 0x3C);

  if (!accel.begin()) {
    Serial.println(F("ADXL345 allocation failed"));
    while (1)
      ;
  }

  ParticleManager::GetInstance().spawnParticle(SCREEN_WIDTH / 2 - 10,
                                               SCREEN_HEIGHT / 2);

  ParticleManager::GetInstance().spawnParticle(SCREEN_WIDTH / 2 + 10,
                                               SCREEN_HEIGHT / 2);
}

void loop() {
  gravity = readAccelerometer();
  oled.clearDisplay();

  // ParticleManager::GetInstance().updateParticles(timeStep);
  // ParticleManager::GetInstance().renderParticles(oled);

  // oled.drawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, PARTICLE_RADIUS,
  // WHITE);

  for (int y = 0; y < SCREEN_HEIGHT; y++) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
      oled.drawPixel(x, y, WHITE);
    }
  }

  // for (int i = 0; i < SCREEN_WIDTH; i++) {
  //   oled.drawPixel(i, 0, WHITE);
  // }

  delay(1000);
  // oled.display();
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