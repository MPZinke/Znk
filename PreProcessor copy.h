
// max number of characters in a file is defined by the INDEX_TYPE C preprocessor definition.
// overlying process of read file, find definitions, find instances, allocate space, copy/substitute/uncomment file
// uses a total time of ~O(5N).

// {
// "email": "mathew.zinke@hotmail.com",
// "product_key": "3996b5-f4749b-f805c6-381ad1-4ef7c2"
// }


#ifndef _PREPROCESSOR_
#define _PREPROCESSOR_

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"Global.h"

// enum PREPRO_TYPE
// {
// 	CODE,
// 	DEFINE,
// 	IF,
// 	IFN,
// 	ELIF,
// 	ELIFN,
// 	FI,
// 	IMPORT,
// 	INCLUDE,
// 	TEMPLATE
// };


enum PREPRO_IFS_ENUM
{
	NOT_IF,
	IFN,
	IF,
	ELIFN,
	ELIF,
	ELSE,
	FI
};


char PREPRO_IFS_STR[][10] = {"#NOT_IF", "#IFN", "#IF", "#ELIFN", "#ELIF", "#ELSE", "#FI"};


bool SMART_ARRAY = true;  // pass size of array as hidden arguments



typedef struct DEFINITION
{
	char* key;  // the definition key: #define KEY
	char* value;  // the value for it: #define key VALUE
	TOKEN_COUNT_TYPE count;  // number of occurences that the key shows up as `KEY`
	struct DEFINITION* previous;
	struct DEFINITION* next;
} DEFINITION;


typedef struct INSTANCE
{
	DEFINITION* definition;  // which which DEFINITION this instance pertains to 
	INDEX_TYPE start;  // starting index of `KEY`
	INDEX_TYPE stop;  // stopping index of `KEY`
	struct INSTANCE* next;
} INSTANCE;

// ———— LL ————
void __PREPRO__add_new_DEFINITION_node(DEFINITION** head, char* key, char* value);
void __PREPRO__add_new_INSTANCE_node(INSTANCE** head, DEFINITION* definition, 
INDEX_TYPE start, INDEX_TYPE stop);
bool __PREPRO__remove_DEFINITION(DEFINITION** head, char key[]);
// ———— SKIP ————
void __PREPRO__skip_comment(char code[], INDEX_TYPE* index_address);
void __PREPRO__skip_comment_and_record_length(char code[], INDEX_TYPE* index_address,
INDEX_TYPE* comment_characters);
void __PREPRO__skip_string_literal(char string[], INDEX_TYPE* read_index);
// ———— SCAN ————
char* __PREPRO__copy_preprocessor_line(char code[], INDEX_TYPE* index);


// ————————————————————— DEFINITIONS —————————————————————

void __PREPRO__definition_define(char buffer[], DEFINITION** head)
{
	//TODO: validate format
	printf("DEFINITION FOUND: %s\n", buffer);

	buffer = strtok(buffer+7, " \t");
	char* key = __GLOBAL__copy_to_new_string(buffer);
	buffer = strtok(NULL, " \f\n\r\t\v");
	char* value = __GLOBAL__copy_to_new_string(buffer);
	printf("\n");

	__PREPRO__add_new_DEFINITION_node(head, key, value);
}


void __PREPRO__undefine_define(char buffer[], DEFINITION** head)
{
	buffer = strtok(buffer+6, " \t");
	if(!__PREPRO__remove_DEFINITION(head, buffer))
	{
		fprintf(stderr, "No definition defined with key %s\n", buffer);
		exit(BAD_UNDEFINE_NOT_FOUND);
	}
}


int __PREPRO__is_if_statement(char instruction[])
{
	for(int x = 1; x < 7; x++) if(strstr(instruction, PREPRO_IFS_STR[x])) return x;
	return NOT_IF;
}


bool __PREPRO__if_evaluates_to_true(char* if_clause, DEFINITION** head, int type)
{
	if(type == FI) return true;  // shouldn't matter
	if(type == ELSE) return true;  // 

	int offset = 2 + type;
	char* copy = __GLOBAL__copy_to_new_string(if_clause);
	char* definition = strtok(copy + offset, " \t\n");

	DEFINITION* definitions = *head;
	while(definitions)
	{
		if(!strcmp(definition, definitions->key)) {printf("MATCH\n"); return type % 2 != 0;}  // flip for N values
		definitions = definitions->next;
	}
	return false;  // flip for N values
}


// ——————————————————————— FILE ———————————————————————

// read from file and add to character array
// takes in a string for the filename
// opens and reads file size; allocate memory & copies contents
// returns pointer to copied file
char* __PREPRO__read_file_in(char file_name[])
{
	FILE* file = fopen(file_name, "r");
	if(!file)
	{
		fprintf(stderr, "No file found for %s\n", file_name);
		exit(BAD_FILE_OPEN);
	}
	// get needed buffer size
	fseek(file, 0L, SEEK_END);
	char* extracted_file = malloc(ftell(file)+1);
	rewind(file);

	INDEX_TYPE index = 0;
	char current;
	current = fgetc(file);
	while(!feof(file))
	{
		extracted_file[index++] = current;
		current = fgetc(file);
	}

	return extracted_file;
}


