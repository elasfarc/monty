#include "monty.h"
#include "memory-allocation.h"


/**
 * get_instruc_args - Create an INSTRUCTION_ARGS structure for an instruction
 * @stack: A pointer to a STACK structure for stack manipulation
 * @line_num: The line number where the instruction appears
 * @param: The parameter or argument associated with the instruction
 *
 * Return:
 * A pointer to the newly created INSTRUCTION_ARGS structure on success,
 * or NULL if memory allocation fails.
 */
INSTRUCTION_ARGS *get_instruc_args(STACK *stack, size_t line_num, char *param)
{
	INSTRUCTION_ARGS *args = malloc(sizeof(INSTRUCTION_ARGS));

	if (!args)
		return (NULL);
	args->stack = stack;
	args->line_number = line_num;
	args->param = param;
	return (args);
}



/**
 * interpret - Process and interpret lines from a file stream
 * @fstream: A pointer to the FILE stream to be interpreted
 *
 * Return:
 * None (void)
 */
void interpret(FILE *fstream)
{
	char *token, *line = NULL, **line_ptr = &line;
	size_t len = 0, line_number = 0;
	ssize_t nread;
	long linep_alloc_id, instruc_args_id;
	INSTRUCTION_ARGS *args;
	STACK *monty_stack;
	void (*op_func)(INSTRUCTION_ARGS *);

	linep_alloc_id = push_allocated_memory(
		create_allocated_memory(STRING_POINTER, line_ptr));
	while ((nread = getline(&line, &len, fstream)) != -1)
	{
		line_number++;
		token = strtok(line, " $\t\n");
		if (!token || strcmp(token, "nop") == 0 || *token == '#')
			continue;
		op_func = get_op_function(token);

		if (op_func == NULL)
		{
			fprintf(stderr, "L%lu: unknown instruction %s\n",
				line_number, token);
			clean_allocated_memory();
			exit(EXIT_FAILURE);
		}
		monty_stack = get_monty_stack();

		args = get_instruc_args(monty_stack, line_number, strtok(NULL, " $\n"));
		if (!args)
			handle_malloc_fail();
		instruc_args_id =  push_allocated_memory(
			create_allocated_memory(GENERIC, args));

		op_func(args);
		deallocate_memory(instruc_args_id);
		safe_free(args);

	}
	deallocate_memory(linep_alloc_id);
	free(line);
}
