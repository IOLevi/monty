#include "monty.h"

/**
 * _pall - prints all the values on the stack
 * @head: pointer to the head of stack
 * @line_number: line number
 */
void _pall(stack_t **head, __attribute__((unused)) unsigned int line_number)
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
	int negativeflag;

	negativeflag = 0;
	if (n[0] == '-')
	{
		n++;
		negativeflag = 1;
	}
	if (atoi(n) == 0 && strcmp(n, "0") != 0)
	{
		printf("L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	else
		newn = atoi(n);

	if (negativeflag)
		newn *= -1;

	new = malloc(sizeof(stack_t));
	if (!new)
	{
		printf("Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new->n = newn;
	new->next = NULL;
	new->prev = NULL;

	if (*head == NULL)
	{
		*head = new;
		return;
	}

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

	if (!head || !*head)
	{
		printf("L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}

	hpointer = *head;

	if (hpointer->next == NULL)
	{
		free(hpointer);
		*head = NULL;
		return;
	}

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
	if (hpointer->next->next == NULL)
	{
		hpointer->next->next = hpointer;
		hpointer->next->prev = NULL;
		hpointer->prev = hpointer->next;
		hpointer->next = NULL;
		return;
	}
	while (hpointer->next->next != NULL)
		hpointer = hpointer->next;


	hpointer->next->next = hpointer;
	hpointer->next->prev = hpointer->prev;
	hpointer->prev = hpointer->next;
	hpointer->next = NULL;
}
