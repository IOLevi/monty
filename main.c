#include "monty.h"

char *n = NULL;

/**
 * main - main function of the monty byte code program
 * @argc: number of arguments
 * @argv: pointer to string of arguments
 * Return: 0 on success, -1 on failure
 */
int main(int argc, char **argv)
{

	FILE *fd;
	size_t len;
	unsigned int line_number;
	int i;
	char *strinput;
	instruction_t p[14];
	char *command;
	char *argument;
	stack_t *head;

	initialize_instructions(p);
	head = NULL;

	if (argc != 2)
	{
		printf("USAGE: monty file\n");
		exit(EXIT_FAILURE);

	}
	fd = fopen(argv[1], "r");

	if (fd == NULL)
	{
		printf("Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);

	}
	line_number = 0;
	strinput = NULL;
	while (getline(&strinput, &len, fd) != -1)
	{
		line_number++;
		command = strtok(strinput, DELIM);
		if (command == NULL)
		{
		/*	free(strinput);*/
			continue;
		}

		argument = strtok(NULL, DELIM);
		n = argument;
		i = 0;
		if (check_comment(command))
			continue;

		while (p[i].opcode != NULL)
		{
			if (strcmp(command, p[i].opcode) == 0)
			{
				p[i].f(&head, line_number);
				break;
			}
			i++;
			if (p[i].opcode == NULL)
			{
				printf("L%d: unknown instruction %s\n", line_number, command);
				exit(EXIT_FAILURE);

			}
		}
		
		n = NULL;
	}
	fclose(fd);
	free_list(head);
	if (strinput)
		free(strinput);
	return (EXIT_SUCCESS);
}
