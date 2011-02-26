#include <stdio.h>

#include "x86.hh"
#include "x86-compiler.hh"
#include "il.hh"
#include "gdl.hh"
#include "ssa.hh"

int call(int (*f)()) {
  return (*f)();
}

int main() {
  while (1) {
    char* line = NULL;
    size_t lineBufSize;
    if (getline(&line, &lineBufSize, stdin) == -1) {
      break;
    }
    std::string lineString = line;
    GDL::Parser parser = GDL::Parser(lineString);
    IL::Function* lineFunc = new IL::Function(parser.parseExpression());
    unsigned char* rawCode = X86::compile(lineFunc);
    int (*callableCode)() = (int (*)())rawCode;
    printf("%i\n", call(callableCode));
  }
  return 0;
}
