#include "ssa.hh"

namespace SSA {
  Instruction::Instruction(InstructionOp op, InstructionArg dest) :
    _op(op),
    _dest(dest),
    _srcA(),
    _srcB(),
    _immediate()
  {

  }

  Instruction::Instruction(InstructionOp op, InstructionArg dest, int immediate) :
    _op(op),
    _dest(dest),
    _srcA(),
    _srcB(),
    _immediate(immediate)
  {
    
  }
  
  Instruction::Instruction(InstructionOp op, InstructionArg dest, InstructionArg srcA) :
    _op(op),
    _dest(dest),
    _srcA(srcA),
    _srcB(),
    _immediate()
  {

  }

  Instruction::Instruction(InstructionOp op, InstructionArg dest, InstructionArg srcA, InstructionArg srcB) :
    _op(op),
    _dest(dest),
    _srcA(srcA),
    _srcB(srcB),
    _immediate()
  {
    
  }

  InstructionOp Instruction::op() const {
    return _op;
  }

  InstructionArg Instruction::dest() const {
    return _dest;
  }

  InstructionArg Instruction::srcA() const {
    return _srcA;
  }

  InstructionArg Instruction::srcB() const {
    return _srcB;
  }

  int Instruction::immediate() const {
    return _immediate;
  }
  
  Block::Block() :
    _instructions()
  {

  }

  const std::vector<Instruction>& Block::instructions() {
    return _instructions;
  }

  void Block::add(Instruction inst) {
    _instructions.push_back(inst);
  }
}
