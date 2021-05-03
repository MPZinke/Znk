
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


#define GLOBABL_SYMBOL_DEF "~"

// ———— BRANCHING
#define FOR_KEYWORD_DEF "for"
#define DO_KEYWORD_DEF "do"
#define WHILE_KEYWORD_DEF "while"
#define IF_KEYWORD_DEF "if"
#define ELIF_KEYWORD_DEF "elif"
#define ELSE_KEYWORD_DEF "else"

// ———— ENCAPSULATION/ENUMERATION
#define OPEN_ENCAPSULATE_DEF "("
#define CLOSE_ENCAPSULATE_DEF ")"
#define ENUMERATOR_DEF ","
#define OPEN_ENUMERATION_DEF "{"
#define CLOSE_ENUMERATION_DEF "}"

// ———— KEY WORDS
#define CHAR_KEYWORD_DEF "char"
// ——— KEY WORDS::INTEGER
#define SMALL_KEYWORD_DEF "small"
#define SHORT_KEYWORD_DEF "short"
#define INT_KEYWORD_DEF "int"
#define LONG_KEYWORD_DEF "long"
#define LARGE_KEYWORD_DEF "large"
// ———— KEY WORDS::FLOATING POINT
#define DOUBLE_KEYWORD_DEF "double"
// ———— KEY WORDS::OTHER
#define COMP_KEYWORD_DEF "comp"

// ———— OPERATORS
// ———— OPERATORS::ASSIGN
#define ASSIGN_OPERATOR_DEF "="
#define ADDITION_ASSIGN_OPERATOR_DEF "+="
#define SUBTRACT_ASSIGN_OPERATOR_DEF "-="
#define MULTIPLY_ASSIGN_OPERATOR_DEF "*="
#define DIVIDE_ASSIGN_OPERATOR_DEF "/="
#define AND_ASSIGN_OPERATOR_DEF "&&= (a &&= b   ≡   a)"
#define OR_ASSIGN_OPERATOR_DEF "||= (a||= b   ≡   a)"
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
#define COMPLEMENT_OPERATOR_DEF "!- (equivalent to 0xFFFFFFFF ^ value)"
#define BITWISE_OR_OPERATOR_DEF "|"
#define BITWISE_AND_OPERATOR_DEF "&"
#define XOR_OPERATOR_DEF "^"
#define BIT_SHIFT_LEFT_OPERATOR_DEF "<<"
#define BIT_SHIFT_RIGHT_OPERATOR_DEF ">>"
// ———— OPERATORS::ADDRESSING
#define DEREFERENCE_OPERATOR_DEF "$"
#define REFERENCE_OPERATOR_DEF "@"
#define DOT_OPERATOR_DEF ". (for accessing an offset from an address of an array or structure/composition)"