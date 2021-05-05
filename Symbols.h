
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


#ifndef _SYMBOLS_
#define _SYMBOLS_


// ————————————————————————————————————————————————————— TYPES —————————————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

enum
{
	WHITE_SPACE = 0,
	// ———— PREPROCESSOR
	LINE_COMMENT,  // //.*
	BLOCK_COMMENT,  /* (.|\n)* */
	PREPROCESSOR_INSTRUCTION,  // #.*
	// ———— OTHER
	GLOBAL_SYMBOL,  // ~
	SEMI_COLON,  // ;

	// ———— BRANCHING
	FOR_KEYWORD,  // for
	DO_KEYWORD,  // do
	WHILE_KEYWORD,  // while
	BREAK_KEYWORD,  // break
	CONTINUE_KEYWORD,  // continue
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
	MAIN_KEYWORD,  // return
	RETURN_KEYWORD,  // return

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
	IDENTIFIER,  // [_—a-zA-Z][_—a-zA-Z0-9]
	MAX_SYMBOL_COUNT  // MUST BE LAST
};


// ————————————————————————————————————————————— LITERALS  DEFINITIONS —————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

// ———— OTHER
#define GLOBAL_SYMBOL_DEF "~"
#define SEMI_COLON_DEF ";"
// ———— BRANCHING
#define FOR_KEYWORD_DEF "for"
#define DO_KEYWORD_DEF "do"
#define WHILE_KEYWORD_DEF "while"
#define BREAK_KEYWORD_DEF "break"
#define CONTINUE_KEYWORD_DEF "continue"
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
#define MAIN_KEYWORD_DEF "main"
#define RETURN_KEYWORD_DEF "return"

// ———— OPERATORS
// ———— OPERATORS::ASSIGN
#define ASSIGN_OPERATOR_DEF "="
#define ADDITION_ASSIGN_OPERATOR_DEF "+="
#define SUBTRACT_ASSIGN_OPERATOR_DEF "-="
#define MULTIPLY_ASSIGN_OPERATOR_DEF "*="
#define DIVIDE_ASSIGN_OPERATOR_DEF "/="
#define AND_ASSIGN_OPERATOR_DEF "&&="  // (a &&= b   ≡   a)
#define OR_ASSIGN_OPERATOR_DEF "||="  // (a||= b   ≡   a)
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
#define COMPLEMENT_OPERATOR_DEF "!-"  // (equivalent to 0xFFFFFFFF ^ value)
#define BITWISE_OR_OPERATOR_DEF "|"
#define BITWISE_AND_OPERATOR_DEF "&"
#define XOR_OPERATOR_DEF "^"
#define BIT_SHIFT_LEFT_OPERATOR_DEF "<<"
#define BIT_SHIFT_RIGHT_OPERATOR_DEF ">>"
// ———— OPERATORS::ADDRESSING
#define DEREFERENCE_OPERATOR_DEF "$"
#define REFERENCE_OPERATOR_DEF "@"
#define DOT_OPERATOR_DEF "."  // (for accessing an offset from an address of an array or structure/composition)



// ————————————————————————————————————————————————————  TITLES ————————————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

#define WHITE_SPACE_TITLE "WHITE_SPACE"
// ———— PREPROCESSOR
#define LINE_COMMENT_TITLE "LINE_COMMENT"
#define BLOCK_COMMENT_TITLE "BLOCK_COMMENT"
#define PREPROCESSOR_INSTRUCTION_TITLE "PREPROCESSOR_INSTRUCTION"
// ———— OTHER
#define GLOBAL_SYMBOL_TITLE "GLOBAL_SYMBOL"
#define SEMI_COLON_TITLE "SEMI_COLON"
// ———— BRANCHING
#define FOR_KEYWORD_TITLE "FOR_KEYWORD"
#define DO_KEYWORD_TITLE "DO_KEYWORD"
#define WHILE_KEYWORD_TITLE "WHILE_KEYWORD"
#define BREAK_KEYWORD_TITLE "BREAK_KEYWORD"
#define CONTINUE_KEYWORD_TITLE "CONTINUE_KEYWORD"
#define IF_KEYWORD_TITLE "IF_KEYWORD"
#define ELIF_KEYWORD_TITLE "ELIF_KEYWORD"
#define ELSE_KEYWORD_TITLE "ELSE_KEYWORD"
// ———— ENCAPSULATION/ENUMERATION
#define OPEN_ENCAPSULATE_TITLE "OPEN_ENCAPSULATE"
#define CLOSE_ENCAPSULATE_TITLE "CLOSE_ENCAPSULATE"
#define ENUMERATOR_TITLE "ENUMERATOR"
#define OPEN_ENUMERATION_TITLE "OPEN_ENUMERATION"
#define CLOSE_ENUMERATION_TITLE "CLOSE_ENUMERATION"
// ———— KEY WORDS
#define CHAR_KEYWORD_TITLE "CHAR_KEYWORD"
// ——— KEY WORDS::INTEGER
#define SMALL_KEYWORD_TITLE "SMALL_KEYWORD"
#define SHORT_KEYWORD_TITLE "SHORT_KEYWORD"
#define INT_KEYWORD_TITLE "INT_KEYWORD"
#define LONG_KEYWORD_TITLE "LONG_KEYWORD"
#define LARGE_KEYWORD_TITLE "LARGE_KEYWORD"
// ———— KEY WORDS::FLOATING POINT
#define DOUBLE_KEYWORD_TITLE "DOUBLE_KEYWORD"
// ———— KEY WORDS::OTHER
#define COMP_KEYWORD_TITLE "COMP_KEYWORD"
#define MAIN_KEYWORD_TITLE "MAIN_KEYWORD"
#define RETURN_KEYWORD_TITLE "RETURN_KEYWORD"

