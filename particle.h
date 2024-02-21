#pragma once

#include "list.h"
#include "vec.h"

class Particle {
 public:
  Vector2 pos;
  Vector2 prevPos;
  Vector2 vel;
  uint16_t index;

  Particle() {}
  Particle(float x, float y, uint16_t index) {
    this->pos = Vector2(x, y);
    this->prevPos = Vector2(x, y);
    this->vel = Vector2();
    this->index = index;
  }

  float dist(const Particle& other) { return this->pos.dist(other.pos); }

  float distSq(const Particle& other) { return this->pos.distSq(other.pos); }

  bool is(const Particle& other) { return this == &other; }
};