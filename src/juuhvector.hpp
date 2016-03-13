#pragma once
#include <cstdint>
#include <cstring>

template <class T> class JuuhVector {
public:
  JuuhVector() { elements = new T[currentMaximumSize]; }

  JuuhVector(const JuuhVector &other) {
    elements = new T[other.currentMaximumSize];

    std::memcpy(elements, other.elements, other.currentIndex * sizeof(T));

    currentIndex = other.currentIndex;
    currentMaximumSize = other.currentMaximumSize;
  }

  ~JuuhVector() {}

  void push_back(T const &item) {
    if (currentIndex == currentMaximumSize) {
      resize();
    }

    elements[currentIndex++] = item;
  }

  size_t size() const { return currentIndex; }

  T &operator[](size_t index) const { return elements[index]; }

private:
  T *elements;
  size_t currentIndex = 0;
  size_t currentMaximumSize = 4;

  void resize() {
    currentMaximumSize <<= 1;

    T* temp = new T[currentMaximumSize];

    std::memcpy(temp, elements, (currentIndex) * sizeof(T));

    delete[] elements;
    elements = temp;
  }
};
