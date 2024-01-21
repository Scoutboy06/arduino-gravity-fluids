#pragma once

#include "arduino-gravity-fluids.ino"
#include "distance_field.h"
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
  Particle _particles[NUM_PARTICLES];

  /**
   * This component hashes the particles based on their position to a grid, to
   * allow faster neighbor search. Particles register their movement to this
   * component and the neighbor lists gets their data from this component
   */
  Grid _grid;

  /**
   * This component manages the world representation. The world is represented
   * by a distance field, where each data point contains the distance to the
   * closest edge and the normal away from that edge.
   */
  DistanceField _distanceField;

  /**
   * Described in [Mån13], 3.1.3, Algorithm 2 - Applying external forces.
   *
   * Applies external forces to all particles. There is currently a single
   * source of external force, `gravity`, which can be manipulated by the user.
   */
  void applyExternalForces(float timeStep) {
    for (Particle p : _particles) {
      p.vel += gravity;
    }
  }

  /**
   * Described in [Mån13], 3.1.3, Algorithm 3 - Applying viscosity
   *
   * Viscosity has the effect of smoothing the velocities of the
   * particles. It is an impulse applied radially between neighboring particles.
   */
  void applyViscosity(float timeStep) {
    for (Particle p : _particles) {
      for (Particle* n : p.neighbors()) {
      }
    }
  }

  void advanceParticles(float timeStep) {}

  void updateNeighbors() {}

  void doubleDensityRelaxation() {}

  void resolveCollisions() {}

  void updateVelocity(float timeStep) {}
};