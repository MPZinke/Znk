
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


#include "Symbols.h"


char* SYMBOL_TITLES[MAX_SYMBOL_COUNT+1];


void setup_symbol_titles()
{
	SYMBOL_TITLES[WHITE_SPACE] = WHITE_SPACE_TITLE;
	SYMBOL_TITLES[LINE_COMMENT] = LINE_COMMENT_TITLE;
	SYMBOL_TITLES[BLOCK_COMMENT] = BLOCK_COMMENT_TITLE;
	SYMBOL_TITLES[PREPROCESSOR_INSTRUCTION] = PREPROCESSOR_INSTRUCTION_TITLE;
	SYMBOL_TITLES[GLOBAL_SYMBOL] = GLOBAL_SYMBOL_TITLE;
	SYMBOL_TITLES[SEMI_COLON] = SEMI_COLON_TITLE;

	SYMBOL_TITLES[FOR_KEYWORD] = FOR_KEYWORD_TITLE;
	SYMBOL_TITLES[DO_KEYWORD] = DO_KEYWORD_TITLE;
	SYMBOL_TITLES[WHILE_KEYWORD] = WHILE_KEYWORD_TITLE;
	SYMBOL_TITLES[BREAK_KEYWORD] = BREAK_KEYWORD_TITLE;
	SYMBOL_TITLES[CONTINUE_KEYWORD] = CONTINUE_KEYWORD_TITLE;
	SYMBOL_TITLES[IF_KEYWORD] = IF_KEYWORD_TITLE;
	SYMBOL_TITLES[ELIF_KEYWORD] = ELIF_KEYWORD_TITLE;
	SYMBOL_TITLES[ELSE_KEYWORD] = ELSE_KEYWORD_TITLE;

	SYMBOL_TITLES[OPEN_ENCAPSULATE] = OPEN_ENCAPSULATE_TITLE;
	SYMBOL_TITLES[CLOSE_ENCAPSULATE] = CLOSE_ENCAPSULATE_TITLE;
	SYMBOL_TITLES[ENUMERATOR] = ENUMERATOR_TITLE;
	SYMBOL_TITLES[OPEN_ENUMERATION] = OPEN_ENUMERATION_TITLE;
	SYMBOL_TITLES[CLOSE_ENUMERATION] = CLOSE_ENUMERATION_TITLE;

	SYMBOL_TITLES[CHAR_KEYWORD] = CHAR_KEYWORD_TITLE;
	SYMBOL_TITLES[SMALL_KEYWORD] = SMALL_KEYWORD_TITLE;
	SYMBOL_TITLES[SHORT_KEYWORD] = SHORT_KEYWORD_TITLE;
	SYMBOL_TITLES[INT_KEYWORD] = INT_KEYWORD_TITLE;
	SYMBOL_TITLES[LONG_KEYWORD] = LONG_KEYWORD_TITLE;
	SYMBOL_TITLES[LARGE_KEYWORD] = LARGE_KEYWORD_TITLE;
	SYMBOL_TITLES[DOUBLE_KEYWORD] = DOUBLE_KEYWORD_TITLE;

	SYMBOL_TITLES[COMP_KEYWORD] = COMP_KEYWORD_TITLE;
	SYMBOL_TITLES[MAIN_KEYWORD] = MAIN_KEYWORD_TITLE;
	SYMBOL_TITLES[RETURN_KEYWORD] = RETURN_KEYWORD_TITLE;

	SYMBOL_TITLES[BINARY_INT_LITERAL] = BINARY_INT_LITERAL_TITLE;
	SYMBOL_TITLES[OCTAL_INT_LITERAL] = OCTAL_INT_LITERAL_TITLE;
	SYMBOL_TITLES[DECIMAL_INT_LITERAL] = DECIMAL_INT_LITERAL_TITLE;
	SYMBOL_TITLES[HEXIDECIMAL_INT_LITERAL] = HEXIDECIMAL_INT_LITERAL_TITLE;
	SYMBOL_TITLES[DOUBLE_LITERAL] = DOUBLE_LITERAL_TITLE;

	SYMBOL_TITLES[CHARACTER_LITERAL] = CHARACTER_LITERAL_TITLE;
	SYMBOL_TITLES[STRING_LITERAL] = STRING_LITERAL_TITLE;

	SYMBOL_TITLES[ASSIGN_OPERATOR] = ASSIGN_OPERATOR_TITLE;
	SYMBOL_TITLES[ADDITION_ASSIGN_OPERATOR] = ADDITION_ASSIGN_OPERATOR_TITLE;
	SYMBOL_TITLES[SUBTRACT_ASSIGN_OPERATOR] = SUBTRACT_ASSIGN_OPERATOR_TITLE;
	SYMBOL_TITLES[MULTIPLY_ASSIGN_OPERATOR] = MULTIPLY_ASSIGN_OPERATOR_TITLE;
	SYMBOL_TITLES[DIVIDE_ASSIGN_OPERATOR] = DIVIDE_ASSIGN_OPERATOR_TITLE;
	SYMBOL_TITLES[AND_ASSIGN_OPERATOR] = AND_ASSIGN_OPERATOR_TITLE;
	SYMBOL_TITLES[OR_ASSIGN_OPERATOR] = OR_ASSIGN_OPERATOR_TITLE;
	SYMBOL_TITLES[BITWISE_OR_ASSIGN_OPERATOR] = BITWISE_OR_ASSIGN_OPERATOR_TITLE;
	SYMBOL_TITLES[BITWISE_AND_ASSIGN_OPERATOR] = BITWISE_AND_ASSIGN_OPERATOR_TITLE;
	SYMBOL_TITLES[XOR_ASSIGN_OPERATOR] = XOR_ASSIGN_OPERATOR_TITLE;
	SYMBOL_TITLES[BIT_SHIFT_LEFT_ASSIGN_OPERATOR] = BIT_SHIFT_LEFT_ASSIGN_OPERATOR_TITLE;
	SYMBOL_TITLES[BIT_SHIFT_RIGHT_ASSIGN_OPERATOR] = BIT_SHIFT_RIGHT_ASSIGN_OPERATOR_TITLE;

	SYMBOL_TITLES[ADDITION_OPERATOR] = ADDITION_OPERATOR_TITLE;
	SYMBOL_TITLES[SUBTRACTION_OPERATOR] = SUBTRACTION_OPERATOR_TITLE;
	SYMBOL_TITLES[MULTIPLY_OPERATOR] = MULTIPLY_OPERATOR_TITLE;
	SYMBOL_TITLES[DIVIDE_OPERATOR] = DIVIDE_OPERATOR_TITLE;
	SYMBOL_TITLES[MODULO_OPERATOR] = MODULO_OPERATOR_TITLE;
	SYMBOL_TITLES[INCREMENT_OPERATOR] = INCREMENT_OPERATOR_TITLE;
	SYMBOL_TITLES[DECREMENT_OPERATOR] = DECREMENT_OPERATOR_TITLE;
	SYMBOL_TITLES[SQUARE_OPERATOR] = SQUARE_OPERATOR_TITLE;

	SYMBOL_TITLES[EQUIVALENCE_OPERATOR] = EQUIVALENCE_OPERATOR_TITLE;
	SYMBOL_TITLES[NON_EQUIVALENCE_OPERATOR] = NON_EQUIVALENCE_OPERATOR_TITLE;
	SYMBOL_TITLES[OR_OPERATOR] = OR_OPERATOR_TITLE;
	SYMBOL_TITLES[AND_OPERATOR] = AND_OPERATOR_TITLE;
	SYMBOL_TITLES[LESS_THAN_OPERATOR] = LESS_THAN_OPERATOR_TITLE;
	SYMBOL_TITLES[GREATER_THAN_OPERATOR] = GREATER_THAN_OPERATOR_TITLE;
	SYMBOL_TITLES[LESS_THAN_EQUAL_OPERATOR] = LESS_THAN_EQUAL_OPERATOR_TITLE;
	SYMBOL_TITLES[GREATER_THAN_EQUAL_OPERATOR] = GREATER_THAN_EQUAL_OPERATOR_TITLE;
	SYMBOL_TITLES[BOOLEAN_NOT_OPERATOR] = BOOLEAN_NOT_OPERATOR_TITLE;

	SYMBOL_TITLES[COMPLEMENT_OPERATOR] = COMPLEMENT_OPERATOR_TITLE;
	SYMBOL_TITLES[BITWISE_OR_OPERATOR] = BITWISE_OR_OPERATOR_TITLE;
	SYMBOL_TITLES[BITWISE_AND_OPERATOR] = BITWISE_AND_OPERATOR_TITLE;
	SYMBOL_TITLES[XOR_OPERATOR] = XOR_OPERATOR_TITLE;
	SYMBOL_TITLES[BIT_SHIFT_LEFT_OPERATOR] = BIT_SHIFT_LEFT_OPERATOR_TITLE;
	SYMBOL_TITLES[BIT_SHIFT_RIGHT_OPERATOR] = BIT_SHIFT_RIGHT_OPERATOR_TITLE;

	SYMBOL_TITLES[DEREFERENCE_OPERATOR] = DEREFERENCE_OPERATOR_TITLE;
	SYMBOL_TITLES[REFERENCE_OPERATOR] = REFERENCE_OPERATOR_TITLE;
	SYMBOL_TITLES[DOT_OPERATOR] = DOT_OPERATOR_TITLE;
	SYMBOL_TITLES[ARROW_OPERATOR] = ARROW_OPERATOR_TITLE;

	SYMBOL_TITLES[IDENTIFIER] = IDENTIFIER_TITLE;
}
