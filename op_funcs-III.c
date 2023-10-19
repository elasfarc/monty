#include "memory-allocation.h"
#include "monty.h"

/**
 * op_rotl - Rotate the top element of the stack to the bottom.
 * @args: A pointer to the INSTRUCTION_ARGS structure.
 *
 * Description:
 * The op_rotl function takes the top element of the stack and moves it to
 * the bottom of the stack, (rotating the stack to the left).
 * If the stack contains less than two elements, it does nothing.
 *
 * Return: void
 */
void op_rotl(INSTRUCTION_ARGS *args)
{
	DL_NODE *top, *second_top, *last;

	if (args->stack->counter < 2)
		return;

	top = args->stack->top;
	second_top = top->prev;
	last = top;

	while (last->prev)
		last = last->prev;

	second_top->next = NULL;
	args->stack->top = second_top;

	top->prev = NULL;
	top->next = last;

	last->prev = top;
}
