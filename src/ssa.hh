#ifndef SSA_H
#define SSA_H

#include <string>
#include <vector>

namespace SSA {
  enum InstructionOp {
    LabelOp,
    RetOp,
    MoveOp,
    AddOp,
    LoadConstOp
  };

  typedef std::string InstructionArg;
  
  class Instruction {
  public:
    Instruction(InstructionOp, InstructionArg);
    Instruction(InstructionOp, InstructionArg, int);
    Instruction(InstructionOp, InstructionArg, InstructionArg);
    Instruction(InstructionOp, InstructionArg, InstructionArg, InstructionArg);

    InstructionOp op() const;
    InstructionArg dest() const;
    InstructionArg srcA() const;
    InstructionArg srcB() const;
    int immediate() const;

  private:
    InstructionOp _op;
    InstructionArg _dest, _srcA, _srcB;
    int _immediate;
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
