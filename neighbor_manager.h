#pragma once

#include "arduino-gravity-fluids.ino"
#include "particle.h"

#define INITIAL_CAPACITY 4

class NeighborManager {
 public:
  static NeighborManager& GetInstance() {
    static NeighborManager instance;
    return instance;
  }

  void addNeighbor(Particle* particle, Particle* neighbor) {
    int index = findParticle(particle);
  }

  Particle** getNeighborsOf(Particle* particle) {
    int index = findParticle(particle);
    return _neighborData[index].neighbors;
  }

 private:
  /**
   * The Singleton's constructor should always be private to prevent direct
   * construction calls with the `new` operator.
   */
  NeighborManager() {}

  /**
   * Singletons should not be cloneable.
   */
  NeighborManager(const NeighborManager&) = delete;

  /**
   * Singletons should not be assignable.
   */
  NeighborManager& operator=(const NeighborManager&) = delete;

  struct NeighborData {
    Particle* particle;
    Particle** neighbors = new Particle*[INITIAL_CAPACITY];
    uint32_t numNeighbors = 0;
    uint32_t capacity = INITIAL_CAPACITY;
  };

  NeighborData _neighborData[NUM_PARTICLES];

  int findParticle(Particle* particle) {
    for (int i = 0; i < NUM_PARTICLES; ++i) {
      if (_neighborData[i].particle == particle) {
        return i;
      }
    }

    return -1;  // Particle not found
  }

  int addParticle(Particle* particle) {
    for (int i = 0; i < NUM_PARTICLES; ++i) {
      if (_neighborData[i].particle == nullptr) {
        _neighborData[i].particle = particle;
        return i;
      }
    }

    return -1;  // No room to add more particles
  }
};