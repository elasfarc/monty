#include "memory-allocation.h"
#include "monty.h"
#include <stdio.h>

/**
 * push_allocated_memory - Pushes allocated memory onto the memory List.
 * @memory_alloc: memoryAlloc Pointer to the allocated memory.
 *
 * Return: The ID of the pushed memory allocation, or 0 on error.
 */
long int push_allocated_memory(AllocatedMemory *memory_alloc)
{
	AllocatedMemoryList *list = get_alloc_mem_list();
	AllocatedMemoryNode *node = malloc(sizeof(AllocatedMemoryNode));

	node->id = (long int)node;
	if (!node)
		return (0);
	node->data = memory_alloc;
	node->next = NULL;
	node->prev = list->tail ? list->tail : NULL;
	list->tail ? list->tail->next = node : (void *)0;
	list->tail = node;
	list->head = list->head ? list->head : node;
	return (node->id);
}

/**
 * deallocate_memory - deallocates memory with the specified ID
 * from memory list.
 *
 * @id: The ID  of the memory allocation to deallocate.
 *
 * Return: 1 if deallocation is successful, 0 otherwise.
 */

int deallocate_memory(long id)
{
	AllocatedMemoryList *list = get_alloc_mem_list();
	AllocatedMemoryNode *current = list->head;

	while (current)
	{
		if (current->id == id)
		{
			if (current->prev)
				current->prev->next = current->next;
			else
				list->head = current->next;

			if (current->next)
				current->next->prev = current->prev;
			else
				list->tail = current->prev;

			safe_free(current->data);
			safe_free(current);
			return (1);

		}
		current = current->next;
	}
	return (0);
}

/**
 * pop_allocated_memory - Pops the top allocated memory from the memory list.
 *
 * Return: 1 if a memory allocation is popped successfully,
 * 0 if the list is empty.
 */
int pop_allocated_memory(void)
{
	AllocatedMemoryNode *to_be_removed;
	AllocatedMemoryList *list = get_alloc_mem_list();

	if (!list->tail)
		return (0);
	to_be_removed = list->tail;

	list->tail = list->tail->prev;
	if (list->tail)
		list->tail->next = NULL;
	else
		list->head = NULL;
	safe_free(to_be_removed->data);
	safe_free(to_be_removed);
	return (1);
}

/**
 * clean_allocated_memory - Cleans up all allocated memory on the memory list
 * and frees resources.
 *
 * Return: void
 */
void clean_allocated_memory(void)
{
	char **str_arr;
	AllocatedMemoryNode *top_node = get_top_allocated_memory();
	alloc_type_t type;

	while (top_node)
	{
		type = top_node->data->type;
		printf("::cleaning::%ld\n", top_node->id);

		if (type == GENERIC)
			safe_free(top_node->data->data);
		else if (type == STRING_ARRAY)
		{
			str_arr = (char **)top_node->data->data;
			free_string_array(str_arr, NULL);
		}
		else if (type == STRING_POINTER)
		{
			/*char **str_ptr = (char **)top_node->data->data; */
			safe_free(*((char **)(top_node->data->data)));
		}
		else if (type == FILE_DESCRIPTOR)
		{
			fclose((FILE *)top_node->data->data);
		}

		deallocate_memory(top_node->id);
		top_node = get_top_allocated_memory();
	}
	safe_free(get_alloc_mem_list());
	safe_free(get_monty_stack());
}

AllocatedMemoryNode *get_top_allocated_memory(void)
{
	AllocatedMemoryList *mem_list = get_alloc_mem_list();
	AllocatedMemoryNode *top = mem_list->tail;

	return (top);
}
