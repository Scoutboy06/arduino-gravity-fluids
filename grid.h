#pragma once

#include "globals.h"
#include "list.h"
#include "particle.h"
#include "particle_manager.h"

#define CELL_SIZE 16
const uint8_t ROWS = SCREEN_HEIGHT / CELL_SIZE;
const uint8_t COLS = SCREEN_WIDTH / CELL_SIZE;

class Grid {
 public:
  Grid() {}

  void moveParticle(Particle& p) {
    int currCellIndex;

    for (int i = 0; i < ROWS * COLS; i++) {
      for (Particle* par : _grid[i]) {
        if (p.is(*par)) {
          currCellIndex = i;
        }
      }
    }

    // int cellRow
  }

  List<Particle*> possibleNeighbors(Particle& p) {
    // TODO: Implementation
  }

 private:
  List<Particle*> _grid[ROWS * COLS];
};