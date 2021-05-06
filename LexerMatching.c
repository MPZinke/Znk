
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


#include "LexerMatching.h"


uint64_t global_symbol_length(char string[], TinyToken* tiny_token)
{
	return string[0] == '~';
}


uint64_t semi_colon_length(char string[], TinyToken* tiny_token)
{
	return string[0] == ';';
}


// ———— BRANCHING
uint64_t for_keyword_length(char string[], TinyToken* tiny_token)
{
	char for_keyword_str[] = FOR_KEYWORD_DEF;
	uint64_t x;
	for(x = 0; string[x] == for_keyword_str[x]; x++);
	return (x == (sizeof(FOR_KEYWORD_DEF)-1)) * x;
}


uint64_t do_keyword_length(char string[], TinyToken* tiny_token)
{
	char do_keyword_str[] = DO_KEYWORD_DEF;
	uint64_t x;
	for(x = 0; string[x] == do_keyword_str[x]; x++);
	return (x == (sizeof(DO_KEYWORD_DEF)-1)) * x;
}


uint64_t while_keyword_length(char string[], TinyToken* tiny_token)
{
	char while_keyword_str[] = WHILE_KEYWORD_DEF;
	uint64_t x;
	for(x = 0; string[x] == while_keyword_str[x]; x++);
	return (x == (sizeof(WHILE_KEYWORD_DEF)-1)) * x;
}


uint64_t break_keyword_length(char string[], TinyToken* tiny_token)
{
	char break_keyword_str[] = BREAK_KEYWORD_DEF;
	uint64_t x;
	for(x = 0; string[x] == break_keyword_str[x]; x++);
	return (x == (sizeof(BREAK_KEYWORD_DEF)-1)) * x;
}


uint64_t continue_keyword_length(char string[], TinyToken* tiny_token)
{
	char continue_keyword_str[] = CONTINUE_KEYWORD_DEF;
	uint64_t x;
	for(x = 0; string[x] == continue_keyword_str[x]; x++);
	return (x == (sizeof(CONTINUE_KEYWORD_DEF)-1)) * x;
}


uint64_t if_keyword_length(char string[], TinyToken* tiny_token)
{
	char if_keyword_str[] = IF_KEYWORD_DEF;
	uint64_t x;
	for(x = 0; string[x] == if_keyword_str[x]; x++);
	return (x == (sizeof(IF_KEYWORD_DEF)-1)) * x;
}


uint64_t elif_keyword_length(char string[], TinyToken* tiny_token)
{
	char elif_keyword_str[] = ELIF_KEYWORD_DEF;
	uint64_t x;
	for(x = 0; string[x] == elif_keyword_str[x]; x++);
	return (x == (sizeof(ELIF_KEYWORD_DEF)-1)) * x;
}


uint64_t else_keyword_length(char string[], TinyToken* tiny_token)
{
	char else_keyword_str[] = ELSE_KEYWORD_DEF;
	uint64_t x;
	for(x = 0; string[x] == else_keyword_str[x]; x++);
	return (x == (sizeof(ELSE_KEYWORD_DEF)-1)) * x;
}



// ———— ENCAPSULATION/ENUMERATION
uint64_t open_encapsulate_length(char string[], TinyToken* tiny_token)
{
	char open_encapsulate_str[] = OPEN_ENCAPSULATE_DEF;
	uint64_t x;
	for(x = 0; string[x] == open_encapsulate_str[x]; x++);
	return (x == (sizeof(OPEN_ENCAPSULATE_DEF)-1)) * x;
}


uint64_t close_encapsulate_length(char string[], TinyToken* tiny_token)
{
	char close_encapsulate_str[] = CLOSE_ENCAPSULATE_DEF;
	uint64_t x;
	for(x = 0; string[x] == close_encapsulate_str[x]; x++);
	return (x == (sizeof(CLOSE_ENCAPSULATE_DEF)-1)) * x;
}


uint64_t enumerator_length(char string[], TinyToken* tiny_token)
{
	char enumerator_str[] = ENUMERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == enumerator_str[x]; x++);
	return (x == (sizeof(ENUMERATOR_DEF)-1)) * x;
}


