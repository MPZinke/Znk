
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


#include "FileData.h"


// DESCR: Copies the file data from one struct to another.
// PARAMS: Takes the destination struct pointer, the source struct pointer.
// DETAILS:
void copy_file_data(FILE_DATA* destination, FILE_DATA* source)
{

}


// DESCR: Deletes the FILE_DATA struct and attributes.
// PARAMS: Takes the pointer to the FILE_DATA struct.
// DETAILS: Deletes all the malloced data.
void delete_file_data(void* file_data)
{
	FILE_DATA* file_data_pointer = (FILE_DATA*)file_data;
	free(file_data_pointer->filename);
	free(file_data_pointer->text);
	free(file_data_pointer);
}


// DESCR: Creates a new FILE_DATA struct with values.
// PARAMS: Takes the pointer to the filename string, the content length, the pointer to the content string.
// DETAILS: Mallocs a FILE_DATA struct & assigns values to it.
FILE_DATA* new_file_data(char* filename, uint64_t length, char* text)
{
	FILE_DATA* new_data = (FILE_DATA*)malloc(sizeof(FILE_DATA));
	new_data->filename = filename;
	new_data->length = length;
	new_data->text = text;

	return new_data;
}


char* get_file_contents(FILE* file);
bool open_file_data(char filename[], FILE_DATA* file_data);
void print_file_data(FILE_DATA* file_data);


