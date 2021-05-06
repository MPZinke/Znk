
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


#ifndef _LEXER_MATCHING_
#define _LEXER_MATCHING_


#include "stdint.h"


#include "Global.h"
#include "Symbols.h"


uint64_t global_symbol_length(char string[], TinyToken* tiny_token);
uint64_t semi_colon_length(char string[], TinyToken* tiny_token);

uint64_t for_keyword_length(char string[], TinyToken* tiny_token);
uint64_t do_keyword_length(char string[], TinyToken* tiny_token);
uint64_t while_keyword_length(char string[], TinyToken* tiny_token);
uint64_t break_keyword_length(char string[], TinyToken* tiny_token);
uint64_t continue_keyword_length(char string[], TinyToken* tiny_token);
uint64_t if_keyword_length(char string[], TinyToken* tiny_token);
uint64_t elif_keyword_length(char string[], TinyToken* tiny_token);
uint64_t else_keyword_length(char string[], TinyToken* tiny_token);

uint64_t open_encapsulate_length(char string[], TinyToken* tiny_token);
uint64_t close_encapsulate_length(char string[], TinyToken* tiny_token);
uint64_t enumerator_length(char string[], TinyToken* tiny_token);
uint64_t open_enumeration_length(char string[], TinyToken* tiny_token);
uint64_t close_enumeration_length(char string[], TinyToken* tiny_token);

uint64_t char_keyword_length(char string[], TinyToken* tiny_token);
uint64_t small_keyword_length(char string[], TinyToken* tiny_token);
uint64_t short_keyword_length(char string[], TinyToken* tiny_token);
uint64_t int_keyword_length(char string[], TinyToken* tiny_token);
uint64_t long_keyword_length(char string[], TinyToken* tiny_token);
uint64_t large_keyword_length(char string[], TinyToken* tiny_token);
uint64_t double_keyword_length(char string[], TinyToken* tiny_token);

uint64_t comp_keyword_length(char string[], TinyToken* tiny_token);
uint64_t main_keyword_length(char string[], TinyToken* tiny_token);
uint64_t return_keyword_length(char string[], TinyToken* tiny_token);

uint64_t assign_operator_length(char string[], TinyToken* tiny_token);
uint64_t addition_assign_operator_length(char string[], TinyToken* tiny_token);
uint64_t subtract_assign_operator_length(char string[], TinyToken* tiny_token);
uint64_t multiply_assign_operator_length(char string[], TinyToken* tiny_token);
uint64_t divide_assign_operator_length(char string[], TinyToken* tiny_token);
uint64_t and_assign_operator_length(char string[], TinyToken* tiny_token);
uint64_t or_assign_operator_length(char string[], TinyToken* tiny_token);
uint64_t bitwise_or_assign_operator_length(char string[], TinyToken* tiny_token);
uint64_t bitwise_and_assign_operator_length(char string[], TinyToken* tiny_token);
uint64_t xor_assign_operator_length(char string[], TinyToken* tiny_token);
uint64_t bit_shift_left_assign_operator_length(char string[], TinyToken* tiny_token);
uint64_t bit_shift_right_assign_operator_length(char string[], TinyToken* tiny_token);

uint64_t addition_operator_length(char string[], TinyToken* tiny_token);
uint64_t subtraction_operator_length(char string[], TinyToken* tiny_token);
uint64_t multiply_operator_length(char string[], TinyToken* tiny_token);
uint64_t divide_operator_length(char string[], TinyToken* tiny_token);
uint64_t modulo_operator_length(char string[], TinyToken* tiny_token);
uint64_t increment_operator_length(char string[], TinyToken* tiny_token);
uint64_t decrement_operator_length(char string[], TinyToken* tiny_token);
uint64_t square_operator_length(char string[], TinyToken* tiny_token);

uint64_t equivalence_operator_length(char string[], TinyToken* tiny_token);
uint64_t non_equivalence_operator_length(char string[], TinyToken* tiny_token);
uint64_t or_operator_length(char string[], TinyToken* tiny_token);
uint64_t and_operator_length(char string[], TinyToken* tiny_token);
uint64_t less_than_operator_length(char string[], TinyToken* tiny_token);
uint64_t greater_than_operator_length(char string[], TinyToken* tiny_token);
uint64_t less_than_equal_operator_length(char string[], TinyToken* tiny_token);
uint64_t greater_than_equal_operator_length(char string[], TinyToken* tiny_token);
uint64_t boolean_not_operator_length(char string[], TinyToken* tiny_token);

uint64_t complement_operator_length(char string[], TinyToken* tiny_token);
uint64_t bitwise_or_operator_length(char string[], TinyToken* tiny_token);
uint64_t bitwise_and_operator_length(char string[], TinyToken* tiny_token);
uint64_t xor_operator_length(char string[], TinyToken* tiny_token);
uint64_t bit_shift_left_operator_length(char string[], TinyToken* tiny_token);
uint64_t bit_shift_right_operator_length(char string[], TinyToken* tiny_token);

uint64_t dereference_operator_length(char string[], TinyToken* tiny_token);
uint64_t reference_operator_length(char string[], TinyToken* tiny_token);
uint64_t dot_operator_length(char string[], TinyToken* tiny_token);
uint64_t arrow_operator_length(char string[], TinyToken* tiny_token);


#endif
