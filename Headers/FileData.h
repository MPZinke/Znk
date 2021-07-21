
/***********************************************************************************************************************
*                                                                                                                      *
*   created by: MPZinke                                                                                                *
*   on 2021.07.21                                                                                                      *
*                                                                                                                      *
*   DESCRIPTION: TEMPLATE                                                                                              *
*   BUGS:                                                                                                              *
*   FUTURE:                                                                                                            *
*                                                                                                                      *
***********************************************************************************************************************/


#ifndef _FILE_DATA_
#define _FILE_DATA_


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct FILE_DATA
{
	char* filename;
	uint64_t length;  // number of characters in the file
	char* text;  // the contents of the file
} FILE_DATA;


void copy_file_data(FILE_DATA* destination, FILE_DATA* source);
void delete_file_data(void* file_data);
FILE_DATA* new_file_data(char* filename, uint64_t length, char* text);

char* get_file_contents(FILE* file);
bool open_file_data(char filename[], FILE_DATA* file_data);
void print_file_data(FILE_DATA* file_data);


#endif
