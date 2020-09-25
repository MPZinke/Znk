
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

enum PREPRO_TYPE
{
	CODE,
	DEFINE,
	IF,
	IFN,
	ELIF,
	ELIFN,
	FI,
	IMPORT,
	INCLUDE,
	TEMPLATE
};


bool SMART_ARRAY = true;  // pass size of array as hidden arguments


// ——————————————————————— LL ————————————————————————

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


void __PREPRO__add_new_INSTANCE_node(INSTANCE**, DEFINITION*, INDEX_TYPE, INDEX_TYPE);
void __PREPRO__skip_comment(char[], INDEX_TYPE*);
void __PREPRO__process_if(char[]);


// —————————————————————— UTILITY ———————————————————————

char* __PREPRO__copy_line(char line_start[])
{
	INDEX_TYPE line_length = 0;
	while(line_start[line_length] && line_start[line_length] != '\n') line_length++;

	char* copy = malloc(line_length+1);
	strncpy(copy, line_start, line_length);

	return copy;
}


// copy raw code to a new char array removing comments and prepro defines; replace definitions with values.
// takes locations of new code, old code, index for old code, index for new code; index to stop copying.
// iterates old code from old code location to new code location, copying * chars except comments & defines.
// writes the final indexes to their locations.
void __PREPRO__copy_string(char code[], char raw_code[], INDEX_TYPE* index_address, 
INDEX_TYPE* copy_index_address, INDEX_TYPE position)
{
	INDEX_TYPE sink, index = *index_address, copy_index = *copy_index_address;  // makes below prettier

	bool in_string = false;
	bool escape_character = false;

	while(index < position)
	{
		// string literal identification
		if(!in_string && raw_code[index] == '"') in_string = true;
		else if(in_string)
		{
			if(raw_code[index] == '\\') escape_character = !escape_character;
			else if(escape_character) escape_character = false;  // not escape character && does not end string
			else if(raw_code[index] == '"') in_string = false;
		}

		// pass over comment and count number of characters used in it
		while(!in_string && raw_code[index] && raw_code[index] == '#') index++;
		if(!in_string && raw_code[index+1] && raw_code[index] == '/' 
		&& (raw_code[index+1] == '*' || raw_code[index+1] == '/'))
		{
			 __PREPRO__skip_comment(raw_code, &index);
			 index++;
			 continue;  // skip copying last character
		}
		code[copy_index++] = raw_code[index++];
	}

	*index_address = index;
	*copy_index_address = copy_index;
}


// calculate the size of the processed code string.
// takes raw code, number of comment character, definition linked list, number of define characters.
// goes through defintion list and calculates the count of definition characters & instances characters.
// get string length of original code, add replacement length & null char; subtract defintions & comments.
// return sum of values.
INDEX_TYPE __PREPRO__finished_code_string_size(INDEX_TYPE comment, 
DEFINITION* definitions, INDEX_TYPE definition_characters, INDEX_TYPE raw_code_length)
{
	INDEX_TYPE instance_characters = 0;  // char count of instances in code
	INDEX_TYPE replacement_characters = 0;  // number of characters for replacement string
	// sum char counts for defintion and instance characters
	while(definitions)
	{
		instance_characters += strlen(definitions->key) * definitions->count;
		replacement_characters += strlen(definitions->value) * definitions->count;
		definitions = definitions->next;
	}

	INDEX_TYPE add_length = raw_code_length+ replacement_characters + 1;
	INDEX_TYPE remove_characters = instance_characters + comment - definition_characters;
	INDEX_TYPE total = add_length - remove_characters;  // actual size
	return total;
}


bool __PREPRO__match_DEFINITION(char* if_clause, DEFINITION** head, int type)
{
	int offset;
	if(type == IF) offset = 3;
	else if(type == IFN) offset = 4;
	else if(type == ELIF) offset = 5;
	else if(type == ELIFN) offset = 6;
	char* definition = strtok(if_clause + offset, " \t\n");

	DEFINITION* definitions = *head;
	while(definitions)
	{
		if(!strcmp(definition, definitions->key)) return true;
		definitions = definitions->next;
	}
	return false;
}


