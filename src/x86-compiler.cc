#include <sstream>
#include "x86-compiler.hh"
#include "panic.hh"
#include "x86.hh"
#include "instbuffer.hh"

namespace X86 {
  unsigned char* compile(IL::Function* func) {
    FunctionCompiler comp(func);
    return comp.compile();
  }

  FunctionCompiler::FunctionCompiler(IL::Function* func) :
    _func(func),
    _stackMan(),
    _gen(),
    _nameCounter(0)
  {
    
  }

  unsigned char* FunctionCompiler::compile() {
    std::string retloc = genName();
    _gen.push(Reg32::ebp);
    _gen.mov(Reg32::ebp, Reg32::esp);
    size_t stackSpacePos = _gen.add(Reg32::esp, X86::Imm32(0));
    compileExpression(_func->body(), retloc);
    _gen.mov(Reg32::esp, Reg32::ebp);
    _gen.pop(Reg32::ebp);
    _gen.ret();
    _gen.buffer().alter(stackSpacePos, X86::Imm32(_stackMan.stackSpace()));
    return _gen.getData();
  }

  std::string FunctionCompiler::genName() {
    std::stringstream s;
    s << "__name_" << _nameCounter;
    _nameCounter++;
    return s.str();
  }
  
  void FunctionCompiler::compileExpression(IL::Expression* expr, std::string retloc) {
    IL::AddExpression* addExpr;
    IL::IntConstExpression* intConstExpr;
    if (addExpr = dynamic_cast<IL::AddExpression*>(expr)) {
      compileAddExpression(addExpr, retloc);
    } else if (intConstExpr = dynamic_cast<IL::IntConstExpression*>(expr)) {
      compileIntConstExpression(intConstExpr, retloc);
    } else {
      panic("Unknown expression type.\n");
    }
  }

  void FunctionCompiler::compileAddExpression(IL::AddExpression* addExpr, std::string retloc) {
    std::string leftLoc = genName();
    std::string rightLoc = genName();
    compileExpression(addExpr->leftArg(), leftLoc);
    compileExpression(addExpr->rightArg(), rightLoc);
    _gen.mov(Reg32::eax, Ptr32(_stackMan.stackIndex(leftLoc), Reg32::ebp, Reg32::eax, Scale::none));
    _gen.mov(Reg32::ebx, Ptr32(_stackMan.stackIndex(rightLoc), Reg32::ebp, Reg32::eax, Scale::none));
    _gen.add(Reg32::eax, Reg32::ebx);
    _gen.mov(Ptr32(_stackMan.stackIndex(retloc), Reg32::ebp, Reg32::eax, Scale::none), Reg32::eax);
  }

  void FunctionCompiler::compileIntConstExpression(IL::IntConstExpression* expr, std::string retloc) {
    _gen.mov(Reg32::eax, Imm32(expr->value()));
    _gen.mov(Ptr32(_stackMan.stackIndex(retloc), Reg32::ebp, Reg32::eax, Scale::none), Reg32::eax);
  }
}
