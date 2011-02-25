#include "gdl.hh"
#include "panic.hh"

namespace GDL {
  Parser::Parser(std::string& s) :
    _pos(s.begin()),
    _end(s.end())
  {
    
  }

  IL::Expression* Parser::parseExpression() {
    return parseAddExpression();
  }

  IL::Expression* Parser::parseAddExpression() {
    IL::IntConstExpression* expr = parseIntConstExpression();
    if (_pos == _end || *_pos == '\n') {
      return expr;
    } else if (*_pos == '+') {
      _pos++;
      return new IL::AddExpression(expr, parseAddExpression());
    } else {
      panic("Parse error in add expression.\n");
    }
  }

  IL::IntConstExpression* Parser::parseIntConstExpression() {
    char c = *_pos;
    if ('0' <= c && c <= '9') {
      _pos++;
      return new IL::IntConstExpression(c - '0');
    } else {
      panic("Parse error in int const expression.\n");
    }
  }
}
