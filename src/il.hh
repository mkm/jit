#ifndef IL_H
#define IL_H

#include <vector>
#include <string>

namespace IL {
  class Object {
  public:
    virtual ~Object();
  };

  class Expression : public Object {
  
  };

  class AddExpression : public Expression {
  public:
    AddExpression(Expression*, Expression*);

    Expression* leftArg();
    Expression* rightArg();
    
  private:
    Expression* _leftArg;
    Expression* _rightArg;
  };

  class IntConstExpression : public Expression {
  public:
    IntConstExpression(int);

    int value();

  private:
    int _value;
  };
  
  class VariableExpression : public Expression {
  public:
    VariableExpression(std::string);

    std::string& name();

  private:
    std::string _name;
  };

  class Function : public Object {
  public:
    Function(Expression*);
    Function(std::vector<std::string>, Expression*);

    std::vector<std::string>& params();
    Expression* body();
    
  private:
    std::vector<std::string> _params;
    Expression* _body;
  };
}

#endif
