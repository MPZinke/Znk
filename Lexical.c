
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


#include <stdio.h>
#include <stdlib.h>


enum
{
	INT_LITERAL,
	DOUBLE_LITERAL,

	// ———— KEY WORDS
	// ——— KEY WORDS::INTEGER
	SMALL_KEYWORD,
	SHORT_KEYWORD,
	INT_KEYWORD,
	LONG_KEYWORD,
	LARGE_KEYWORD,
	// ———— KEY WORDS::FLOATING POINT
	DOUBLE_KEYWORD,
	// ———— BRANCHING ————
	FOR_KEYWORD,
	DO_KEYWORD,
	WHILE_KEYWORD,
	IF_KEYWORD,
	ELIF_KEYWORD,
	ELSE_KEYWORD

	// ———— OPERATORS ————



}


typedef struct Token
{
	uint32_t type;
	uint32_t line;
	uint32_t column;
	uint32_t length;
	char* string;
} Token;


typedef struct Node
{
	Token token;
	struct Node* next;
} Node;


typedef struct TokenStream
{
	Node* head;
	uint32_t length;
} TokenStream;


// ———————————————————————————————————————————— TOKEN TYPES DETERMINERS ————————————————————————————————————————————— //


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



int main(int argc, char* argv[])
{
	FILE* file = validate_and_open_znk_file(argv[1]);
	
	return 0;
}