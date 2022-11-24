/* parser.c */

#include "../debug/debug.h"
#include "../util/readfile.h"
#include "parser.h"
#include "lexer.h"
#include "generateAST.h"

#ifdef VERBOSE_DEBUG
#include "statementAST.h"
#endif

// TODO: Only output one error per statement, so as to prevent errors
// caused by previous errors

// In the future, this should return the bytecode representation of the code
struct DeclarationList* parseProgram(const char* filename) {
#ifdef PARSER_DEBUG
  printf("## PARSER ##\nParsing %s...\n", filename);
#endif

#ifdef VERBOSE_DEBUG
  printf("\n### LEXER ###\n");
#endif

  char* program = readFile(filename);
  struct TokenArray* tokens = tokenise(filename, program);
  free(program);

#ifdef VERBOSE_DEBUG
  for(size_t i = 0; i < tokens->length; i++) {
    printf("%03ld: %12s, %10s, (%03ld, %03ld)\n", i,
        getTokenName(tokens->tokens[i].type),
        tokens->tokens[i].literal,
        tokens->tokens[i].row,
        tokens->tokens[i].col);
  }

  printf("\n### AST GENERATION ###\n");
#endif

  struct DeclarationList* decls = generateAST(filename, tokens);

#ifdef VERBOSE_DEBUG
  for(size_t i = 0; i < decls->size; i++) {
    printDeclarationAST(decls->members[i], 0);
  }
#endif

  return decls;
}
