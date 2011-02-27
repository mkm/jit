#ifndef X86_COMPILER_H
#define X86_COMPILER_H

#include "il.hh"
#include "instbuffer.hh"
#include "x86.hh"
#include "x86-storage.hh"
#include "ssa.hh"

namespace X86 {
  unsigned char* compile(SSA::Block*);

  class FunctionCompiler {
  public:
    FunctionCompiler(SSA::Block*);

    unsigned char* compile();

  private:
    SSA::Block* _block;
    StackManager _stackMan;
    CodeGen _gen;

    void compileBlock();
    void compileInstruction(const SSA::Instruction&);
  };
}

#endif
