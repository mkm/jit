#ifndef GDL_H
#define GDL_H

#include <string>
#include "il.hh"

namespace GDL {
  class Parser {
  public:
    Parser(std::string&);

    IL::Expression* parseExpression();
    IL::Expression* parseAddExpression();
    IL::IntConstExpression* parseIntConstExpression();

  private:
    std::string::const_iterator _pos;
    std::string::const_iterator _end;
  };
}

#endif
