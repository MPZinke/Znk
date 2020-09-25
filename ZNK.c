
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


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "Global.h"

#include"PreProcessor.h"
#include"LexicalAnalyzer.h"




int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		fprintf(stderr, "No arguments passed\n");
		exit(BAD_ARGS);
	}	

	// preprocessing
	char* extracted_code = __PREPRO__preprocess_file(argv[1]);

	// ———— LEXICAL ANALYSIS ————
	// scan
	Token* tokens = __LEXANAL__tokenize_code(extracted_code);

	// parse
	__LEXANAL__print_tokens(tokens);
	printf("\n");


	return 0;
}