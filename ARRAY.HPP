#ifndef __ARRAY_HPP__
#define __ARRAY_HPP__

#include "types.hpp"

template<class T>
class Array {
public:
  T *data;
  int64_t usedSize;
  int64_t allocatedSize;

  Array() {
    usedSize = 0;
    allocatedSize = 100;
    data = new T[allocatedSize];
  }

  const Array &operator=(const Array &b) {
    T *copy = new T[b.allocatedSize];
    for (int64_t i = 0; i < b.usedSize; i++)
      copy[i] = b.data[i];
    if (data != NULL) delete[] data;
    data = copy;
    usedSize = b.usedSize;
    allocatedSize = b.allocatedSize;
    return *this;
  }
  
  ~Array() {
    if (data != NULL) delete[] data;
    usedSize = 0;
    allocatedSize = 0;
  }
  
  void reAlloc(int64_t numElements) {
    T *data2 = new T[numElements];
    for (int64_t i = 0; i < numElements; i++)
      data2[i] = i < usedSize ? data[i] : T();
    delete[] data;
    data = data2;
    allocatedSize = numElements;
  }
  
  void resize(int64_t numElements) {
    if (numElements<allocatedSize) {
      usedSize = numElements;
    } else {
      reAlloc(numElements*1.5);
      usedSize = numElements;
    }
  }
  
  void push_back(const T& elem) {
    if (usedSize < allocatedSize) {
      data[usedSize] = elem;
      usedSize++;
    } else {
      reAlloc(allocatedSize*1.5);
      data[usedSize] = elem;
      usedSize++;
    }
  }
  
  void clear() {
    usedSize = 0;
  }
  
  int64_t size() {
    return usedSize;
  }
  
  bool empty() {
    return size()==0;
  }
  
  T &operator[](int64_t index) {
    return data[index];
  }
  
  T& back() {
    return data[usedSize-1];
  }
  
  void pop_back() {
    if (usedSize > 0)
      usedSize--;
  }
};
#endif //__ARRAY_HPP__