#ifndef GDL_H
#define GDL_H

#include <string>
#include "il.hh"

namespace GDL {
  enum TokenType {
    IdentToken,
    OpToken,
    IntLitToken,
    EOFToken
  };

  std::string tokenTypeString(TokenType);
  
  class Token {
  public:
    Token(TokenType, std::string);
    Token(TokenType, int);

    TokenType type() const;
    std::string value() const;
    int intValue() const;
    std::string toString() const;

  private:
    TokenType _type;
    std::string _value;
    int _intValue;
  };

  class Tokeniser {
  public:
    Tokeniser(std::string&);

    std::vector<Token> tokenise();
    
  private:
    std::string::const_iterator _pos;
    std::string::const_iterator _end;
    std::vector<Token> _tokens;

    void add(TokenType, std::string);
    void add(TokenType, int);
    void number();
    void ident();
    bool isDigit(char);
    bool isLetter(char);
    bool isWhiteSpace(char);
  };
  
  class Parser {
  public:
    Parser(const std::vector<Token>&);

    void parseEOF();
    IL::Expression* parseExpression();
    IL::Expression* parseAddExpression();
    IL::IntConstExpression* parseIntConstExpression();

  private:
    std::vector<Token>::const_iterator _pos;

    void error(TokenType) __attribute__((noreturn));
  };
}

#endif
