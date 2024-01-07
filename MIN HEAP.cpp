#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

struct BinaryMinHeap {
    int heap[MAX_HEAP_SIZE];
    int size;
};


void insert(struct BinaryMinHeap *minHeap, int value);
int deleteMin(struct BinaryMinHeap *minHeap);
void display(struct BinaryMinHeap *minHeap);

int main() {
    struct BinaryMinHeap minHeap;
    minHeap.size = 0;

    int choice, value;

    do {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. DeleteMin\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(&minHeap, value);
                break;
            case 2:
                value = deleteMin(&minHeap);
                if (value != -1)
                    printf("Deleted Min Value: %d\n", value);
                else
                    printf("Heap is empty.\n");
                break;
            case 3:
                printf("Heap elements: ");
                display(&minHeap);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 4);

    return 0;
}

void insert(struct BinaryMinHeap *minHeap, int value) {
    if (minHeap->size == MAX_HEAP_SIZE) {
        printf("Heap is full. Cannot insert.\n");
        return;
    }

    int index = minHeap->size;
    minHeap->heap[index] = value;

    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (minHeap->heap[index] < minHeap->heap[parentIndex]) {
            
            int temp = minHeap->heap[index];
            minHeap->heap[index] = minHeap->heap[parentIndex];
            minHeap->heap[parentIndex] = temp;
        } else {
            break;
        }
        index = parentIndex;
    }

    minHeap->size++;
}

int deleteMin(struct BinaryMinHeap *minHeap) {
    if (minHeap->size == 0) {
       
        return -1;
    }

    int deletedValue = minHeap->heap[0];

    
    minHeap->heap[0] = minHeap->heap[minHeap->size - 1];
    minHeap->size--;

    
    int index = 0;
    while (1) {
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;
        int smallest = index;

        if (leftChildIndex < minHeap->size && minHeap->heap[leftChildIndex] < minHeap->heap[smallest]) {
            smallest = leftChildIndex;
        }

        if (rightChildIndex < minHeap->size && minHeap->heap[rightChildIndex] < minHeap->heap[smallest]) {
            smallest = rightChildIndex;
        }

        if (smallest != index) {
            
            int temp = minHeap->heap[index];
            minHeap->heap[index] = minHeap->heap[smallest];
            minHeap->heap[smallest] = temp;
            index = smallest;
        } else {
            break;
        }
    }

    return deletedValue;
}

void display(struct BinaryMinHeap *minHeap) {
    for (int i = 0; i < minHeap->size; i++) {
        printf("%d ", minHeap->heap[i]);
    }
    printf("\n");
}

