#ifndef IL_COMPILER_H
#define IL_COMPILER_H

#include "il.hh"
#include "namegen.hh"
#include "ssa.hh"
#include <string>

namespace IL {
  SSA::Block* compile(Function*);

  class Compiler {
  public:
    Compiler(Function*);

    SSA::Block* compile();
    void compileFunction(Function*);
    void compileExpression(Expression*, std::string&);
    void compileAddExpression(AddExpression*, std::string&);
    void compileSubtractExpression(SubtractExpression*, std::string&);
    void compileIntConstExpression(IntConstExpression*, std::string&);
    
  private:
    Function* _func;
    SSA::Block* _block;
    NameGen _nameGen;
  };
}

#endif
