
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


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// ———— KEY WORDS
// ——— KEY WORDS::INTEGER
#define SMALL_KEYWORD_DEF "small"
#define SHORT_KEYWORD_DEF "short"
#define INT_KEYWORD_DEF "int"
#define LONG_KEYWORD_DEF "long"
#define LARGE_KEYWORD_DEF "large"
// ———— KEY WORDS::FLOATING POINT
#define DOUBLE_KEYWORD_DEF "double"
// ———— BRANCHING ————
#define FOR_KEYWORD_DEF "for"
#define DO_KEYWORD_DEF "do"
#define WHILE_KEYWORD_DEF "while"
#define IF_KEYWORD_DEF "if"
#define ELIF_KEYWORD_DEF "elif"
#define ELSE_KEYWORD_DEF "else"
// ———— OPERATORS::ASSIGN
#define ADDITION_ASSIGN_OPERATOR_DEF "+="
#define SUBTRACT_ASSIGN_OPERATOR_DEF "-="
#define MULTIPLY_ASSIGN_OPERATOR_DEF "*="
#define DIVIDE_ASSIGN_OPERATOR_DEF "/="
#define AND_ASSIGN_OPERATOR_DEF "&&="
#define OR_ASSIGN_OPERATOR_DEF "||="
#define BITWISE_OR_ASSIGN_OPERATOR_DEF "|="
#define BITWISE_AND_ASSIGN_OPERATOR_DEF "&="
#define XOR_ASSIGN_OPERATOR_DEF "^="
#define BIT_SHIFT_LEFT_ASSIGN_OPERATOR_DEF "<<="
#define BIT_SHIFT_RIGHT_ASSIGN_OPERATOR_DEF ">>="
// ———— OPERATORS::MATHEMATICAL
#define ADDITION_OPERATOR_DEF "+"
#define SUBTRACTION_OPERATOR_DEF "-"
#define MULTIPLY_OPERATOR_DEF "*"
#define DIVIDE_OPERATOR_DEF "/"
#define MODULO_OPERATOR_DEF "%"
#define INCREMENT_OPERATOR_DEF "++"
#define DECREMENT_OPERATOR_DEF "--"
#define SQUARE_OPERATOR_DEF "**"
// ———— OPERATORS::LOGICAL
#define EQUIVALENCE_OPERATOR_DEF "=="
#define NON_EQUIVALENCE_OPERATOR_DEF "!="
#define OR_OPERATOR_DEF "||"
#define AND_OPERATOR_DEF "&&"
#define LESS_THAN_OPERATOR_DEF "<"
#define GREATER_THAN_OPERATOR_DEF ">"
#define LESS_THAN_EQUAL_OPERATOR_DEF "<="
#define GREATER_THAN_EQUAL_OPERATOR_DEF ">="
#define BOOLEAN_NOT_OPERATOR_DEF "!"
// ———— OPERATORS::BINARY
#define COMPLEMENT_OPERATOR_DEF "!-"
#define BITWISE_OR_OPERATOR_DEF "|"
#define BITWISE_AND_OPERATOR_DEF "&"
#define XOR_OPERATOR_DEF "^"
#define BIT_SHIFT_LEFT_OPERATOR_DEF "<<"
#define BIT_SHIFT_RIGHT_OPERATOR_DEF ">>"
// ———— OPERATORS::ADDRESSING
#define DEREFERENCE_OPERATOR_DEF "$"
#define REFERENCE_OPERATOR_DEF "@"
#define DOT_OPERATOR_DEF "."
//TODO: Enumations, etc

// ———— COMPARISIONS
#define STRING_CHAR_IS_WHITESPACE ((8 <= string[x] && string[x] <= 13) || string[x] == 32)
#define STRING_CHAR_IS_NOT_WHITESPACE ((string[x] < 9 || 13 < string[x]) && string[x] != 32)
#define STRING_CHAR_IS_NOT_NEWLINE (string[x] != 10 && string[x] != 13)
#define HEXIDECIMAL_ALLOWED_VALUES ((47 < string[x] && string[x] < 58) || (64 < string[x] && string[x] < 71))

#include "SymbolEnum.c"


typedef struct Token
{
	uint32_t type;
	uint32_t line;
	uint32_t column;
	uint32_t length;
	char* filename;
	char* string;
} Token;


typedef struct Node
{
	Token token;
	struct Node* next;
} Node;


typedef struct TokenStream
{
	Node* head;
	uint32_t length;
} TokenStream;