uint64_t open_enumeration_length(char string[], TinyToken* tiny_token)
{
	char open_enumeration_str[] = OPEN_ENUMERATION_DEF;
	uint64_t x;
	for(x = 0; string[x] == open_enumeration_str[x]; x++);
	return (x == (sizeof(OPEN_ENUMERATION_DEF)-1)) * x;
}


uint64_t close_enumeration_length(char string[], TinyToken* tiny_token)
{
	char close_enumeration_str[] = CLOSE_ENUMERATION_DEF;
	uint64_t x;
	for(x = 0; string[x] == close_enumeration_str[x]; x++);
	return (x == (sizeof(CLOSE_ENUMERATION_DEF)-1)) * x;
}



// ———— KEY WORDS
uint64_t char_keyword_length(char string[], TinyToken* tiny_token)
{
	char char_keyword_str[] = CHAR_KEYWORD_DEF;
	uint64_t x;
	for(x = 0; string[x] == char_keyword_str[x]; x++);
	return (x == (sizeof(CHAR_KEYWORD_DEF)-1)) * x;
}


// ——— KEY WORDS::INTEGER
uint64_t small_keyword_length(char string[], TinyToken* tiny_token)
{
	char small_keyword_str[] = SMALL_KEYWORD_DEF;
	uint64_t x;
	for(x = 0; string[x] == small_keyword_str[x]; x++);
	return (x == (sizeof(SMALL_KEYWORD_DEF)-1)) * x;
}


uint64_t short_keyword_length(char string[], TinyToken* tiny_token)
{
	char short_keyword_str[] = SHORT_KEYWORD_DEF;
	uint64_t x;
	for(x = 0; string[x] == short_keyword_str[x]; x++);
	return (x == (sizeof(SHORT_KEYWORD_DEF)-1)) * x;
}


uint64_t int_keyword_length(char string[], TinyToken* tiny_token)
{
	char int_keyword_str[] = INT_KEYWORD_DEF;
	uint64_t x;
	for(x = 0; string[x] == int_keyword_str[x]; x++);
	return (x == (sizeof(INT_KEYWORD_DEF)-1)) * x;
}


uint64_t long_keyword_length(char string[], TinyToken* tiny_token)
{
	char long_keyword_str[] = LONG_KEYWORD_DEF;
	uint64_t x;
	for(x = 0; string[x] == long_keyword_str[x]; x++);
	return (x == (sizeof(LONG_KEYWORD_DEF)-1)) * x;
}


uint64_t large_keyword_length(char string[], TinyToken* tiny_token)
{
	char large_keyword_str[] = LARGE_KEYWORD_DEF;
	uint64_t x;
	for(x = 0; string[x] == large_keyword_str[x]; x++);
	return (x == (sizeof(LARGE_KEYWORD_DEF)-1)) * x;
}


// ———— KEY WORDS::FLOATING POINT
uint64_t double_keyword_length(char string[], TinyToken* tiny_token)
{
	char double_keyword_str[] = DOUBLE_KEYWORD_DEF;
	uint64_t x;
	for(x = 0; string[x] == double_keyword_str[x]; x++);
	return (x == (sizeof(DOUBLE_KEYWORD_DEF)-1)) * x;
}


// ———— KEY WORDS::OTHER
uint64_t comp_keyword_length(char string[], TinyToken* tiny_token)
{
	char comp_keyword_str[] = COMP_KEYWORD_DEF;
	uint64_t x;
	for(x = 0; string[x] == comp_keyword_str[x]; x++);
	return (x == (sizeof(COMP_KEYWORD_DEF)-1)) * x;
}


uint64_t main_keyword_length(char string[], TinyToken* tiny_token)
{
	char main_keyword_str[] = MAIN_KEYWORD_DEF;
	uint64_t x;
	for(x = 0; string[x] == main_keyword_str[x]; x++);
	return (x == (sizeof(MAIN_KEYWORD_DEF)-1)) * x;
}


