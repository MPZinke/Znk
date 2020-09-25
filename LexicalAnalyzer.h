

#ifndef _LEXICALANALYZER_
#define _LEXICALANALYZER_

#include<stdbool.h>
#include<string.h>

#include"Global.h"

enum
{
	UNPROCESSED,
	STRING,
	SPECIAL
};


// char __LEXANAL__white_space_number[] = {32, 9, 10, 11, 12, 13};
// char __LEXANAL__white_space[] = {' ', '\t', '\n', '\r', '\f', '\v'};
// int __LEXANAL__white_space_count = sizeof(__LEXANAL__white_space);
void __LEXANAL__step_index_past_string_litertal(char[], INDEX_TYPE*, INDEX_TYPE*);



// —————————————————— CHARACTER SEGMENTS ———————————————————
// —————————————————————————————————————————————————

typedef struct CharacterSegment
{
	char* segment;
	bool is_fully_divided;
	INDEX_TYPE line_number;
	struct CharacterSegment* next;
} CharacterSegment;


// —————————————————————— UTILITY ———————————————————————

void __LEXANAL__add_new_CharacterSegement(CharacterSegment** head, char* segment, 
INDEX_TYPE line_number, bool is_fully_divided)
{
	CharacterSegment* new_segment = malloc(sizeof(CharacterSegment));
	*new_segment = (CharacterSegment){segment, is_fully_divided, line_number, NULL};

	if(!*head) *head = new_segment;
	else
	{
		CharacterSegment* iter = *head;
		while(iter->next) iter = iter->next;
		iter->next = new_segment;
	}
}


char* __LEXANAL__copy_code_in_range(char code[], INDEX_TYPE* start, INDEX_TYPE stop)
{
	INDEX_TYPE span = stop - *start;

	char* code_segment = malloc(span + 1);
	strncpy(code_segment, code + *start, span);
	code_segment[span] = 0;

	*start = stop;
	return code_segment;
}


void __LEXANAL__free_CharacterSegment(CharacterSegment* head)
{
	CharacterSegment* next;
	while(head)
	{
		next = head->next;
		free(head->segment);
		free(head);
		head = next;
	}
}


void __LEXANAL__print_segments(CharacterSegment* head)
{
	while(head)
	{
		printf("Segment: %s, Is Fully Divided %s, Line Number: %lu\n", head->segment, head->is_fully_divided ? "true" : "false",
				head->line_number);
		head = head->next;
	}
}


void __LEXANAL__step_index_past_string_litertal(char code[], INDEX_TYPE* index_address, 
INDEX_TYPE* line_number)
{
	INDEX_TYPE index = *index_address + 1;

	bool escape_character = false;
	while(code[index] && (code[index] != '"' || escape_character))
	{
		if(code[index] == '\n') (*line_number)++;

		if(code[index++] == '\\') escape_character = !escape_character;
		else if(escape_character) escape_character = false;  // last char is not escape char; escape eaten up
	}

	*index_address = index+1;
}


// —————————————————————— PROCESSING ———————————————————————

CharacterSegment* __LEXANAL__split_by_white_space(char* code)
{
	CharacterSegment* head = NULL;

	INDEX_TYPE index = 0, line_number = 1;
	while(code[index])
	{
		// ignore whitespace and count new lines
		while(code[index] == 32 || (9 <= code[index] && code[index] <= 13))
			if(code[index++] == '\n') line_number++;

		if(code[index])
		{
			INDEX_TYPE start = index;
			while(code[index] && code[index] != '"' && code[index] != 32 
			&& (code[index] < 9 || 13 < code[index]))
				index++;
			if(code[index] == '"')
			{	
				char* segment = __LEXANAL__copy_code_in_range(code, &start, index);
				__LEXANAL__add_new_CharacterSegement(&head, segment, line_number, code[index-1] == '"');
				__LEXANAL__step_index_past_string_litertal(code, &index, &line_number);
			}
			char* segment = __LEXANAL__copy_code_in_range(code, &start, index);
			__LEXANAL__add_new_CharacterSegement(&head, segment, line_number, code[index-1] == '"');
		}
	}
	return head;
}


// —————————————————————— TOKENIZE ——————————————————————
// —————————————————————————————————————————————————

typedef struct Token
{
	char* part;  // the string associated with it
	int type;  // the enum type
	// long order;  // where it is in the file
	struct Token* next;
} Token;


// —————————————————————— UTILITY ———————————————————————

void __LEXANAL__add_new_token_to_tokens(Token** tokens, char* string, long long string_length, int type)
{
	char* part = malloc(string_length+1);
	strncpy(part, string, string_length);

	Token* new_token = malloc(sizeof(Token));
	*new_token = (Token){part, type, NULL};

	if(!*tokens) *tokens = new_token;
	else
	{
		Token* iter = *tokens;
		while(iter->next) iter = iter->next;
		iter->next = new_token;
	}
}


void __LEXANAL__split_token_and_insert_new(Token* token, char* split_point, int token1_type, int token2_type)
{
	char* name1 = malloc(split_point - token->part + 1);
	char* name2 = malloc(strlen(split_point));
	strcpy(name2, split_point);
	*split_point = 0;
	strcpy(name1, token->part);
	free(token->part);

	Token* new_token = malloc(sizeof(Token));
	*new_token = (Token){name2, token2_type, token->next};
	*token = (Token){name1, token1_type, new_token};
}


