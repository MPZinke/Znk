
/********************************************************************************************************************************
*
*	created by: MPZinke
*	on ..
*
*	DESCRIPTION: TEMPLATE
*	BUGS:
*	FUTURE:
*
********************************************************************************************************************************/

// max number of characters in a file is defined by the INDEX_TYPE C preprocessor definition.
// overlying process of read file, find definitions, find instances, allocate space, copy/substitute/uncomment file
// uses a total time of ~O(2N).


#ifndef _PREPROCESSOR_
#define _PREPROCESSOR_

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"Global.h"


// PREPRO_IFS_ENUM numbers must match corresponding PREPRO_IFS_STR indexes
enum PREPRO_IFS_ENUM 
{
	NOT_IF,  // must be 0
	IFN,  // must come before IF & be odd
	IF,  // must be even
	ELIFN,  // must come before ELIF
	ELIF,  // must be even
	ELSE,
	FI
};

char PREPRO_IFS_STR[][10] = {"#NOT_IF", "#IFN", "#IF", "#ELIFN", "#ELIF", "#ELSE", "#FI"};


bool SMART_ARRAY = true;  // pass size of array as hidden arguments



typedef struct Definition
{
	char* key;  // the definition key: #define KEY
	char* value;  // the value for it: #define key VALUE
	TOKEN_COUNT_TYPE count;  // number of occurences that the key shows up as `KEY`
	struct Definition* previous;
	struct Definition* next;
} Definition;


typedef struct Instance
{
	Definition* definition;  // which which Definition this instance pertains to 
	INDEX_TYPE start;  // starting index of `KEY`
	INDEX_TYPE stop;  // stopping index of `KEY`
	struct Instance* next;
} Instance;


// ———— DEFINITIONS ————
void __PREPRO__definition_define(char[], Definition**);
int __PREPRO__is_if_statement(char[]);
bool __PREPRO__if_evaluates_to_true(char*, Definition*, int);
// ———— FILE ————
char* __PREPRO__read_file_in(char[]);
// ———— INSERT ————
char* __PREPRO__clear_non_code_and_insert_Instances(char[], Definition*, Instance*, INDEX_TYPE);
void __PREPRO__copy_code(char[], char[], INDEX_TYPE*, INDEX_TYPE*, INDEX_TYPE);
// ———— LL ————
void __PREPRO__add_new_Definition_node(Definition**, char*, char*);
void __PREPRO__add_new_Instance_node(Instance**, Definition*, INDEX_TYPE, INDEX_TYPE);
void __PREPRO__free_definitions(Definition*);
void __PREPRO__free_instances(Instance*);
// ———— SCAN ————
void __PREPRO__interpret_if(char[], Definition**,  INDEX_TYPE*, INDEX_TYPE*, Instance**, char[], bool);
Instance* __PREPRO__scan_for_instruction(char[], Definition**, INDEX_TYPE*);
// ———— SKIP SECTION ————
void __PREPRO__skip_comment_but_copy_newlines(char[], char[], INDEX_TYPE*, INDEX_TYPE*);
void __PREPRO__skip_comment_and_count_length(char[], INDEX_TYPE*, INDEX_TYPE*);
// ———— UTILITY ————
char* __PREPRO__copy_preprocessor_line(char[], INDEX_TYPE*);
INDEX_TYPE __PREPRO__finished_code_string_size(INDEX_TYPE, INDEX_TYPE, Definition*);
void __PREPRO__match_Instance(char[], Definition*, Instance**, INDEX_TYPE*);
void __PREPRO__set_string_conditions(char, bool*, bool* );
void __PREPRO__set_write_over_and_if_satisfied(Definition**, bool*, int, char[], bool, bool*);
char* __PREPRO__preprocess_file(char[]);


// ————————————————————— DefinitionS —————————————————————

// create a definition for a found define.
// take char* to the line copy where the define occurs.
// validates line, then splits the line into the key and values, copying them to new char arrays.
// adds them to Definition LL with function __PREPRO__add_new_Definition_node(...).
void __PREPRO__definition_define(char line[], Definition** head)
{
	//TODO: validate format
	line = strtok(line+7, " \t");  // skip "#DEFINE"
	// if(line[0] == '#') __GLOBAL__throw_error_without_line("Bad");  //TODO
	char* key = __GLOBAL__copy_to_new_string(line);
	line = strtok(NULL, " \f\n\r\t\v");
	char* value = __GLOBAL__copy_to_new_string(line);

	__PREPRO__add_new_Definition_node(head, key, value);
}


