#include "ssa.hh"

namespace SSA {
  Instruction::Instruction(InstructionOp op, InstructionArg dest) :
    _op(op),
    _dest(dest),
    _srcA(),
    _srcB()
  {

  }

  Instruction::Instruction(InstructionOp op, InstructionArg dest, InstructionArg srcA) :
    _op(op),
    _dest(dest),
    _srcA(srcA),
    _srcB()
  {

  }

  Instruction::Instruction(InstructionOp op, InstructionArg dest, InstructionArg srcA, InstructionArg srcB) :
    _op(op),
    _dest(dest),
    _srcA(srcA),
    _srcB(srcB)
  {

  }

  InstructionArg Instruction::dest() {
    return _dest;
  }

  InstructionArg Instruction::srcA() {
    return _srcA;
  }

  InstructionArg Instruction::srcB() {
    return _srcB;
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
