
/***********************************************************************************************************************
*                                                                                                                      *
*   created by: MPZinke                                                                                                *
*   on ..                                                                                                              *
*                                                                                                                      *
*   DESCRIPTION: TEMPLATE                                                                                              *
*   BUGS:                                                                                                              *
*   FUTURE:                                                                                                            *
*                                                                                                                      *
***********************************************************************************************************************/


#ifndef _LEXER_LENGTHS_
#define _LEXER_LENGTHS_


#include <stdint.h>
#include <stdlib.h>


#include "LexerLiterals.h"
#include "LexerMatching.h"
#include "LexerRegexes.h"
#include "Symbols.h"


uint64_t (*LENGTH_FUNCTIONS[MAX_SYMBOL_COUNT])(char*);

void setup_length_functions();


#endif
