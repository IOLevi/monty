#include "monty.h"
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
	if (hpointer->next->next == NULL)
	{
		sum = hpointer->n + hpointer->next->n;
		hpointer->n = sum;
		_pop(head, line_number);
		return;
	}

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
void _nop(__attribute__((unused)) stack_t **head, __attribute__((unused)) unsigned int line_number)
{
	;
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
void _pstr(stack_t **head, __attribute__((unused)) unsigned int line_number)
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
