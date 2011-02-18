#ifndef X86_H
#define X86_H

#include "instbuffer.hh"

class Reg32 {
public:
  Reg32(unsigned int);

  unsigned int regCode();

  static const Reg32 eax, ebx, ecx, edx, edi, esi, esp, ebp;

private:
  unsigned int _regCode;
};

class Imm32 {
public:
  Imm32(unsigned int);

  unsigned int value();
  void encode(InstBuffer&);

private:
  unsigned int _value;
};

class Mem32 {
public:
  Mem32(unsigned int);

  void encode(InstBuffer&);

private:
  unsigned int _value;
};

class ModRM {
public:
  ModRM(unsigned char, Reg32, Reg32);

  void encode(InstBuffer&);

private:
  unsigned char _value;
};

class X86CodeGen {
public:
  X86CodeGen();

  unsigned char* getData();

  void add(Reg32, Reg32);
  void add(Reg32, Imm32);
  void mov(Reg32, Reg32);
  void mov(Reg32, Imm32);
  void mov(Reg32, Mem32);
  void ret();

private:
  InstBuffer _buffer;
};

enum Prefix {
  WordImmediate
};

#endif
