// Online C compiler to run C program online#include <stdio.h>
#include <stdlib.h>



// Defining a structure for the queue node
struct QueueNode {
    int data;
    struct QueueNode* next;
};

// Defining a structure for the queue
struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
    int size;
};

// Function to initialize an empty queue
void initializeQueue(struct Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return (queue->size == 0);
}

// Function to enqueue/insert an element into the queue
void enqueue(struct Queue* queue, int element) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    if (newNode == NULL) {
        printf("Memory allocation failed. Queue is full.\n");
        return;
    }
    
    newNode->data = element;
    newNode->next = NULL;
    
    if (isEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    
    queue->size++;
    printf("Element %d enqueued successfully.\n", element);
}

// Function to delete/dequeue an element from the queue
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot delete.\n");
        return -1; // Returning a sentinel value indicating failure
    }
    
    struct QueueNode* temp = queue->front;
    int element = temp->data;
    
    queue->front = temp->next;
    free(temp);
    
    queue->size--;
    
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    
    return element;
}

// Function to print the elements of the queue
void printQueue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("The queue is empty.\n");
        return;
    }
    
    printf("Queue elements: ");
    struct QueueNode* current = queue->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to free the memory allocated for the queue
void freeQueue(struct Queue* queue) {
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
}

int main() {
    struct Queue myQueue;
    initializeQueue(&myQueue);
    
    int choice, element;
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. insert element\n");
        printf("2. Delete element\n");
        printf("3. Print \n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter the element to insert: ");
                scanf("%d", &element);
                enqueue(&myQueue, element);
                break;
            case 2:
                element = dequeue(&myQueue);
                if (element != -1) {
                    printf("Element %d deleted successfully.\n", element);
                }
                break;
            case 3:
                printQueue(&myQueue);
                break;
            case 4:
                freeQueue(&myQueue);
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }
    
    return 0;