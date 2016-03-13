#pragma once
#include <cstdint>

static const size_t MAXIMUM_SIZE = 65536;

template <class T> class JuuhVector {
public:
  JuuhVector() { elements = new T[MAXIMUM_SIZE]; }

  JuuhVector(const JuuhVector &other) {
    elements = new T[MAXIMUM_SIZE];

    for (size_t i = 0; i < other.size(); ++i) {
      elements[i] = other[i];
    }

    currentIndex = other.currentIndex;
  }

  ~JuuhVector() {}

  void push_back(T const &item) { elements[currentIndex++] = item; }

  size_t size() const { return currentIndex; }

  T &operator[](size_t index) const { return elements[index]; }

private:
  T *elements;
  size_t currentIndex = 0;
};
