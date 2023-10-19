#include "monty.h"
#include "memory-allocation.h"

/**
 * main - Entry point of the Monty bytecode interpreter
 * @argc: Number of arguments passed to the program
 * @argv: Array of string arguments
 *
 * Return:
 * - 0 on successful execution.
 * - EXIT_FAILURE (1) if an error occurs.
 */
int main(int argc, char **argv)
{
	int provided_args = argc - 1;
	FILE *file_ptr;

	if (provided_args != 1)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file_ptr = fopen(argv[1], "r");
	if (file_ptr == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	push_allocated_memory(
		create_allocated_memory(FILE_DESCRIPTOR, file_ptr));

	interpret(file_ptr);

	clean_allocated_memory();
	return (0);
}
