#include "il.hh"

namespace IL {
  Object::~Object() {
    
  }
  
  AddExpression::AddExpression(Expression* leftArg, Expression* rightArg) :
    _leftArg(leftArg),
    _rightArg(rightArg)
  {

  }

  Expression* AddExpression::leftArg() {
    return _leftArg;
  }
  
  Expression* AddExpression::rightArg() {
    return _rightArg;
  }

  IntConstExpression::IntConstExpression(int value) :
    _value(value)
  {

  }

  int IntConstExpression::value() {
    return _value;
  }
  
  VariableExpression::VariableExpression(std::string name) :
    _name(name)
  {

  }

  std::string& VariableExpression::name() {
    return _name;
  }

  Function::Function(Expression* body) :
    _params(),
    _body(body)
  {

  }
  
  Function::Function(std::vector<std::string> params, Expression* body) :
    _params(params),
    _body(body)
  {

  }

  std::vector<std::string>& Function::params() {
    return _params;
  }
  
  Expression* Function::body() {
    return _body;
  }
}
