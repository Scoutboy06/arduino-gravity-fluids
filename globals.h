#pragma once

#include <Adafruit_ADXL345_U.h>
#include <Adafruit_SSD1306.h>

#include "particle_manager.h"
#include "vec.h"

// -------- OLED Screen -------- //

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// -------- Accelerometer -------- //

#define ACC_SCL A3
#define ACC_SDA A2

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

// -------- Fluid simulation -------- //

// ParticleManager particleManager;

float timeStep = 0.1;
#define NUM_PARTICLES 2
#define PARTICLE_RADIUS 3

// Variables described in [Mån13], 3.1.3, List 3

const float radius =
    PARTICLE_RADIUS;  // Maximum distance particles effect each other.
const float collisionRadius =
    PARTICLE_RADIUS;    // The distance from a wall that counts as a collision.
const float p_0 = 1.0;  // Rest density
const float sigma = 1.0;  // The viscosity's linear dependence on the velocity
const float beta = 1.0;  // The viscosity's quadratic dependence on the velocity
const float k = 1.0;     // Stiffness used in DoubleDensityRelaxation
const float k_near = 1.0;  // Near-stiffness used in DoubleDensityRelaxation
Vector2 gravity;           // The global gravity acceleration

// Variabled described in [Mån13], 3.1.3, below Algorithm 7
float friction = 0.8;
float collisionSoftness = 0.1;

float bounceFriction = 0.1;