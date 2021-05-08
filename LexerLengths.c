
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


#include "LexerLengths.h"


void setup_length_functions()
{
	for(int x = 0; x < MAX_SYMBOL_COUNT; x++)
	{
		LENGTH_FUNCTIONS[x] = NULL;
	}

	LENGTH_FUNCTIONS[WHITE_SPACE] = white_space_length;
	// ———— PREPROCESSOR
	LENGTH_FUNCTIONS[LINE_COMMENT] = line_comment_length;
	LENGTH_FUNCTIONS[BLOCK_COMMENT] = block_comment_length;
	LENGTH_FUNCTIONS[PREPROCESSOR_INSTRUCTION] = preprocessor_instruction_length;
	LENGTH_FUNCTIONS[GLOBAL_SYMBOL] = global_symbol_length;
	LENGTH_FUNCTIONS[SEMI_COLON] = semi_colon_length;

	// ———— BRANCHING
	LENGTH_FUNCTIONS[FOR_KEYWORD] = for_keyword_length;
	LENGTH_FUNCTIONS[DO_KEYWORD] = do_keyword_length;
	LENGTH_FUNCTIONS[WHILE_KEYWORD] = while_keyword_length;
	LENGTH_FUNCTIONS[BREAK_KEYWORD] = break_keyword_length;
	LENGTH_FUNCTIONS[CONTINUE_KEYWORD] = continue_keyword_length;
	LENGTH_FUNCTIONS[IF_KEYWORD] = if_keyword_length;
	LENGTH_FUNCTIONS[ELIF_KEYWORD] = elif_keyword_length;
	LENGTH_FUNCTIONS[ELSE_KEYWORD] = else_keyword_length;

	// ———— ENCAPSULATION/ENUMERATION
	LENGTH_FUNCTIONS[OPEN_ENCAPSULATE] = open_encapsulate_length;
	LENGTH_FUNCTIONS[CLOSE_ENCAPSULATE] = close_encapsulate_length;
	LENGTH_FUNCTIONS[ENUMERATOR] = enumerator_length;
	LENGTH_FUNCTIONS[OPEN_ENUMERATION] = open_enumeration_length;
	LENGTH_FUNCTIONS[CLOSE_ENUMERATION] = close_enumeration_length;

	// ———— KEY WORDS
	LENGTH_FUNCTIONS[CHAR_KEYWORD] = char_keyword_length;
	// ——— KEY WORDS::INTEGER
	LENGTH_FUNCTIONS[SMALL_KEYWORD] = small_keyword_length;
	LENGTH_FUNCTIONS[SHORT_KEYWORD] = short_keyword_length;
	LENGTH_FUNCTIONS[INT_KEYWORD] = int_keyword_length;
	LENGTH_FUNCTIONS[LONG_KEYWORD] = long_keyword_length;
	LENGTH_FUNCTIONS[LARGE_KEYWORD] = large_keyword_length;
	// ———— KEY WORDS::FLOATING POINT
	LENGTH_FUNCTIONS[DOUBLE_KEYWORD] = double_keyword_length;
	// ———— KEY WORDS::OTHER
	LENGTH_FUNCTIONS[COMP_KEYWORD] = comp_keyword_length;
	LENGTH_FUNCTIONS[MAIN_KEYWORD] = main_keyword_length;
	LENGTH_FUNCTIONS[RETURN_KEYWORD] = return_keyword_length;

	// ———— LITERALS
	LENGTH_FUNCTIONS[BINARY_INT_LITERAL] = binary_int_literal_length;
	LENGTH_FUNCTIONS[OCTAL_INT_LITERAL] = octal_int_literal_length;
	LENGTH_FUNCTIONS[DECIMAL_INT_LITERAL] = decimal_int_literal_length;
	LENGTH_FUNCTIONS[HEXIDECIMAL_INT_LITERAL] = hexidecimal_int_literal_length;
	// LENGTH_FUNCTIONS[DOUBLE_LITERAL] = double_literal_length;
	// LENGTH_FUNCTIONS[CHARACTER_LITERAL] = character_literal_length;
	// LENGTH_FUNCTIONS[STRING_LITERAL] = string_literal_length;

	// ———— OPERATORS
	// ———— OPERATORS::ASSIGN
	LENGTH_FUNCTIONS[ASSIGN_OPERATOR] = assign_operator_length;
	LENGTH_FUNCTIONS[ADDITION_ASSIGN_OPERATOR] = addition_assign_operator_length;
	LENGTH_FUNCTIONS[SUBTRACT_ASSIGN_OPERATOR] = subtract_assign_operator_length;
	LENGTH_FUNCTIONS[MULTIPLY_ASSIGN_OPERATOR] = multiply_assign_operator_length;
	LENGTH_FUNCTIONS[DIVIDE_ASSIGN_OPERATOR] = divide_assign_operator_length;
	LENGTH_FUNCTIONS[AND_ASSIGN_OPERATOR] = and_assign_operator_length;
	LENGTH_FUNCTIONS[OR_ASSIGN_OPERATOR] = or_assign_operator_length;
	LENGTH_FUNCTIONS[BITWISE_OR_ASSIGN_OPERATOR] = bitwise_or_assign_operator_length;
	LENGTH_FUNCTIONS[BITWISE_AND_ASSIGN_OPERATOR] = bitwise_and_assign_operator_length;
	LENGTH_FUNCTIONS[XOR_ASSIGN_OPERATOR] = xor_assign_operator_length;
	LENGTH_FUNCTIONS[BIT_SHIFT_LEFT_ASSIGN_OPERATOR] = bit_shift_left_assign_operator_length;
	LENGTH_FUNCTIONS[BIT_SHIFT_RIGHT_ASSIGN_OPERATOR] = bit_shift_right_assign_operator_length;
	// ———— OPERATORS::MATHEMATICAL
	LENGTH_FUNCTIONS[ADDITION_OPERATOR] = addition_operator_length;
	LENGTH_FUNCTIONS[SUBTRACTION_OPERATOR] = subtraction_operator_length;
	LENGTH_FUNCTIONS[MULTIPLY_OPERATOR] = multiply_operator_length;
	LENGTH_FUNCTIONS[DIVIDE_OPERATOR] = divide_operator_length;
	LENGTH_FUNCTIONS[MODULO_OPERATOR] = modulo_operator_length;
	LENGTH_FUNCTIONS[INCREMENT_OPERATOR] = increment_operator_length;
	LENGTH_FUNCTIONS[DECREMENT_OPERATOR] = decrement_operator_length;
	LENGTH_FUNCTIONS[SQUARE_OPERATOR] = square_operator_length;
	// ———— OPERATORS::LOGICAL
	LENGTH_FUNCTIONS[EQUIVALENCE_OPERATOR] = equivalence_operator_length;
	LENGTH_FUNCTIONS[NON_EQUIVALENCE_OPERATOR] = non_equivalence_operator_length;
	LENGTH_FUNCTIONS[OR_OPERATOR] = or_operator_length;
	LENGTH_FUNCTIONS[AND_OPERATOR] = and_operator_length;
	LENGTH_FUNCTIONS[LESS_THAN_OPERATOR] = less_than_operator_length;
	LENGTH_FUNCTIONS[GREATER_THAN_OPERATOR] = greater_than_operator_length;
	LENGTH_FUNCTIONS[LESS_THAN_EQUAL_OPERATOR] = less_than_equal_operator_length;
	LENGTH_FUNCTIONS[GREATER_THAN_EQUAL_OPERATOR] = greater_than_equal_operator_length;
	LENGTH_FUNCTIONS[BOOLEAN_NOT_OPERATOR] = boolean_not_operator_length;
	// ———— OPERATORS::BINARY
	LENGTH_FUNCTIONS[COMPLEMENT_OPERATOR] = complement_operator_length;
	LENGTH_FUNCTIONS[BITWISE_OR_OPERATOR] = bitwise_or_operator_length;
	LENGTH_FUNCTIONS[BITWISE_AND_OPERATOR] = bitwise_and_operator_length;
	LENGTH_FUNCTIONS[XOR_OPERATOR] = xor_operator_length;
	LENGTH_FUNCTIONS[BIT_SHIFT_LEFT_OPERATOR] = bit_shift_left_operator_length;
	LENGTH_FUNCTIONS[BIT_SHIFT_RIGHT_OPERATOR] = bit_shift_right_operator_length;
	// ———— OPERATORS::ADDRESSING
	LENGTH_FUNCTIONS[DEREFERENCE_OPERATOR] = dereference_operator_length;
	LENGTH_FUNCTIONS[REFERENCE_OPERATOR] = reference_operator_length;
	LENGTH_FUNCTIONS[DOT_OPERATOR] = dot_operator_length;
	LENGTH_FUNCTIONS[ARROW_OPERATOR] = arrow_operator_length;

	// ———— OTHER
	LENGTH_FUNCTIONS[IDENTIFIER] = identifier_length;
}