// checks if the preprocessor instruction is a if #IF(N), #ELIF(N), #ELSE, #FI.
// takes char* to instruction line.
// iterates list of listed prepro if statement tags PREPRO_IFS_STR.
// return instance number if match ( > 0), else NULL.
int __PREPRO__is_if_statement(char instruction[])
{
	for(int x = 1; x < 7; x++) if(strstr(instruction, PREPRO_IFS_STR[x])) return x;
	return NOT_IF;
}


// checks if the if statement is evaluates to true (#IFN false == true, #IFN true == false, #IF true == true, etc).
// takes char* to if clause string, definition head, type of define evaluated.
// got through definitions until value found.
// return truthiness if found and #if type.
bool __PREPRO__if_evaluates_to_true(char* if_clause, Definition* head, int type)
{
	if(type == ELSE) return true;  // default to true; knowing if true statement already found

	int offset = 2 + type;
	char* copy = __GLOBAL__copy_to_new_string(if_clause);
	char* definition = strtok(copy + offset, " \t\n");

	while(head)
	{
		if(!strcmp(definition, head->key)) return type % 2 == 0;  // flip for N values
		head = head->next;
	}
	return type % 2 != 0;  // flip for N values
}


// ——————————————————————— FILE ———————————————————————

// read from file and add to character array.
// takes in a string for the filename.
// opens and reads file size; allocate memory & copies contents.
// returns pointer to copied file.
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

	// definition instance at beginning of file: cannot happen
	if(current == '`')
		__GLOBAL__throw_error("", 1, "File cannot start with definiton instance", REPLACE_SYNTAX);

	while(!feof(file))
	{
		extracted_file[index++] = current;
		current = fgetc(file);
	}

	return extracted_file;
}


// —————————————————————— INSERT ———————————————————————

// create new string containing code with definitions instances spliced in.
// takes location of code, copy of definition head, copy of instance head, # of characters to ignore
// allocates a new char array for size of code, additions and reductions; copies code up to instance then 
// instance value.  repeats while actual nodes, then copies up to dummy node at end and null terminates.
// returns char* to new code.
char* __PREPRO__clear_non_code_and_insert_Instances(char raw_code[], Definition* definitions, 
Instance* instances, INDEX_TYPE ignorable_chars)
{
	INDEX_TYPE raw_length = strlen(raw_code);
	INDEX_TYPE processed_code_length =	__PREPRO__finished_code_string_size(raw_length, 
														ignorable_chars, definitions);
	char* code = malloc(processed_code_length);

	__PREPRO__add_new_Instance_node(&instances, NULL, raw_length, 0);  // add dummy to end string
	
	INDEX_TYPE index = 0, code_index = 0;
	__PREPRO__copy_code(code, raw_code, &code_index, &index, instances->start);
	while(instances->next)
	{
		// copy value in
		strcpy(code+code_index, instances->definition->value);
		index = instances->stop + 1;
		code_index += instances->stop - instances->start - 1;

		__PREPRO__copy_code(code, raw_code, &code_index, &index, instances->next->start);  // copy null
		instances = instances->next;
	}
	code[code_index] = 0;

	return code;
}


// copy raw code to a new char array removing comments and prepro defines; replace definitions with values.
// takes locations of new code, old code, index for old code, index for new code; index to stop copying.
// iterates old code from old code location to new code location, copying * chars except comments & defines.
// writes the final indexes to their locations.
void __PREPRO__copy_code(char code[], char raw_code[], INDEX_TYPE* copy_index_address,
INDEX_TYPE* index_address, INDEX_TYPE position)
{
	INDEX_TYPE sink, index = *index_address, copy_index = *copy_index_address;  // makes below prettier

	bool in_string = false, escape_character = false;
	while(index < position && raw_code[index])
	{
		char current_char = raw_code[index];
		__PREPRO__set_string_conditions(current_char, &in_string, &escape_character);  // string literal check

		if(!in_string && current_char == '#') index++;  // skip preprocessor symbols

		// if not in comment: copy character; else: only copy \n from comments
		else if(in_string || current_char != '/' || (raw_code[index+1] != '*' && raw_code[index+1] != '/'))
			code[copy_index++] = raw_code[index++];
		else __PREPRO__skip_comment_but_copy_newlines(code, raw_code, &copy_index, &index);
	}

	*index_address = index;  // update indexes
	*copy_index_address = copy_index;
}


