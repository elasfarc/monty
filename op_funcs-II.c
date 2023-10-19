#include "memory-allocation.h"
#include "monty.h"


/**
  * handle_div_by_zero - Handle division by zero error.
  * @line_num: The line number where the error occurred.
  *
  * Return: void
  */
void handle_div_by_zero(int line_num)
{
	fprintf(stderr, "L%d: division by zero\n", line_num);
	clean_allocated_memory();
	exit(EXIT_FAILURE);
}

/**
 * op_arithmetic - Execute arithmetic operations on the stack.
 * @args: A pointer to the INSTRUCTION_ARGS structure.
 *
 * Description:
 * The op_arithmetic function performs various arithmetic operations on the top
 * two elements of the stack (+, -, /, *, %).
 * It also checks for division by zero errors and handles them using the
 * handle_div_by_zero function.
 *
 * Return: void
 */
void op_arithmetic(INSTRUCTION_ARGS *args)
{
	int result, n1, n2;
	DL_NODE *top = args->stack->top;
	char *op = args->param;

	if (args->stack->counter < 2)
	{
		fprintf(stderr, "L%d: can't %s, stack too short\n",
			args->line_number, op);
		clean_allocated_memory();
		exit(EXIT_FAILURE);
	}

	n1 = top->n;
	n2 = top->prev->n;

	if (n1 == 0 && (!strcmp(op, "div") || !strcmp(op, "mod")))
		handle_div_by_zero(args->line_number);

	result = strcmp(op, "add") == 0
		? n1 + n2
		: strcmp(op, "sub") == 0
		? n2 - n1
		: strcmp(op, "div") == 0
		? n2 / n1
		: strcmp(op, "mul") == 0
		? n1 * n2
		: n2 % n1;

	args->stack->pop(args->stack);
	args->stack->top->n = result;
}

/**
 * op_pchar - Print the character represented by the top element of the stack.
 * @args: A pointer to the INSTRUCTION_ARGS structure.
 *
 * Description:
 * The op_pchar function prints the character represented by the top element of
 * the stack. It checks if the stack is empty or if the value is out of
 * the valid ASCII character range (0-127) and handles errors accordingly.
 * If successful, it prints the character and a newline character.
 *
 * Return: void
 */
void op_pchar(INSTRUCTION_ARGS *args)
{
	DL_NODE *top = args->stack->top;
	int is_empty = (args->stack->counter == 0);
	int in_range = top && top->n >= 0 && top->n <= 127;

	if (is_empty || !in_range)
	{
		char *empty_err = "can't pchar, stack empty";
		char *out_range_err = "can't pchar, value out of range";

		fprintf(stderr, "L%d: %s\n",
			args->line_number, is_empty ? empty_err : out_range_err);
		clean_allocated_memory();
		exit(EXIT_FAILURE);
	}

	printf("%c\n", top->n);
}
