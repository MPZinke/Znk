
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


#include "LexerLengthMatching.h"


// —————————————————————————————————————————————————— DEFINITIONS ——————————————————————————————————————————————————— //

uint64_t global_symbol_length(char string[], Symbol* symbol, TinyToken* type_token)
{
	if(string[0] != '~') return 0;

	type_token->column++;
	return 1;
}


uint64_t semi_colon_length(char string[], Symbol* symbol, TinyToken* type_token)
{
	if(string[0] != ';') return 0;

	type_token->column++;
	return 1;
}


uint64_t match_symbol_length(char string[], Symbol* symbol, TinyToken* type_token)
{
	register uint64_t x;
	for(x = 0; string[x] && string[x] == symbol->definition[x] && x < UINT64_MAX; x++) type_token->column++;
	return x * (x == strlen(symbol->definition));
}


// ———————————————————————————————————————————————————— LITERALS ————————————————————————————————————————————————————— //

// Regex: 0x[0-9]+
uint64_t hexidecimal_int_literal_length(char string[], Symbol* symbol, TinyToken* type_token)
{
	if(!string[0] || !string[1]) return 0;
	if(string[0] != '0' || string[1] != 'x') return 0;

	register uint64_t x;
	for(x = 2; HEXIDECIMAL_ALLOWED_VALUES && x < UINT64_MAX; x++) type_token->column++;
	
	if(x == 2) return 0;
	type_token->column += x;
	return x;
}


// Regex: 0b[01]+
uint64_t binary_int_literal_length(char string[], Symbol* symbol, TinyToken* type_token)
{
	if(!string[0] || !string[1]) return 0;
	if(string[0] != '0' || string[1] != 'b') return 0;

	register uint64_t x;
	for(x = 2; (string[x] == '0' || string[x] == '1') && x < UINT64_MAX; x++);

	if(x == 2) return 0;
	type_token->column += x;
	return x;
}


uint64_t octal_int_literal_length(char string[], Symbol* symbol, TinyToken* type_token)
{
	if(!string[0] || !string[1]) return 0;
	if(string[0] != '0') return 0;

	register uint64_t x;
	for(x = 1; 47 < string[x] && string[x] < 57 && x < UINT64_MAX; x++);
	
	if(x == 1) return 0;
	type_token->column += x;
	return x;
}


uint64_t decimal_int_literal_length(char string[], Symbol* symbol, TinyToken* type_token)
{
	if(!string[0]) return 0;

	register uint64_t x;
	for(x = 0; 47 < string[x] && string[x] < 58 && x < UINT64_MAX; x++);

	type_token->column += x;
	return x;
}


uint64_t double_literal_length(char string[], Symbol* symbol, TinyToken* type_token)
{
	register uint64_t x;
	for(x = 0; 47 < string[x] && string[x] < 58 && x < UINT64_MAX; x++);

	if(!x || string[x] != '.') return 0;

	for(x++; 47 < string[x] && string[x] < 58 && x < UINT64_MAX; x++);

	type_token->column += x;
	return x;
}


uint64_t character_literal_length(char string[], Symbol* symbol, TinyToken* type_token)
{
	if(string[0] == '\'' && string[1] == '\\' && string[2] && string[3] == '\'') return 4;
	if(string[0] == '\'' && string[1] && string[2] == '\'') return 3;
	return 0;
}


uint64_t string_literal_length(char string[], Symbol* symbol, TinyToken* type_token)
{
	//TODO
	return 0;
}


// ———————————————————————————————————————————————————— REGEXES ————————————————————————————————————————————————————— //

// Regex: //.*
uint64_t line_comment_length(char string[], Symbol* symbol, TinyToken* type_token)
{
	if(string[0] != '/' || string[1] != '/') return 0;

	register uint64_t x = 0;
	for(x = 2; string[x] && STRING_CHAR_IS_NOT_NEWLINE && x < UINT64_MAX; x++)
	{
		type_token->column++;
	}
	return x;
}


uint64_t block_comment_length(char string[], Symbol* symbol, TinyToken* type_token)
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


uint64_t preprocessor_instruction_length(char string[], Symbol* symbol, TinyToken* type_token)
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
uint64_t white_space_length(char string[], Symbol* symbol, TinyToken* type_token)
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


// Regex: [_–—a-zA-Z][_–—a-zA-Z0-9]*
uint64_t identifier_length(char string[], Symbol* symbol, TinyToken* type_token)
{
	register uint64_t x = 0;
	// if first char is not '—', not '–', not A-Z, not a-z, and not '_'
	if(!IS_IDENTIFIER_CHAR)
	{
		return 0;
	}

	for(x = IS_DASH ? 3 : 1; IS_SUBSEQUENT_IDENTIFIER_CHAR && x < UINT64_MAX; x++)
	{
		if(IS_DASH) x += 2;
	}

	type_token->column += x;
	return x;
}


uint64_t unknown_char_length(char string[], Symbol* symbol, TinyToken* type_token)
{
	type_token->column++;
	return 1;
}
