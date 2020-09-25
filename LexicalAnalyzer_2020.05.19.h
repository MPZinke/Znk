

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


// ——————————————————— SPLIT BY WHITESPACE ———————————————————

typedef struct CharacterSegment
{
	char* segment;
	bool is_singular;
	struct CharacterSegment* next;
} CharacterSegment;


void add_new_word_to_words(CharacterSegment** segments, char* string, bool is_singular)
{
	char* segment = malloc(strlen(string)+1);
	strcpy(segment, string);

	CharacterSegment* new_segment = malloc(sizeof(CharacterSegment));
	*new_segment = (CharacterSegment){segment, is_singular, NULL};

	if(!*segments) *segments = new_segment;
	else
	{
		CharacterSegment* iter = *segments;
		while(iter->next) iter = iter->next;
		iter->next = new_segment;
	}
}


long length_of_string(char* string_start)
{
	bool no_preceding_escape_character = true;
	long long x = 1;
	while(string_start[x])
	{
		if(string_start[x] == '"' && no_preceding_escape_character) return x + 1;
		if(string_start[x] == '\\') no_preceding_escape_character = !no_preceding_escape_character;
		else no_preceding_escape_character = true;
		x++;
	}
	fprintf(stderr, "Bad string format\n");
	exit(BAD_STRING_FORMAT);
}


void print_words(CharacterSegment* segments)
{
	while(segments)
	{
		printf("%s\n", segments->segment);
		segments = segments->next;
	}
}


CharacterSegment* sepparate_by_whitespace(char* extracted_file)
{
	CharacterSegment* words = NULL;

	long long x = 0;
	while(extracted_file[0])
	{
		long long file_length = strlen(extracted_file);
		// sepparate into code & first string
		char* next_quotation = strchr(extracted_file, '"');
		// length of code to process
		long length_until_string_literal = next_quotation ? next_quotation - extracted_file : file_length + 1;

		// if code before literal: sepparate and add word
		if(length_until_string_literal)
		{
			char* code_string = malloc(length_until_string_literal);
			strncpy(code_string, extracted_file, length_until_string_literal);
			const char* standard_white_space = " \f\n\r\t\v";

			// sepparate code
			char* buffer = strtok(code_string, standard_white_space);
			while(buffer)
			{
				add_new_word_to_words(&words, buffer, false);
				buffer = strtok(NULL, standard_white_space);
			}
			extracted_file += length_until_string_literal;
		}
		// if literal exists: sepparate and add word
		if(extracted_file[0])
		{
			int literal_length = length_of_string(extracted_file);  // length of literal
			char* string_literal = malloc(literal_length+1);
			strncpy(string_literal, extracted_file, literal_length);
			add_new_word_to_words(&words, string_literal, true);
			extracted_file += literal_length;
		}
	}

	return words;
}



// —————————————————————— TOKENIZE ——————————————————————

typedef struct Token
{
	char* part;  // the string associated with it
	int type;  // the enum type
	// long order;  // where it is in the file
	struct Token* next;
} Token;


typedef struct TokenList
{
	Token token;
	struct TokenList* next;
} TokenList;


typedef struct Scope
{
	long start;
	long end;
	struct Token contents;
} Scope;


void add_new_token_to_tokens(Token** tokens, char* string, long long string_length, int type)
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


void split_token_and_insert_new(Token* token, char* split_point, int token1_type, int token2_type)
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


int delimiter_match(int delimiter_count, int delimiter_size, char delimiters[][delimiter_size], char* string)
{
	for(int x = 0; x < delimiter_count; x++)
	{
		for(int y = 0; string[y] && string[y] == delimiters[x][y] && y < delimiter_size; y++)
			if(y == delimiter_size-1) return x;
	}
	return -1;  // not found
}


void print_tokens(Token* tokens)
{
	while(tokens)
	{
		printf("%s\n", tokens->part);
		tokens = tokens->next;
	}
}


Token* tokenize_largest_operators(CharacterSegment* segments, int delimiter_count, int delimiter_size, 
char delimiters[][delimiter_size])
{
	Token* tokens = NULL;
	CharacterSegment* previous = NULL;
	while(segments)
	{
		char* segment = segments->segment;
		long long offset = 0;

		if(segments->is_singular)
		{
			add_new_token_to_tokens(&tokens, segment, strlen(segment), STRING);
			segments = segments->next;
			continue;
		}

		while(segment[offset])
		{
			int delimiter = delimiter_match(delimiter_count, 3, delimiters, segment+offset);
			if(-1 == delimiter) offset++;
			else
			{
				if(offset) add_new_token_to_tokens(&tokens, segment, offset, UNPROCESSED);
				add_new_token_to_tokens(&tokens, segment+offset, 3, SPECIAL);
				segment += offset + 3;
				offset = 0;
			}
		}
		if(offset) add_new_token_to_tokens(&tokens, segment, offset, UNPROCESSED);
		segments = segments->next;
	}
	return tokens;
}


void tokenize_smaller_operators(Token* tokens, int delimiter_count, int delimiter_size, 
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
			int delimiter = delimiter_match(delimiter_count, delimiter_size, delimiters, name+offset);
			if(-1 == delimiter) offset++;
			else
			{
				// special is at beginning
				if(!offset)
				{
					if(strlen(name) == delimiter_size) tokens->type = SPECIAL;  // token is special char
					else split_token_and_insert_new(tokens, name+delimiter_size, SPECIAL, UNPROCESSED);
				}
				// token is at middle or end
				else
				{
					if(strlen(name+offset) == delimiter_size)  // remainder of string is special char
						split_token_and_insert_new(tokens, name+offset, UNPROCESSED, SPECIAL);
					else split_token_and_insert_new(tokens, name+offset, UNPROCESSED, UNPROCESSED);

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


Token* tokenize_words(CharacterSegment* segments)
{
	// defined operators/delimiting special character
	char triple_delimiters[][3] = {{'<', '<', '='}, {'>', '>', '='}, {'&', '&', '='}, {'|', '|', '='}};
	const int triple_delimiter_count = sizeof(triple_delimiters) / 3;
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
	Token* tokens = tokenize_largest_operators(segments, triple_delimiter_count, 3, triple_delimiters);
	tokenize_smaller_operators(tokens, double_delimiter_count, 2, double_delimiters);
	tokenize_smaller_operators(tokens, single_delimiter_count, 1, single_delimiters);

	return tokens;
}



#endif