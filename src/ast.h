#pragma once

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace llvm;

static std::unique_ptr<LLVMContext> TheContext;
static std::unique_ptr<Module> TheModule;
static std::unique_ptr<IRBuilder<>> Builder;
static std::map<std::string, Value *> NamedValues;

namespace AST {

/// Expr - Base class for all expression nodes.
class Expr {
public:
  virtual ~Expr() = default;
  virtual Value *codegen() = 0;
};

/// NumberExpr - Expression class for numeric literals like "1.0".
class NumberExpr : public Expr {
  double Val;

public:
  NumberExpr(double Val) : Val(Val) {}
  Value *codegen() override;
};

/// VariableExpr - Expression class for referencing a variable, like "a".
class VariableExpr : public Expr {
  std::string Name;

public:
  VariableExpr(const std::string &Name) : Name(Name) {}
  Value *codegen() override;
};

/// BinaryExpr - Expression class for a binary operator.
class BinaryExpr : public Expr {
  char Op;
  std::unique_ptr<Expr> LHS, RHS;

public:
  BinaryExpr(char Op, std::unique_ptr<Expr> LHS, std::unique_ptr<Expr> RHS)
      : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
  Value *codegen() override;
};

/// CallExpr - Expression class for function calls.
class CallExpr : public Expr {
  std::string Callee;
  std::vector<std::unique_ptr<Expr>> Args;

public:
  CallExpr(const std::string &Callee, std::vector<std::unique_ptr<Expr>> Args)
      : Callee(Callee), Args(std::move(Args)) {}
  Value *codegen() override;
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
  Function *codegen();

  const std::string &getName() const { return Name; }
};

/// Function - This class represents a function definition itself.
class FunctionAST {
  std::unique_ptr<Prototype> Proto;
  std::unique_ptr<Expr> Body;

public:
  FunctionAST(std::unique_ptr<Prototype> Proto, std::unique_ptr<Expr> Body)
      : Proto(std::move(Proto)), Body(std::move(Body)) {}
  Function *codegen();
};

/// LogError* - These are little helper functions for error handling.
std::unique_ptr<AST::Expr> LogError(const char *Str);
std::unique_ptr<AST::Prototype> LogErrorP(const char *Str);
Value *LogErrorV(const char *Str);

} // namespace AST