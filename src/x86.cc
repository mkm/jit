#include "x86.hh"

X86CodeGen::X86CodeGen() :
  _buffer()
{
  
}

unsigned char* X86CodeGen::getData() {
  return _buffer.getData();
}

void X86CodeGen::ret() {
  genericOp(0, 0xC3, 0, 0, 0, 0, 0, 0);
}

void X86CodeGen::genericOp(int prefixes, unsigned char opCode, int mod, int reg, int rm, int sib, int imm, int disp) {
  if (prefixes & WordImmediate == prefixes) {
    // what was the byte value?
  }
  _buffer.add(opCode);
}