uint64_t return_keyword_length(char string[], TinyToken* tiny_token)
{
	char return_keyword_str[] = RETURN_KEYWORD_DEF;
	uint64_t x;
	for(x = 0; string[x] == return_keyword_str[x]; x++);
	return (x == (sizeof(RETURN_KEYWORD_DEF)-1)) * x;
}


// ———— OPERATORS
// ———— OPERATORS::ASSIGN
uint64_t assign_operator_length(char string[], TinyToken* tiny_token)
{
	char assign_operator_str[] = ASSIGN_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == assign_operator_str[x]; x++);
	return (x == (sizeof(ASSIGN_OPERATOR_DEF)-1)) * x;
}


uint64_t addition_assign_operator_length(char string[], TinyToken* tiny_token)
{
	char addition_assign_operator_str[] = ADDITION_ASSIGN_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == addition_assign_operator_str[x]; x++);
	return (x == (sizeof(ADDITION_ASSIGN_OPERATOR_DEF)-1)) * x;
}


uint64_t subtract_assign_operator_length(char string[], TinyToken* tiny_token)
{
	char subtract_assign_operator_str[] = SUBTRACT_ASSIGN_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == subtract_assign_operator_str[x]; x++);
	return (x == (sizeof(SUBTRACT_ASSIGN_OPERATOR_DEF)-1)) * x;
}


uint64_t multiply_assign_operator_length(char string[], TinyToken* tiny_token)
{
	char multiply_assign_operator_str[] = MULTIPLY_ASSIGN_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == multiply_assign_operator_str[x]; x++);
	return (x == (sizeof(MULTIPLY_ASSIGN_OPERATOR_DEF)-1)) * x;
}


uint64_t divide_assign_operator_length(char string[], TinyToken* tiny_token)
{
	char divide_assign_operator_str[] = DIVIDE_ASSIGN_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == divide_assign_operator_str[x]; x++);
	return (x == (sizeof(DIVIDE_ASSIGN_OPERATOR_DEF)-1)) * x;
}


uint64_t and_assign_operator_length(char string[], TinyToken* tiny_token)
{
	char and_assign_operator_str[] = AND_ASSIGN_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == and_assign_operator_str[x]; x++);
	return (x == (sizeof(AND_ASSIGN_OPERATOR_DEF)-1)) * x;
}


uint64_t or_assign_operator_length(char string[], TinyToken* tiny_token)
{
	char or_assign_operator_str[] = OR_ASSIGN_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == or_assign_operator_str[x]; x++);
	return (x == (sizeof(OR_ASSIGN_OPERATOR_DEF)-1)) * x;
}


uint64_t bitwise_or_assign_operator_length(char string[], TinyToken* tiny_token)
{
	char bitwise_or_assign_operator_str[] = BITWISE_OR_ASSIGN_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == bitwise_or_assign_operator_str[x]; x++);
	return (x == (sizeof(BITWISE_OR_ASSIGN_OPERATOR_DEF)-1)) * x;
}


uint64_t bitwise_and_assign_operator_length(char string[], TinyToken* tiny_token)
{
	char bitwise_and_assign_operator_str[] = BITWISE_AND_ASSIGN_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == bitwise_and_assign_operator_str[x]; x++);
	return (x == (sizeof(BITWISE_AND_ASSIGN_OPERATOR_DEF)-1)) * x;
}


uint64_t xor_assign_operator_length(char string[], TinyToken* tiny_token)
{
	char xor_assign_operator_str[] = XOR_ASSIGN_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == xor_assign_operator_str[x]; x++);
	return (x == (sizeof(XOR_ASSIGN_OPERATOR_DEF)-1)) * x;
}


uint64_t bit_shift_left_assign_operator_length(char string[], TinyToken* tiny_token)
{
	char bit_shift_left_assign_operator_str[] = BIT_SHIFT_LEFT_ASSIGN_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == bit_shift_left_assign_operator_str[x]; x++);
	return (x == (sizeof(BIT_SHIFT_LEFT_ASSIGN_OPERATOR_DEF)-1)) * x;
}


uint64_t bit_shift_right_assign_operator_length(char string[], TinyToken* tiny_token)
{
	char bit_shift_right_assign_operator_str[] = BIT_SHIFT_RIGHT_ASSIGN_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == bit_shift_right_assign_operator_str[x]; x++);
	return (x == (sizeof(BIT_SHIFT_RIGHT_ASSIGN_OPERATOR_DEF)-1)) * x;
}


