#include "monty.h"

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


	interpret(file_ptr);
	fclose(file_ptr);
	return (0);
}
