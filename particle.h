#pragma once

#include "list.h"
// #include "neighbor_manager.h"
#include "vec.h"

class Particle {
 public:
  Vector2 pos;
  Vector2 prevPos;
  Vector2 vel;
  uint32_t index;

  Particle() {}
  Particle(float x, float y, uint32_t index) {
    this->pos = Vector2(x, y);
    this->prevPos = Vector2(x, y);
    this->vel = Vector2();
    this->index = index;
  }

  float dist(Particle& other) { return this->pos.dist(other.pos); }

  float distSq(Particle& other) { return this->pos.distSq(other.pos); }

  // List<Particle*> neighbors() {
  //   return NeighborManager::GetInstance().getNeighborsOf(this);
  // }
};