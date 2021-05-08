
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
uint64_t line_comment_length(char string[], TinyToken* type_token)
{
	if(string[0] != '/' || string[1] != '/') return 0;

	register uint64_t x = 0;
	for(x = 2; string[x] && STRING_CHAR_IS_NOT_NEWLINE && x < UINT64_MAX; x++)
	{
		type_token->column++;
	}
	return x;
}


uint64_t block_comment_length(char string[], TinyToken* type_token)
{
	if(string[0] != '/' || string[1] != '*' || !string[2]) return 0;

	register uint64_t x;
	for(x = 3; string[x] && string[x-1] != '*' && string[x] != '/'; x++)
	{
		if(string[x] != '\n') type_token->column++;
		else
		{
			type_token->line++;
			type_token->column = 0;
		}
	}
	return x;
}


uint64_t preprocessor_instruction_length(char string[], TinyToken* type_token)
{
	if(string[0] != '#') return 0;

	register uint64_t x;
	for(x = 1; string[x] && STRING_CHAR_IS_NOT_NEWLINE && x < UINT64_MAX; x++)
	{
		type_token->column++;
	}
	return x;
}


// Regex: [ \t\r\n\f\z]+
uint64_t white_space_length(char string[], TinyToken* type_token)
{
	register uint64_t x;
	for(x = 0; STRING_CHAR_IS_WHITESPACE && x < UINT64_MAX; x++)
	{
		if(string[x] != '\n') type_token->column++;
		else
		{
			type_token->line++;
			type_token->column = 0;
		}
	}
	return x;
}


// Regex: [_—a-zA-Z][_—a-zA-Z0-9]*
uint64_t identifier_length(char string[], TinyToken* type_token)
{
	register uint64_t x = 0;
	// if first char is not '–', not A-Z, and not a-z
	if((uint8_t)string[0] != 226 && !IS_CAPITAL_LETTER && !IS_LOWER_LETTER && string[0] != '_')
	{
		return 0;
	}

	type_token->column++;
	for(x = 1; IS_IDENTIFIER_CHARACTER && x < UINT64_MAX; x++)
	{
		type_token->column++;
	}
	return x;
}
