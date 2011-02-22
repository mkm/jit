#include <stdio.h>

#include "x86.hh"
#include "il.hh"
#include "x86-compiler.hh"

int call(int (*f)()) {
  return (*f)();
}

int main() {
  /*
  int x = 14;
  X86::CodeGen gen;
  gen.push(X86::Reg32::ebp);
  gen.mov(X86::Reg32::ebp, X86::Reg32::esp);
  gen.mov(X86::Reg32::eax, X86::Ptr32(8, X86::Reg32::ebp, 0, X86::Scale::none));
  gen.add(X86::Reg32::eax, X86::Imm32(1));
  gen.mov(X86::Reg32::esp, X86::Reg32::ebp);
  gen.pop(X86::Reg32::ebp);
  gen.ret();
  */
  IL::Function* func = new IL::Function(new IL::AddExpression(new IL::IntConstExpression(3), new IL::IntConstExpression(5)));
  unsigned char* data = X86::compile(func);
  int (*funcCode)() = (int (*)())data;
  printf("%i\n", call(funcCode));
  return 0;
}
