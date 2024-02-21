#pragma once

#include "distance_field.h"
#include "globals.h"
#include "grid.h"
#include "neighbor_manager.h"
#include "particle.h"
#include "vec.h"

class ParticleManager {
 public:
  static ParticleManager& GetInstance() {
    static ParticleManager instance;
    return instance;
  }

  void spawnParticle(float x, float y) {
    if (_particleCount >= NUM_PARTICLES) return;

    Particle p = Particle(x, y, _particleCount);
    particles[_particleCount] = p;
    _particleCount++;
  }

  void updateParticles(float timeStep) {}

  void renderParticles() {}

 private:
  size_t _particleCount = 0;

  /**
   * The Singleton's constructor should always be private to prevent
   * direct construction calls with the `new` operator.
   */
  ParticleManager() {}

  /**
   * Singletons should not be cloneable.
   */
  ParticleManager(const ParticleManager&) = delete;

  /**
   * Singletons should not be assignable.
   */
  ParticleManager& operator=(const ParticleManager&) = delete;

  /**
   * @brief The main list of particles. This list is created and initialized in
   * the beginning of the simulation.
   */
  Particle particles[NUM_PARTICLES];

  /**
   * @brief This component hashes the particles based on their position to a
   * grid, to allow faster neighbor search. Particles register their movement to
   * this component and the neighbor lists gets their data from this component
   */
  Grid grid;

  /**
   * @brief This component manages the world representation. The world is
   * represented by a distance field, where each data point contains the
   * distance to the closest edge and the normal away from that edge.
   */
  DistanceField distanceField;

  /**
   * @brief Described in [Mån13], 3.1.3, Algorithm 2 - Applying external forces.
   *
   * Applies external forces to all particles. There is currently a single
   * source of external force, `gravity`, which can be manipulated by the user.
   */
  void applyExternalForces(float timeStep) {
    for (Particle p : particles) {
      p.vel += gravity;
    }
  }

  /**
   * @brief Described in [Mån13], 3.1.3, Algorithm 3 - Applying viscosity.
   * Viscosity has the effect of smoothing the velocities of the particles. It
   * is an impulse applied radially between neighboring particles.
   * @param timeStep The time between frames
   */
  void applyViscosity(float timeStep) {
    for (Particle p : particles) {
      for (Particle* n : NeighborManager::GetInstance().getNeighborsOf(p)) {
        Vector2 v_pn = n->pos - p.pos;
        float vel_inward = (p.vel - n->vel) * v_pn;

        if (vel_inward > 0) {
          float length = v_pn.mag();
          vel_inward /= length;
          v_pn /= length;
          float q = length / radius;
          Vector2 I = 0.5 * timeStep * (1 - q) *
                      (sigma * vel_inward + beta * pow(vel_inward, 2)) * v_pn;
          p.vel -= I;
        }
      }
    }
  }

  /**
   * @brief Described in [Mån13], 3.1.3, Algorithm 4 - Advancing particles to
   * predicted position.
   *
   * @note In the original paper, there is an error in Algorithm 4, line 4. It
   * should be `p.pos ← p.pos + timeStep ∗ p.vel`, which has been corrected in
   * the code.
   */
  void advanceParticles(float timeStep) {
    for (Particle p : particles) {
      p.prevPos = p.pos.copy();
      p.pos += timeStep * p.vel;
      grid.moveParticle(p);
    }
  }

  void updateNeighbors() {
    for (Particle p : particles) {
      NeighborManager::GetInstance().clear();

      for (Particle* n : grid.possibleNeighbors(p)) {
        if ((p.pos - n->pos).magSq() < radius * radius) {
          NeighborManager::GetInstance().addNeighbor(p, n);
        }
      }
    }
  }

  /**
   * @brief Described in [Mån13], 3.1.3, Algorithm 6 - Double Density Relaxation
   *
   * @note In the original paper, the author uses the same variable name for the
   * particle `p` and the float `p`. This has been modified, as the particle is
   * called `par`. Also, on line 19 of the original algorithm, D is not defined
   * in the current scope. I presume this is a bug, and I have thus moved the
   * line into the for loop (it was below before).
   */
  void doubleDensityRelaxation() {
    for (Particle par : particles) {
      float p = 0.0;
      float p_near = 0.0;

      for (Particle* n : NeighborManager::GetInstance().getNeighborsOf(par)) {
        float temp_n = (par.pos - n->pos).mag();
        float q = 1.0 - temp_n / radius;
        p = k * pow(q, 2);
        p_near += pow(q, 3);
      }

      float P = k * (P - p_0);
      float P_near = k_near * p_near;
      Vector2 delta;

      for (Particle* n : NeighborManager::GetInstance().getNeighborsOf(par)) {
        float temp_n = (par.pos - n->pos).mag();
        float q = 1.0 - temp_n / radius;
        Vector2 v_pn = (par.pos - n->pos) / temp_n;
        Vector2 D =
            0.5 * pow(timeStep, 2) * (P * q + P_near * pow(q, 2)) * v_pn;
        n->pos += D;
        delta -= D;
        par.pos += D;  // NOTE: different from original
      }
    }
  }

  void resolveCollisions(float timeStep) {
    for (Particle p : particles) {
      int index = distanceField.getIndex(p.pos);

      if (index != -1) {
        float distance = distanceField.getDistance(index);

        if (distance > -collisionRadius) {
          // Vector2 v_pn = (p.pos - )
          Vector2 normal = distanceField.getNormal(index);
          Vector2 tangent = normal.perpendicularCCW();
          tangent = timeStep * friction * (v_pn * tangent) * tangent;
        }
      }
    }
  }

  void updateVelocity(float timeStep) {}
};