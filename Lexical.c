
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


// ———— COMPARISIONS
#define STRING_CHAR_IS_WHITESPACE ((8 <= string[x] && string[x] <= 13) || string[x] == 32)
#define STRING_CHAR_IS_NOT_WHITESPACE ((string[x] < 9 || 13 < string[x]) && string[x] != 32)
#define STRING_CHAR_IS_NOT_NEWLINE (string[x] != 10 && string[x] != 13)
#define HEXIDECIMAL_ALLOWED_VALUES ((47 < string[x] && string[x] < 58) || (64 < string[x] && string[x] < 71))

// #define UINT64_MAX 0xFFFFFFFFFFFFFFFF


#include "SymbolDefinitions.h"
#include "SymbolEnum.h"


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


typedef struct Node
{
	void* value;
	struct Node* next;
} Node;


typedef struct TokenStream
{
	Node* tokens;
	uint64_t length;
} TokenStream;


// ———————————————————————————————————————————————————— GLOBAL ————————————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

Node* add_value_to_linked_list(Node** head, void* value);
void delete_linked_list(Node** head, void(*delete_node_value_function)(void*));

void delete_token(void* token_pointer);
Token* new_complete_token(uint64_t column, char filename[], uint64_t length, uint64_t line, uint64_t position, char* token_string, uint16_t type);
Token* new_partial_token(uint64_t length, uint64_t position, char* token_string, uint16_t type);

TokenStream get_token_stream(char string[]);
char* next_token(uint64_t* length, char string[], uint16_t* type);
uint64_t line_comment_length(char string[]);
uint64_t white_space_length(char string[]);
uint64_t hexidecimal_int_literal_length(char string[]);
uint64_t binary_int_literal_length(char string[]);
uint64_t octal_int_literal_length(char string[]);
uint64_t decimal_int_literal_length(char string[]);
uint64_t double_literal_length(char string[]);

FILE* validate_and_open_znk_file(char filename[]);
char* get_file_contents(FILE* file);


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
	}
}


// ————————————————————————————————————————————————————— TOKEN —————————————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

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


void print_token(void* token_pointer)
{
	Token* token = (Token*)token_pointer;
	printf(	"Token:\n\tcolumn: %llu\n\tfilename: %s\n\tlength: %llu"
			"\n\tline: %llu\n\tposition: %llu\n\tstring: %s\n\ttype:%u\n",
			token->column, token->filename, token->length, token->line, token->position, token->string, token->type);
}


// ———————————————————————————————————————————— TOKEN TYPES DETERMINERS ————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

TokenStream get_token_stream(char string[])
{
	#include "LengthFunctions.h"

	TokenStream token_stream = {NULL, 0};
	Node** iterator = &token_stream.tokens;

	for(uint64_t x = 0; string[x] && x < UINT64_MAX; x++)
	{
		uint64_t length;
		uint16_t type;
		char* token_string = next_token(&length, string+x, &type);

		if(token_string == NULL) continue;

		Token* new_token = new_partial_token(length, x, string+x, type);
		add_value_to_linked_list(&token_stream.tokens, (void*)new_token);

		x += length;
	}
	return token_stream;
}


char* next_token(uint64_t* length, char string[], uint16_t* type)
{
	#include "LengthFunctions.h"

	// ———— CALCULATE ————
	// calculate the lengths for each type of symbol match
	uint64_t longest_match_length = 0, longest_match_type = 0;
	for(uint64_t type = 0; type < MAX_SYMBOL_COUNT; type++)
	{
		if(LENGTH_FUNCTIONS[type])  //TESTING
		{  //TESTING
			uint64_t type_match_length = LENGTH_FUNCTIONS[type](string);
			if(type_match_length > longest_match_length)
			{
				longest_match_length = type_match_length;
				longest_match_type = type;
			}
		}  //TESTING
	}

	*length = longest_match_length;
	*type = longest_match_type;

	char* token_string = NULL;
	if(type)
	{
		token_string = malloc(longest_match_length+1);
		strncpy(token_string, string, longest_match_length);
		token_string[longest_match_length] = 0;
	}

	return token_string;
}


// ———————————————————————————————————————————————————— MATCHES ————————————————————————————————————————————————————— //


// Regex: //.*
uint64_t line_comment_length(char string[])
{
	register uint64_t x = 0;
	if(string[0] != '/' || string[1] != '/') return x;
	for(x = 2; string[x] && STRING_CHAR_IS_NOT_NEWLINE && x < UINT64_MAX; x++);
	return x;
}


uint64_t white_space_length(char string[])
{
	uint64_t x;
	for(x = 0; STRING_CHAR_IS_WHITESPACE && x < UINT64_MAX; x++);
	return x;
}


// ———————————————————————————————————————————————————— LITERALS ————————————————————————————————————————————————————— //



// ———————————————————————————————————————————————————— LITERALS ————————————————————————————————————————————————————— //

// Regex: 0x[0-9]+
uint64_t hexidecimal_int_literal_length(char string[])
{
	if(!string[0] || !string[1]) return 0;
	if(string[0] != '0' || string[1] != 'x') return 0;

	uint64_t x;
	for(x = 2; HEXIDECIMAL_ALLOWED_VALUES && x < UINT64_MAX; x++);
	return (x != 2) * x;
}


// Regex: 0b[01]+
uint64_t binary_int_literal_length(char string[])
{
	if(!string[0] || !string[1]) return 0;
	if(string[0] != '0' || string[1] != 'b') return 0;

	uint64_t x;
	for(x = 2; 47 < string[x] && string[x] < 50 && x < UINT64_MAX; x++);
	return (x != 2) * x;
}


uint64_t octal_int_literal_length(char string[])
{
	if(!string[0] || !string[1]) return 0;
	if(string[0] != '0') return 0;

	uint64_t x;
	for(x = 1; 47 < string[x] && string[x] < 57 && x < UINT64_MAX; x++);
	return (x != 1) * x;
}


uint64_t decimal_int_literal_length(char string[])
{
	if(!string[0]) return 0;

	uint64_t x;
	for(x = 0; 47 < string[x] && string[x] < 58 && x < UINT64_MAX; x++);
	return x;
}


uint64_t double_literal_length(char string[])
{
	uint64_t x = 0;
	//TODO
	return x;
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
	printf("STRLEN: %lu\n", strlen(file_string));

	TokenStream token_stream = get_token_stream(file_string);
	print_linked_list(token_stream.tokens, print_token);

	free(file_string);
	
	return 0;
}