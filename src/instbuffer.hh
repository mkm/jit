#ifndef INSTBUFFER_H
#define INSTBUFFER_H

#include <stdlib.h>

class InstBuffer {
public:
  InstBuffer();
  unsigned char* getData();
  size_t pos();
  template<typename T>
  void alter(size_t, T);
  template<typename T>
  void add(T);
  template<typename T>
  InstBuffer& operator<<(T);

private:
  unsigned char* _data;
  size_t _length;
  size_t _pos;

  void ensureLength();
};

template<typename T>
inline void InstBuffer::alter(size_t pos, T value) {
  size_t curPos = _pos;
  _pos = pos;
  add(value);
  _pos = curPos;
}

template<typename T>
inline void InstBuffer::add(T value) {
  value.encode(*this);
}

template<>
inline void InstBuffer::add<unsigned char>(unsigned char value) {
  ensureLength();
  _data[_pos] = value;
  _pos += 1;
}

template<>
inline void InstBuffer::add<int>(int value) {
  add((unsigned char)value);
}

template<typename T>
inline InstBuffer& InstBuffer::operator<<(T value) {
  add(value);
  return *this;
}

#endif
