#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5  // Maximum number of planes in the queue

// Define a structure to hold plane details
typedef struct {
    char planeName[50];
    int priority;  // 1 for landing (high), 2 for takeoff (low)
} Plane;

// Queue structure for runway management
typedef struct {
    Plane queue[MAX];
    int front;
    int rear;
} RunwayQueue;

// Initialize the queue
void initQueue(RunwayQueue* rq) {
    rq->front = -1;
    rq->rear = -1;
}

// Check if the queue is full
int isFull(RunwayQueue* rq) {
    return rq->rear == MAX - 1;
}

// Check if the queue is empty
int isEmpty(RunwayQueue* rq) {
    return rq->front == -1;
}

// Add a plane to the queue (for landing or takeoff)
void enqueue(RunwayQueue* rq, char* planeName, int priority) {
    if (isFull(rq)) {
        printf("Queue is full! Cannot add more planes.\n");
        return;
    }
    
    Plane newPlane;
    strcpy(newPlane.planeName, planeName);
    newPlane.priority = priority;
    
    if (rq->front == -1) {  // Queue is empty
        rq->front = 0;
    }
    rq->rear++;
    rq->queue[rq->rear] = newPlane;
    printf("Plane %s added to the queue.\n", planeName);
}

// Remove a plane from the queue (process landing or takeoff)
void dequeue(RunwayQueue* rq) {
    if (isEmpty(rq)) {
        printf("No planes in the queue.\n");
        return;
    }
    
    // Find the plane with the highest priority (landing first)
    int highestPriorityIndex = rq->front;
    for (int i = rq->front + 1; i <= rq->rear; i++) {
        if (rq->queue[i].priority < rq->queue[highestPriorityIndex].priority) {
            highestPriorityIndex = i;
        }
    }

    printf("Plane %s is processed for %s.\n",
        rq->queue[highestPriorityIndex].planeName,
        rq->queue[highestPriorityIndex].priority == 1 ? "Landing" : "Takeoff");

    // Shift all elements to fill the space
    for (int i = highestPriorityIndex; i < rq->rear; i++) {
        rq->queue[i] = rq->queue[i + 1];
    }

    rq->rear--;
    if (rq->rear == -1) {
        rq->front = -1;
    }
}

// View all planes in the queue
void viewQueue(RunwayQueue* rq) {
    if (isEmpty(rq)) {
        printf("No planes in the queue.\n");
        return;
    }

    printf("\n--- Current Planes in the Queue ---\n");
    for (int i = rq->front; i <= rq->rear; i++) {
        printf("Plane %s (Priority %d)\n", rq->queue[i].planeName, rq->queue[i].priority);
    }
}

int main() {
    RunwayQueue rq;
    initQueue(&rq);
    
    int choice;
    char planeName[50];
    int priority;

    while (1) {
        printf("\n--- Airport Ground System ---\n");
        printf("1. Add Plane to Queue\n");
        printf("2. Process Plane (Landing/Takeoff)\n");
        printf("3. View Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter plane name: ");
                getchar();  // Clear the buffer
                fgets(planeName, sizeof(planeName), stdin);
                planeName[strcspn(planeName, "\n")] = '\0'; // Remove newline

                printf("Enter priority (1 for landing, 2 for takeoff): ");
                scanf("%d", &priority);

                enqueue(&rq, planeName, priority);
                break;
            case 2:
                dequeue(&rq);
                break;
            case 3:
                viewQueue(&rq);
                break;
            case 4:
                printf("Exiting system...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
