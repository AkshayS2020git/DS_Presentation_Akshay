#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5
#define NAME_LEN 30

typedef struct {
    int orderId;
    char customerName[NAME_LEN];
} Order;

typedef struct {
    Order orders[MAX];
    int front;
    int rear;
} OrderQueue;

void initialize(OrderQueue* q) {
    q->front = -1;
    q->rear = -1;
}

int isFull(OrderQueue* q) {
    return (q->rear == MAX - 1);
}

int isEmpty(OrderQueue* q) {
    return (q->front == -1 || q->front > q->rear);
}

void enqueue(OrderQueue* q, int orderId, const char* name) {
    if (isFull(q)) {
        printf("Order queue is full. Cannot take more orders.\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear++;
    q->orders[q->rear].orderId = orderId;
    strcpy(q->orders[q->rear].customerName, name);
    printf("Order %d by %s added to the queue.\n", orderId, name);
}

void dequeue(OrderQueue* q) {
    if (isEmpty(q)) {
        printf("No orders to serve.\n");
        return;
    }
    printf("Serving Order %d for %s\n", q->orders[q->front].orderId, q->orders[q->front].customerName);
    q->front++;
}

void display(OrderQueue* q) {
    if (isEmpty(q)) {
        printf("Order queue is empty.\n");
        return;
    }
    printf("\nCurrent Orders in Queue:\n");
    for (int i = q->front; i <= q->rear; i++) {
        printf("Order ID: %d | Customer: %s\n", q->orders[i].orderId, q->orders[i].customerName);
    }
}

int main() {
    OrderQueue queue;
    initialize(&queue);

    int choice, orderId = 1;
    char name[NAME_LEN];

    do {
        printf("\n--- Restaurant Order Queue ---\n");
        printf("1. Add Order\n2. Serve Order\n3. View Orders\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                printf("Enter customer name: ");
                fgets(name, NAME_LEN, stdin);
                name[strcspn(name, "\n")] = '\0';  // Remove trailing newline
                enqueue(&queue, orderId++, name);
                break;
            case 2:
                dequeue(&queue);
                break;
            case 3:
                display(&queue);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);

    return 0;
}
