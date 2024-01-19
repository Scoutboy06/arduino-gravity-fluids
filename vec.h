class Vec {
 public:
  float x;
  float y;
  float z;

  Vec() : x(0.0), y(0.0), z(0.0) {}
  Vec(float x, float y, float z = 0.0) : x(x), y(y), z(z) {}

  static Vec fromAngle(float angle, float length = 1.0) {
    float x = cos(angle) * length;
    float y = sin(angle) * length;
    return Vec(x, y);
  }

  static Vec fromAngles(float theta, float phi, float length = 1.0) {
    float sinTheta = sin(theta);
    float cosTheta = cos(theta);
    float sinPhi = sin(phi);
    float cosPhi = cos(phi);

    return Vec(length * sinTheta * sinPhi, -length * cosTheta,
               length * sinTheta * cosPhi);
  }

  Vec copy() { return Vec(this->x, this->y, this->z); }

  void set(float x, float y, float z = 0.0) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  void set(Vec& other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
  }

  void add(float x, float y, float z = 0.0) {
    this->x += x;
    this->y += y;
    this->z += z;
  }

  void add(Vec& other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
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
