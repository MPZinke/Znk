
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
#include <string.h>


#include "Global.h"
#include "Symbol.h"
#include "Token.h"


// ———————————————————————————————————————————————————— GLOBAL ————————————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

char* make_string_copy(char string[], uint64_t size);
void print_raw(char string[]);

TokenStream get_token_stream(char string[]);
char* next_token(TinyToken* current_data, char string[]);
FILE* validate_and_open_znk_file(char filename[]);
char* get_file_contents(FILE* file);


// ———————————————————————————————————————————————————— UTILITY ————————————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

char* make_string_copy(char string[], uint64_t size)
{
	char* copy = malloc(size+1);
	strncpy(copy, string, size);
	copy[size] = 0;
	return copy;
}


void print_raw(char string[])
{
	for(uint64_t x = 0; string[x] && x < UINT64_MAX; x++)
	{
		printf("X: %lu, string[x]: %hhu\n", x, string[x]);
	}
}


// ———————————————————————————————————————————— TOKEN TYPES DETERMINERS ————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

TokenStream get_token_stream(char string[])
{
	TokenStream token_stream = {NULL, 0};
	Node** iterator = &token_stream.tokens;

	TinyToken current_data = {0, 1, 1, 0};  // column stores ending column
	for(uint64_t x = 0; string[x] && x < UINT64_MAX; x += current_data.length ? current_data.length : 1)
	{
		uint64_t column = current_data.column;  // starting column of token
		char* token_string = next_token(&current_data, string+x);

		// printf("X: %lu, string[x]: %hhu, Length: %lu\n", x, string[x], length);  //TESTING
		if(token_string == NULL) continue;

		char null = 0;  //TESTING
		Token* new_token = new_complete_token(	column, &null, current_data.length, current_data.line, 
		  										x, token_string, current_data.type);
		add_value_to_linked_list(&token_stream.tokens, (void*)new_token);
	}
	return token_stream;
}


char* next_token(TinyToken* current_data, char string[])
{
	// ———— CALCULATE ————
	// calculate the lengths for each type of symbol match
	TinyToken longest_token = {0, current_data->line, current_data->column, 0};
	bool is_ignored = SYMBOLS[0].is_ignored;
	for(uint64_t symbol = 0; symbol < sizeof(SYMBOLS) / sizeof(Symbol); symbol++)
	{
		TinyToken type_token = {SYMBOLS[symbol].type, current_data->line, current_data->column, 0};
		type_token.length = SYMBOLS[symbol].function(string, SYMBOLS+symbol, &type_token);
		if(type_token.length > longest_token.length)
		{
			is_ignored = SYMBOLS[symbol].is_ignored;
			copy_tiny_token(&longest_token, &type_token);
		}
	}

	copy_tiny_token(current_data, &longest_token);  // make the data of the token be known to calling function

	if(is_ignored) return NULL;
	return make_string_copy(string, longest_token.length);
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


char* get_file_contents(FILE* file)
{
	fseek(file, 0L, SEEK_END);
	uint64_t size = ftell(file);
	char* contents = malloc(size);

	rewind(file);
	char tmp = fgetc(file);
	for(uint64_t x = 0; tmp != EOF && x < UINT64_MAX; x++)
	{
		contents[x] = tmp;
		tmp = fgetc(file);
	}

	return contents;
}



int main(int argc, char* argv[])
{
	FILE* file = validate_and_open_znk_file(argv[1]);
	char* file_string = get_file_contents(file);
	// print_raw(file_string);  //TESTING

	TokenStream token_stream = get_token_stream(file_string);
	print_linked_list(token_stream.tokens, print_token);

	// print_raw(file_string);  //TESTING

	free(file_string);
	
	return 0;
}