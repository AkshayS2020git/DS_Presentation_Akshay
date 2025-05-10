#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    char from[50];
    char to[50];
    char arrival[10];
    char departure[10];
} Train;

int main() {
    Train* trains = NULL;
    int count = 0;
    int choice;

    while (1) {
        printf("\n--- Train Timetable Menu ---\n");
        printf("1. Add Train\n");
        printf("2. Delete Train by Number\n");
        printf("3. View All Trains\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            trains = realloc(trains, (count + 1) * sizeof(Train));
            printf("Enter Train Name: ");
            scanf("%s", trains[count].name);
            printf("From Station: ");
            scanf("%s", trains[count].from);
            printf("To Station: ");
            scanf("%s", trains[count].to);
            printf("Arrival Time: ");
            scanf("%s", trains[count].arrival);
            printf("Departure Time: ");
            scanf("%s", trains[count].departure);
            count++;
            printf("Train added.\n");
        }

        else if (choice == 2) {
            if (count == 0) {
                printf("No trains to delete.\n");
                continue;
            }
            int delIndex;
            printf("Enter train number to delete (1 to %d): ", count);
            scanf("%d", &delIndex);

            if (delIndex < 1 || delIndex > count) {
                printf("Invalid number.\n");
                continue;
            }

            for (int i = delIndex - 1; i < count - 1; i++) {
                trains[i] = trains[i + 1];
            }
            count--;
            trains = realloc(trains, count * sizeof(Train));
            printf("Train deleted.\n");
        }

        else if (choice == 3) {
            if (count == 0) {
                printf("No trains scheduled.\n");
                continue;
            }
            for (int i = 0; i < count; i++) {
                printf("\nTrain %d:\n", i + 1);
                printf("Name: %s\n", trains[i].name);
                printf("From: %s\n", trains[i].from);
                printf("To: %s\n", trains[i].to);
                printf("Arrival: %s\n", trains[i].arrival);
                printf("Departure: %s\n", trains[i].departure);
            }
        }

        else if (choice == 4) {
            free(trains);
            printf("Exiting.\n");
            break;
        }

        else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