// —————————————————————————————————————————————————— PROTOTYPES ——————————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

uint32_t token_type(char string[]);
uint32_t line_comment_length(char string[]);
uint32_t hexidecimal_literal_length(char string[]);
uint32_t binary_literal_length(char string[]);
uint32_t octal_literal_length(char string[]);
uint32_t decimal_literal_length(char string[]);
uint32_t double_literal_length(char string[]);
FILE* validate_and_open_znk_file(char filename[]);


// ———————————————————————————————————————————— TOKEN TYPES DETERMINERS ————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

TokenStream get_token_stream(char string[])
{
	for(uint32_t x = 0; string[x] && x < 0xFFFFFFFF; x++)
	{
		uint32_t type = 
	}
}


uint32_t token_type(char string[])
{
	// ———— OVERHEAD ————
	uint32_t (*length_functions[])(char*) =
	{
		white_space_length,
		line_comment_length,
		hexidecimal_literal_length,
		binary_literal_length,
		octal_literal_length,
		decimal_literal_length,
	};

	uint32_t lengths[sizeof(line_comment_length) / sizeof(void*)];


	// ———— CALCULATE ————
	// calculate the lengths for each type of symbol match
	for(uint32_t x = 0; x < sizeof(line_comment_length) / sizeof(void*); x++)
	{
		lengths[x] = length_functions[x](string);
	}

	// determine longest match
	uint32_t longest_match = 0, longest_match_index = -1;
	for(uint32_t x = 0; x < sizeof(line_comment_length) / sizeof(void*); x++)
	{
		printf("X: %d, Length: %d\n", x, lengths[x]);
	}

	return 0;
}


// ———————————————————————————————————————————————————— MATCHES ————————————————————————————————————————————————————— //


// Regex: //.*
uint32_t line_comment_length(char string[])
{
	register uint32_t x = 0;
	if(string[0] != '/' || string[1] != '/') return x;
	for(x = 2; string[x] && STRING_CHAR_IS_NOT_NEWLINE && x < 0xFFFFFFFF; x++);
	return x;
}


uint32_t white_space_length(char string[])
{
	uint32_t x;
	for(x = 0; STRING_CHAR_IS_WHITESPACE && x < 0xFFFFFFFF; x++);
	return x;
}


// ———————————————————————————————————————————————————— LITERALS ————————————————————————————————————————————————————— //



// ———————————————————————————————————————————————————— LITERALS ————————————————————————————————————————————————————— //

// Regex: 0x[0-9]+
uint32_t hexidecimal_literal_length(char string[])
{
	if(!string[0] || !string[1]) return 0;
	if(string[0] != '0' || string[1] != 'x') return 0;

	uint32_t x = 0;
	for(x = 2; HEXIDECIMAL_ALLOWED_VALUES && x < 0xFFFFFFFF; x++);
	return (x != 2) * x;
}


// Regex: 0b[01]+
uint32_t binary_literal_length(char string[])
{
	if(!string[0] || !string[1]) return 0;
	if(string[0] != '0' || string[1] != 'b') return 0;

	uint32_t x = 0;
	for(x = 2; 47 < string[x] && string[x] < 50 && x < 0xFFFFFFFF; x++);
	return (x != 2) * x;
}


uint32_t octal_literal_length(char string[])
{
	if(!string[0] || !string[1]) return 0;
	if(string[0] != '0') return 0;

	uint32_t x = 0;
	for(x = 1; 47 < string[x] && string[x] < 57 && x < 0xFFFFFFFF; x++);
	return (x != 1) * x;
}


uint32_t decimal_literal_length(char string[])
{

	if(!string[0]) return 0;
	if(string[0] != '0') return 0;

	uint32_t x = 0;
	for(x = 1; 47 < string[x] && string[x] < 58 && x < 0xFFFFFFFF; x++);
	return x;
}


uint32_t double_literal_length(char string[])
{
	uint32_t x = 0;
	//TODO
	return x;
}


// ————————————————————————————————————————————————————— FILE —————————————————————————————————————————————————————— //

FILE* validate_and_open_znk_file(char filename[])
{
	// if filename does not end with .znk: fuss and exit

	FILE* file = fopen(filename, "r");
	if(!file)
	{
		// fuss and exit
	}

	return file;
}



int main(int argc, char* argv[])
{
	FILE* file = validate_and_open_znk_file(argv[1]);
	
	return 0;
}