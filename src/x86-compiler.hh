#ifndef X86_COMPILER_H
#define X86_COMPILER_H

#include "il.hh"
#include "instbuffer.hh"
#include "x86.hh"
#include "x86-storage.hh"

namespace X86 {
  unsigned char* compile(IL::Function*);

  class FunctionCompiler {
  public:
    FunctionCompiler(IL::Function*);

    unsigned char* compile();

  private:
    IL::Function* _func;
    StackManager _stackMan;
    CodeGen _gen;
    int _nameCounter;

    std::string genName();
    void compileExpression(IL::Expression*, std::string retloc);
    void compileAddExpression(IL::AddExpression*, std::string retloc);
    void compileIntConstExpression(IL::IntConstExpression*, std::string retloc);
  };
}

#endif
