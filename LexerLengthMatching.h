
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


#ifndef _LEXER_MATCHING_
#define _LEXER_MATCHING_


#include <stdint.h>
#include <string.h>


#include "Global.h"
#include "Symbol.h"
#include "Token.h"


uint64_t global_symbol_length(char string[], Symbol* symbol, TinyToken* tiny_token);
uint64_t semi_colon_length(char string[], Symbol* symbol, TinyToken* tiny_token);
uint64_t match_symbol_length(char string[], Symbol* symbol, TinyToken* type_token);


// ———————————————————————————————————————————————————— LITERALS ————————————————————————————————————————————————————— //


#define HEXIDECIMAL_ALLOWED_VALUES ((47 < string[x] && string[x] < 58) || (64 < string[x] && string[x] < 71))


uint64_t hexidecimal_int_literal_length(char string[], Symbol* symbol, TinyToken* tiny_token);
uint64_t binary_int_literal_length(char string[], Symbol* symbol, TinyToken* tiny_token);
uint64_t octal_int_literal_length(char string[], Symbol* symbol, TinyToken* tiny_token);
uint64_t decimal_int_literal_length(char string[], Symbol* symbol, TinyToken* tiny_token);
uint64_t double_literal_length(char string[], Symbol* symbol, TinyToken* tiny_token);
uint64_t character_literal_length(char string[], Symbol* symbol, TinyToken* type_token);
uint64_t string_literal_length(char string[], Symbol* symbol, TinyToken* type_token);


// ———————————————————————————————————————————————————— REGEXES ————————————————————————————————————————————————————— //


#define STRING_CHAR_IS_NOT_WHITESPACE ((string[x] < 9 || 13 < string[x]) && string[x] != 32)
#define STRING_CHAR_IS_WHITESPACE ((8 < string[x] && string[x] < 14) || string[x] == 32)
#define STRING_CHAR_IS_NOT_NEWLINE (string[x] != 10 && string[x] != 13)
#define IS_CAPITAL_LETTER (64 < string[x] && string[x] < 91)
#define IS_LOWER_LETTER (96 < string[x] && string[x] < 123)
#define IS_EM_DASH ((uint8_t)string[x] == 226 && (uint8_t)string[x+1] == 128 && (uint8_t)string[x+2] == 148)
#define IS_EN_DASH ((uint8_t)string[x] == 226 && (uint8_t)string[x+1] == 128 && (uint8_t)string[x+2] == 147)
#define IS_DASH (IS_EM_DASH || IS_EN_DASH)
#define IS_NUMBER (47 < string[x] && string[x] < 58)
#define IS_IDENTIFIER_CHAR (IS_CAPITAL_LETTER || IS_LOWER_LETTER || string[x] == '_' || IS_DASH)
#define IS_SUBSEQUENT_IDENTIFIER_CHAR (IS_IDENTIFIER_CHAR || IS_NUMBER)


uint64_t line_comment_length(char string[], Symbol* symbol, TinyToken* tiny_token);
uint64_t preprocessor_instruction_length(char string[], Symbol* symbol, TinyToken* tiny_token);
uint64_t block_comment_length(char string[], Symbol* symbol, TinyToken* tiny_token);
uint64_t white_space_length(char string[], Symbol* symbol, TinyToken* tiny_token);
uint64_t identifier_length(char string[], Symbol* symbol, TinyToken* tiny_token);
uint64_t unknown_char_length(char string[], Symbol* symbol, TinyToken* type_token);


#endif
