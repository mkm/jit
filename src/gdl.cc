#include "gdl.hh"
#include "panic.hh"

namespace GDL {
  std::string tokenTypeString(TokenType type) {
    switch (type) {
    case IdentToken:
      return "IdentToken";
    case OpToken:
      return "OpToken";
    case IntLitToken:
      return "IntLitToken";
    case EOFToken:
      return "EOFToken";
    default:
      panic("Unknown token type.\n");
    }
  }
  
  Token::Token(TokenType type, std::string value) :
    _type(type),
    _value(value),
    _intValue(0)
  {

  }

  Token::Token(TokenType type, int intValue) :
    _type(type),
    _value(),
    _intValue(intValue)
  {
    
  }

  TokenType Token::type() const {
    return _type;
  }

  std::string Token::value() const {
    return _value;
  }

  int Token::intValue() const {
    return _intValue;
  }

  std::string Token::toString() const {
    std::string s;
    s +=  "(";
    s += tokenTypeString(_type);
    s += ")";
    return s;
  }
  
  Tokeniser::Tokeniser(std::string& s) :
    _pos(s.begin()),
    _end(s.end()),
    _tokens()
  {
    
  }

  std::vector<Token> Tokeniser::tokenise() {
    while (_pos != _end) {
      char c = *_pos;
      switch (c) {
      case '+':
        add(OpToken, "+");
        ++_pos;
        break;
      default:
        if (isDigit(c)) {
          number();
        } else if (isLetter(c)) {
          ident();
        } else if (isWhiteSpace(c)) {
          ++_pos;
        } else {
          panic("Unknown symbol.\n");
        }
      }
    }

    add(EOFToken, 0);
    
    return _tokens;
  }

  void Tokeniser::add(TokenType type, std::string value) {
    _tokens.push_back(Token(type, value));
  }

  void Tokeniser::add(TokenType type, int value) {
    _tokens.push_back(Token(type, value));
  }

  void Tokeniser::number() {
    char c = *_pos;
    int n = 0;
    do {
      n *= 10;
      n += c - '0';
      ++_pos;
      c = *_pos;
    } while (isDigit(c));

    add(IntLitToken, n);
  }

  void Tokeniser::ident() {
    char c = *_pos;
    std::string s;
    do {
      s += c;
      ++_pos;
      c = *_pos;
    } while (isLetter(c));

    add(IdentToken, s);
  }

  bool Tokeniser::isDigit(char c) {
    return '0' <= c && c <= '9';
  }

  bool Tokeniser::isLetter(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_';
  }

  bool Tokeniser::isWhiteSpace(char c) {
    return c == ' ' || c == '\t' || c == '\n';
  }
  
  Parser::Parser(const std::vector<Token>& tokens) :
    _pos(tokens.begin())
  {
    
  }

  void Parser::parseEOF() {
    if ((*_pos).type() != EOFToken) {
      error(EOFToken);
    }
  }
  
  IL::Expression* Parser::parseExpression() {
    return parseAddExpression();
  }

  IL::Expression* Parser::parseAddExpression() {
    IL::Expression* left = parseIntConstExpression();
    if ((*_pos).type() == OpToken) {
      ++_pos;
      IL::Expression* right = parseExpression();
      return new IL::AddExpression(left, right);
    } else {
      return left;
    }
  }

  IL::IntConstExpression* Parser::parseIntConstExpression() {
    if ((*_pos).type() == IntLitToken) {
      return new IL::IntConstExpression((*_pos++).intValue());
    } else {
      error(IntLitToken);
    }
  }

  void Parser::error(TokenType expected) {
    std::string s = "Parser: expected '" + tokenTypeString(expected) + "', got " + (*_pos).toString() + ".\n";
    panic(s);
  }
}
