#include <stdio.h>

#include "x86.hh"
#include "il.hh"
#include "x86-compiler.hh"

int call(int (*f)()) {
  return (*f)();
}

int main() {
  IL::Function* func = new IL::Function(new IL::AddExpression(new IL::IntConstExpression(3), new IL::IntConstExpression(5)));
  unsigned char* data = X86::compile(func);
  int (*funcCode)() = (int (*)())data;
  printf("%i\n", call(funcCode));
  return 0;
}
