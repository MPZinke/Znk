
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


#include "LexerLiterals.h"


// ———————————————————————————————————————————————————— LITERALS ————————————————————————————————————————————————————— //

// Regex: 0x[0-9]+
uint64_t hexidecimal_int_literal_length(char string[], TinyToken* type_token)
{
	if(!string[0] || !string[1]) return 0;
	if(string[0] != '0' || string[1] != 'x') return 0;

	uint64_t x;
	for(x = 2; HEXIDECIMAL_ALLOWED_VALUES && x < UINT64_MAX; x++) type_token->column++;
	
	if(x == 2) return 0;
	type_token->column += x;
	return x;
}


// Regex: 0b[01]+
uint64_t binary_int_literal_length(char string[], TinyToken* type_token)
{
	if(!string[0] || !string[1]) return 0;
	if(string[0] != '0' || string[1] != 'b') return 0;

	uint64_t x;
	for(x = 2; (string[x] == '0' || string[x] == '1') && x < UINT64_MAX; x++) type_token->column++;

	if(x == 2) return 0;
	type_token->column += x;
	return x;
}


uint64_t octal_int_literal_length(char string[], TinyToken* type_token)
{
	if(!string[0] || !string[1]) return 0;
	if(string[0] != '0') return 0;

	uint64_t x;
	for(x = 1; 47 < string[x] && string[x] < 57 && x < UINT64_MAX; x++) type_token->column++;
	
	if(x == 1) return 0;
	type_token->column += x;
	return x;
}


uint64_t decimal_int_literal_length(char string[], TinyToken* type_token)
{
	if(!string[0]) return 0;

	uint64_t x;
	for(x = 0; 47 < string[x] && string[x] < 58 && x < UINT64_MAX; x++) type_token->column++;

	type_token->column += x;
	return x;
}


uint64_t double_literal_length(char string[], TinyToken* type_token)
{
	register uint64_t x;
	for(x = 0; 47 < string[x] && string[x] < 58 && x < UINT64_MAX; x++)
	{
		type_token->column++;
	}
	if(!x || string[x] != '.') return 0;

	for(x++; 47 < string[x] && string[x] < 58 && x < UINT64_MAX; x++)
	{
		type_token->column++;
	}

	return x;
}


uint64_t character_literal_length(char string[], TinyToken* type_token)
{
	if(string[0] == '\'' && string[1] == '\\' && string[2] && string[3] == '\'') return 4
	if(string[0] == '\'' && string[1] && string[2] == '\'') return 3;
	return 0;
}


uint64_t string_literal_length(char string[], TinyToken* type_token)
{
	//TODO
	return 0;
}

