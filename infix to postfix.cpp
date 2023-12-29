#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Structure to represent a stack
struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

// Function to create a stack of given capacity
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Function to check if the stack is full
bool isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Function to check if the stack is empty
bool isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(struct Stack* stack, char item) {
    if (isFull(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->array[++stack->top] = item;
}

// Function to pop an element from the stack
char pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return '\0';
    }
    return stack->array[stack->top--];
}

// Function to get the precedence of an operator
int getPrecedence(char operator) {
    if (operator == '^') return 3;
    else if (operator == '*' || operator == '/') return 2;
    else if (operator == '+' || operator == '-') return 1;
    else return 0;  // for '('
}

// Function to convert infix expression to postfix
void infixToPostfix(char* infixExpression) {
    struct Stack* stack = createStack(strlen(infixExpression));
    char postfixExpression[strlen(infixExpression) + 1];
    int i, j;
    i = j = 0;

    while (infixExpression[i] != '\0') {
        char currentChar = infixExpression[i];

        if ((currentChar >= 'a' && currentChar <= 'z') || (currentChar >= 'A' && currentChar <= 'Z')) {
            postfixExpression[j++] = currentChar;
        } else if (currentChar == '(') {
            push(stack, currentChar);
        } else if (currentChar == ')') {
            while (!isEmpty(stack) && stack->array[stack->top] != '(') {
                postfixExpression[j++] = pop(stack);
            }
            pop(stack);  // Pop '(' from the stack
        } else {
            while (!isEmpty(stack) && getPrecedence(currentChar) <= getPrecedence(stack->array[stack->top])) {
                postfixExpression[j++] = pop(stack);
            }
            push(stack, currentChar);
        }

        i++;
    }

    while (!isEmpty(stack)) {
        postfixExpression[j++] = pop(stack);
    }

    postfixExpression[j] = '\0';

    printf("Postfix Expression: %s\n", postfixExpression);

    // Free the dynamically allocated memory for the stack
    free(stack->array);
    free(stack);
}

// Driver program to test the above functions
int main() {
    char infixExpression[100];
    printf("Enter an infix expression: ");
    scanf("%s", infixExpression);

    infixToPostfix(infixExpression);

    return 0;
}

