#pragma once

class Vector2 {
 public:
  float x;
  float y;

  /**
   * @brief Default constructor that initializes x and y to 0.0
   */
  Vector2() : x(0.0f), y(0.0f) {}

  /**
   * @brief Constructor that initializes x and y to given values
   * @param x The x-corrdinate
   * @param y The y-corrdinate
   */
  Vector2(float x, float y) : x(x), y(y) {}

  /**
   * @brief Creates a Vector2 object from an angle and length
   * @param angle The angle in radians
   * @param length The length of the vector (optional, defaults to 1.0)
   * @return A new Vector2 object with x and y coordinates calculated from
   * the angle and length
   */
  static Vector2 fromAngle(float angle, float length = 1.0) {
    float x = cos(angle) * length;
    float y = sin(angle) * length;
    return Vector2(x, y);
  }

  /**
   * @brief Returns a copy of the Vector2 object
   */
  Vector2 copy() { return Vector2(this->x, this->y); }

  /**
   * @brief Adds to a vector's x and y components using separate numbers
   */
  void add(float x, float y) {
    this->x += x;
    this->y += y;
  }

  /**
   * @brief Adds the x and y components of the vector using another Vec object
   * @param other The Vector2 object whose coordinates will be added onto this
   * Vector2
   */
  void add(const Vector2& other) {
    x += other.x;
    y += other.y;
  }

  /**
   * @brief Overloads the `+` operator to add two Vector2 objects
   * @param rhs The Vector2 object on the right-hand side of the `+` operator
   * @return A new Vector2 object that is the sum of this Vector2 and `rhs`
   */
  Vector2 operator+(const Vector2& rhs) const {
    return Vector2(this->x + rhs.x, this->y + rhs.y);
  }

  /**
   * @brief Overloads the `+=` operator to add a Vector2 object to this Vector2
   * @param rhs The Vector2 object on the right-hand side of the `+=` operator
   * @return A reference to this Vector2 after `rhs` has been added to it
   */
  Vector2& operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  /**
   * @brief Subtracts from a vector's x and y components using separate numbers
   */
  void sub(float x, float y) {
    this->x -= x;
    this->y -= y;
  }

  /**
   * @brief Subrracts the x and y components of the vector using another Vec
   * object
   * @param other The Vector2 object whose coordinates will be subtracted from
   * this Vector2
   */
  void sub(const Vector2& other) {
    x -= other.x;
    y -= other.y;
  }

  /**
   * @brief Overloads the `-` operator to subtract a Vector2 object from this
   * Vector2
   * @param rhs The Vector2 object on the right-hand side of the `-` operator
   * @return A new Vector2 object that is the difference of this Vector2 and
   * `rhs`
   */
  Vector2 operator-(const Vector2& rhs) const {
    return Vector2(x - rhs.x, y - rhs.y);
  }

  /**
   * @brief Overloads the `-=` operator to subtract a Vector2 object to this
   * Vector2
   * @param rhs The Vector2 object on the right-hand side of the `-=` operator
   * @return A reference to this Vector2 after `rhs` has been subtracted from it
   */
  Vector2& operator-=(const Vector2& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  /**
   * @brief Scales a vector using a scalar
   * @param scalar The scalar to scale the vector with
   */
  void mult(float scalar) {
    x *= scalar;
    y *= scalar;
  }

  /**
   * @brief Overloads the `*` operator to dot multiply a Vector2 object with
   * this Vector2
   * @param rhs The Vector2 object on the right-hand side of the `*` operator.
   * @return A new Vector2 object that is the dot product of the Vector2 and
   * `rhs`
   */
  float operator*(const Vector2& rhs) const { return x * rhs.x + y * rhs.y; }

  /**
   * @brief Overloads the `*` operator to scale a Vector2 object using a scalar
   * @param scalar The scalar on the right-hand side of the `*` operator.
   * @return A new Vector2 object that is a scaled version of the Vector2 object
   * on the left-hand side of the `*` operator.
   */
  Vector2 operator*(const float scalar) const {
    return Vector2(x * scalar, y * scalar);
  }

  /**
   * @brief Overloads the `*` operator to scale a Vector2 object using a scalar
   * @param scalar The scalar on the right-hand side of the `*` operator.
   * @return A new Vector2 object that is the scaled Vector2 object and
   */
  friend Vector2 operator*(float scalar, const Vector2& v) {
    return Vector2(v.x * scalar, v.y * scalar);
  }

  /**
   * @brief Overloads the `*=` operator to scale a Vector2 object
   * @param scalar The scalar to scale this vector with
   */
  Vector2& operator*=(const float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  /**
   * @brief Scales a vector by dividing using a scalar
   * @param scalar The scalar to scale the vector with
   */
  void div(float scalar) {
    x /= scalar;
    y /= scalar;
  }

  /**
   * @brief Overloads the `/=` operator to scale a Vector2 object
   * @param scalar The scalar to scale this vector with
   */
  Vector2& operator/=(const float scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
  }

  /**
   * @brief Calculates the vector's magnitude
   * @return The vector's magnitude
   */
  float mag() { return sqrt(magSq()); }

  /**
   * @brief Calculates the vector's squared magnitude.
   * @return The vector's squared magnitude.
   */
  float magSq() { return x * x + y * y; }

  /**
   * @brief Calculates the distance between this vector and the point (x, y)
   * @return The distance between this vector and (x, y)
   */
  float dist(float x, float y) { return sqrt(distSq(x, y)); }

  /**
   * @brief Calculates the distance between this vector and `other`
   * @param other The vector to calculate the distance to
   * @return The distance between this vector and (x, y)
   */
  float dist(Vector2& other) { return sqrt(distSq(other)); }

  /**
   * @brief Calculates the squared distance between this vector and the point
   * (x, y)
   * @return The squared distance between this vector and (x, y)
   */
  float distSq(float x, float y) {
    float dx = this->x - x;
    float dy = this->y - y;
    return dx * dx + dy * dy;
  }

  /**
   * @brief Calculates the squared distance between this vector and `other`
   * @param other The vector to calculate the squared distance to
   * @return The squared distance between this vector and (x, y)
   */
  float distSq(Vector2& other) {
    float dx = this->x - other.x;
    float dy = this->y - other.y;
    return dx * dx + dy * dy;
  }

  /**
   * @brief Normalizes the vector
   */
  void normalize() {
    float mag = this->mag();

    if (mag != 0) {
      this->div(mag);
    }
  }

  /**
   * @brief Limits the vector's magnitude. If the magnitude is smaller or equal
   * to the maximum magnitude, it does nothing
   * @param magMag The maximum magnitude
   */
  void limit(float maxMag) {
    float magSq = this->magSq();

    if (magSq > maxMag * maxMag) {
      this->div(sqrt(magSq));
      this->mult(maxMag);
    }
  }

  /**
   * @brief Checks if the vector's x- and y-coordinates matches the parameter
   * values.
   * @returns If the x- and y-coordinates match
   */
  bool equals(float x, float y) { return this->x == x && this->y == y; }

  /**
   * @brief Checks if the two vectors are identical
   * @returns If the two vectors are identical
   */
  bool equals(Vector2& other) { return x == other.x && y == other.y; }

  /**
   * @brief Overloads the `==` operator to check if the two vectors are
   * identical
   * @returns If the two vectors are identical
   */
  bool operator==(Vector2& rhs) { return this->equals(rhs); }
};
