#ifndef TYPEAST_H
#define TYPEAST_H

#include <stdbool.h>
#include "expressionAST.h"

struct TypeAST;

// used for "int8" or "int8*", depends on its label in the TypeAST
enum BaseTypes {
  BASETYPE_UNDEFINED,
  BASETYPE_INT8,
  BASETYPE_INT16,
  BASETYPE_INT32,
  BASETYPE_INT64,
  BASETYPE_ISIZE,
  BASETYPE_UINT8,
  BASETYPE_UINT16,
  BASETYPE_UINT32,
  BASETYPE_UINT64,
  BASETYPE_USIZE,
  BASETYPE_FLOAT8, // this has got to be the funniest data type i've heard of
  BASETYPE_FLOAT16,
  BASETYPE_FLOAT32,
  BASETYPE_FLOAT63,
  BASETYPE_FSIZE,
  BASETYPE_BYTE,
  BASETYPE_CHAR,
  BASETYPE_VOID,
  BASETYPE_BOOL,
};

enum BaseTypeTypes {
  BTT_UNDEFINED,
  BTT_IDENTIFIER,
  BTT_TYPE,
};

struct BaseType {
  enum BaseTypeTypes type;
  union {
    const char* identifier;
    enum BaseTypes type;
  } as;
};

// int8*
struct PtrType {
  struct TypeAST* type;
};

// int8[34 + 35]
struct ArrayType {
  struct TypeAST* type;
  struct ExprAST* size;
};

enum StructTypes {
  STRUCT_UNDEFINED,
  STRUCT_STRUCT,
  STRUCT_UNION,
  STRUCT_ENUM,
  STRUCT_SUM,
  STRUCT_INTERFACE
};

// struct Test
struct StructType {
  enum StructTypes type;
  const char* name;
};

enum TypeASTTypes {
  TYPE_UNDEFINED,
  TYPE_BASE,
  TYPE_ARRAY,
  TYPE_PTR,
  TYPE_STRUCT
};

// TODO: char** is broken
struct TypeAST {
  enum TypeASTTypes type;
  bool ismutable;
  union {
    struct BaseType base;
    struct PtrType pointer;
    struct ArrayType array;
    struct StructType structure;
  } as;
};

struct TypeAST* allocNewBaseType(enum BaseTypes, bool);
struct TypeAST* allocNewBaseTypeStr(const char*, bool);
struct TypeAST* allocNewPointerType(struct TypeAST*, bool);
struct TypeAST* allocNewArrayType(struct TypeAST*, struct ExprAST*, bool);
struct TypeAST* allocNewStructType(const char*, enum StructTypes, bool);

void freeTypeAST(struct TypeAST*);

void printTypeAST(const struct TypeAST*);

#endif
