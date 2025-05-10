#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a game state
typedef struct GameState {
    int level;
    int score;
    char position[50];
} GameState;

// Stack node structure
typedef struct StackNode {
    GameState state;
    struct StackNode* next;
} StackNode;

// Stack structure
typedef struct Stack {
    StackNode* top;
} Stack;

// Create an empty stack
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

// Push a game state onto the stack
void saveState(Stack* stack, GameState state) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->state = state;
    newNode->next = stack->top;
    stack->top = newNode;
    printf("Game state saved.\n");
}

// Pop the last saved state
void undoLastSave(Stack* stack) {
    if (stack->top == NULL) {
        printf("No saved states to undo.\n");
        return;
    }
    StackNode* temp = stack->top;
    printf("Undoing last save: Level %d, Score %d, Position %s\n",
           temp->state.level, temp->state.score, temp->state.position);
    stack->top = stack->top->next;
    free(temp);
}

// Display the current (top) game state
void viewCurrentState(Stack* stack) {
    if (stack->top == NULL) {
        printf("No saved states available.\n");
    } else {
        GameState current = stack->top->state;
        printf("Current Save -> Level: %d | Score: %d | Position: %s\n",
               current.level, current.score, current.position);
    }
}

// Display all saved states
void viewAllStates(Stack* stack) {
    if (stack->top == NULL) {
        printf("No saved states in history.\n");
        return;
    }
    StackNode* temp = stack->top;
    int count = 1;
    printf("All Saved States (Most Recent to Oldest):\n");
    while (temp != NULL) {
        printf("%d. Level: %d | Score: %d | Position: %s\n",
               count++, temp->state.level, temp->state.score, temp->state.position);
        temp = temp->next;
    }
}

// Main function to simulate game state saving
int main() {
    Stack* gameHistory = createStack();
    int choice;
    GameState state;

    while (1) {
        printf("\n--- Game Save State Menu ---\n");
        printf("1. Save current state\n");
        printf("2. Undo last save\n");
        printf("3. View current state\n");
        printf("4. View all saved states\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                printf("Enter level: ");
                scanf("%d", &state.level);
                printf("Enter score: ");
                scanf("%d", &state.score);
                getchar(); // Consume newline
                printf("Enter position (e.g., X:5,Y:10): ");
                fgets(state.position, sizeof(state.position), stdin);
                state.position[strcspn(state.position, "\n")] = '\0'; // Remove newline
                saveState(gameHistory, state);
                break;

            case 2:
                undoLastSave(gameHistory);
                break;

            case 3:
                viewCurrentState(gameHistory);
                break;

            case 4:
                viewAllStates(gameHistory);
                break;

            case 5:
                printf("Exiting game save system.\n");
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
