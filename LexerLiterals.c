
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
uint64_t hexidecimal_int_literal_length(char string[])
{
	if(!string[0] || !string[1]) return 0;
	if(string[0] != '0' || string[1] != 'x') return 0;

	uint64_t x;
	for(x = 2; HEXIDECIMAL_ALLOWED_VALUES && x < UINT64_MAX; x++);
	return (x != 2) * x;
}


// Regex: 0b[01]+
uint64_t binary_int_literal_length(char string[])
{
	if(!string[0] || !string[1]) return 0;
	if(string[0] != '0' || string[1] != 'b') return 0;

	uint64_t x;
	for(x = 2; (string[x] == '0' || string[x] == '1') && x < UINT64_MAX; x++);
	return (x != 2) * x;
}


uint64_t octal_int_literal_length(char string[])
{
	if(!string[0] || !string[1]) return 0;
	if(string[0] != '0') return 0;

	uint64_t x;
	for(x = 1; 47 < string[x] && string[x] < 57 && x < UINT64_MAX; x++);
	return (x != 1) * x;
}


uint64_t decimal_int_literal_length(char string[])
{
	if(!string[0]) return 0;

	uint64_t x;
	for(x = 0; 47 < string[x] && string[x] < 58 && x < UINT64_MAX; x++);
	return x;
}


uint64_t double_literal_length(char string[])
{
	uint64_t x = 0;
	//TODO
	return x;
}