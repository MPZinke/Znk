
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


#include "Symbol.h"
#include "Token.h"


void copy_tiny_token(TinyToken* destination, TinyToken* source)
{
	destination->type = source->type;
	destination->line = source->line;
	destination->column = source->column;
	destination->length = source->length;
}


void delete_tiny_token(void* token_pointer)
{
	TinyToken* token = (TinyToken*)token_pointer;
	free(token);
}


TinyToken duplicate_tiny_token(TinyToken token)
{
	TinyToken new_token = {token.type, token.line, token.column, token.length};
	return new_token;
}


Token duplicate_token(Token token)
{
	Token new_token = {token.type, token.line, token.column, token.length, token.position, NULL, NULL};

	new_token.filename = malloc(strlen(token.filename)+1);
	strcpy(new_token.filename, token.filename);
	new_token.string = malloc(strlen(token.string)+1);
	strcpy(new_token.string, token.string);

	return new_token;
}


void delete_token(void* token_pointer)
{
	Token* token = (Token*)token_pointer;
	free(token->filename);
	free(token->string);
	free(token);
}


Token* full_token_from_tiny_token(TinyToken* token, char filename[], uint64_t position, char* token_string)
{
	return new_complete_token(token->column, filename, token->length, token->line, position, token_string, token->type);
}


//TODO: fix so that it doesn't run over 120 chars
Token* new_complete_token(	uint64_t column, char filename[], uint64_t length, uint64_t line, uint64_t position, 
  							char* token_string, uint16_t type)
{
	Token* new_token = malloc(sizeof(Token));
	new_token->column = column;
	new_token->length = length;
	new_token->line = line;
	new_token->position = position;
	new_token->string = token_string;
	new_token->type = type;

	new_token->filename = malloc(strlen(filename)+1);
	strcpy(new_token->filename, filename);

	return new_token;
}


Token* new_partial_token(uint64_t length, uint64_t position, char* token_string, uint16_t type)
{
	Token* new_token = malloc(sizeof(Token));
	new_token->length = length;
	new_token->position = position;
	new_token->string = token_string;
	new_token->type = type;

	return new_token;
}


void print_tiny_token(void* token_pointer)
{
	TinyToken* token = (TinyToken*)token_pointer;
	Symbol* symbol = find_symbol_by_(token->type);
	char* title = symbol ? symbol->title : "";
	printf(	"Token:\n\tcolumn: %llu\n\tlength: %llu\n\tline: %llu\n\ttype: %s\n",
			token->column, token->length, token->line, title);
}


void print_token(void* token_pointer)
{
	Token* token = (Token*)token_pointer;
	Symbol* symbol = find_symbol_by_(token->type);
	char* title = symbol ? symbol->title : "";
	printf(	"Token:\n\tcolumn: %llu\n\tfilename: %s\n\tlength: %llu"
			"\n\tline: %llu\n\tposition: %llu\n\tstring: %s\n\ttype: %s\n",
			token->column, token->filename, token->length, token->line, 
			token->position, token->string, title);
}


void print_token_type(void* token_pointer)
{
	Token* token = (Token*)token_pointer;
	Symbol* symbol = find_symbol_by_(token->type);
	char* title = symbol ? symbol->title : "";
	printf(	"Token type: %s\n", title);
}


void print_token_type_verbose(void* token_pointer)
{
	Token* token = (Token*)token_pointer;
	Symbol* symbol = find_symbol_by_(token->type);
	char* title = symbol ? symbol->title : "";
	printf(	"Token type: %-30s %s\n", title, token->string);
}
