#include "monty.h"

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
