#ifndef _ALLOC_MEM_
#define _ALLOC_MEM_

#include <stddef.h>
#include <stdlib.h>
/**
 * enum alloc_type - Enumeration of allocation types.
 * @STRING_ARRAY: Represents an array of strings allocation.
 * @STRING_POINTER: Represents a pointer to a string.
 * @FILE_DESCRIPTOR: Represents a FILE DESCRIPTOR.
 * @GENERIC: Represents a generic or unspecified allocation type.
 *
 */
typedef enum alloc_type
{
	STRING_ARRAY, STRING_POINTER, FILE_DESCRIPTOR, GENERIC
} alloc_type_t;

/**
 * struct AllocatedMemory -  hold allocated memory information.
 *
 * @type: The type of allocation.
 * @data: Pointer to the allocated memory data.
 */
typedef struct AllocatedMemory
{
	alloc_type_t type;
	void *data;
} AllocatedMemory;

/**
 * struct AllocatedMemoryNode - representing a node
 * in the allocated memory stack.
 *
 * @id: Unique identifier for the node.
 * @data: Pointer to the allocated memory.
 * @next: Pointer to the next node in the stack.
 * @prev: Pointer to the previous node in the stack.
 */
typedef struct AllocatedMemoryNode
{
	long int id;
	AllocatedMemory *data;
	struct AllocatedMemoryNode *next;
	struct AllocatedMemoryNode *prev;
} AllocatedMemoryNode;

/**
 * struct AllocatedMemoryList - representing a lin§ked list of
 * allocated memory nodes
 *
 * @head: Pointer to the head of the list.
 * @tail: Pointer to the last added element to the list.
 * @size: The number of nodes in the list.
 */
typedef struct AllocatedMemoryList
{
		AllocatedMemoryNode *head;
		AllocatedMemoryNode *tail;
		unsigned int size;
} AllocatedMemoryList;



AllocatedMemoryList *get_alloc_mem_list();

long int push_allocated_memory(AllocatedMemory *memory_alloc);
int deallocate_memory(long);
int pop_allocated_memory(void);

void clean_allocated_memory(void);
AllocatedMemoryNode *get_top_allocated_memory(void);

AllocatedMemory *create_allocated_memory(alloc_type_t type, void *data);


void safe_free(void *v);
void free_string_array(char **str_arr, const int *const length);

#endif
