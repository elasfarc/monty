#include "memory-allocation.h"


/**
 * init_alloc_mem_list - Initializes an AllocatedMemoryList.
 * @mem_list_ptr: Pointer to the AllocatedMemoryList to be initialized.
 *
 * Return: void
 */
void init_alloc_mem_list(AllocatedMemoryList **mem_list_ptr)
{
	(*mem_list_ptr)->head = NULL;
	(*mem_list_ptr)->tail = NULL;
	(*mem_list_ptr)->size = 0;
}

/**
 * get_alloc_mem_list - Retrieves or creates a global AllocatedMemoryList.
 *
 * Return: Pointer to the global AllocatedMemoryList.
 */
AllocatedMemoryList *get_alloc_mem_list()
{
	static AllocatedMemoryList *mem_list;

	if (!mem_list)
	{
		mem_list = malloc(sizeof(AllocatedMemoryList));
			init_alloc_mem_list(&mem_list);
	}
	return (mem_list);
}

/**
 * create_allocated_memory - Creates an allocated memory object.
 * @type: The type of allocation (STRING/ STRING_ARRAY).
 * @data: Pointer to the allocated memory data.
 *
 * Return: Pointer to the allocated memory object.
 */
AllocatedMemory *create_allocated_memory(alloc_type_t type, void *data)
{
	AllocatedMemory *mem = malloc(sizeof(AllocatedMemory));

	/*handle fail malloc*/
	mem->data = data;
	mem->type = type;

	return (mem);
}
