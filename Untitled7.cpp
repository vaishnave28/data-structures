#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

// Function to check if parentheses are balanced
bool areParenthesesBalanced(char* expression) {
    struct Stack* stack = createStack(strlen(expression));
    
    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[') {
            push(stack, expression[i]);
        } else if (expression[i] == ')' || expression[i] == '}' || expression[i] == ']') {
            if (isEmpty(stack)) {
                return false;
            } else if ((expression[i] == ')' && stack->array[stack->top] == '(') ||
                       (expression[i] == '}' && stack->array[stack->top] == '{') ||
                       (expression[i] == ']' && stack->array[stack->top] == '[')) {
                pop(stack);
            } else {
                return false;
            }
        }
    }
    
    return isEmpty(stack);
}

// Driver program to test the above functions
int main() {
    char expression[100];
    printf("Enter an expression with parentheses: ");
    scanf("%s", expression);

    if (areParenthesesBalanced(expression)) {
        printf("The parentheses are balanced.\n");
    } else {
        printf("The parentheses are not balanced.\n");
    }

    return 0;
}

