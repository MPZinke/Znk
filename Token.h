
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


#ifndef _TOKEN_
#define _TOKEN_


#include <string.h>


#include "Global.h"
#include "LinkedList.h"


typedef struct TokenStream
{
	Node* tokens;
	uint64_t length;
} TokenStream;


typedef struct TinyToken
{
	uint16_t type;
	uint64_t line;
	uint64_t column;
	uint64_t length;
} TinyToken;


typedef struct Token
{
	uint16_t type;
	uint64_t line;
	uint64_t column;
	uint64_t length;
	uint64_t position;
	char* filename;
	char* string;
} Token;


void copy_tiny_token(TinyToken* destination, TinyToken* source);
void delete_tiny_token(void* token_pointer);
TinyToken duplicate_tiny_token(TinyToken token);
Token duplicate_token(Token token);
void delete_token(void* token_pointer);
Token* full_token_from_tiny_token(TinyToken* token, char filename[], uint64_t position, char* token_string);
Token* new_complete_token(uint64_t, char[], uint64_t, uint64_t, uint64_t, char*, uint16_t);
Token* new_partial_token(uint64_t length, uint64_t position, char* token_string, uint16_t type);
void print_tiny_token(void* token_pointer);
void print_token(void* token_pointer);
void print_token_type(void* token_pointer);
void print_token_type_verbose(void* token_pointer);


#endif
