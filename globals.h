#pragma once

#include <Adafruit_ADXL345_U.h>
#include <Adafruit_SSD1306.h>

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

float timeStep = 1 / 60;
#define NUM_PARTICLES 512

// Variables described in [Mån13], 3.1.3, List 3

const float radius = 1.0;  // Maximum distance particles effect each other.
const float collisionRadius =
    1.0;                // The distance from a wall that counts as a collision.
const float p_0 = 1.0;  // Rest density
const float sigma = 1.0;  // The viscosity's linear dependence on the velocity
const float beta = 1.0;  // The viscosity's quadratic dependence on the velocity
const float k = 1.0;     // Stiffness used in DoubleDensityRelaxation
const float k_near = 1.0;  // Near-stiffness used in DoubleDensityRelaxation
Vector2 gravity;           // The global gravity acceleration