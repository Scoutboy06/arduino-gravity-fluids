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


A fluid (falling sand) simulation that responds to motion (gravity).

*/

#include <Adafruit_ADXL345_U.h>
#include <Adafruit_Sensor.h>

#include "oled.h"
#include "simulation.h"

// -------- Oled -------- //

Oled oled;

// -------- Simulation -------- //

Simulation simulation;

// -------- Accelerometer -------- //

#define ACC_SCL A3
#define ACC_SDA A2

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

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

  for (int y = 0; y < 30; y++) {
    for (int x = SCREEN_WIDTH / 2 - 15; x < SCREEN_WIDTH / 2 + 15; x++) {
      simulation.spawnParticle(x, y);
    }
  }
}

void loop() {
  for (int i = 0; i < 10; i++) {
    simulation.update();
  }

  oled.draw(simulation.bitmap);
  Serial.print(F("."));

  // gravity = readAccelerometer();

  // ParticleManager::GetInstance().updateParticles(timeStep);
  // ParticleManager::GetInstance().renderParticles(oled);

  // oled.display();
}

// Vector2 readAccelerometer() {
//   sensors_event_t event;
//   accel.getEvent(&event);
//   return Vector2(event.acceleration.x, -event.acceleration.y);
// }

int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}