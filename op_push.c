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
 * is_all_digits - Check if an ASCII string consists of all digit characters.
 * @ascii: The ASCII string to be examined.
 *
 * Description:
 * This function checks if the given ASCII string contains only digit
 * characters (0-9).
 *
 * Return:
 * 1 if the string contains only digit characters (0-9), 0 otherwise.
 */
int is_all_digits(char *ascii)
{
	int i, ASCII_ZERO = 48, ASCII_NINE = 57;

	for (i = 0; ascii[i]; i++)
		if (ascii[i] < ASCII_ZERO || ascii[i] > ASCII_NINE)
			return (0);
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

	if (!ascii || !is_all_digits(ascii))
		return (NULL);

	num = atoi(ascii);
	*int_ptr = num;

	return (int_ptr);
}