// ———— OPERATORS::MATHEMATICAL
uint64_t addition_operator_length(char string[], TinyToken* tiny_token)
{
	char addition_operator_str[] = ADDITION_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == addition_operator_str[x]; x++);
	return (x == (sizeof(ADDITION_OPERATOR_DEF)-1)) * x;
}


uint64_t subtraction_operator_length(char string[], TinyToken* tiny_token)
{
	char subtraction_operator_str[] = SUBTRACTION_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == subtraction_operator_str[x]; x++);
	return (x == (sizeof(SUBTRACTION_OPERATOR_DEF)-1)) * x;
}


uint64_t multiply_operator_length(char string[], TinyToken* tiny_token)
{
	char multiply_operator_str[] = MULTIPLY_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == multiply_operator_str[x]; x++);
	return (x == (sizeof(MULTIPLY_OPERATOR_DEF)-1)) * x;
}


uint64_t divide_operator_length(char string[], TinyToken* tiny_token)
{
	char divide_operator_str[] = DIVIDE_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == divide_operator_str[x]; x++);
	return (x == (sizeof(DIVIDE_OPERATOR_DEF)-1)) * x;
}


uint64_t modulo_operator_length(char string[], TinyToken* tiny_token)
{
	char modulo_operator_str[] = MODULO_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == modulo_operator_str[x]; x++);
	return (x == (sizeof(MODULO_OPERATOR_DEF)-1)) * x;
}


uint64_t increment_operator_length(char string[], TinyToken* tiny_token)
{
	char increment_operator_str[] = INCREMENT_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == increment_operator_str[x]; x++);
	return (x == (sizeof(INCREMENT_OPERATOR_DEF)-1)) * x;
}


uint64_t decrement_operator_length(char string[], TinyToken* tiny_token)
{
	char decrement_operator_str[] = DECREMENT_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == decrement_operator_str[x]; x++);
	return (x == (sizeof(DECREMENT_OPERATOR_DEF)-1)) * x;
}


uint64_t square_operator_length(char string[], TinyToken* tiny_token)
{
	char square_operator_str[] = SQUARE_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == square_operator_str[x]; x++);
	return (x == (sizeof(SQUARE_OPERATOR_DEF)-1)) * x;
}


// ———— OPERATORS::LOGICAL
uint64_t equivalence_operator_length(char string[], TinyToken* tiny_token)
{
	char equivalence_operator_str[] = EQUIVALENCE_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == equivalence_operator_str[x]; x++);
	return (x == (sizeof(EQUIVALENCE_OPERATOR_DEF)-1)) * x;
}


uint64_t non_equivalence_operator_length(char string[], TinyToken* tiny_token)
{
	char non_equivalence_operator_str[] = NON_EQUIVALENCE_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == non_equivalence_operator_str[x]; x++);
	return (x == (sizeof(NON_EQUIVALENCE_OPERATOR_DEF)-1)) * x;
}


uint64_t or_operator_length(char string[], TinyToken* tiny_token)
{
	char or_operator_str[] = OR_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == or_operator_str[x]; x++);
	return (x == (sizeof(OR_OPERATOR_DEF)-1)) * x;
}


uint64_t and_operator_length(char string[], TinyToken* tiny_token)
{
	char and_operator_str[] = AND_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == and_operator_str[x]; x++);
	return (x == (sizeof(AND_OPERATOR_DEF)-1)) * x;
}


uint64_t less_than_operator_length(char string[], TinyToken* tiny_token)
{
	char less_than_operator_str[] = LESS_THAN_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == less_than_operator_str[x]; x++);
	return (x == (sizeof(LESS_THAN_OPERATOR_DEF)-1)) * x;
}


uint64_t greater_than_operator_length(char string[], TinyToken* tiny_token)
{
	char greater_than_operator_str[] = GREATER_THAN_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == greater_than_operator_str[x]; x++);
	return (x == (sizeof(GREATER_THAN_OPERATOR_DEF)-1)) * x;
}


