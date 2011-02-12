#include <stdio.h>

#include "x86.hh"

int main() {
  X86CodeGen gen;
  gen.ret();
  int (*func)() = (int (*)())gen.getData();
  printf("%i\n", (*func)());
  return 0;
}
