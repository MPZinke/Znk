
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


#ifndef _LexerLiterals_
#define _LexerLiterals_


#include <stdint.h>


#include "Global.h"
#include "Symbols.h"


#define HEXIDECIMAL_ALLOWED_VALUES ((47 < string[x] && string[x] < 58) || (64 < string[x] && string[x] < 71))


// ———————————————————————————————————————————————————— LITERALS ————————————————————————————————————————————————————— //

uint64_t hexidecimal_int_literal_length(char string[], TinyToken* tiny_token);
uint64_t binary_int_literal_length(char string[], TinyToken* tiny_token);
uint64_t octal_int_literal_length(char string[], TinyToken* tiny_token);
uint64_t decimal_int_literal_length(char string[], TinyToken* tiny_token);
uint64_t double_literal_length(char string[], TinyToken* tiny_token);
uint64_t character_literal_length(char string[], TinyToken* type_token);
uint64_t string_literal_length(char string[], TinyToken* type_token);


#endif
