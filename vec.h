#pragma once

class Vec {
 public:
  float x;
  float y;
  float z;

  /**
   * @brief Default constructor that initializes x, y, and z to 0.0
   */
  Vec() : x(0.0), y(0.0), z(0.0) {}

  /**
   * @brief Constructor that initializes x, y, and z to given values
   * @param x The x-corrdinate
   * @param y The y-corrdinate
   * @param z The z-corrdinate
   */
  Vec(float x, float y, float z = 0.0) : x(x), y(y), z(z) {}

  /**
   * @brief Creates a Vec object from an angle and length
   * @param angle The angle in radians
   * @param length The length of the vector (optional, defaults to 1.0)
   * @return A new Vec object with x, y and z coordinates calculated from the
   * angle and length
   */
  static Vec fromAngle(float angle, float length = 1.0) {
    float x = cos(angle) * length;
    float y = sin(angle) * length;
    return Vec(x, y);
  }

  /**
   * @brief Creates a Vec object from two angles and length
   * @param theta The theta angle in radians
   * @param phi The phi angle in radians
   * @param length The length of the vector (optional, defaults to 1.0)
   * @return A new Vec object with x, y, and z coordinates calculated from the
   * angles and length
   */
  static Vec fromAngles(float theta, float phi, float length = 1.0) {
    float sinTheta = sin(theta);
    float cosTheta = cos(theta);
    float sinPhi = sin(phi);
    float cosPhi = cos(phi);

    return Vec(length * sinTheta * sinPhi, -length * cosTheta,
               length * sinTheta * cosPhi);
  }

  /**
   * Returns a copy of the Vec object
   */
  Vec copy() { return Vec(this->x, this->y, this->z); }

  /**
   * Sets the x, y, and z components of the vector using separate numbers
   */
  void set(float x, float y, float z = 0.0) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  /**
   * Sets the x, y, and z components of the vector using another Vec object
   */
  void set(Vec& other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
  }

  /**
   * Adds to a vector's x, y, and z components using separate numbers
   */
  void add(float x, float y, float z = 0.0) {
    this->x += x;
    this->y += y;
    this->z += z;
  }

  /**
   * Adds to a vector's x, y, and z components using another `Vec` object
   * @param other The Vec that will be added from
   */
  void add(Vec& other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
  }

  /**
   * @brief Overloads the `+` operator to add two Vec objects
   * @param rhs The Vec object on the right-hand side of the `+` operator
   * @return A new Vec object that is the sum of this Vec and `rhs`
   */
  Vec operator+(const Vec& rhs) const {
    return Vec(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
  }

  /**
   * @brief Overloads the `+=` operator to add a Vec object to this Vec
   * @param rhs The Vec object on the right-hand side of the `+=` operator
   * @return A reference to this Vec after `rhs` has been added to it
   */
  Vec& operator+=(const Vec& other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
  }

  void sub(float x, float y, float z = 0.0) {
    this->x -= x;
    this->y -= y;
    this->z -= z;
  }

  void sub(Vec& other) {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
  }

  /**
   * @brief Overloads the `-` operator to subtract a Vec object from this Vec
   * @param rhs The Vec object on the right-hand side of the - operator
   * @return A new Vec object that is the difference of this Vec and `rhs`
   */
  Vec operator-(const Vec& rhs) const {
    return Vec(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
  }

  void mult(float scalar) {
    this->x *= scalar;
    this->y *= scalar;
  }

  void div(float scalar) {
    this->x /= scalar;
    this->y /= scalar;
  }

  float mag() {
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
  }

  float magSq() {
    return this->x * this->x + this->y * this->y + this->z * this->z;
  }

  float dist(float x, float y, float z = 0.0) {
    return sqrt(this->distSq(x, y, z));
  }

  float dist(Vec& other) { return sqrt(this->distSq(other)); }

  float distSq(float x, float y, float z = 0.0) {
    float dx = this->x - x;
    float dy = this->y - y;
    float dz = this->z - z;
    return dx * dx + dy * dy + dz * dz;
  }

  float distSq(Vec& other) {
    float dx = this->x - other.x;
    float dy = this->y - other.y;
    float dz = this->z - other.z;
    return dx * dx + dy * dy + dz * dz;
  }

  void normalize() {
    float mag = this->mag();

    if (mag != 0) {
      this->div(mag);
    }
  }

  void limit(float maxMag) {
    float magSq = this->magSq();

    if (magSq > maxMag * maxMag) {
      this->div(sqrt(magSq));
      this->mult(maxMag);
    }
  }

  bool equals(float x, float y, float z = 0.0) {
    return this->x == x && this->y == y && this->z == z;
  }

  bool equals(Vec& other) {
    return this->x == other.x && this->y == other.y && this->z == other.z;
  }
};
