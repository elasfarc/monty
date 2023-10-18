#ifndef _MONTY_H_
#define _MONTY_H_

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * struct dlist_node_s - doubly linked list node
 * @n: integer
 * @prev: points to the previous node
 * @next: points to the next node
 *
 * Description: doubly linked list node structure
 */
typedef struct dlist_node_s
{
	int n;
	struct dlist_node_s *prev;
	struct dlist_node_s *next;
} DL_NODE;

/**
 * struct stack_s - Structure for a stack data structure
 * @top: Pointer to the top element of the stack
 * @counter: Number of elements in the stack
 * @push: Pointer to the push function
 * @pop: Pointer to the pop function
 *
 * Description:
 * This structure represents a stack data structure. It contains a pointer to
 * the top element, a counter to keep track of the number of elements,
 * and function pointers for the push and pop operations.
 */
typedef struct stack_s
{
	DL_NODE *top;
	unsigned int counter;
	int (*push)(struct stack_s *, int);
	int (*pop)(struct stack_s *);
} STACK;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(DL_NODE **stack, unsigned int line_number);
} instruction_t;


STACK *get_monty_stack();

#endif
