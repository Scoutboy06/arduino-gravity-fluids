class Vec2 {
 public:
  float x;
  float y;

  Vec2() {}
  Vec2(float x, float y) : x(x), y(y) {}
  Vec2(const Vec2& rhs){};

  void set(float x, float y) {
    this->x = x;
    this->y = y;
  }

  void add(float x, float y) {
    this->x += x;
    this->y += y;
  }

  void add(Vec2& other) {
    this->x += other.x;
    this->y += other.y;
  }

  void sub(float x, float y) {
    this->x -= x;
    this->y -= y;
  }

  void sub(Vec2& other) {
    this->x -= other.x;
    this->y -= other.y;
  }

  void mult(float scalar) {
    this->x *= scalar;
    this->y *= scalar;
  }

  void div(float scalar) {
    this->x /= scalar;
    this->y /= scalar;
  }
};
