#include <vector>
#include "x86-compiler.hh"
#include "panic.hh"
#include "x86.hh"
#include "instbuffer.hh"

namespace X86 {
  unsigned char* compile(SSA::Block* block) {
    FunctionCompiler comp(block);
    return comp.compile();
  }

  FunctionCompiler::FunctionCompiler(SSA::Block* block) :
    _block(block),
    _stackMan(),
    _gen()
  {
    
  }

  unsigned char* FunctionCompiler::compile() {
    _gen.push(Reg32::ebp);
    _gen.mov(Reg32::ebp, Reg32::esp);
    size_t stackSpacePos = _gen.add(Reg32::esp, X86::Imm32(0));
    compileBlock();
    _gen.mov(Reg32::esp, Reg32::ebp);
    _gen.pop(Reg32::ebp);
    _gen.ret();
    _gen.buffer().alter(stackSpacePos, X86::Imm32(_stackMan.stackSpace()));
    return _gen.getData();
  }

  void FunctionCompiler::compileBlock() {
    const std::vector<SSA::Instruction>& ins = _block->instructions();
    std::vector<SSA::Instruction>::const_iterator i, end;
    for (i = ins.begin(), end = ins.end(); i != end; ++i) {
      compileInstruction(*i);
    }
  }

  void FunctionCompiler::compileInstruction(const SSA::Instruction& in) {
    switch (in.op()) {
    case SSA::RetOp:
      _gen.mov(Reg32::eax, Ptr32(_stackMan.stackIndex(in.dest()), Reg32::ebp, Reg32::eax, Scale::none));
      break;
    case SSA::MoveOp:
      _gen.mov(Reg32::eax, Ptr32(_stackMan.stackIndex(in.srcA()), Reg32::ebp, Reg32::eax, Scale::none));
      _gen.mov(Ptr32(_stackMan.stackIndex(in.dest()), Reg32::ebp, Reg32::eax, Scale::none), Reg32::eax);
      break;
    case SSA::AddOp:
      _gen.mov(Reg32::eax, Ptr32(_stackMan.stackIndex(in.srcA()), Reg32::ebp, Reg32::eax, Scale::none));
      _gen.mov(Reg32::ebx, Ptr32(_stackMan.stackIndex(in.srcB()), Reg32::ebp, Reg32::eax, Scale::none));
      _gen.add(Reg32::eax, Reg32::ebx);
      _gen.mov(Ptr32(_stackMan.stackIndex(in.dest()), Reg32::ebp, Reg32::eax, Scale::none), Reg32::eax);
      break;
    case SSA::SubOp:
      _gen.mov(Reg32::eax, Ptr32(_stackMan.stackIndex(in.srcA()), Reg32::ebp, Reg32::eax, Scale::none));
      _gen.mov(Reg32::ebx, Ptr32(_stackMan.stackIndex(in.srcB()), Reg32::ebp, Reg32::eax, Scale::none));
      _gen.sub(Reg32::eax, Reg32::ebx);
      _gen.mov(Ptr32(_stackMan.stackIndex(in.dest()), Reg32::ebp, Reg32::eax, Scale::none), Reg32::eax);
      break;
    case SSA::LoadConstOp:
      _gen.mov(Reg32::eax, Imm32(in.immediate()));
      _gen.mov(Ptr32(_stackMan.stackIndex(in.dest()), Reg32::ebp, Reg32::eax, Scale::none), Reg32::eax);
      break;
    default:
      panic("Unknown instruction.\n");
    }
  }
}
