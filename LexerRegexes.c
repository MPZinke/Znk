
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



#include "LexerRegexes.h"



// ———————————————————————————————————————————————————— REGEXES ————————————————————————————————————————————————————— //

// Regex: //.*
uint64_t line_comment_length(char string[], TinyToken* tiny_token)
{
	register uint64_t x = 0;
	if(string[0] != '/' || string[1] != '/') return x;
	for(x = 2; string[x] && STRING_CHAR_IS_NOT_NEWLINE && x < UINT64_MAX; x++);
	return x;
}


// Regex: [ \t\r\n\f\z]+
uint64_t white_space_length(char string[], TinyToken* tiny_token)
{
	uint64_t x;
	for(x = 0; STRING_CHAR_IS_WHITESPACE && x < UINT64_MAX; x++);
	return x;
}


// Regex: [_—a-zA-Z][_—a-zA-Z0-9]*
uint64_t identifier_length(char string[], TinyToken* tiny_token)
{
	uint64_t x = 0;
	// if first char is not '–', not A-Z, and not a-z
	if((uint8_t)string[0] != 226 && !IS_CAPITAL_LETTER && !IS_LOWER_LETTER && string[0] != '_')
	{
		return 0;
	}

	for(x = 1; (uint8_t)string[x] == 226 || IS_CAPITAL_LETTER || IS_LOWER_LETTER || string[x] == '_'; x++);
	return x;
}
