#ifndef INSTBUFFER_H
#define INSTBUFFER_H

#include <stdlib.h>

class InstBuffer {
public:
  InstBuffer();
  unsigned char* getData();
  void add(unsigned char);

private:
  unsigned char* _data;
  size_t _length;
  size_t _pos;

  void ensureLength();
};

#endif
