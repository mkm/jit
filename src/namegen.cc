#include <sstream>
#include "namegen.hh"

NameGen::NameGen() :
  _nameCounter(0)
{
  
}

std::string NameGen::next() {
  std::stringstream s;
  s << "__name_" << _nameCounter;
  _nameCounter++;
  return s.str();
}
