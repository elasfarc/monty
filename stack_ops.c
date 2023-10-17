#include "monty.h"



/**
 * push - Push an element onto the stack
 * @stack: Pointer to the stack
 * @n: The integer value to push onto the stack
 *
 * Description:
 * This function pushes an integer value onto the stack. It allocates memory
 * for a new node and adds it to the top of the stack.
 *
 * Return:
 * 1 on success, 0 on failure (e.g., if memory allocation fails or if the stack
 * pointer is NULL).
 */
int push(STACK *stack, int n)
{
	DL_NODE *node;

	if (stack == NULL)
		return (0);

	node = malloc(sizeof(DL_NODE));
	if (node == NULL)
		return (0);

	node->next = NULL;
	node->prev = stack->top;
	node->n = n;

	stack->top ? (stack->top)->next = node : (void *)0;
	stack->top = node;
	stack->counter++;

	return (1);
}

/**
 * pop - Pop an element from the stack
 * @stack: Pointer to the stack
 *
 * Description:
 * This function removes the top element from the stack and frees the
 * associated memory.
 * It updates the stack's top pointer and decreases the element count.
 *
 * Return:
 * 1 on success, 0 on failure (e.g., if the stack is empty or if the stack
 * pointer is NULL).
 */
int pop(STACK *stack)
{
	DL_NODE *to_poped;

	if (stack == NULL || !stack->top)
		return (0);

	to_poped = stack->top;
	stack->top = (stack->top)->prev;
	free(to_poped);

	return (1);
}

/**
 * init_stack - Initialize a new stack
 *
 * Description:
 * This function initializes and returns a new stack. It allocates memory for
 * a stack structure, sets the element count to 0, and initializes the
 * top pointer and function pointers for push and pop operations.
 *
 * Return:
 * A pointer to the newly initialized stack on success, or NULL on failure
 * (if memory allocation fails,...).
 */
STACK *init_stack()
{
	STACK *stack = malloc(sizeof(STACK));

	if (!stack)
		return (NULL);
	stack->counter = 0;
	stack->top = NULL;
	stack->push = push;
	stack->pop = pop;
	return (stack);
}
