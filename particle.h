#pragma once

#include "vec.h"

class Particle {
 public:
  Vec pos;
  Vec prevPos;
  Vec vel;
  Vec acc;
  float radius;

  Particle() {}

  Particle(float x, float y) {
    this->pos = Vec(x, y);
    this->prevPos = Vec(x, y);
    this->vel = Vec();
    this->acc = Vec();
  }

  float dist(Particle& other) { return this->pos.dist(other.pos); }

  float distSq(Particle& other) { return this->pos.distSq(other.pos); }
};