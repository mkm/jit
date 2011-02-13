#include "x86.hh"

const Reg32 Reg32::eax = 0b000;
const Reg32 Reg32::ebx = 0b011;
const Reg32 Reg32::ecx = 0b001;
const Reg32 Reg32::edx = 0b010;
const Reg32 Reg32::edi = 0b111;
const Reg32 Reg32::esi = 0b110;
const Reg32 Reg32::esp = 0b100;
const Reg32 Reg32::ebp = 0b101;

Reg32::Reg32(unsigned int regCode) :
  _regCode(regCode)
{

}

unsigned int Reg32::regCode() {
  return _regCode;
}

Imm32::Imm32(unsigned int value) :
  _value(value)
{

}

unsigned int Imm32::value() {
  return _value;
}

void Imm32::encode(InstBuffer& buf) {
  buf.add((unsigned char)(_value >> 0x00));
  buf.add((unsigned char)(_value >> 0x08));
  buf.add((unsigned char)(_value >> 0x10));
  buf.add((unsigned char)(_value >> 0x18));
}

ModRM::ModRM(unsigned char mod, unsigned char reg, unsigned char rm) :
  _mod(mod),
  _reg(reg),
  _rm(rm)
{

}

void ModRM::encode(InstBuffer& buf) {
  unsigned char value = (_mod << 6) | (_reg << 3) | (_rm << 0);
  buf.add(value);
}

X86CodeGen::X86CodeGen() :
  _buffer()
{
  
}

unsigned char* X86CodeGen::getData() {
  return _buffer.getData();
}

void X86CodeGen::mov(Reg32 regD, Reg32 regS) {
  _buffer.add(0x89);
  ModRM(0b11, regS.regCode(), regD.regCode()).encode(_buffer);
}

void X86CodeGen::mov(Reg32 reg, Imm32 imm) {
  _buffer.add(0xC7);
  ModRM(0b11, 0b000, reg.regCode()).encode(_buffer);
  imm.encode(_buffer);
}

void X86CodeGen::ret() {
  _buffer.add(0xC3);
}