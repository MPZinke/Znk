
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


#include "LinkedList.h"


Node* add_value_to_linked_list(Node** head, void* value)
{
	Node* new_node = malloc(sizeof(new_node));
	new_node->next = NULL;
	new_node->value = value;

	if(!*head) *head = new_node;
	else
	{
		Node* iter = *head;
		for(uint64_t x = 0; iter->next && x < UINT64_MAX; x++) iter = iter->next;
		iter->next = new_node;
	}

	return new_node;
}


void delete_linked_list(Node** head, void(*delete_node_value_function)(void*))
{
	Node* iter = *head;
	*head = NULL;

	for(uint64_t x = 0; iter && x < UINT64_MAX; x++)
	{
		Node* temp = iter->next;
		if(iter->value) delete_node_value_function(iter->value);
		free(iter);
		iter = temp;
	}
}


void print_linked_list(Node* head, void(*print_function)(void*))
{
	for(uint64_t x = 0; head && x < UINT64_MAX; x++)
	{
		print_function(head->value);
		head = head->next;
	}
}

