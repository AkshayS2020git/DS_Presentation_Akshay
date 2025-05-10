#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SLOTS 10
#define PLATE_LEN 15

char parkingLot[MAX_SLOTS][PLATE_LEN];  // Array for parking slots

void initialize() {
    for (int i = 0; i < MAX_SLOTS; i++) {
        strcpy(parkingLot[i], ""); // Empty all slots
    }
}

void displaySlots() {
    printf("\n--- Parking Lot Status ---\n");
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (strlen(parkingLot[i]) == 0)
            printf("Slot %d: Empty\n", i);
        else
            printf("Slot %d: %s\n", i, parkingLot[i]);
    }
}

void parkVehicle() {
    char plate[PLATE_LEN];
    printf("Enter vehicle plate number: ");
    scanf("%s", plate);

    for (int i = 0; i < MAX_SLOTS; i++) {
        if (strlen(parkingLot[i]) == 0) {
            strcpy(parkingLot[i], plate);
            printf("Vehicle %s parked at slot %d\n", plate, i);
            return;
        }
    }
    printf("Parking is full!\n");
}

void leaveSlot() {
    int slot;
    printf("Enter slot number to free: ");
    scanf("%d", &slot);

    if (slot < 0 || slot >= MAX_SLOTS) {
        printf("Invalid slot number!\n");
        return;
    }

    if (strlen(parkingLot[slot]) == 0) {
        printf("Slot %d is already empty.\n", slot);
    } else {
        printf("Vehicle %s left from slot %d\n", parkingLot[slot], slot);
        strcpy(parkingLot[slot], "");
    }
}

void findVehicle() {
    char plate[PLATE_LEN];
    printf("Enter vehicle plate number to search: ");
    scanf("%s", plate);

    for (int i = 0; i < MAX_SLOTS; i++) {
        if (strcmp(parkingLot[i], plate) == 0) {
            printf("Vehicle %s is parked at slot %d\n", plate, i);
            return;
        }
    }
    printf("Vehicle %s not found in the parking lot.\n", plate);
}

int main() {
    int choice;
    initialize();

    do {
        printf("\n--- Parking Lot Menu ---\n");
        printf("1. Park Vehicle\n");
        printf("2. Remove Vehicle (Leave Slot)\n");
        printf("3. Find Vehicle\n");
        printf("4. Display Parking Lot\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: parkVehicle(); break;
            case 2: leaveSlot(); break;
            case 3: findVehicle(); break;
            case 4: displaySlots(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}
