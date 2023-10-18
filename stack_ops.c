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
 * init_stack - Initialize a stack structure
 * @stack: Pointer to the stack structure to be initialized
 *
 * Description:
 * This function initializes a stack structure by setting the element
 * count to 0, initializing the top pointer to NULL,
 * and setting the push and pop function pointers.
 *
 * Return:
 * None (void)
 */
void init_stack(STACK *stack)
{
	stack->counter = 0;
	stack->top = NULL;
	stack->push = push;
	stack->pop = pop;
}

/**
 * get_monty_stack - Get a pointer to the Monty stack
 *
 * Description:
 * This function provides access to the Monty stack. If the stack has not been
 * previously created, it allocates memory for it, initializes the stack
 * structure using `init_stack`, and returns a pointer to the stack.
 *
 * Return:
 * A pointer to the Monty stack on success,
 * or NULL on failure (e.g., if memory allocation fails).
 */
STACK *get_monty_stack()
{
	static STACK *stack;

	if (!stack)
	{
		stack = malloc(sizeof(STACK));
		if (!stack)
			return (NULL);

		init_stack(stack);
	}
	return (stack);
}
