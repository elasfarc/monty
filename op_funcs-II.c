#include "memory-allocation.h"
#include "monty.h"

/**
 * op_add - adds the top two elements of the stack.
 * @args: A pointer to the INSTRUCTION_ARGS structure.
 *
 * Return: void
 */
void op_add(INSTRUCTION_ARGS *args)
{
	int result;
	DL_NODE *top = args->stack->top;

	if (args->stack->counter < 2)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", args->line_number);
		clean_allocated_memory();
		exit(EXIT_FAILURE);
	}

	result = top->n + top->prev->n;
	args->stack->pop(args->stack);
	args->stack->top->n = result;
}
