#include "monty.h"
#include "memory-allocation.h"

int is_valid_integer_string(char *ascii);


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
	int arg, is_pushed;
	STACK *monty_stack;

	if (is_valid_integer_string(args->param))
		arg = atoi(args->param);
	else
		handle_push_err(args->line_number);

	monty_stack = get_monty_stack();
	is_pushed = (monty_stack->push)(monty_stack, arg);

	if (!is_pushed && errno == ENOMEM)
		handle_malloc_fail();
}

/**
 * is_valid_integer_string - Check if an ASCII string is a valid
 * integer representation.
 * @ascii: The ASCII string to be checked.
 *
 * Description:
 * checks for characters that are allowed in an integer representation,
 * such as digits (0-9), optional leading signs (+ or -), and spaces.
 * It ensures that these characters are correctly formatted and
 * that there are no unexpected characters.
  *
 * Return:
 * 1 if the string is a valid integer representation, 0 otherwise.
 */
int is_valid_integer_string(char *ascii)
{
	int i, ASCII_ZERO = 48, ASCII_NINE = 57;
	short is_first_digit = 0, is_sign = 0;
	char c;

	if (!ascii)
		return (0);

	for (i = 0; (c = ascii[i]); i++)
	{
		if (c == ' ' || c == '+' || c == '-' ||
			(c >= ASCII_ZERO && c <= ASCII_NINE))
		{
			if ((is_first_digit || is_sign) && c == ' ')
				return (0);
			if (is_first_digit && (c == '+' || c == '-'))
				return (0);
			if (is_sign && (c == '+' || c == '-'))
				return (0);

			is_first_digit = (c >= ASCII_ZERO && c <= ASCII_NINE);
			is_sign = (c == '+' || c == '-');
		}
		else
			return (0);
	}
	return (1);
}
