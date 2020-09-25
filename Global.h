

#ifndef _GLOBAL_
#define _GLOBAL_

#define INDEX_TYPE unsigned long  // type determines max number of character allowed to be evaluated
#define TOKEN_COUNT_TYPE unsigned int
#define MAX_DEFINITION_BUFFER 1024


// error codes
#define BAD_ARGS 1
#define BAD_FILE_OPEN 2
#define BAD_COMMENT_FORMAT 3
#define BAD_STRING_FORMAT 4
#define BAD_STRING_LITERAL_FORMAT 5
#define REPLACE_SYNTAX 6
#define DEFINE_NOT_FOUND 7
#define BAD_MULTIPLE_DEFINITION 8
#define BAD_PREPRO_DEPTH 9
#define BAD_UNKOWN_PREPRO 10
#define BAD_UNDEFINE_NOT_FOUND 11
#define ELSE_OUT_OF_ORDER 12


char* __GLOBAL__copy_to_new_string(char original[])
{
	char* copy = malloc(strlen(original) + 1);
	strcpy(copy, original);
	return copy;
}


void __GLOBAL__throw_error(char* code, INDEX_TYPE index, char message[], int error_code)
{
	INDEX_TYPE line_number = 1;
	INDEX_TYPE x = 0;
	while(code[x] && x < index) if(code[x++] == '\n') line_number++;

	fprintf(stderr, "%s on line %lu\n", message, line_number);
	exit(error_code);
}


#endif