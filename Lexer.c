
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


#include "LexerLengths.h"
#include "Global.h"
#include "Symbols.h"


// ———————————————————————————————————————————————————— GLOBAL ————————————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

void print_raw(char string[]);

Node* add_value_to_linked_list(Node** head, void* value);
void delete_linked_list(Node** head, void(*delete_node_value_function)(void*));
void print_linked_list(Node* head, void(*print_function)(void*));
void copy_tiny_token(TinyToken* destination, TinyToken* source);
void delete_tiny_token(void* token_pointer);
TinyToken duplicate_tiny_token(TinyToken token);
Token duplicate_token(Token token);
void delete_token(void* token_pointer);
Token* new_complete_token(uint64_t column, char filename[], uint64_t length, uint64_t line, uint64_t position, char* token_string, uint16_t type);
Token* new_partial_token(uint64_t length, uint64_t position, char* token_string, uint16_t type);
void print_token(void* token_pointer);
void print_token_type(void* token_pointer);
void print_token_type_verbose(void* token_pointer);
TokenStream get_token_stream(char string[]);
char* next_token(uint64_t* column, uint64_t* length, uint64_t* line, char string[], uint16_t* type);
FILE* validate_and_open_znk_file(char filename[]);
char* get_file_contents(FILE* file);


// ———————————————————————————————————————————————————— UTILITY ————————————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

void print_raw(char string[])
{
	for(uint64_t x = 0; string[x]; x++)
	{
		printf("X: %llu, string[x]: %hhu\n", x, string[x]);
	}
}


// —————————————————————————————————————————————————— LINKED LIST ——————————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //


Node* add_value_to_linked_list(Node** head, void* value)
{
	Node* new_node = malloc(sizeof(new_node));
	new_node->next = NULL;
	new_node->value = value;

	if(!*head) *head = new_node;
	else
	{
		Node* iter = *head;
		for(uint64_t x = 0; iter->next && x < UINT64_MAX; x++) iter = iter->next;
		iter->next = new_node;
	}

	return new_node;
}


void delete_linked_list(Node** head, void(*delete_node_value_function)(void*))
{
	Node* iter = *head;
	*head = NULL;

	for(uint64_t x = 0; iter && x < UINT64_MAX; x++)
	{
		Node* temp = iter->next;
		if(iter->value) delete_node_value_function(iter->value);
		free(iter);
		iter = temp;
	}
}


void print_linked_list(Node* head, void(*print_function)(void*))
{
	for(uint64_t x = 0; head && x < UINT64_MAX; x++)
	{
		print_function(head->value);
		head = head->next;
	}
}


// ————————————————————————————————————————————————————— TOKEN —————————————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

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


//TODO: fix so that it doesn't run over 120 chars
Token* new_complete_token(uint64_t column, char filename[], uint64_t length, uint64_t line, uint64_t position, char* token_string, uint16_t type)
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
	printf(	"Token:\n\tcolumn: %llu\n\tlength: %llu\n\tline: %llu\n\ttype: %s\n",
			token->column, token->length, token->line, SYMBOL_TITLES[token->type]);
}


void print_token(void* token_pointer)
{
	Token* token = (Token*)token_pointer;
	printf(	"Token:\n\tcolumn: %llu\n\tfilename: %s\n\tlength: %llu"
			"\n\tline: %llu\n\tposition: %llu\n\tstring: %s\n\ttype: %s\n",
			token->column, token->filename, token->length, token->line, 
			token->position, token->string, SYMBOL_TITLES[token->type]);
}


void print_token_type(void* token_pointer)
{
	Token* token = (Token*)token_pointer;
	printf(	"Token type: %s\n", SYMBOL_TITLES[token->type]);
}


void print_token_type_verbose(void* token_pointer)
{
	Token* token = (Token*)token_pointer;
	printf(	"Token type: %-30s %s\n", SYMBOL_TITLES[token->type], token->string);
}


// ———————————————————————————————————————————— TOKEN TYPES DETERMINERS ————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

TokenStream get_token_stream(char string[])
{
	TokenStream token_stream = {NULL, 0};
	Node** iterator = &token_stream.tokens;

	uint64_t column = 0, length = 0, line = 1;  // length is automatically updated to 0 if no match found
	for(uint64_t x = 0; string[x] && x < UINT64_MAX; x += length ? length : 1)
	{
		uint16_t type;
		char* token_string = next_token(&column, &length, &line, string+x, &type);

		// printf("X: %llu, string[x]: %hhu, Length: %llu\n", x, string[x], length);  //TESTING

		if(token_string == NULL) continue;

		Token* new_token = new_partial_token(length, x, token_string, type);
		add_value_to_linked_list(&token_stream.tokens, (void*)new_token);
	}
	return token_stream;
}


char* next_token(uint64_t* column, uint64_t* length, uint64_t* line, char string[], uint16_t* type)
{
	// ———— CALCULATE ————
	// calculate the lengths for each type of symbol match
	TinyToken longest_token = {0, *line, *column, 0};
	for(uint64_t type = 0; type < MAX_SYMBOL_COUNT; type++)
	{
		if(LENGTH_FUNCTIONS[type])  //TESTING: function is implemented
		{  //TESTING: function is implemented
			TinyToken tiny_token = {type, *line, *column, 0};
			tiny_token.length = LENGTH_FUNCTIONS[type](string, &tiny_token);
			if(tiny_token.length > longest_token.length)
			{
				copy_tiny_token(&longest_token, &tiny_token);
			}
		}  //TESTING: function is implemented
	}

	*column = longest_token.column;
	*length = longest_token.length;
	*line = longest_token.line;
	*type = longest_token.type;

	char* token_string = NULL;
	if(longest_token.type)
	{
		token_string = malloc(longest_token.length+1);
		strncpy(token_string, string, longest_token.length);
		token_string[longest_token.length] = 0;
	}

	return token_string;
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
	setup_length_functions();
	setup_symbol_titles();

	FILE* file = validate_and_open_znk_file(argv[1]);
	char* file_string = get_file_contents(file);
	// print_raw(file_string);  //TESTING

	TokenStream token_stream = get_token_stream(file_string);
	print_linked_list(token_stream.tokens, print_token_type_verbose);

	free(file_string);
	
	return 0;
}