#include <stdio.h>

#include "x86.hh"

int main() {
  int x = 14;
  X86CodeGen gen;
  gen.mov(Reg32::eax, Mem32((unsigned int)&x));
  gen.mov(Reg32::ebx, Imm32(3));
  gen.add(Reg32::ebx, Imm32(2));
  gen.add(Reg32::eax, Reg32::ebx);
  gen.ret();
  unsigned char* data = gen.getData();
  int (*func)() = (int (*)())data;
  printf("%i\n", (*func)());
  return 0;
}
