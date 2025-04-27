#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    int quantity;
    float price;
} Item;

void addItem(Item inventory[], int *count);
void displayInventory(Item inventory[], int count);
void updateQuantity(Item inventory[], int count);
void deleteItem(Item inventory[], int *count);
void saveInventory(Item inventory[], int count);
void loadInventory(Item inventory[], int *count);

int main() {
    Item inventory[MAX_ITEMS];
    int count = 0;
    int choice;

    loadInventory(inventory, &count);

    while (1) {
        printf("\nInventory Management System\n");
        printf("1. Add Item\n");
        printf("2. Display Inventory\n");
        printf("3. Update Quantity\n");
        printf("4. Delete Item\n");
        printf("5. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addItem(inventory, &count);
                break;
            case 2:
                displayInventory(inventory, count);
                break;
            case 3:
                updateQuantity(inventory, count);
                break;
            case 4:
                deleteItem(inventory, &count);
                break;
            case 5:
                saveInventory(inventory, count);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void addItem(Item inventory[], int *count) {
    if (*count >= MAX_ITEMS) {
        printf("Inventory is full. Cannot add more items.\n");
        return;
    }

    printf("Enter item name: ");
    scanf("%s", inventory[*count].name);
    printf("Enter quantity: ");
    scanf("%d", &inventory[*count].quantity);
    printf("Enter price: ");
    scanf("%f", &inventory[*count].price);

    (*count)++;
    printf("Item added successfully.\n");
}

void displayInventory(Item inventory[], int count) {
    if (count == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    printf("\nCurrent Inventory:\n");
    printf("Name\t\tQuantity\tPrice\n");
    for (int i = 0; i < count; i++) {
        printf("%s\t\t%d\t\t%.2f\n", inventory[i].name, inventory[i].quantity, inventory[i].price);
    }
}

void updateQuantity(Item inventory[], int count) {
    char name[MAX_NAME_LENGTH];
    int quantity;
    int found = 0;

    printf("Enter item name to update quantity: ");
    scanf("%s", name);
    printf("Enter new quantity: ");
    scanf("%d", &quantity);

    for (int i = 0; i < count; i++) {
        if (strcmp(inventory[i].name, name) == 0) {
            inventory[i].quantity = quantity;
            found = 1;
            printf("Quantity updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Item not found in inventory.\n");
    }
}

void deleteItem(Item inventory[], int *count) {
    char name[MAX_NAME_LENGTH];
    int found = 0;

    printf("Enter item name to delete: ");
    scanf("%s", name);

    for (int i = 0; i < *count; i++) {
        if (strcmp(inventory[i].name, name) == 0) {
            found = 1;
            // Shift all items after the deleted item to the left
            for (int j = i; j < *count - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            (*count)--;
            printf("Item deleted successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Item not found in inventory.\n");
    }
}

void saveInventory(Item inventory[], int count) {
    FILE *file = fopen("inventory.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d %.2f\n", inventory[i].name, inventory[i].quantity, inventory[i].price);
    }

    fclose(file);
    printf("Inventory saved to file.\n");
}

void loadInventory(Item inventory[], int *count) {
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf("No existing inventory file found.\n");
        return;
    }
    *count = 0;
    while (fscanf(file, "%s %d %f", inventory[*count].name, &inventory[*count].quantity, &inventory[*count].price) != EOF) {
        (*count)++;
    }

    fclose(file);
    printf("Inventory loaded from file.\n");
    printf("////");
}
    