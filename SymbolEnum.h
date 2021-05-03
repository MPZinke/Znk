
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


#pragma once


enum
{
	WHITE_SPACE = 0,
	// ———— PREPROCESSOR
	LINE_COMMENT,  // //.*
	BLOCK_COMMENT,  /* (.|\n)* */
	PREPROCESSOR_INSTRUCTION,  // #.*
	GLOBABL_SYMBOL,  // ~

	// ———— BRANCHING
	FOR_KEYWORD,  // for
	DO_KEYWORD,  // do
	WHILE_KEYWORD,  // while
	IF_KEYWORD,  // if
	ELIF_KEYWORD,  // elif
	ELSE_KEYWORD,  // else

	// ———— ENCAPSULATION/ENUMERATION
	OPEN_ENCAPSULATE,  // (
	CLOSE_ENCAPSULATE,  // )
	ENUMERATOR,  // ,
	OPEN_ENUMERATION,  // {
	CLOSE_ENUMERATION,  // }

	// ———— KEY WORDS
	CHAR_KEYWORD,  // char
	// ——— KEY WORDS::INTEGER
	SMALL_KEYWORD,  // small
	SHORT_KEYWORD,  // short
	INT_KEYWORD,  // int
	LONG_KEYWORD,  // long
	LARGE_KEYWORD,  // large
	// ———— KEY WORDS::FLOATING POINT
	DOUBLE_KEYWORD,  // double
	// ———— KEY WORDS::OTHER
	COMP_KEYWORD,

	// ———— LITERALS
	BINARY_INT_LITERAL,  // RegEx: 0b[01]+
	OCTAL_INT_LITERAL,  // RegEx: 0[0-8]+
	DECIMAL_INT_LITERAL,  // RegEx: ([1-9][0-9]*|0)
	HEXIDECIMAL_INT_LITERAL,  // RegEx: 0x[0-9]+
	DOUBLE_LITERAL,  // RegEx: [0-9]+.[0-9]+
	CHARACTER_LITERAL,  // RegEx: '([a-zA-Z]|\[abefnrtv\'"?])'
	STRING_LITERAL,  // RegEx: "(\\.|[^"\\])*"

	// ———— OPERATORS
	// ———— OPERATORS::ASSIGN
	_OPERATOR,  // 
	ASSIGN_OPERATOR,  // =
	ADDITION_ASSIGN_OPERATOR,  // +=
	SUBTRACT_ASSIGN_OPERATOR,  // -=
	MULTIPLY_ASSIGN_OPERATOR,  // *=
	DIVIDE_ASSIGN_OPERATOR,  // /=
	AND_ASSIGN_OPERATOR,  // &&= (a &&= b   ≡   a = a && b)
	OR_ASSIGN_OPERATOR,  // ||= (a||= b   ≡   a = a || b)
	BITWISE_OR_ASSIGN_OPERATOR,  // |=
	BITWISE_AND_ASSIGN_OPERATOR,  // &=
	XOR_ASSIGN_OPERATOR,  // ^=
	BIT_SHIFT_LEFT_ASSIGN_OPERATOR,  // <<=
	BIT_SHIFT_RIGHT_ASSIGN_OPERATOR,  // >>=
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
	BITWISE_OR_OPERATOR,  // |
	BITWISE_AND_OPERATOR,  // &
	XOR_OPERATOR,  // ^
	BIT_SHIFT_LEFT_OPERATOR,  // <<
	BIT_SHIFT_RIGHT_OPERATOR,  // >>
	// ———— OPERATORS::ADDRESSING
	DEREFERENCE_OPERATOR,  // $
	REFERENCE_OPERATOR,  // @
	DOT_OPERATOR,  // . (for accessing an offset from an address of an array or structure/composition)

	// ————— OTHER
	MAX_SYMBOL_COUNT  // MUST BE LAST
};