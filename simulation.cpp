#include "simulation.h"

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

void Simulation::update() {
  for (uint8_t y = SCREEN_HEIGHT - 2; y > 0; y--) {
    for (uint8_t x = 0; x < SCREEN_WIDTH; x++) {
      if (!this->getCell(x, y)) continue;

      // Down
      if (!this->getCell(x, y + 1)) {
        this->setCell(x, y + 1, true);
        this->setCell(x, y, false);
      }

      // Down left
      else if (x > 0 && !this->getCell(x - 1, y + 1)) {
        this->setCell(x - 1, y + 1, true);
        this->setCell(x, y, false);
      }

      // Down right
      else if (x < SCREEN_WIDTH - 1 && !this->getCell(x + 1, y + 1)) {
        this->setCell(x + 1, y + 1, true);
        this->setCell(x, y, false);
      }

      // Left
      else if (x > 0 && !this->getCell(x - 1, y)) {
        this->setCell(x - 1, y, true);
        this->setCell(x, y, false);
      }

      // Right
      else if (x < SCREEN_WIDTH - 1 && !this->getCell(x + 1, y)) {
        this->setCell(x + 1, y, true);
        this->setCell(x, y, false);
      }
    }
  }
}
