#include "simulation.h"

void Simulation::setCell(uint8_t x, uint8_t y, bool state) {
  int byteIndex = (y / 8) * SCREEN_WIDTH + x;
  int bit = y % 8;

  if (state) {
    bitmap[byteIndex] |= (1 << bit);
  } else {
    bitmap[byteIndex] |= ~(1 << bit);
  }
}

bool Simulation::getCell(uint8_t x, uint8_t y) {
  int byteIndex = (y / 8) * SCREEN_WIDTH + x;
  int bit = y % 8;

  return bitmap[byteIndex] & (1 << bit);
}

void Simulation::spawnParticle(uint8_t x, uint8_t y) { setCell(x, y, true); }

void Simulation::update() {}
