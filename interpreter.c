#include "monty.h"


/**
 * interpret - Process and interpret lines from a file stream
 * @fstream: A pointer to the FILE stream to be interpreted
 *
 * Return:
 * None (void)
 */
void interpret(FILE *fstream)
{
	char *line = NULL;
	size_t len = 0, line_number = 0;
	ssize_t nread;

	while ((nread = getline(&line, &len, fstream)) != -1)
	{
		line_number++;
		printf("%s", line);
	}
	free(line);
}