uint64_t less_than_equal_operator_length(char string[], TinyToken* tiny_token)
{
	char less_than_equal_operator_str[] = LESS_THAN_EQUAL_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == less_than_equal_operator_str[x]; x++);
	return (x == (sizeof(LESS_THAN_EQUAL_OPERATOR_DEF)-1)) * x;
}


uint64_t greater_than_equal_operator_length(char string[], TinyToken* tiny_token)
{
	char greater_than_equal_operator_str[] = GREATER_THAN_EQUAL_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == greater_than_equal_operator_str[x]; x++);
	return (x == (sizeof(GREATER_THAN_EQUAL_OPERATOR_DEF)-1)) * x;
}


uint64_t boolean_not_operator_length(char string[], TinyToken* tiny_token)
{
	char boolean_not_operator_str[] = BOOLEAN_NOT_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == boolean_not_operator_str[x]; x++);
	return (x == (sizeof(BOOLEAN_NOT_OPERATOR_DEF)-1)) * x;
}


// ———— OPERATORS::BINARY
uint64_t complement_operator_length(char string[], TinyToken* tiny_token)
{
	char complement_operator_str[] = COMPLEMENT_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == complement_operator_str[x]; x++);
	return (x == (sizeof(COMPLEMENT_OPERATOR_DEF)-1)) * x;
}


uint64_t bitwise_or_operator_length(char string[], TinyToken* tiny_token)
{
	char bitwise_or_operator_str[] = BITWISE_OR_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == bitwise_or_operator_str[x]; x++);
	return (x == (sizeof(BITWISE_OR_OPERATOR_DEF)-1)) * x;
}


uint64_t bitwise_and_operator_length(char string[], TinyToken* tiny_token)
{
	char bitwise_and_operator_str[] = BITWISE_AND_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == bitwise_and_operator_str[x]; x++);
	return (x == (sizeof(BITWISE_AND_OPERATOR_DEF)-1)) * x;
}


uint64_t xor_operator_length(char string[], TinyToken* tiny_token)
{
	char xor_operator_str[] = XOR_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == xor_operator_str[x]; x++);
	return (x == (sizeof(XOR_OPERATOR_DEF)-1)) * x;
}


uint64_t bit_shift_left_operator_length(char string[], TinyToken* tiny_token)
{
	char bit_shift_left_operator_str[] = BIT_SHIFT_LEFT_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == bit_shift_left_operator_str[x]; x++);
	return (x == (sizeof(BIT_SHIFT_LEFT_OPERATOR_DEF)-1)) * x;
}


uint64_t bit_shift_right_operator_length(char string[], TinyToken* tiny_token)
{
	char bit_shift_right_operator_str[] = BIT_SHIFT_RIGHT_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == bit_shift_right_operator_str[x]; x++);
	return (x == (sizeof(BIT_SHIFT_RIGHT_OPERATOR_DEF)-1)) * x;
}


// ———— OPERATORS::ADDRESSING
uint64_t dereference_operator_length(char string[], TinyToken* tiny_token)
{
	char dereference_operator_str[] = DEREFERENCE_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == dereference_operator_str[x]; x++);
	return (x == (sizeof(DEREFERENCE_OPERATOR_DEF)-1)) * x;
}


uint64_t reference_operator_length(char string[], TinyToken* tiny_token)
{
	char reference_operator_str[] = REFERENCE_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == reference_operator_str[x]; x++);
	return (x == (sizeof(REFERENCE_OPERATOR_DEF)-1)) * x;
}


uint64_t dot_operator_length(char string[], TinyToken* tiny_token)
{
	char dot_operator_str[] = DOT_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == dot_operator_str[x]; x++);
	return (x == (sizeof(DOT_OPERATOR_DEF)-1)) * x;
}


uint64_t arrow_operator_length(char string[], TinyToken* tiny_token)
{
	char arrow_operator_str[] = ARROW_OPERATOR_DEF;
	uint64_t x;
	for(x = 0; string[x] == arrow_operator_str[x]; x++);
	return (x == (sizeof(ARROW_OPERATOR_DEF)-1)) * x;
}

