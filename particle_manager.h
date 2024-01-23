#pragma once

#include "distance_field.h"
#include "globals.h"
#include "grid.h"
#include "neighbor_manager.h"
#include "particle.h"

class ParticleManager {
 public:
  static ParticleManager& GetInstance() {
    static ParticleManager instance;
    return instance;
  }

  void spawnParticle(float x, float y) {}

  void updateParticles(float timeStep) {}

  void renderParticles() {}

 private:
  /**
   * The Singleton's constructor should always be private to prevent direct
   * construction calls with the `new` operator.
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
   * The main list of particles. This list is created and initialized in the
   * beginning of the simulation.
   */
  Particle particles[NUM_PARTICLES];

  /**
   * This component hashes the particles based on their position to a grid, to
   * allow faster neighbor search. Particles register their movement to this
   * component and the neighbor lists gets their data from this component
   */
  Grid grid;

  /**
   * This component manages the world representation. The world is represented
   * by a distance field, where each data point contains the distance to the
   * closest edge and the normal away from that edge.
   */
  DistanceField distanceField;

  /**
   * Described in [Mån13], 3.1.3, Algorithm 2 - Applying external forces.
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
      for (Particle* n : p.neighbors()) {
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

  void updateNeighbors() {}

  void doubleDensityRelaxation() {}

  void resolveCollisions() {}

  void updateVelocity(float timeStep) {}
};