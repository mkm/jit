#include "x86.hh"

namespace X86 {
  const Reg32 Reg32::eax = 0b000;
  const Reg32 Reg32::ebx = 0b011;
  const Reg32 Reg32::ecx = 0b001;
  const Reg32 Reg32::edx = 0b010;
  const Reg32 Reg32::edi = 0b111;
  const Reg32 Reg32::esi = 0b110;
  const Reg32 Reg32::esp = 0b100;
  const Reg32 Reg32::ebp = 0b101;

  Reg32::Reg32(unsigned char regCode) :
    _regCode(regCode)
  {

  }

  unsigned char Reg32::regCode() {
    return _regCode;
  }

  const Scale Scale::none = -1;
  const Scale Scale::one = 0;
  const Scale Scale::two = 1;
  const Scale Scale::four = 2;
  const Scale Scale::eight = 3;

  Scale::Scale(unsigned int value) :
    _value(value)
  {
  
  }

  unsigned int Scale::value() {
    return _value;
  }

  bool Scale::isNone() {
    return _value == Scale::none._value;
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

  Mem32::Mem32(unsigned int value) :
    _value(value)
  {
  
  }

  unsigned int Mem32::value() {
    return _value;
  }

  void Mem32::encode(InstBuffer& buf) {
    buf.add((unsigned char)(_value >> 0x00));
    buf.add((unsigned char)(_value >> 0x08));
    buf.add((unsigned char)(_value >> 0x10));
    buf.add((unsigned char)(_value >> 0x18));
  }

  ModRM::ModRM(unsigned char mod, Reg32 reg, Reg32 rm) :
    _value((mod << 6) | (reg.regCode() << 3) | (rm.regCode() << 0))
  {
  
  }

  void ModRM::encode(InstBuffer& buf) {
    buf << _value;
  }

  SIB::SIB(Scale scale, Reg32 index, Reg32 base) :
    _value((scale.value() << 6) | (index.regCode() << 3) | (base.regCode() << 0))
  {
  
  }

  void SIB::encode(InstBuffer& buf) {
    buf << _value;
  }

  Ptr32::Ptr32(Mem32 displacement, Reg32 base, Reg32 index, Scale scale) :
    _displacement(displacement),
    _base(base),
    _index(index),
    _scale(scale)
  {

  }

  Mem32 Ptr32::displacement() {
    return _displacement;
  }

  Reg32 Ptr32::base() {
    return _base;
  }

  Reg32 Ptr32::index() {
    return _index;
  }

  Scale Ptr32::scale() {
    return _scale;
  }

  SIB Ptr32::sib() {
    return SIB(_scale, _index, _base);
  }

  CodeGen::CodeGen() :
    _buffer()
  {
  
  }

  unsigned char* CodeGen::getData() {
    return _buffer.getData();
  }

  void CodeGen::add(Reg32 regD, Reg32 regS) {
    _buffer << 0x01 << ModRM(0b11, regS, regD);
  }

  void CodeGen::add(Reg32 reg, Imm32 imm) {
    _buffer << 0x81 << ModRM(0b11, 0b000, reg) << imm;
  }

  void CodeGen::mov(Reg32 regD, Reg32 regS) {
    _buffer << 0x89 << ModRM(0b11, regS, regD);
  }

  void CodeGen::mov(Reg32 reg, Imm32 imm) {
    _buffer << 0xC7 << ModRM(0b11, 0b000, reg) << imm;
  }

  void CodeGen::mov(Reg32 reg, Mem32 mem) {
    _buffer << 0x8B << ModRM(0b00, reg, 0b101) << mem;
  }

  void CodeGen::mov(Reg32 reg, Ptr32 ptr) {
    if (ptr.scale().isNone()) {
      _buffer << 0x8B << ModRM(0b10, reg, ptr.base()) << ptr.displacement();
    } else {
      _buffer << 0x8B << ModRM(0b10, reg, 0b100) << ptr.sib() << ptr.displacement();
    }
  }

  void CodeGen::push(Reg32 reg) {
    _buffer << (0x50 + reg.regCode());
  }

  void CodeGen::pop(Reg32 reg) {
    _buffer << (0x58 + reg.regCode());
  }

  void CodeGen::ret() {
    _buffer << 0xC3;
  }
}
