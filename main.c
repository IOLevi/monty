#include "monty.h"

char *n = NULL;
//NOTE TO SELF: RUN "./a.out byte.m" exactly to get it to read the line

/**
 * free_list: frees the list
 * @head: pointer to the stack
 */
void free_list(stack_t *head)
{
	stack_t *temp;

	if (!head)
		return;

	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}


}
/**
 * main - main function of the monty byte code program
 * @argc: number of arguments
 * @argv: pointer to string of arguments
 * Return: 0 on success, -1 on failure
 */
int main(int argc, char **argv)
{

	FILE *fd;
	int readnum;
	size_t len;
	unsigned int line_number;
	int i;
	char *strinput;
	instruction_t p[8];
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
	//push, pall, pint, pop, swap, add, nop
	line_number = 0;
	while (getline(&strinput, &len, fd) != -1)
	{
		line_number++;
		//get first token (the command)
		command = strtok(strinput, DELIM);
		//store all the tokens in a char array first
		//skip empty lines
		if (command == NULL)
		{
			free(strinput);
			continue;
		}

		//get command argument
		argument = strtok(NULL, DELIM);
		n = argument;
		i = 0;
		//check for comment
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
		}
		n = NULL; //TODO: do i need this
	}
	//free dkist
	//fclose
	fclose(fd);
	free_list(head);
	return (EXIT_SUCCESS);

}
/**
 * initialize_instructions: an array of opcode functions
 * @p: array to interate through
 */
void initialize_instructions(instruction_t p[])
{
	p[0].opcode = "push";
	p[0].f = _push;

	p[1].opcode = "pall";
	p[1].f = _pall;

	p[2].opcode = "pint";
	p[2].f = _pint;

	p[3].opcode = "pop";
	p[3].f = _pop;

	p[4].opcode = "swap";
	p[4].f = _swap;

	p[5].opcode = "add";
	p[5].f = _add;

	p[6].opcode = "nop";
	p[6].f = _nop;

	p[7].opcode = NULL;
	p[7].f = NULL;
}
/**
 * _pall - prints all the values on the stack
 * @head: pointer to the head of stack
 * @line_number: line number
 */
void _pall(stack_t **head, unsigned int line_number)
{
	stack_t *hpointer;

	if (!head || !*head)
		return;

	hpointer = *head;

	while (hpointer->next)
	{
		hpointer = hpointer->next;
	}

	while (hpointer)
	{
		printf("%d\n", hpointer->n);
		hpointer = hpointer->prev;

	}
}
/**
 * _push - pushes an element to the stack
 * @head: pointer to the head of stack
 * @line_number: line number
 */
void _push(stack_t **head, unsigned int line_number)
{
	stack_t *new;
	stack_t *hpointer;
	int newn;

	//no n global variable
	if (atoi(n) == 0 && strcmp(n, "0") != 0)
	{
		printf("L%d: usage: push integer\n", line_number);
		//TODO: call freeing stuff
		exit(EXIT_FAILURE);
	}
	else
		newn = atoi(n);


	new = malloc(sizeof(stack_t));
	if (!new)
	{
		printf("Error: malloc failed\n");
		//TODO: free before exiting
		exit(EXIT_FAILURE);
	}

	new->n = newn;
	new->next = NULL;
	new->prev = NULL;

	//empty list
	if (*head == NULL)
	{
		*head = new;
		return;
	}

	//nonempty list
	hpointer = *head;

	while (hpointer->next != NULL)
		hpointer = hpointer->next;

	hpointer->next = new;
	new->prev = hpointer;
}
/**
 * _pint - prints the value at the top of the stack
 * @head: pointer to the head of stack
 * @line_number: line number
 */
