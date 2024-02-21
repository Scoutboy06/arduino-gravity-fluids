#pragma once

#define DEFAULT_CAPACITY 4

template <typename T>
class List {
 public:
  List()
      : _data(new T[DEFAULT_CAPACITY]),
        _capacity(DEFAULT_CAPACITY),
        _length(0) {}

  /**
   * @brief Object destructor
   */
  ~List() { delete[] _data; }

  /**
   * @brief Pushes a value onto the list. If the capacity of the list would
   * overflow, it re-allocates itself with double it's previous capactiy
   * @param value The value to push onto the back of the list
   */
  void push(const T& value) {
    if (_length >= _capacity) {  // Re-allocate and resize array
      size_t newCapacity = _capacity * 2;
      T* newData = new T[newCapacity];

      for (size_t i = 0; i < _length; i++) {
        newData[i] = _data[i];
      }

      delete[] _data;
      _data = newData;
      _capacity = newCapacity;
    }

    _data[_length] = value;
    _length++;
  }

  /**
   * @brief Clears the list of it's values. Note that it will keep it's previous
   * capacity.
   */
  void clear() { _length = 0; }

  /**
   * @return The length of the List
   */
  size_t len() const { return _length; }

  /**
   * @brief The beginning of the list. Used for iterating over the data
   */
  T* begin() { return _data; }

  /**
   * @brief The end of the list. Used for iterating over the data
   */
  T* end() { return _data + _length; }

  // T& operator const {
  //   if (index >= _length) {
  //     Serial.println(F("List index out of range"));
  //     throw;
  //   }

  //   return _data[index];
  // }

 private:
  T* _data;
  size_t _capacity;
  size_t _length;

  size_t reserve(size_t size) {}
};