#include "memory-allocation.h"
#include "monty.h"

/**
 * op_pall - Print all elements of the stack
 * @args: A pointer to the INSTRUCTION_ARGS structure
 *
 * Description:
 * This function prints all elements of the stack, starting from the top and
 * moving towards the bottom. It iterates through the linked list of stack
 * elements, printing each element's value, followed by a newline character.
 *
 * Return: None
 */
void op_pall(INSTRUCTION_ARGS *args)
{
	DL_NODE *top = args->stack->top;

	while (top)
	{
		printf("%d\n", top->n);
		top = top->prev;
	}
}

/**
 * op_pint - Print the value at the top of the stack.
 * @args: A pointer to the INSTRUCTION_ARGS structure.
 *
 * Return: void
 */
void op_pint(INSTRUCTION_ARGS *args)
{
	if (args->stack->top)
		printf("%d\n", args->stack->top->n);
	else
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", args->line_number);
		clean_allocated_memory();
		exit(EXIT_FAILURE);
	}
}

/**
 * op_pop - Removes the top element of the stack.
 * @args: A pointer to the INSTRUCTION_ARGS structure.
 *
 * Return: void
 */
void op_pop(INSTRUCTION_ARGS *args)
{
	if (args->stack->top)
		args->stack->pop(args->stack);
	else
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", args->line_number);
		clean_allocated_memory();
		exit(EXIT_FAILURE);
	}
}

/**
 * get_op_function - Get a function pointer corresponding to an operation
 * @op: The string representing the operation to be looked up
 *
 * Description:
 * This function takes a string 'op' representing an operation and returns the
 * corresponding function pointer for that operation. It performs a lookup
 * in a predefined array of operation structures to find a match based
 * on the 'opcode'.
 *
 * Return:
 * - A function pointer to the operation function if a match is found.
 * - NULL if no matching operation is found.
 */
void (*get_op_function(char *op))(INSTRUCTION_ARGS *args)
{
	int i, ops_len;

	instruction_t ops[] = {
		{"push", op_push},
		{"pall", op_pall},
		{"pint", op_pint},
		{"pop", op_pop},
	};

	ops_len = sizeof(ops) / sizeof(ops[0]);
	for (i = 0; i < ops_len; i++)
		if (strcmp(op, ops[i].opcode) == 0)
			return (ops[i].f);

	return (NULL);
}
