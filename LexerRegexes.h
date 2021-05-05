
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


#ifndef _LEXER_REGEXES_
#define _LEXER_REGEXES_


#include <stdint.h>


#define STRING_CHAR_IS_NOT_WHITESPACE ((string[x] < 9 || 13 < string[x]) && string[x] != 32)
#define STRING_CHAR_IS_WHITESPACE ((8 < string[x] && string[x] < 14) || string[x] == 32)
#define STRING_CHAR_IS_NOT_NEWLINE (string[x] != 10 && string[x] != 13)
#define IS_CAPITAL_LETTER (64 < string[x] && string[x] < 91)
#define IS_LOWER_LETTER (96 < string[x] && string[x] < 123)


// ———————————————————————————————————————————————————— REGEXES ————————————————————————————————————————————————————— //

uint64_t line_comment_length(char string[]);
uint64_t white_space_length(char string[]);
uint64_t identifier_length(char string[]);


#endif