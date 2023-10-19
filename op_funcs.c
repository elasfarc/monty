#include "monty.h"

void op_pall(INSTRUCTION_ARGS *args)
{}

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
	};

	ops_len = sizeof(ops) / sizeof(ops[0]);
	for (i = 0; i < ops_len; i++)
		if (strcmp(op, ops[i].opcode) == 0)
			return (ops[i].f);

	return (NULL);
}
