#ifndef SSA_H
#define SSA_H

#include <string>
#include <vector>

namespace SSA {
  enum InstructionOp {
    LabelOp,
    MoveOp,
    AddOp
  };

  typedef std::string InstructionArg;
  
  class Instruction {
  public:
    Instruction(InstructionOp, InstructionArg);
    Instruction(InstructionOp, InstructionArg, InstructionArg);
    Instruction(InstructionOp, InstructionArg, InstructionArg, InstructionArg);

    InstructionArg dest();
    InstructionArg srcA();
    InstructionArg srcB();

  private:
    InstructionOp _op;
    InstructionArg _dest, _srcA, _srcB;
  };
  
  class Block {
  public:
    Block();

    const std::vector<Instruction>& instructions();
    void add(Instruction);

  private:
    std::vector<Instruction> _instructions;
  };
};

#endif
