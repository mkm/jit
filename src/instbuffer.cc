#include <sys/mman.h>
#include <stdlib.h>

#include "instbuffer.hh"

#define PAGESIZE 4096

InstBuffer::InstBuffer() :
  _length(PAGESIZE),
  _pos(0)
{
  _data = (unsigned char*)mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

unsigned char* InstBuffer::getData() {
  return _data;
}

size_t InstBuffer::pos() {
  return _pos;
}

void InstBuffer::ensureLength() {
  if (_pos >= _length) {
    _data = (unsigned char*)mremap(_data, _length, _length + PAGESIZE, MREMAP_MAYMOVE);
    _length += PAGESIZE;
  }
}
