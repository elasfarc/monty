#include "monty.h"
#include "memory-allocation.h"


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
	long linep_alloc_id;
	void (*op_func)(INSTRUCTION_ARGS *);

	linep_alloc_id = push_allocated_memory(
		create_allocated_memory(STRING_POINTER, line_ptr)
	);

	while ((nread = getline(&line, &len, fstream)) != -1)
	{
		line_number++;
		token = strtok(line, " $\n");
		op_func = get_op_function(token);

		if (op_func == NULL)
		{
			fprintf(stderr, "L%lu: unknown instruction %s\n",
				line_number, token);
			clean_allocated_memory();
			exit(EXIT_FAILURE);
		}

	}
	deallocate_memory(linep_alloc_id);
	free(line);
}