// ——————————————————————— LL ————————————————————————

// add new Definition to linked list.
// takes pointer to head (Definition pointer), string key, string value.
// creates a Definition instance, adds values to instance & sets it at end of list.
void __PREPRO__add_new_Definition_node(Definition** head, char* key, char* value)
{
	Definition* new_value = malloc(sizeof(Definition));
	*new_value = (Definition){key, value, 0, 0, 0};

	if(!*head) *head = new_value;  // no previous nodes in list
	else
	{
		Definition* iter = *head;
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


// add new Instance to linked list.
// takes pointer to head (Instance pointer), Definition, start location & stop location.
// creates a Instance instance, adds values to instance & sets it at end of list.
void __PREPRO__add_new_Instance_node(Instance** head, Definition* definition, 
INDEX_TYPE start, INDEX_TYPE stop)
{
	Instance* new_value = malloc(sizeof(Instance));
	*new_value = (Instance){definition, start, stop, 0};

	if(!*head) *head = new_value;  // no previous nodes in list
	else
	{
		Instance* iter = *head;
		while(iter->next) iter = iter->next;
		iter->next = new_value;
	}
}


// frees memory of definitions
// iterates LL and frees malloced parts
void __PREPRO__free_definitions(Definition* head)
{
	while(head)
	{
		Definition* next = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = next;
	}
}


// frees memory of definition instances
// iterates LL and frees malloced parts
void __PREPRO__free_instances(Instance* head)
{
	while(head)
	{
		Instance* next = head->next;
		free(head);
		head = next;
	}
}


// ——————————————————————— SCAN ———————————————————————

// recursively negotiate if statements & levels.
// takes location of code, pointer to definition head, location of index, location of count of chars to ignore,
// point to instance head, the if declaration that triggered this, whether this block is writeable.
// iteratates code from current index, picking out instances, comments, & prepro symbols.  if #IF recurses to 
// next block level.  if #FI (end block) returns to previous level.  records number of characters that will be filtered
// out later in ignore_chars. after processing, prepro symbols are covered by # to be removed later.
void __PREPRO__interpret_if(char code[], Definition** head,  INDEX_TYPE* index,
INDEX_TYPE* ignorable_chars, Instance** instances, char line[], bool writeable)
{
	int if_value = __PREPRO__is_if_statement(line);  // check if #IF statement
	bool if_satisfied = false, write_over;
	__PREPRO__set_write_over_and_if_satisfied(head, &if_satisfied, if_value, line, writeable, &write_over);

	bool in_string = false, escape_character = false;
	while(code[*index])
	{
		char current_char = code[*index];
		if(!write_over) __PREPRO__set_string_conditions(current_char, &in_string, &escape_character);

		if(!in_string && current_char == '/' && (code[(*index)+1] == '*' || code[(*index)+1] == '/'))
			__PREPRO__skip_comment_and_count_length(code, index, ignorable_chars);

		// define instance found: add to list
		else if(current_char == '`' && !escape_character)
			__PREPRO__match_Instance(code, *head, instances, index);

		// additional preprocessor info
		else if(!in_string && current_char == '#')
		{
			line = __PREPRO__copy_preprocessor_line(code, index);
			if_value = __PREPRO__is_if_statement(line);
			if(if_value)
			{
				if(if_value == FI) return free(line);

				if(if_value <= IF)  // nested #IF(N)
					__PREPRO__interpret_if(code, head, index, ignorable_chars, instances, line, !write_over);
				else	__PREPRO__set_write_over_and_if_satisfied(head, &if_satisfied, if_value, line, writeable, 
								&write_over);
			}
			else if(!write_over && strstr(line, "#DEFINE")) __PREPRO__definition_define(line, head);
			else
			{
				// to do
			}
			free(line);
		}

		if(write_over && code[*index] && code[*index] != '\n') code[(*index)++] = '#';
		else if(code[*index]) (*index)++;
	}
	__GLOBAL__throw_error(code, *index, "Unfinished preprocessor statement", BAD_PREPRO_DEPTH);
}


// read code string and determine parts, adding to definitions and symbols.
// takes location of code, pointer to definition head, location of count of characters to ignore.
// iteratates code from current index, picking out instances, comments, & prepro symbols.  if #IF recurses to 
// next block level.  records number of characters that will be filtered out later in ignore_chars. after processing,
// prepro symbols are covered by # to be removed later.
// return instances of definitions and replacements.
Instance* __PREPRO__scan_for_instruction(char code[], Definition** head, INDEX_TYPE* ignorable_chars)
{
	Instance* instances = NULL;

	bool in_string = false;
	bool escape_character = false;

	INDEX_TYPE index = 0;
	while(code[index])
	{
		char current_char = code[index];
		__PREPRO__set_string_conditions(current_char, &in_string, &escape_character);

		if(!in_string && current_char == '/' && (code[index+1] == '*' || code[index+1] == '/'))
			 __PREPRO__skip_comment_and_count_length(code, &index, ignorable_chars);

		// define instance found: add to list
		else if(code[index] == '`' && !escape_character)
			__PREPRO__match_Instance(code, *head, &instances, &index);

		// additional preprocessor info
		else if(!in_string && current_char == '#')
		{
			char* line = __PREPRO__copy_preprocessor_line(code, &index);
			int if_value = __PREPRO__is_if_statement(line);  // check if #IF statement
			if(strstr(line, "#DEFINE")) __PREPRO__definition_define(line, head);
			else if(if_value && if_value <= IF)
				__PREPRO__interpret_if(code, head, &index, ignorable_chars, &instances, line, true);
			else if(if_value)  // elif, else, or fi
				__GLOBAL__throw_error(code, index, "No preceeding #IF found", ELSE_OUT_OF_ORDER);
			else
			{
				// to do
			}
			free(line);
		}

		if(code[index]) index++;
	}
	return instances;
}


// ————————————————————— SKIP SECTION —————————————————————

// copy new lines to new code but skips rest of comment.
// takes location of copy code, location of raw code, location of copy index, location of raw index (to write back).
// determines comment type and iterates through comment until end found, copying new lines as it goes.
// writes indexes to locations.
void __PREPRO__skip_comment_but_copy_newlines(char copy_code[], char raw_code[], 
INDEX_TYPE* copy_index_address, INDEX_TYPE* index_address)
{
	INDEX_TYPE index = *index_address, copy_index = *copy_index_address;

	index += 2;  // move index past comment signifier
	if(raw_code[index-1] == '/')
	{
		while(raw_code[index] && raw_code[index] != '\n') index++;
	}
	// block comment
	else
	{
		while(raw_code[index] && (raw_code[index] != '*' || raw_code[index+1] != '/'))
			if(raw_code[index++] == '\n') copy_code[copy_index++] = raw_code[index-1];
		// skip possible last comment char but check we don't skip over null char
		if(raw_code[index] && raw_code[index+1]) index += 2;
		else if(raw_code[index]) index++;

	}
	*index_address = index;
	*copy_index_address = copy_index;
}


// read over a comment and update its calling index
// takes code, location of code index & comment character count.
// determines comment type. iterate over characters or until EOF
// write index of file reader & number of comment characters to locations
void __PREPRO__skip_comment_and_count_length(char code[], INDEX_TYPE* index_address,
INDEX_TYPE* ignorable_chars)
{
	INDEX_TYPE index = *index_address;
	INDEX_TYPE new_lines = 0;

	index += 2;  // move index past comment signifier
	if(code[index-1] == '/')
	{
		while(code[index] && code[index] != '\n') index++;
	}
	// block comment
	else
	{
		// pass over comment
		while(code[index] && (code[index] != '*' || code[index+1] != '/')) if(code[index++] == '\n') new_lines++;
		// skip possible last comment char but check we don't skip over null char
		if(code[index] && code[index+1]) index += 2;
		else if(code[index]) index++;
	}
	*ignorable_chars += index - *index_address - new_lines;
	*index_address = index;
}


// —————————————————————— UTILITY ———————————————————————

// makes a copy of the preprocessor line & writes over original segment with #.
// takes location of code, location of index
// reads line, copies to new string, then replaces previous section with # to be later ignored.
// returns copy of line.
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


// calculate the size of the processed code string.
// takes raw code size, number of ignorable characters, definition linked list.
// goes through defintion list and calculates the count of definition characters & instances characters.
// add original code length, replacement length & null char; subtract defintions & (comments - \n).
// return sum of values.
INDEX_TYPE __PREPRO__finished_code_string_size(INDEX_TYPE raw_code_length,
INDEX_TYPE ignorable_chars, Definition* definitions)
{
	INDEX_TYPE instance_characters = 0;  // char count of `instances` in code
	INDEX_TYPE replacement_characters = 0;  // number of characters for replacement string
	// sum char counts for defintion and instance characters
	while(definitions)
	{
		instance_characters += strlen(definitions->key) * definitions->count;
		replacement_characters += strlen(definitions->value) * definitions->count;
		definitions = definitions->next;
	}

	INDEX_TYPE add_length = raw_code_length + replacement_characters + 1;
	INDEX_TYPE remove_characters = instance_characters + ignorable_chars;
	INDEX_TYPE total = add_length - remove_characters;  // actual size
	return total;
}


// possible instance found: determine what definition it is, increment its value & add to instance list.
// takes location of raw code, definition list, instance list, location of index.
// determine what definition it is, increment its value & add to instance list recording beginning & end in code.
// writes final location to its index location.
void __PREPRO__match_Instance(char code[], Definition* definitions, Instance** instances,
INDEX_TYPE* index_address)
{
	for(Definition* def = definitions; def; def = def->next)
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
			__GLOBAL__throw_error(code, *index_address, "Invalid preprocessor syntax", REPLACE_SYNTAX);

		if(!def->key[x] && code[stop] == '`')  // match
		{
			def->count++;
			__PREPRO__add_new_Instance_node(instances, def, start, stop);
			*index_address = stop;
			return;
		}
	}

	__GLOBAL__throw_error(code, *index_address, "Define not found", DEFINE_NOT_FOUND);
}


// set variables to indicate whether currently in string
// takes the current character, location of bool for whether in string, location of bool of activated escape char.
// logic.
// writes whether in string or an escape character activated.
void __PREPRO__set_string_conditions(char current_char, bool* in_string, bool* escape_character)
{
	// string checking
	if(!*in_string && current_char == '"') *in_string = true;
	else if(*in_string)
	{
		if(current_char == '\\') *escape_character = !*escape_character;
		else if(*escape_character) *escape_character = false;  // not escape character && does not end string
		else if(current_char == '"') *in_string = false;
	}
}


// set variables to indicate if a prepro block will be written over and if truthiness is satisfied.
// takes definition head, location of bool for it if is satisfied, the if value, copy of line, if it is writeable, location of
// whether to write over block.
// calls function __PREPRO__if_evaluates_to_true(...) to determine if #IF is true.
// writes write_over & if_satisfied.
void __PREPRO__set_write_over_and_if_satisfied(Definition** head, bool* if_satisfied, int if_value, char line[],
bool writeable, bool *write_over)
{
	bool current_if_true = __PREPRO__if_evaluates_to_true(line, *head, if_value);
	*write_over = !current_if_true || !writeable || *if_satisfied;
	*if_satisfied = *if_satisfied || current_if_true;
}



// void __TESTING__PREPRO__print_definitions(Definition* head)
// {
// 	while(head)
// 	{
// 		printf("%s %s %u\n", head->key, head->value, head->count);
// 		head = head->next;
// 	}
// }


// void __TESTING__PREPRO__print_instances(Instance* head)
// {
// 	while(head)
// 	{
// 		printf("%lu %lu\n", head->start, head->stop);	
// 		head = head->next;
// 	}
// }


// call preprocessor functions to create a code string for lexical analysis based on file name.
// takes a file name as passed by command line argument
// opens & reads file. finds definitions and prepro symbols. removes prepro symbols and comments & leaves
// new lines to maintain file-code line consistency.
// return preprocessed file.
char* __PREPRO__preprocess_file(char file_name[])
{
	char* raw_code = __PREPRO__read_file_in(file_name);

	INDEX_TYPE ignorable_chars = 0;
	Definition* definitions = NULL;
	Instance* instances = __PREPRO__scan_for_instruction(raw_code, &definitions, &ignorable_chars);

	// write code 
	char* code =	__PREPRO__clear_non_code_and_insert_Instances(raw_code, definitions, instances, 
											ignorable_chars);

	free(raw_code);
	__PREPRO__free_definitions(definitions);
	__PREPRO__free_instances(instances);

	return code;
}

#endif