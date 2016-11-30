#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h" 	
#include "stack.c"

//Type conversions starts here//

char* charToString(char c) {
	char *str = (char*)malloc(sizeof(char)*TWO);
	str[ZERO] = c;
	str[ONE] = '\0';
	return str;
}
char stringToChar(char* str) {
	return str[ZERO];
}

char* intToString(int res) {
	char *str = (char*)malloc(BUFSIZ);
	sprintf(str,"%d",res);
	return str;
}

int stringToInt(char* str) {
	return atoi(str);
}
//Type conversions end here

// --------------------------------------------------------------------------

//Helper function to return precedence of operator
int precedence(char x) {
	switch (x) {
		case '(':
			return 1;
		case '+':
			return 2;
		case '-': 
			return 2;
		case '*':
			return 3;
		case '/':
			return 3;
	}

	return -1;
}


char* convertToPostFix(char* str) {
	Stack* operatorStack = stack_init();
	char* output = "";

	printf("Entered function");

	char current = str[0];
	char* c;
	sprintf(c, "%c", current); 

	int i = 0;
	while (strcmp(c, "\0") != 0) 
	{
		// if the current token is an operand, append to the end of output string
		// atoi() also takes a char* as an argument, not a char
		if (atoi(c) != 0) {
			strcat(output, c);
		}

		// if it's not an operand
		else {
			// if it's a left parentheses, push onto stack (the stack can only push char*, not char)
			// which is one thing i'm confused on here since idk how to convert from char to char*
			if (strcmp(c, "(") == 0) {
				push(operatorStack, c);
			}

			// if it's a right parentheses, keep popping from stack until the corresponding left parentheses
			// is returned, and append each popped operator to the end of the output string
			// 
			else if (strcmp(c, ")") == 0) {
				char* popped = pop(operatorStack);

				while (strcmp(popped, "(") != 0) {
					strcat(output, popped);
					popped = pop(operatorStack);
				}

				// append ( to end of output string
				strcat(output, popped);
			}

			// if current token is operator
			else if (strcmp(c, "+") == 0 || strcmp(c, "-") == 0 || strcmp(c, "*") == 0 || strcmp(c, "/") == 0 || strcmp(c, "\%") == 0) {

				// get top of stack 
				char* peeked = peek(operatorStack);

				// while there is an operator at the top of the stack whose precedence is greater than
				// or equal to precedence of current token in input string
				while (precedence(*peeked) >= precedence(*c)) {

					// pop the peeked element from top of stack and append to the output
					peeked = pop(operatorStack);
					strcat(output, peeked);

					// if no more operators on stack, break out of loop
					if (isEmpty(operatorStack)) {
						break;
					}

					// otherwise get next element on top of stack to check for precedence at beginning of loop
					else {
						peeked = peek(operatorStack);
					}
				}

				// push current input token onto stack
				push(operatorStack, c);
			}
		}

		i++;
		current = str[i];
		sprintf(c, "%c", current);
	}

	// when input string has been completely processed, pop all remaining operators from stack and append
	// them to end of output string
	while (isEmpty(operatorStack) != 1) {
		char* popped = pop(operatorStack);
		strcat(output, popped);
	}

	return output;
	
}


int calculateExpression(char* str) {
	//TODO
	return -1;
}


int main(int argc, char **argv) {
	printf("Entered here");
	
	if(argc<TWO) {
		printf(STR_INCORRECT_ARGUMENT);
	} else {

		char* postfix = convertToPostFix(argv[1]);
		int answer;
		printf("%s", postfix);
		//TODO CHANGE ABOVE!!
		
		// printf(STR_POSTFIX_EXPRESSION,postfix);
		printf(STR_RESULT,answer);
		// free(input);
		// free(postfix);
	}
	return EXIT_SUCCESS;
}
