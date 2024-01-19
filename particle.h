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
    pos = Vec(x, y);
    prevPos = Vec(x, y);
    vel = Vec();
    acc = Vec();
  }

  float dist(Particle& other) { return pos.dist(other.pos); }

  float distSq(Particle& other) { return pos.distSq(other.pos); }
};