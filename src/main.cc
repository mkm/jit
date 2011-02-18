#include <stdio.h>

#include "x86.hh"

int main() {
  int x = 14;
  X86CodeGen gen;
  gen.push(Reg32::ebp);
  gen.mov(Reg32::ebp, Reg32::esp);
  gen.mov(Reg32::eax, Ptr32(8, Reg32::ebp, 0, Scale::none));
  gen.add(Reg32::eax, Imm32(1));
  gen.mov(Reg32::esp, Reg32::ebp);
  gen.pop(Reg32::ebp);
  gen.ret();
  unsigned char* data = gen.getData();
  int (*func)(int) = (int (*)(int))data;
  printf("%i\n", (*func)(x));
  return 0;
}