void _pint(stack_t **head, unsigned int line_number)
{
	stack_t *hpointer;
	if (!head || !*head)
	{
		printf("L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}

	hpointer = *head;
	while (hpointer->next)
		hpointer = hpointer->next;

	printf("%d\n", hpointer->n);
}

/**
 * pop - removes the top element of the stack
 * @head: pointer to the head of stack
 * @line_number: line number
 */
void _pop(stack_t **head, unsigned int line_number)
{
	stack_t *hpointer;

	//list of len 0
	if (!head || !*head)
	{
		printf("L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}

	hpointer = *head;

	//list of len 1
	if (hpointer->next == NULL)
	{
		free(hpointer);
		*head = NULL;
		return;
	}

	//list of 2 or more
	while (hpointer->next != NULL)
		hpointer = hpointer->next;

	hpointer->prev->next = NULL;
	free(hpointer);

}
/**
 * swap - swaps the top two elements of the stack
 * @head: pointer to the head of stack
 * @line_number: line number
 */
void _swap(stack_t **head, unsigned int line_number)
{
	stack_t *hpointer;

	if (!head || !*head || (*head)->next == NULL)
	{
		printf("L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	hpointer = *head;
	//list of length 2
	if (hpointer->next->next == NULL)
	{
		hpointer->next->next = hpointer;
		hpointer->next->prev = NULL;
		hpointer->prev = hpointer->next;
		hpointer->next = NULL;
		return;
	}
	//longer than 2
	while (hpointer->next->next != NULL)
		hpointer = hpointer->next;


	hpointer->next->next = hpointer;
	hpointer->next->prev = hpointer->prev;
	hpointer->prev = hpointer->next;
	hpointer->next = NULL;
}
/**
 * add: adds the top two elements of the stack
 * @head: pointer to the doubled linked list
 * @line_number: line number
 */
void _add(stack_t **head, unsigned int line_number)
{
	stack_t *hpointer;
	int sum;

	if (!head || !*head || (*head)->next == NULL)
	{
		printf("L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	hpointer = *head;
	//list of length 2
	if (hpointer->next->next == NULL)
	{
		sum = hpointer->n + hpointer->next->n;
		hpointer->n = sum;
		_pop(head, line_number);
		return;
	}

	//longer than 2
	while (hpointer->next->next != NULL)
		hpointer = hpointer->next;

	sum = hpointer->n + hpointer->next->n;
	hpointer->n = sum;
	_pop(head, line_number);
}
/**
 * nop: doesn't do anything
 * @head: pointer to double linked list to the stack
 * @line_number: line number
 */
void _nop(stack_t **head, unsigned int line_number)
{
	;
}
/**
 * _sub - subtracts the top element of the stack from the second
 * top element of the stack
 * @head: pointer to the head
 * @line_number: line number
 */
void _sub(stack_t **head, unsigned int line_number)
{
	int sub;
	stack_t *hpointer;

	if (!head || !*head || (*head)->next == NULL)
	{
		printf("L%d: can't sub, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	hpointer =*head;
	while (hpointer->next->next != NULL)
		hpointer = hpointer->next;
	sub = hpointer->n - hpointer->next->n;
	hpointer->n = sub;
	_pop(head, line_number);

}
/**
 * _div - divides the second top element of the stack by the top
 * element of the stack
 * @head: pointer to the stack
 * @line_number: line number
 */
void _div(stack_t **head, unsigned int line_number)
{
	stack_t *hpointer;
	int result;

	if (!head || !*head || (*head)->next == NULL)
	{
		printf("L%d: can't div, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	hpointer = *head;
	while (hpointer->next->next != NULL)
		hpointer = hpointer->next;

	if (hpointer->next->n == 0)
	{
		printf("L%d: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}

	result = hpointer->n / hpointer->next->n;
	hpointer->n = result;
	_pop(head, line_number);
}
/**
 * _mul - multiplies the second top element of the stack with the to
 * element of the stack
 * @head: pointer to the stack
 * @line_number: line number
 */
void _mul(stack_t **head, unsigned int line_number)
{
	stack_t *hpointer;
	int result;

	if (!head || !*head || (*head)->next == NULL)
	{
		printf("L%d: can't mul, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	hpointer = *head;
	while (hpointer->next->next != NULL)
		hpointer = hpointer->next;

	result = hpointer->next->n * hpointer->n;
	hpointer->n = result;
	_pop(head, line_number);
}
/**
 * _mod - computes the rest of the division of the secont top element
 * of the stack by the top element of the stack
 * @head: pointer to the stack
 * @line_number: line number
 */
void _mod(stack_t **head, unsigned int line_number)
{
	int result;
	stack_t *hpointer;

	if (!head || !*head || (*head)->next == NULL)
	{
		printf("L%d: can't mod, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	hpointer = *head;
	while (hpointer->next->next != NULL)
		hpointer = hpointer->next;

	if (hpointer->next->n == 0)
	{
		printf("L%d: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}

	result = hpointer->n % hpointer->next->n;
	hpointer->n = result;
	_pop(head, line_number);
}
/**
 * check_comment - checks to see if the first comment is a #
 * @s: the command string
 * Return: 1 if yes; 0 if no
 */
int check_comment(char *s)
{
	if (s[0] == '#')
		return (1);
	else
		return (0);
}
/**
 * _pchar - prints the char at the top of the stack
 * @head: pointer to the stack
 * @line_number: line number
 */
void _pchar(stack_t **head, unsigned int line_number)
{
	stack_t *hpointer;

	if (!head || !*head)
	{
		printf("L%d: can't pchar, value out of range\n", line_number);
		exit(EXIT_FAILURE);
	}

	hpointer = *head;

	while (hpointer->next != NULL)
		hpointer = hpointer->next;

	if (hpointer->n < 0 || hpointer->n > 127)
	{
		printf("L%d: can't pchar, value out of range\n", line_number);
		exit(EXIT_FAILURE);
	}
	putchar(hpointer->n);
}
/**
 * _pstr - prints the char at the top of the stack
 * @head: pointer to the stack
 * @line_number: line number
 */
void _pstr(stack_t **head, unsigned int line_number)
{
	stack_t *hpointer;

	if (!head || !*head)
	{
		printf("\n");
		return;
	}

	hpointer = *head;

	while (hpointer->next != NULL)
		hpointer = hpointer->next;

	while (hpointer != NULL && hpointer->n != 0)
	{
		if (hpointer->n >= 0 || hpointer->n <= 127)
			putchar(hpointer->n);
		else
			break;

		hpointer = hpointer->prev;
	}
	putchar('\n');
}









