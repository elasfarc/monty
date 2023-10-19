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

/**
 * op_rotr - Rotate the stack to the right.
 * @args: A pointer to the INSTRUCTION_ARGS structure.
 *
 * Description:
 * Rotates the stack to the right, where the top element becomes the
 * last element, and all other elements are shifted one position to
 * the right. If the stack contains less than 2 elements, no action is taken.
 *
 * Return: void
 */
void op_rotr(INSTRUCTION_ARGS *args)
{
	DL_NODE *top, *penultimate, *last;

	if (args->stack->counter < 2)
		return;

	top = args->stack->top;

	last = top;
	while (last->prev)
		last = last->prev;
	penultimate = last->next;

	top->next = last;
	last->next = NULL;
	last->prev = top;
	penultimate->prev = NULL;

	args->stack->top = last;
}


/**
 * op_switch_mood - Toggle the mood of the stack between STACK and QUEUE.
 * @args: A pointer to the INSTRUCTION_ARGS structure.
 *
 * Description:
 * The mood of the stack determines whether it operates
 * as a stack (last-in, first-out) or a queue (first-in, first-out).
 *
 * Return: void
 */
void op_switch_mood(INSTRUCTION_ARGS *args)
{
	if (args->stack->mood == _STACK)
		args->stack->mood = _QUEUE;
	else
		args->stack->mood = _STACK;
}
