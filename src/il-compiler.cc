#include "il-compiler.hh"
#include "panic.hh"

namespace IL {
  SSA::Block* compile(Function* func) {
    return Compiler(func).compile();
  }

  Compiler::Compiler(Function* func) :
    _func(func),
    _block(new SSA::Block()),
    _nameGen()
  {
    
  }

  SSA::Block* Compiler::compile() {
    compileFunction(_func);
    return _block;
  }
  
  void Compiler::compileFunction(Function* func) {
    std::string retloc = _nameGen.next();
    compileExpression(func->body(), retloc);
    _block->add(SSA::Instruction(SSA::RetOp, retloc));
  }

  void Compiler::compileExpression(Expression* expr, std::string& retloc) {
    AddExpression* addExpr;
    SubtractExpression* subtractExpr;
    IntConstExpression* intConstExpr;
    if ((addExpr = dynamic_cast<AddExpression*>(expr)) != NULL) {
      compileAddExpression(addExpr, retloc);
    } else if ((subtractExpr = dynamic_cast<SubtractExpression*>(expr)) != NULL) {
      compileSubtractExpression(subtractExpr, retloc);
    } else if ((intConstExpr = dynamic_cast<IntConstExpression*>(expr)) != NULL) {
      compileIntConstExpression(intConstExpr, retloc);
    } else {
      panic("Unknown expression type.\n");
    }
  }

  void Compiler::compileAddExpression(AddExpression* expr, std::string& retloc) {
    std::string leftloc = _nameGen.next();
    std::string rightloc = _nameGen.next();
    compileExpression(expr->leftArg(), leftloc);
    compileExpression(expr->rightArg(), rightloc);
    _block->add(SSA::Instruction(SSA::AddOp, retloc, leftloc, rightloc));
  }

  void Compiler::compileSubtractExpression(SubtractExpression* expr, std::string& retloc) {
    std::string leftloc = _nameGen.next();
    std::string rightloc = _nameGen.next();
    compileExpression(expr->leftArg(), leftloc);
    compileExpression(expr->rightArg(), rightloc);
    _block->add(SSA::Instruction(SSA::SubOp, retloc, leftloc, rightloc));
  }

  void Compiler::compileIntConstExpression(IntConstExpression* expr, std::string& retloc) {
    _block->add(SSA::Instruction(SSA::LoadConstOp, retloc, expr->value()));
  }
}

