#ifndef X86_H
#define X86_H

#include "instbuffer.hh"

class X86CodeGen {
public:
  X86CodeGen();

  unsigned char* getData();

  void ret();

private:
  InstBuffer _buffer;

  void genericOp(int, unsigned char, int, int, int, int, int, int);
};

enum Prefix {
  WordImmediate
};

#endif
