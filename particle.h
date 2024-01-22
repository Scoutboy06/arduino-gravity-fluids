#pragma once

#include "list.h"
#include "neighbor_manager.h"
#include "vec.h"

class Particle {
 public:
  Vector2 pos;
  Vector2 prevPos;
  Vector2 vel;
  Vector2 acc;
  float radius;
  unsigned int index;

  Particle() {}
  Particle(float x, float y, float radius) {
    this->pos = Vector2(x, y);
    this->prevPos = Vector2(x, y);
    this->vel = Vector2();
    this->acc = Vector2();
    this->radius = radius;
  }

  float dist(Particle& other) { return this->pos.dist(other.pos); }

  float distSq(Particle& other) { return this->pos.distSq(other.pos); }

  List<Particle*> neighbors() {
    return NeighborManager::GetInstance().getNeighborsOf(this);
  }
};