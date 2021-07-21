
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


#ifndef _LINKED_LIST_
#define _LINKED_LIST_


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct Node
{
	void* value;
	struct Node* next;
} Node;


Node* add_value_to_linked_list(Node** head, void* value);
void delete_linked_list(Node** head, void(*delete_node_value_function)(void*));
void print_linked_list(Node* head, void(*print_function)(void*));


#endif
