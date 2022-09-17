#ifndef AST_H
#define AST_H

#include <stdbool.h>

#include "token.h"

struct AST;

enum ASTType {
  AST_UNDEFINED,
  AST_LITERAL,
  AST_UNARY,
  AST_BINARY,
};

enum LiteralType {
  LIT_IDENTIFIER,
  LIT_STRING,
  LIT_INT64,
  LIT_UINT64,
  LIT_FLOAT64,
  LIT_BOOL,
};

union LiteralValue {
  char*   identifier;
  char*   string;
  double        floating;
  long          integer;
  unsigned long uinteger;
  bool          boolean;
};

struct AST {
  enum ASTType type;
  union {
    struct {
      enum LiteralType type;
      union LiteralValue as;
    } literal;

    struct {
      enum TokenType type;
      struct AST* operand;
    } unaryExpression;

    struct {
      enum TokenType type;
      struct AST* left;
      struct AST* right;
    } binaryExpression;
  } as;
};

struct AST* newASTNode(struct AST);
void freeASTNode(struct AST*);
void printASTNode(const struct AST*);

struct AST* newLiteralNode(enum LiteralType, union LiteralValue);
struct AST* newUnaryNode(enum TokenType, struct AST*);
struct AST* newBinaryNode(enum TokenType, struct AST*, struct AST*);

#define NEW_LITERAL_VALUE(type, value) \
  (union LiteralValue){ .type = value }

#endif
