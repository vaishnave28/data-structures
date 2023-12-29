
#include <stdio.h>
void printOddNumbersInOddIndices(int arr[], int size) {
    for (int i = 1; i < size; i += 2) {
        if (arr[i] % 2 != 0) {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Odd numbers in odd indices: ");
    printOddNumbersInOddIndices(arr, size);

    return 0;
}
