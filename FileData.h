
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


#ifndef _FILE_DATA_
#define _FILE_DATA_


typedef struct FILE_DATA
{
	char* filename;
	uint64_t length;
	char* text;
} FILE_DATA;


void copy_file_data(FILE_DATA* destination, FILE_DATA* source);
void delete_file_data(void* file_data);
FILE_DATA* new_file_data();

char* get_file_contents(FILE* file);
bool new_file_data(char filename[], FILE_DATA* file_data);
void print_file_data(FILE_DATA* file_data);