int __LEXANAL__delimiter_match(int delimiter_count, int delimiter_size, char delimiters[][delimiter_size],
char* string)
{
	for(int x = 0; x < delimiter_count; x++)
	{
		for(int y = 0; string[y] && string[y] == delimiters[x][y] && y < delimiter_size; y++)
			if(y == delimiter_size-1) return x;
	}
	return -1;  // not found
}


void __LEXANAL__print_tokens(Token* tokens)
{
	while(tokens)
	{
		printf("%s\n", tokens->part);
		tokens = tokens->next;
	}
}


// —————————————————————— PROCESSING ———————————————————————

Token* __LEXANAL__tokenize_largest_operators(CharacterSegment* segments, int delimiter_count, int delimiter_size, 
char delimiters[][delimiter_size])
{
	Token* tokens = NULL;
	CharacterSegment* previous = NULL;
	while(segments)
	{
		char* segment = segments->segment;
		long long offset = 0;

		if(segments->is_fully_divided)
		{
			__LEXANAL__add_new_token_to_tokens(&tokens, segment, strlen(segment), STRING);
			segments = segments->next;
			continue;
		}

		while(segment[offset])
		{
			int delimiter = __LEXANAL__delimiter_match(delimiter_count, 3, delimiters, segment+offset);
			if(-1 == delimiter) offset++;
			else
			{
				if(offset) __LEXANAL__add_new_token_to_tokens(&tokens, segment, offset, UNPROCESSED);
				__LEXANAL__add_new_token_to_tokens(&tokens, segment+offset, 3, SPECIAL);
				segment += offset + 3;
				offset = 0;
			}
		}
		if(offset) __LEXANAL__add_new_token_to_tokens(&tokens, segment, offset, UNPROCESSED);
		segments = segments->next;
	}
	return tokens;
}


void __LEXANAL__tokenize_smaller_operators(Token* tokens, int delimiter_count, int delimiter_size, 
char delimiters[][delimiter_size])
{
	while(tokens)
	{
		// already sorted: ignore
		if(tokens->type)
		{
			tokens = tokens->next;
			continue;
		}

		char* name = tokens->part;
		long long offset = 0;
		while(name[offset])
		{
			int delimiter = __LEXANAL__delimiter_match(delimiter_count, delimiter_size, delimiters, 
									name+offset);
			if(-1 == delimiter) offset++;
			else
			{
				// special is at beginning
				if(!offset)
				{
					if(strlen(name) == delimiter_size) tokens->type = SPECIAL;  // token is special char
					else __LEXANAL__split_token_and_insert_new(tokens, name+delimiter_size, SPECIAL, 
								UNPROCESSED);
				}
				// token is at middle or end
				else
				{
					if(strlen(name+offset) == delimiter_size)  // remainder of string is special char
						__LEXANAL__split_token_and_insert_new(tokens, name+offset, UNPROCESSED, 
								SPECIAL);
					else __LEXANAL__split_token_and_insert_new(tokens, name+offset, UNPROCESSED, 
								UNPROCESSED);

					// special at end: jump one forward to jump another forward
					if(strlen(tokens->next->part) == delimiter_size) tokens = tokens->next;
				}
				name = tokens->part;
				offset = strlen(name);
			}
		}
		tokens = tokens->next;
	}
}


Token* __LEXANAL__tokenize_code(char extracted_code[])
{
	CharacterSegment* segments = __LEXANAL__split_by_white_space(extracted_code);
	free(extracted_code);

	// defined operators/delimiting special character
	char triple_delimiters[][3] = {{'<', '<', '='}, {'>', '>', '='}, {'&', '&', '='}, {'|', '|', '='}};
	const int triple_count = sizeof(triple_delimiters) / 3;
	char double_delimiters[][2] =	{ 
										{'+', '+'}, {'-', '-'}, {'*', '*'}, {'+', '='}, {'-', '='}, {'*', '='}, {'/', '='}, {'!', '='}, {'&', '&'}, 
										{'|', '|'}, {'<', '='}, {'>', '='}, {'!', '-'}, {'|', '='}, {'&', '='}, {'^', '='}, {'<', '<'}, {'>', '>'}
									};
	const int double_delimiter_count = sizeof(double_delimiters) / 2;
	char single_delimiters[][1] =	{
										{';'}, {'+'}, {'-'}, {'*'}, {'/'}, {'%'}, {'<'}, {'>'}, {'?'}, {'!'}, {'|'}, {'~'}, {'@'}, {'$'}, {'{'}, 
										{'}'}, {'['}, {']'}, {'('}, {')'}, {':'}, {','}, {'='}
									};
	const int single_delimiter_count = sizeof(single_delimiters);

	// create tokens
	Token* tokens = __LEXANAL__tokenize_largest_operators(segments, triple_count, 3, triple_delimiters);
	__LEXANAL__tokenize_smaller_operators(tokens, double_delimiter_count, 2, double_delimiters);
	__LEXANAL__tokenize_smaller_operators(tokens, single_delimiter_count, 1, single_delimiters);

	__LEXANAL__free_CharacterSegment(segments);
	return tokens;
}


#endif