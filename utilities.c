#include "monty.h"

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
 * free_list - frees the list
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
 * initialize_instructions - an array of opcode functions
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

	p[7].opcode = "sub";
	p[7].f = _sub;

	p[8].opcode = "div";
	p[8].f = _div;

	p[9].opcode = "mul";
	p[9].f = _mul;

	p[10].opcode = "mod";
	p[10].f = _mod;

	p[11].opcode = "pchar";
	p[11].f = _pchar;

	p[12].opcode = "pstr";
	p[12].f = _pstr;

	p[13].opcode = NULL;
	p[13].f = NULL;
}