// ——————————————————————— LL ————————————————————————

// add new DEFINITION to linked list.
// takes pointer to head (DEFINITION pointer), string key, string value
// creates a DEFINITION instance, adds values to instance & sets it at end of list
void __PREPRO__add_new_DEFINITION_node(DEFINITION** head, char* key, char* value)
{
	DEFINITION* new_value = malloc(sizeof(DEFINITION));
	*new_value = (DEFINITION){key, value, 0, 0, 0};

	if(!*head) *head = new_value;  // no previous nodes in list
	else
	{
		DEFINITION* iter = *head;
		while(iter->next) 
		{
			if(!strcmp(iter->key, key))
			{
				fprintf(stderr, "Value %s already defined\n", key);
				exit(BAD_MULTIPLE_DEFINITION);
			}
			iter = iter->next;
		}
		iter->next = new_value;
		new_value->previous = iter;
	}
}


// add new INSTANCE to linked list.
// takes pointer to head (INSTANCE pointer), DEFINITION, start location & stop location
// creates a INSTANCE instance, adds values to instance & sets it at end of list
void __PREPRO__add_new_INSTANCE_node(INSTANCE** head, DEFINITION* definition, 
INDEX_TYPE start, INDEX_TYPE stop)
{
	INSTANCE* new_value = malloc(sizeof(INSTANCE));
	*new_value = (INSTANCE){definition, start, stop, 0};

	if(!*head) *head = new_value;  // no previous nodes in list
	else
	{
		INSTANCE* iter = *head;
		while(iter->next) iter = iter->next;
		iter->next = new_value;
	}
}


bool __PREPRO__remove_DEFINITION(DEFINITION** head, char key[])
{
	if(!*head) return false;
	DEFINITION *iter = *head;

	while(iter && strcmp(iter->key, key)) iter = iter->next;
	if(!iter) return false;  // not found

	if(iter != *head) iter->previous->next = iter->next;
	else *head = iter->next ? iter->next : NULL;
	free(iter);
	return true;
}


// ——————————————————————— SCAN ———————————————————————

void __PREPRO__interpret_if(char raw_code[], INDEX_TYPE* index, DEFINITION** head, 
int if_value, char line[], bool writeable)
{
	bool true_satisfied = __PREPRO__if_evaluates_to_true(line, head, if_value);
	bool write_over = !true_satisfied || !writeable;
	while(raw_code[*index])
	{
		if(!write_over && raw_code[*index] == '"') __PREPRO__skip_string_literal(raw_code, index);  

		else if(!write_over && raw_code[*index] && raw_code[(*index)+1] && raw_code[*index] == '/' 
		&& (raw_code[(*index)+1] == '*' || raw_code[(*index)+1] == '/'))
			 __PREPRO__skip_comment(raw_code, index);

		// additional preprocessor info
		else if(raw_code[*index] == '#')
		{
			line = __PREPRO__copy_preprocessor_line(raw_code, index);
			if_value = __PREPRO__is_if_statement(line);
			if(if_value)
			{
				if(if_value == FI) return free(line);

				if(!true_satisfied)  // check if ignoring code
					write_over = !__PREPRO__if_evaluates_to_true(line, head, if_value) || !writeable;
				if(if_value <= IF) __PREPRO__interpret_if(raw_code, index, head, if_value, line, write_over);
			}
			else if(strstr(line, "#DEFINE")) __PREPRO__definition_define(line, head);
			else if(strstr(line, "#UNDEF")) __PREPRO__undefine_define(line, head);
			else
			{
				// to do
			}
			free(line);
		}
		if(write_over && raw_code[*index] && raw_code[*index] != '\n') raw_code[(*index)++] = '#';
		else if(raw_code[*index]) (*index)++;
	}
	printf("Unfinished preprocessor statement\n");
	exit(BAD_PREPRO_DEPTH);
}


DEFINITION* __PREPRO__scan_for_instruction(char raw_code[])
{
	DEFINITION* head = NULL;

	INDEX_TYPE index = 0;
	while(raw_code[index])
	{
		if(raw_code[index] == '"') __PREPRO__skip_string_literal(raw_code, &index);

		else if(raw_code[index] && raw_code[index+1] && raw_code[index] == '/' 
		&& (raw_code[index+1] == '*' || raw_code[index+1] == '/'))
			 __PREPRO__skip_comment(raw_code, &index);

		// additional preprocessor info
		else if(raw_code[index] == '#')
		{
			char* line = __PREPRO__copy_preprocessor_line(raw_code, &index);
			int if_value = __PREPRO__is_if_statement(line);  // check if if statement
			if(if_value && if_value <= IF) __PREPRO__interpret_if(raw_code, &index, &head, if_value, line, true);
			else if(if_value)  // elif, else, or fi
			{
				// throw error
			}
			else if(strstr(line, "#DEFINE")) __PREPRO__definition_define(line, &head);
			else if(strstr(line, "#UNDEF")) __PREPRO__undefine_define(line, &head);
			else
			{
				// to do
			}
			free(line);
		}
		index++;
	}
	return head;
}


