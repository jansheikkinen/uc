/* parser.c */

#include "../debug/debug.h"
#include "../util/readfile.h"
#include "parser.h"
#include "lexer.h"
#include "generateAST.h"

#ifdef VERBOSE_DEBUG
#include "statementAST.h"
#endif

// In the future, this should return the bytecode representation of the code
struct StmtList* parseProgram(const char* filename) {
#ifdef PARSER_DEBUG
  printf("[PARSER]: Parsing %s...\n", filename);
#endif

#ifdef VERBOSE_DEBUG
  printf("### TOKENISER ###\n");
#endif

  char* program = readFile(filename);
  struct TokenArray* tokens = tokenise(program);
  free(program);

#ifdef VERBOSE_DEBUG
  for(size_t i = 0; i < tokens->capacity; i++) {
    if(tokens->tokens[i].type) { // TOKEN_UNDEFINED == 0 == NULL
      printf("%03ld: %12s, %10s, (%03ld, %03ld)\n", i,
          getTokenName(tokens->tokens[i].type),
          tokens->tokens[i].literal,
          tokens->tokens[i].row,
          tokens->tokens[i].col);
    }
  }

  printf("\n### AST GENERATION ###\n");
#endif

  struct StmtList* stmts = generateAST(tokens);

#ifdef VERBOSE_DEBUG
  for(size_t i = 0; i < stmts->size; i++)
    printStmtAST(stmts->stmts[i]);
#endif

  return stmts;
}