// possible instance found: determine what definition it is, increment its value & add to instance list.
// takes location of raw code, definition list, instance list, location of index.
// determine what definition it is, increment its value & add to instance list recording beginning & end in code.
// writes final location to its index location.
bool __PREPRO__match_INSTANCE(char code[], DEFINITION* definitions, INSTANCE** head,
INDEX_TYPE* index_address)
{
	for(DEFINITION* def = definitions; def; def = def->next)
	{
		INDEX_TYPE start = *index_address;  // opening `
		INDEX_TYPE stop = start + 1;  // (soon to be) closing `
		INDEX_TYPE x = 0;
		while(code[stop] && def->key[x] && code[stop] == def->key[x])
		{
			stop++;
			x++;
		}
		if(!code[stop])
		{
			fprintf(stderr, "Preprocessor string syntax is not valid\n");
			exit(BAD_DEFINITION_REPLACE_SYNTAX);
		}
		if(!def->key[x] && code[stop] == '`')  // match
		{
			def->count++;
			__PREPRO__add_new_INSTANCE_node(head, def, start, stop);
			*index_address = stop+1;
			return true;
		}
	}
	fprintf(stderr, "Preprocessor string not found\n");
	exit(BAD_DEFINITION_KEY_NOT_FOUND);
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
	*index_address = index;
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
void __PREPRO__skip_string_literal(char string[], INDEX_TYPE* read_index)
{
	INDEX_TYPE index = *read_index+1;

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

	*read_index = index;
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


// ————————————————————— DEFINITIONS —————————————————————

void __PREPRO__definition_define(char buffer[], DEFINITION** head)
{
	//TODO: validate format

	buffer = strtok(buffer+7, " \t");
	char* key = __GLOBAL__copy_to_new_string(buffer);
	buffer = strtok(NULL, " \f\n\r\t\v");
	char* value = __GLOBAL__copy_to_new_string(buffer);

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


// ———————————————————— CODE SCANNING ————————————————————

// scan code for preprocessor commands
// takes code string and position to stop at
// iterate code looking for '#' that are not in a string; 
void __PREPRO__find_preprocessor_values(char code[], INDEX_TYPE* index,
DEFINITION** head, int block_depth, bool write_over)
{
	printf("FINDER\n");
	while(code[*index])
	{
		printf("%c", code[*index]);
		// ignore string literals
		if(code[*index] == '"') __PREPRO__skip_string_literal(code, index);	

		// pass over comment and count number of characters used in it
		else if(code[*index] && code[(*index)+1] && code[*index] == '/' 
		&& (code[(*index)+1] == '*' || code[(*index)+1] == '/'))
			 __PREPRO__skip_comment(code, index);

		// possible definition found
		else if(code[*index] == '#')
		{
			// get define line
			char* buffer = __PREPRO__copy_line(code + (*index));
			printf("BUFFER: %s\n", buffer);
			while(code[*index] && code[*index] != '\n') code[(*index)++] = '#';  // prepare line to be removed

			if(strstr(buffer, "#ifn"))
			{
				printf("IFN\n");
				write_over = __PREPRO__match_DEFINITION(buffer, head, IFN);
				__PREPRO__find_preprocessor_values(code, index, head, block_depth+1, write_over);
			}
			else if(strstr(buffer, "#if"))
			{
				printf("IF\n");
				write_over = !__PREPRO__match_DEFINITION(buffer, head, IF);
				__PREPRO__find_preprocessor_values(code, index, head, block_depth+1, write_over);
			}
			else if(strstr(buffer, "#elifn"))
			{
				printf("ELIF\n");
				write_over = __PREPRO__match_DEFINITION(buffer, head, ELIFN);
			}
			else if(strstr(buffer, "#elif"))
			{
				printf("ELIFN\n");
				write_over = !__PREPRO__match_DEFINITION(buffer, head, ELIF);
			}
			else if(strstr(buffer, "#fi"))
			{
				while(code[*index] && code[*index] != '\n') code[(*index)++] = '#';
				return;
			}

			else if( strstr(buffer, "#define")) __PREPRO__definition_define(buffer, head);
			else if(strstr(buffer, "#undef")) __PREPRO__undefine_define(buffer, head);

			else if(strstr(buffer, "#include"))
			{
				// load and process file & symbol tree
			}
			else if(strstr(buffer, "#import"))
			{
				// load and process global symbols
			}

			else
			{
				fprintf(stderr, "Undefined preprocessor symbol %s", buffer);
				exit(BAD_UNKOWN_PREPRO);
			}

		}
		if(write_over && code[*index]) code[(*index)++] = '#';
		else if(code[*index]) (*index)++;  // in case index is null terminator, leave for while loop to break
	}

	if(block_depth)
	{
		printf("Unfinished preprocessor statement\n");
		exit(BAD_PREPRO_DEPTH);
	}
}


INSTANCE* __PREPRO__find_instances_of_definition(char code[], DEFINITION* definitions, 
INDEX_TYPE* comment_characters, INDEX_TYPE* definition_characters)
{
	INSTANCE* head = NULL;

	bool in_string = false;
	bool escape_character = false;

	// definition instance at beginning of file: cannot happen
	if(code[0] == '`')
	{
		fprintf(stderr, "Preprocessor string syntax is not valid\n");
		exit(BAD_DEFINITION_REPLACE_SYNTAX);
	}

	INDEX_TYPE index = 0;
	while(code[index])
	{
		// string checking
		if(!in_string && code[index] == '"') in_string = true;
		else if(in_string)
		{
			if(code[index] == '\\') escape_character = !escape_character;
			else if(escape_character) escape_character = false;  // not escape character && does not end string
			else if(code[index] == '"') in_string = false;
		}

		// pass over comment and count number of characters used in it
		if(!in_string && code[index+1] && code[index] == '/' && (code[index+1] == '*' || code[index+1] == '/'))
			 __PREPRO__skip_comment_and_record_length(code, &index, comment_characters);

		// define instance found: add to list
		else if(code[index] == '`' && !escape_character)
			__PREPRO__match_INSTANCE(code, definitions, &head, &index);

		// pass over comment and count number of characters used in it
		while(!in_string && code[index] && code[index] == '#')
		{
			index++;
			(*definition_characters)++;
		}
		index++;
	}
	return head;
}


char* __PREPRO__clear_comments_and_insert_INSTANCEs(char code[], char raw_code[],
INSTANCE* instances, INDEX_TYPE raw_code_length)
{
	__PREPRO__add_new_INSTANCE_node(&instances, NULL, raw_code_length, 0);  // add dummy to end string
	
	INDEX_TYPE index = 0, code_index = 0;
	__PREPRO__copy_string(code, raw_code, &index, &code_index, instances->start);
	while(instances->next)
	{
		// copy value in
		INDEX_TYPE value_size = strlen(instances->definition->value);
		strcpy(code+code_index, instances->definition->value);
		index = instances->stop + 1;
		code_index += value_size;

		__PREPRO__copy_string(code, raw_code, &index, &code_index, instances->next->start);  // copy null
		instances = instances->next;
	}
	code[code_index] = 0;

	return code;
}


void __PREPRO__process_if(char if_start[])
{
	char copy[MAX_DEFINITION_BUFFER];
	strncpy(copy, if_start, MAX_DEFINITION_BUFFER-1);
	char* buffer = strtok(copy, "\n");
	buffer = strtok(buffer+7, " \t");

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
	DEFINITION* definitions;
	INDEX_TYPE index = 0;
	__PREPRO__find_preprocessor_values(raw_code, &index, &definitions, 0, false);
	printf("%s\n", raw_code);

	printf("Finding instances\n");
	INSTANCE* instances = 	__PREPRO__find_instances_of_definition(raw_code, definitions, 
										&comment_characters, &definition_characters);

	INDEX_TYPE raw_code_length = strlen(raw_code);
	INDEX_TYPE code_length =	__PREPRO__finished_code_string_size(comment_characters, definitions,
											definition_characters, raw_code_length);
	char* processed_code = malloc(code_length);
	__PREPRO__clear_comments_and_insert_INSTANCEs(processed_code, raw_code, instances, 
			raw_code_length);

	printf("%s\n", processed_code);

	free(raw_code);
	free(definitions);
	free(instances);

	return processed_code;
}



#endif