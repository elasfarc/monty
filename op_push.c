#include "monty.h"
#include "memory-allocation.h"
#include <errno.h>

int *parseStringToInteger(char *ascii, int *int_ptr);


/**
 * handle_push_err - Handle an error during push instruction.
 * @line_num: The line number where the error occurred.
 *
 * Return: void
 */
void handle_push_err(int line_num)
{
	char *s = "L%d: usage: push integer\n";

	fprintf(stderr, s, line_num);
	clean_allocated_memory();
	exit(EXIT_FAILURE);
}

/**
 * op_push - Execute the push instruction.
 * @args: A pointer to the INSTRUCTION_ARGS structure.
 *
 * Description:
 * executes the "push" instruction. parses the parameter to an integer
 * and pushes it onto the stack. If the parameter cannot be converted to
 * an integer or if memory allocation fails during the push operation,
 * an error is handled.
 *
 * Return: void
 */
void op_push(INSTRUCTION_ARGS *args)
{
	int arg, *arg_ptr = &arg, is_pushed;
	STACK *monty_stack;

	if (parseStringToInteger(args->param, arg_ptr) == NULL)
		handle_push_err(args->line_number);

	monty_stack = get_monty_stack();
	is_pushed = (monty_stack->push)(monty_stack, arg);

	if (!is_pushed && errno == ENOMEM)
		handle_malloc_fail();
}

/**
 * is_zero - Check if an ASCII string represents zero.
 * @ascii: The ASCII string to be checked.
 *
 * Description: checks if the given ASCII string represents zero. iterates
 * through the characters of the string and returns 1 if all characters
 * are '0', indicating that the string represents zero.
 * Otherwise, it returns 0.
 *
 * Return: 1 if the string represents zero, 0 otherwise.
 */
int is_zero(char *ascii)
{
	while (*ascii)
	{
		if (*ascii != '0')
			return (0);
		ascii++;
	}
	return (1);
}

/**
 * parseStringToInteger - Parses an ASCII string to an integer.
 * @ascii: The ASCII string to be converted to an integer.
 * @int_ptr: A pointer to an integer where the result will be stored.
 *
 * Return: on success -> A pointer to the integer where the result is stored.
 *	   on fails or if the string does not represent zero -> NULL
 */
int *parseStringToInteger(char *ascii, int *int_ptr)
{
	int num;

	if (!ascii)
		return (NULL);

	num = atoi(ascii);
	if (num || is_zero(ascii))
		*int_ptr = num;
	else
		int_ptr = NULL;

	return (int_ptr);
}
