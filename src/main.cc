#include <stdio.h>

#include "x86.hh"

int main() {
  X86CodeGen gen;
  gen.mov(Reg32::ecx, Imm32(1337));
  gen.mov(Reg32::eax, Reg32::ecx);
  gen.ret();
  unsigned char* data = gen.getData();
  int (*func)() = (int (*)())data;
  printf("%i\n", (*func)());
  return 0;
}
