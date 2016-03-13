#pragma once
#include <cstdint>
#include <cstring>

template <class T> class JuuhVector {
public:
  JuuhVector() { elements = new T[currentSize]; }

  // copy some other juuhvector's contents to the new one
  JuuhVector(const JuuhVector &other) {
    elements = new T[other.currentSize];

    std::memcpy(elements, other.elements, other.currentIndex * sizeof(T));

    currentIndex = other.currentIndex;
    currentSize = other.currentSize;
  }

  ~JuuhVector() {}

  // push an item to the vector
  void push_back(T const &item) {
    // resize (double the size) if we're out of space
    if (currentIndex == currentSize) {
      resize();
    }

    elements[currentIndex++] = item;
  }

  size_t size() const { return currentIndex; }

  T &operator[](size_t index) const { return elements[index]; }

private:
  T *elements;
  size_t currentIndex = 0;
  size_t currentSize = 4;

  void resize() {
    // double the size
    currentSize <<= 1;

    // create the new array and copy the old contents into it
    T *temp = new T[currentSize];

    std::memcpy(temp, elements, (currentIndex) * sizeof(T));

    delete[] elements;
    elements = temp;
  }
};
