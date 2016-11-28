#include "stack.h"
#include <string.h>

/*
 * Initializes a stack
 * Return:
 *   Normal: An empty stack
 *   When there is no memory available to allocate: null pointer
 */
Stack* stack_init() 
{
	Stack *stack = (Stack *) malloc(sizeof(Stack));
	if (stack == NULL) {
		return NULL;
	}

	stack->top = STACK_EMPTY;
	stack->array = (char **) malloc(STACK_SIZE * sizeof(char*));
	if (stack->array == NULL) {
		return NULL;
	}

	return stack;
}

/*
 * Pushes to a stack
 * Param:
 *   item - the stuff to be pushed
 */
void push(Stack* stack, char* str)
{
	stack->top++;
	stack->array[stack->top] = strdup(str);
	// printf("Top of stack: %s\n", stack->array[stack->top]);
}

/*
 * Pops from a stack
 */
char* pop(Stack* stack) 
{
    if (isEmpty(stack) == ONE) {
 		return NULL;
    }

    char* str = stack->array[stack->top];
    stack->top--;

    return str;
}

/*
 * Returns top element of stack
 */
char* peek(Stack* stack) 
{
	if (isEmpty(stack) == ONE) {
		return NULL;
	}

    char* str = stack->array[stack->top];
 	return str;
}

/*
 * Prints out the information of a stack
 */
void print(Stack* stack)
{	
	if (isEmpty(stack) == ONE) {
		printf("%s\n", STR_PRINT_NO_ITEMS);
	}

	else {
		printf("%s ", STR_PRINT_ITEMS);
		for (int i = 0; i <= stack->top; i++) {
			printf("%s ", stack->array[i]);
		}
	}
}

/*
 * Returns 1 if stack is empty, 0 if not
 */
int isEmpty(Stack* stack) 
{
	if (stack->top == STACK_EMPTY) {
		return 1;
	}

	else {
		return 0;
	}
}

/*
 * Destructs a stack
 */
void stack_delete(Stack* stack) 
{
	for (int i = 0; i <= stack->top; i++) {
		free(stack->array[i]);
	}
	free(stack->array);
}
