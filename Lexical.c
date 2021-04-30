
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


enum
{
	// ———— PREPROCESSOR
	LINE_COMMENT,  // //.*
	BLOCK_COMMENT,  /* (.|\n)* */
	PREPROCESSOR_INSTRUCTION,  // #.*

	// ———— LITERALS
	INT_LITERAL,
	DOUBLE_LITERAL,
	CHARACTER_LITERAL,
	STRING_LITERAL,

	// ———— KEY WORDS
	// ——— KEY WORDS::INTEGER
	SMALL_KEYWORD,
	SHORT_KEYWORD,
	INT_KEYWORD,
	LONG_KEYWORD,
	LARGE_KEYWORD,
	// ———— KEY WORDS::FLOATING POINT
	DOUBLE_KEYWORD,
	// ———— BRANCHING ————
	FOR_KEYWORD,
	DO_KEYWORD,
	WHILE_KEYWORD,
	IF_KEYWORD,
	ELIF_KEYWORD,
	ELSE_KEYWORD

	// ———— OPERATORS
	// ———— OPERATORS::ASSIGN
	ASSIGN_OPERATOR,  // =
	ADDITION_ASSIGN_OPERATOR,  // +=
	SUBTRACT_ASSIGN_OPERATOR,  // -=
	MULTIPLY_ASSIGN_OPERATOR,  // *=
	DIVIDE_ASSIGN_OPERATOR,  // /=
	// &&=
	// ||=
	// |=
	// &=
	// ^=
	// <<=
	// >>=
	// ———— OPERATORS::MATHEMATICAL
	ADDITION_OPERATOR,  // +
	SUBTRACTION_OPERATOR,  // -
	MULTIPLY_OPERATOR,  // *
	DIVIDE_OPERATOR,  // /
	MODULO_OPERATOR,  // %
	INCREMENT_OPERATOR,  // ++
	DECREMENT_OPERATOR,  // --
	SQUARE_OPERATOR,  // **
	// ———— OPERATORS::LOGICAL
	EQUIVALENCE_OPERATOR,  // ==
	NON_EQUIVALENCE_OPERATOR,  // !=
	OR_OPERATOR,  // ||
	AND_OPERATOR,  // &&
	LESS_THAN_OPERATOR,  // <
	GREATER_THAN_OPERATOR,  // >
	LESS_THAN_EQUAL_OPERATOR,  // <=
	GREATER_THAN_EQUAL_OPERATOR,  // >=
	BOOLEAN_NOT_OPERATOR,  // !
	// ———— OPERATORS::BINARY
	COMPLEMENT_OPERATOR,  // !- (equivalent to 0xFFFFFFFF ^ value)
	BINARY_OR_OPERATOR,  // |
	BINARY_AND_OPERATOR,  // &
	XOR_OPERATOR,  // ^
	BIT_SHIFT_LEFT_OPERATOR,  // <<
	BIT_SHIFT_RIGHT_OPERATOR,  // >>
	// ———— OPERATORS::ADDRESSING
	DEREFERENCE_OPERATOR,  // $
	REFERENCE_OPERATOR,  // @
	DOT_OPERATOR,  // . (for accessing an offset from an address of an array or structure/composition)

	// ———— OPERATORS
	_OPERATOR,  // 

	// ———— ENCAPSULATION/ENUMERATION
	OPEN_ENCAPSULATE,  // (
	CLOSE_ENCAPSULATE,  // )
	ENUMERATION,  // ,
	OPEN_ENUMERATION,  // {
	CLOSE_ENUMERATION,  // }
};


typedef struct Token
{
	uint32_t type;
	uint32_t line;
	uint32_t column;
	uint32_t length;
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


// ———————————————————————————————————————————— TOKEN TYPES DETERMINERS ————————————————————————————————————————————— //


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