// ———— LITERALS
#define BINARY_INT_LITERAL_TITLE "BINARY_INT_LITERAL"
#define OCTAL_INT_LITERAL_TITLE "OCTAL_INT_LITERAL"
#define DECIMAL_INT_LITERAL_TITLE "DECIMAL_INT_LITERAL"
#define HEXIDECIMAL_INT_LITERAL_TITLE "HEXIDECIMAL_INT_LITERAL"
#define DOUBLE_LITERAL_TITLE "DOUBLE_LITERAL"
#define CHARACTER_LITERAL_TITLE "CHARACTER_LITERAL"
#define STRING_LITERAL_TITLE "STRING_LITERAL"
// ———— OPERATORS
// ———— OPERATORS::ASSIGN
#define ASSIGN_OPERATOR_TITLE "ASSIGN_OPERATOR"
#define ADDITION_ASSIGN_OPERATOR_TITLE "ADDITION_ASSIGN_OPERATOR"
#define SUBTRACT_ASSIGN_OPERATOR_TITLE "SUBTRACT_ASSIGN_OPERATOR"
#define MULTIPLY_ASSIGN_OPERATOR_TITLE "MULTIPLY_ASSIGN_OPERATOR"
#define DIVIDE_ASSIGN_OPERATOR_TITLE "DIVIDE_ASSIGN_OPERATOR"
#define AND_ASSIGN_OPERATOR_TITLE "AND_ASSIGN_OPERATOR"
#define OR_ASSIGN_OPERATOR_TITLE "OR_ASSIGN_OPERATOR"
#define BITWISE_OR_ASSIGN_OPERATOR_TITLE "BITWISE_OR_ASSIGN_OPERATOR"
#define BITWISE_AND_ASSIGN_OPERATOR_TITLE "BITWISE_AND_ASSIGN_OPERATOR"
#define XOR_ASSIGN_OPERATOR_TITLE "XOR_ASSIGN_OPERATOR"
#define BIT_SHIFT_LEFT_ASSIGN_OPERATOR_TITLE "BIT_SHIFT_LEFT_ASSIGN_OPERATOR"
#define BIT_SHIFT_RIGHT_ASSIGN_OPERATOR_TITLE "BIT_SHIFT_RIGHT_ASSIGN_OPERATOR"
// ———— OPERATORS::MATHEMATICAL
#define ADDITION_OPERATOR_TITLE "ADDITION_OPERATOR"
#define SUBTRACTION_OPERATOR_TITLE "SUBTRACTION_OPERATOR"
#define MULTIPLY_OPERATOR_TITLE "MULTIPLY_OPERATOR"
#define DIVIDE_OPERATOR_TITLE "DIVIDE_OPERATOR"
#define MODULO_OPERATOR_TITLE "MODULO_OPERATOR"
#define INCREMENT_OPERATOR_TITLE "INCREMENT_OPERATOR"
#define DECREMENT_OPERATOR_TITLE "DECREMENT_OPERATOR"
#define SQUARE_OPERATOR_TITLE "SQUARE_OPERATOR"
// ———— OPERATORS::LOGICAL
#define EQUIVALENCE_OPERATOR_TITLE "EQUIVALENCE_OPERATOR"
#define NON_EQUIVALENCE_OPERATOR_TITLE "NON_EQUIVALENCE_OPERATOR"
#define OR_OPERATOR_TITLE "OR_OPERATOR"
#define AND_OPERATOR_TITLE "AND_OPERATOR"
#define LESS_THAN_OPERATOR_TITLE "LESS_THAN_OPERATOR"
#define GREATER_THAN_OPERATOR_TITLE "GREATER_THAN_OPERATOR"
#define LESS_THAN_EQUAL_OPERATOR_TITLE "LESS_THAN_EQUAL_OPERATOR"
#define GREATER_THAN_EQUAL_OPERATOR_TITLE "GREATER_THAN_EQUAL_OPERATOR"
#define BOOLEAN_NOT_OPERATOR_TITLE "BOOLEAN_NOT_OPERATOR"
// ———— OPERATORS::BINARY
#define COMPLEMENT_OPERATOR_TITLE "COMPLEMENT_OPERATOR"
#define BITWISE_OR_OPERATOR_TITLE "BITWISE_OR_OPERATOR"
#define BITWISE_AND_OPERATOR_TITLE "BITWISE_AND_OPERATOR"
#define XOR_OPERATOR_TITLE "XOR_OPERATOR"
#define BIT_SHIFT_LEFT_OPERATOR_TITLE "BIT_SHIFT_LEFT_OPERATOR"
#define BIT_SHIFT_RIGHT_OPERATOR_TITLE "BIT_SHIFT_RIGHT_OPERATOR"
// ———— OPERATORS::ADDRESSING
#define DEREFERENCE_OPERATOR_TITLE "DEREFERENCE_OPERATOR"
#define REFERENCE_OPERATOR_TITLE "REFERENCE_OPERATOR"
#define DOT_OPERATOR_TITLE "DOT_OPERATOR"
// ———— OTHER
#define IDENTIFIER_TITLE "IDENTIFIER"

char* SYMBOL_TITLES[MAX_SYMBOL_COUNT+1];

void setup_symbol_titles();


#endif
