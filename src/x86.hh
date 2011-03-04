#ifndef X86_H
#define X86_H

#include "instbuffer.hh"

namespace X86 {
  class Reg32 {
  public:
    Reg32(unsigned char);

    unsigned char regCode();

    static const Reg32 eax, ebx, ecx, edx, edi, esi, esp, ebp;

  private:
    unsigned char _regCode;
  };

  class Scale {
  public:
    Scale(unsigned int);

    unsigned int value();
    bool isNone();

    static const Scale none, one, two, four, eight;

  private:
    unsigned int _value;
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

    unsigned int value();
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

  class SIB {
  public:
    SIB(Scale, Reg32, Reg32);

    void encode(InstBuffer&);

  private:
    unsigned char _value;
  };

  class Ptr32 {
  public:
    Ptr32(Mem32, Reg32, Reg32, Scale);

    Mem32 displacement();
    Reg32 base();
    Reg32 index();
    Scale scale();
    SIB sib();
  
  private:
    Mem32 _displacement;
    Reg32 _base;
    Reg32 _index;
    Scale _scale;  
  };

  class CodeGen {
  public:
    CodeGen();

    unsigned char* getData();
    InstBuffer& buffer();

    void add(Reg32, Reg32);
    size_t add(Reg32, Imm32);
    void sub(Reg32, Reg32);
    size_t sub(Reg32, Imm32);
    void mov(Reg32, Reg32);
    size_t mov(Reg32, Imm32);
    void mov(Reg32, Mem32);
    void mov(Reg32, Ptr32);
    void mov(Ptr32, Reg32);
    void push(Reg32);
    void pop(Reg32);
    void ret();

  private:
    InstBuffer _buffer;
  };

  enum Prefix {
    WordImmediate
  };
}

#endif
