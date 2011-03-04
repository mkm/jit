#include "il.hh"

namespace IL {
  Object::~Object() {
    
  }
  
  AddExpression::AddExpression(Expression* leftArg, Expression* rightArg) :
    _leftArg(leftArg),
    _rightArg(rightArg)
  {

  }

  std::string AddExpression::toString() {
    return "(AddExpression " + _leftArg->toString() + " " + _rightArg->toString() + ")";
  }
  
  Expression* AddExpression::leftArg() {
    return _leftArg;
  }
  
  Expression* AddExpression::rightArg() {
    return _rightArg;
  }

  SubtractExpression::SubtractExpression(Expression* leftArg, Expression* rightArg) :
    _leftArg(leftArg),
    _rightArg(rightArg)
  {

  }

  std::string SubtractExpression::toString() {
    return "(SubtractExpression" + _leftArg->toString() + " " + _rightArg->toString() + ")";
  }
  
  Expression* SubtractExpression::leftArg() {
    return _leftArg;
  }
  
  Expression* SubtractExpression::rightArg() {
    return _rightArg;
  }

  IntConstExpression::IntConstExpression(int value) :
    _value(value)
  {

  }

  std::string IntConstExpression::toString() {
    return "(IntConstExpression)";
  }
  
  int IntConstExpression::value() {
    return _value;
  }
  
  VariableExpression::VariableExpression(std::string name) :
    _name(name)
  {

  }

  std::string VariableExpression::toString() {
    return "(VariableExpression" + _name + ")";
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

  std::string Function::toString() {
    return "(Function " + _body->toString() + ")";
  }
  
  std::vector<std::string>& Function::params() {
    return _params;
  }
  
  Expression* Function::body() {
    return _body;
  }
}
