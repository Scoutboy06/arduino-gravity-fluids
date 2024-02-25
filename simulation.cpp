#include "simulation.h"

bool goLeft = true;

void Simulation::setCell(uint8_t x, uint8_t y, bool state) {
  int byteIndex = (y / 8) * SCREEN_WIDTH + x;
  int bit = y % 8;

  if (state) {
    bitmap[byteIndex] |= (1 << bit);
  } else {
    bitmap[byteIndex] &= ~(1 << bit);
  }
}

bool Simulation::getCell(uint8_t x, uint8_t y) {
  int byteIndex = (y / 8) * SCREEN_WIDTH + x;
  int bit = y % 8;

  return bitmap[byteIndex] & (1 << bit);
}

void Simulation::spawnParticle(uint8_t x, uint8_t y) { setCell(x, y, true); }

void Simulation::update(Vector2& gravity) {
  int8_t dx;
  if (gravity.x < -2) {  // Left
    dx = -1;
  } else if (gravity.x > 2) {  // Right
    dx = 1;
  } else {  // Middle
    dx = 0;
  }

  int8_t dy;
  if (gravity.y < -2) {  // Up
    dy = -1;
  } else if (gravity.y > 2) {  // Down
    dy = 1;
  } else {
    dy = 0;
  }

  int8_t dPos[] = {dx, dy};

  Serial.println(F("-----"));
  Serial.println("[" + String(gravity.x) + ", " + String(gravity.y) + "]");
  Serial.println("[" + String(dx) + ", " + String(dy) + "]");

  for (int y = SCREEN_HEIGHT - 2; y > 0; y--) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
      if (!this->getCell(x, y)) continue;
      if (x + dx < 0 || x + dx > SCREEN_WIDTH - 1 || y + dy < 0 ||
          y + dy > SCREEN_HEIGHT + 1)
        continue;

      // Main direction
      if (!this->getCell(x + dx, y + dy)) {
        this->setCell(x + dx, y + dy, true);
        this->setCell(x, y, false);
      }

      // Counter-clockwise
      // else if (x < SCREEN_WIDTH - 1 && !this->getCell(x + 1, y + 1)) {
      //   this->setCell(x + 1, y + 1, true);
      //   this->setCell(x, y, false);
      // }

      // // Right
      // else if (x < SCREEN_WIDTH - 1 && !this->getCell(x + 1, y)) {
      //   this->setCell(x + 1, y, true);
      //   this->setCell(x, y, false);
      // }

      // // Left
      // else if (x > 0 && !this->getCell(x - 1, y)) {
      //   this->setCell(x - 1, y, true);
      //   this->setCell(x, y, false);
      // }
    }
  }
}