// ————————————————————— SKIP SECTION —————————————————————

// read over a comment and update its calling index
// takes code, location of code index & comment character count.
// determine what comment type.  iterate over characters or until EOF; set indexes
// write index of file reader & number of comment characters to locations
void __PREPRO__skip_comment(char code[], INDEX_TYPE* index_address)
{
	INDEX_TYPE index = *index_address;

	index++;
	if(code[index] == '/')
	{
		while(code[index+1] && code[index+1] != '\n') index++;
	}
	// block comment
	else
	{
		// pass over comment
		while(code[index+1] && (code[index] != '*' || code[index+1] != '/')) index++;

		// skip possible last char of comment but so we don't skip over null terminator
		if(code[index]) index++;
	}
	*index_address = index+1;
}


// read over a comment and update its calling index
// takes code, location of code index & comment character count.
// determine what comment type.  iterate over characters or until EOF; set indexes
// write index of file reader & number of comment characters to locations
void __PREPRO__skip_comment_and_record_length(char code[], INDEX_TYPE* index_address,
INDEX_TYPE* comment_characters)
{
	INDEX_TYPE index = *index_address;
	INDEX_TYPE comment = *comment_characters;

	index++;
	comment++;
	if(code[index] == '/')
	{
		while(code[index+1] && code[index+1] != '\n')  // pass over comment
		{
			index++;
			comment++;
		}
	}
	// block comment
	else
	{
		// pass over comment
		while(code[index+1] && (code[index] != '*' || code[index+1] != '/'))
		{
			index++;
			comment++;
		}
		if(code[index])  // skip possible last char of comment but so we don't skip over null terminator
		{
			index++;
			comment++;
		}
	}
	*index_address = index;
	*comment_characters = comment;
}


// skip over string literal in file
// takes the code & index that string starts at
// iterates over string, switching escape character flag.  If no flag and end quote reached, stop iterating
// writes current index to location
void __PREPRO__skip_string_literal(char string[], INDEX_TYPE* index_address)
{
	INDEX_TYPE index = (*index_address)+1;

	bool preceding_escape_character = false;
	while(string[index] && (string[index] != '"' || preceding_escape_character))
	{
		if(string[index++] == '\\') preceding_escape_character = !preceding_escape_character;
		else preceding_escape_character = false;
	}

	if(!string[index])
	{
		fprintf(stderr, "Bad string literal\n");
		exit(BAD_STRING_LITERAL_FORMAT);
	}

	*index_address = index+1;
}


// —————————————————————— UTILITY ———————————————————————

char* __PREPRO__copy_preprocessor_line(char code[], INDEX_TYPE* index)
{
	INDEX_TYPE line_stop = *index;
	while(code[line_stop] && code[line_stop] != '\n') line_stop++;
	INDEX_TYPE line_length = line_stop - *index;


	char* copy = malloc(line_length+1);
	strncpy(copy, code + *index, line_length);
	copy[line_length] = 0;  // because this can be faster than calloc
	for(; *index < line_stop; (*index)++) code[*index] = '#';  // prepare line to be ignored
	(*index)++;

	return copy;
}


void print_definitions(DEFINITION* head)
{
	while(head)
	{
		printf("%s %s %u\n", head->key, head->value, head->count);
		head = head->next;
	}
}

void print_instances(INSTANCE* head)
{
	while(head)
	{
		printf("%lu %lu\n", head->start, head->stop);	
		head = head->next;
	}
}






char* __PREPRO__preprocess_file(char file_name[])
{
	INDEX_TYPE comment_characters = 0;
	INDEX_TYPE definition_characters = 0;

	char* raw_code = __PREPRO__read_file_in(file_name);
	DEFINITION* definitions = __PREPRO__scan_for_instruction(raw_code);
	// __PREPRO__find_preprocessor_values(raw_code);
	printf("%s\n", raw_code);

	// printf("Finding instances\n");
	// INSTANCE* instances = 	__PREPRO__find_instances_of_definition(raw_code, definitions, 
	// 									&comment_characters, &definition_characters);

	// INDEX_TYPE raw_code_length = strlen(raw_code);
	// INDEX_TYPE code_length =	__PREPRO__finished_code_string_size(comment_characters, definitions,
	// 										definition_characters, raw_code_length);
	// char* processed_code = malloc(code_length);
	// __PREPRO__clear_comments_and_insert_INSTANCEs(processed_code, raw_code, instances, 
	// 		raw_code_length);

	// printf("%s\n", processed_code);
	printf("DEFINITION:\n");
	print_definitions(definitions);
	// free(raw_code);
	free(definitions);
	// free(instances);

	return raw_code;
}

#endif