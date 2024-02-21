#pragma once

#include "globals.h"
#include "list.h"
#include "particle.h"

class NeighborManager {
 public:
  void addNeighbor(Particle& particle, Particle* neighbor) {
    _neighborData[particle.index].neighbors.push(neighbor);
  }

  List<Particle*> getNeighborsOf(Particle& particle) {
    return _neighborData[particle.index].neighbors;
  }

  void clear() {
    for (NeighborData data : _neighborData) {
      data.neighbors.clear();
    }
  }

 private:
  struct NeighborData {
    Particle* particle;
    List<Particle*> neighbors;
  };

  NeighborData _neighborData[NUM_PARTICLES];

  int addParticle(Particle* particle) {
    for (int i = 0; i < NUM_PARTICLES; i++) {
      if (_neighborData[i].particle == nullptr) {
        _neighborData[i].particle = particle;
        return i;
      }
    }

    return -1;  // No room to add more particles
  }
};