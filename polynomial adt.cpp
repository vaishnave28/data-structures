#include <stdio.h>
#include <stdlib.h>
// Node structure for a term in a polynomial
struct Node {
    int coefficient;
    int exponent;
    struct Node* next;
};
// Polynomial structure
struct Polynomial {
    struct Node* head;
};
// Function to create a new node
struct Node* createNode(int coefficient, int exponent) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->coefficient = coefficient;
    newNode->exponent = exponent;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize an empty polynomial
void initializePolynomial(struct Polynomial* polynomial) {
    polynomial->head = NULL;
}

// Function to insert a term into a polynomial
void insertTerm(struct Polynomial* polynomial, int coefficient, int exponent) {
    struct Node* newNode = createNode(coefficient, exponent);

    if (polynomial->head == NULL || exponent > polynomial->head->exponent) {
        newNode->next = polynomial->head;
        polynomial->head = newNode;
    } else {
        struct Node* current = polynomial->head;
        while (current->next != NULL && current->next->exponent > exponent) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to add two polynomials
struct Polynomial addPolynomials(struct Polynomial poly1, struct Polynomial poly2) {
    struct Polynomial result;
    initializePolynomial(&result);

    struct Node *ptr1 = poly1.head, *ptr2 = poly2.head;

    while (ptr1 != NULL && ptr2 != NULL) {
        if (ptr1->exponent > ptr2->exponent) {
            insertTerm(&result, ptr1->coefficient, ptr1->exponent);
            ptr1 = ptr1->next;
        } else if (ptr1->exponent < ptr2->exponent) {
            insertTerm(&result, ptr2->coefficient, ptr2->exponent);
            ptr2 = ptr2->next;
        } else {
            // Add coefficients for the same exponent
            insertTerm(&result, ptr1->coefficient + ptr2->coefficient, ptr1->exponent);
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    }

    // Add remaining terms from poly1
    while (ptr1 != NULL) {
        insertTerm(&result, ptr1->coefficient, ptr1->exponent);
        ptr1 = ptr1->next;
    }

    // Add remaining terms from poly2
    while (ptr2 != NULL) {
        insertTerm(&result, ptr2->coefficient, ptr2->exponent);
        ptr2 = ptr2->next;
    }

    return result;
}

// Function to display a polynomial
void displayPolynomial(struct Polynomial polynomial) {
    struct Node* current = polynomial.head;

    while (current != NULL) {
        printf("%dx^%d ", current->coefficient, current->exponent);
        if (current->next != NULL) {
            printf("+ ");
        }
        current = current->next;
    }

    printf("\n");
}

// Function to display the menu
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Add Polynomials\n");
    printf("2. Exit\n");
    printf("Enter your choice: ");
}

// Main function with the menu-driven interface
int main() {
    struct Polynomial poly1, poly2, result;
    initializePolynomial(&poly1);
    initializePolynomial(&poly2);
    initializePolynomial(&result);

    int choice, coefficient, exponent;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the first polynomial:\n");
                printf("Enter coefficient (0 to end): ");
                scanf("%d", &coefficient);

                while (coefficient != 0) {
                    printf("Enter exponent: ");
                    scanf("%d", &exponent);
                    insertTerm(&poly1, coefficient, exponent);
                    printf("Enter coefficient (0 to end): ");
                    scanf("%d", &coefficient);
                }

                printf("Enter the second polynomial:\n");
                printf("Enter coefficient (0 to end): ");
                scanf("%d", &coefficient);

                while (coefficient != 0) {
                    printf("Enter exponent: ");
                    scanf("%d", &exponent);
                    insertTerm(&poly2, coefficient, exponent);
                    printf("Enter coefficient (0 to end): ");
                    scanf("%d", &coefficient);
                }

                result = addPolynomials(poly1, poly2);

                printf("Resultant Polynomial: ");
                displayPolynomial(result);
                break;

            case 2:
                printf("Exiting program\n");
                break;

            default:
                printf("Invalid choice, please try again\n");
        }
    } while (choice != 2);

    return 0;
}
