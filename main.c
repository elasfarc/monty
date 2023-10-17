#include "monty.h"

int main(int argc, char **argv)
{
	int provided_args = argc - 1;

	if (provided_args != 1)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	printf("%s\n", argv[1]);
	return (0);
}
