#ifndef NAMEGEN_H
#define NAMEGEN_H

#include <string>

class NameGen {
public:
  NameGen();

  std::string next();
private:
  int _nameCounter;
};

#endif
