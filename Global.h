
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



#ifndef _GLOBAL_
#define _GLOBAL_


typedef struct TinyToken
{
	uint16_t type;
	uint64_t line;
	uint64_t column;
	uint64_t length;
} TinyToken;


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


#endif
