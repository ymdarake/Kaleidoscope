#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace AST {

/// Expr - Base class for all expression nodes.
class Expr {
public:
  virtual ~Expr() = default;
};

/// NumberExpr - Expression class for numeric literals like "1.0".
class NumberExpr : public Expr {
  double Val;

public:
  NumberExpr(double Val) : Val(Val) {}
};

/// VariableExpr - Expression class for referencing a variable, like "a".
class VariableExpr : public Expr {
  std::string Name;

public:
  VariableExpr(const std::string &Name) : Name(Name) {}
};

/// BinaryExpr - Expression class for a binary operator.
class BinaryExpr : public Expr {
  char Op;
  std::unique_ptr<Expr> LHS, RHS;

public:
  BinaryExpr(char Op, std::unique_ptr<Expr> LHS, std::unique_ptr<Expr> RHS)
      : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};

/// CallExpr - Expression class for function calls.
class CallExpr : public Expr {
  std::string Callee;
  std::vector<std::unique_ptr<Expr>> Args;

public:
  CallExpr(const std::string &Callee, std::vector<std::unique_ptr<Expr>> Args)
      : Callee(Callee), Args(std::move(Args)) {}
};

/// Prototype - This class represents the "prototype" for a function,
/// which captures its name, and its argument names (thus implicitly the number
/// of arguments the function takes).
class Prototype {
  std::string Name;
  std::vector<std::string> Args;

public:
  Prototype(const std::string &Name, std::vector<std::string> Args)
      : Name(Name), Args(std::move(Args)) {}

  const std::string &getName() const { return Name; }
};

/// Function - This class represents a function definition itself.
class Function {
  std::unique_ptr<Prototype> Proto;
  std::unique_ptr<Expr> Body;

public:
  Function(std::unique_ptr<Prototype> Proto, std::unique_ptr<Expr> Body)
      : Proto(std::move(Proto)), Body(std::move(Body)) {}
};

} // namespace AST