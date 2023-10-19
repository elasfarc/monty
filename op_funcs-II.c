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
