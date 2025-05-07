#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ITEMS 100
#define MAX_NAME_LENGTH 50
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    int quantity;
    float price;
} Item;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void trimNewline(char *str) {
    str[strcspn(str, "\n")] = 0;
}

int isValidName(const char *name) {
    for (int i = 0; name[i]; i++) {
        if (!isalnum(name[i]) && name[i] != ' ' && name[i] != '_')
            return 0;
    }
    return 1;
}

int registerUser(char *username) {
    char password[MAX_PASSWORD_LENGTH];
    FILE *file = fopen("users.txt", "a+");
    if (!file) {
        printf("Unable to open users file.\n");
        return 0;
    }

    printf("Enter a username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    trimNewline(username);

    printf("Enter a password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    trimNewline(password);

    fprintf(file, "%s %s\n", username, password);
    fclose(file);
    printf("User registered successfully.\n");
    return 1;
}

int loginUser(char *username) {
    char password[MAX_PASSWORD_LENGTH], user[MAX_USERNAME_LENGTH], pass[MAX_PASSWORD_LENGTH];
    FILE *file = fopen("users.txt", "r");
    if (!file) {
        printf("No registered users found.\n");
        return 0;
    }

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    trimNewline(username);

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    trimNewline(password);

    while (fscanf(file, "%s %s", user, pass) != EOF) {
        if (strcmp(username, user) == 0 && strcmp(password, pass) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    printf("Invalid credentials.\n");
    return 0;
}

void addItem(Item inventory[], int *count) {
    if (*count >= MAX_ITEMS) {
        printf("Inventory is full.\n");
        return;
    }

    Item newItem;
    printf("Enter item name: ");
    fgets(newItem.name, MAX_NAME_LENGTH, stdin);
    trimNewline(newItem.name);

    if (!isValidName(newItem.name)) {
        printf("Invalid name. Use alphanumeric, spaces or underscores only.\n");
        return;
    }

    printf("Enter quantity: ");
    scanf("%d", &newItem.quantity);
    clearInputBuffer();

    printf("Enter price: ");
    scanf("%f", &newItem.price);
    clearInputBuffer();

    inventory[*count] = newItem;
    (*count)++;
    printf("Item added successfully.\n");
}

void displayInventory(Item inventory[], int count) {
    if (count == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    printf("\n%-20s %-10s %-10s\n", "Name", "Quantity", "Price");
    printf("---------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-20s %-10d $%-10.2f\n", inventory[i].name, inventory[i].quantity, inventory[i].price);
    }
}

void updateQuantity(Item inventory[], int count) {
    char name[MAX_NAME_LENGTH];
    int found = 0, quantity;

    printf("Enter item name to update: ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    trimNewline(name);

    for (int i = 0; i < count; i++) {
        if (strcmp(inventory[i].name, name) == 0) {
            printf("Enter new quantity: ");
            scanf("%d", &quantity);
            clearInputBuffer();

            inventory[i].quantity = quantity;
            printf("Quantity updated.\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("Item not found.\n");
}

void deleteItem(Item inventory[], int *count) {
    char name[MAX_NAME_LENGTH];
    int found = 0;

    printf("Enter item name to delete: ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    trimNewline(name);

    for (int i = 0; i < *count; i++) {
        if (strcmp(inventory[i].name, name) == 0) {
            for (int j = i; j < *count - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            (*count)--;
            printf("Item deleted.\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("Item not found.\n");
}

void saveInventory(Item inventory[], int count, const char *username) {
    char filename[100];
    sprintf(filename, "inventory_%s.txt", username);
    FILE *file = fopen(filename, "w");

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d %.2f\n", inventory[i].name, inventory[i].quantity, inventory[i].price);
    }

    fclose(file);
    printf("Inventory saved.\n");
}

void loadInventory(Item inventory[], int *count, const char *username) {
    char filename[100];
    sprintf(filename, "inventory_%s.txt", username);
    FILE *file = fopen(filename, "r");
    *count = 0;

    if (file) {
        while (fscanf(file, "%s %d %f", inventory[*count].name, &inventory[*count].quantity, &inventory[*count].price) != EOF) {
            (*count)++;
        }
        fclose(file);
    }
}

void exportToCSV(Item inventory[], int count, const char *username) {
    char filename[100];
    sprintf(filename, "inventory_%s.csv", username);
    FILE *file = fopen(filename, "w");

    if (!file) {
        printf("Error exporting file.\n");
        return;
    }

    fprintf(file, "Name,Quantity,Price\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%d,%.2f\n", inventory[i].name, inventory[i].quantity, inventory[i].price);
    }

    fclose(file);
    printf("Inventory exported to CSV.\n");
}

int main() {
    Item inventory[MAX_ITEMS];
    int count = 0;
    int choice;
    char username[MAX_USERNAME_LENGTH];

    printf("Welcome to the Inventory Management System\n");
    printf("1. Register\n2. Login\nChoice: ");
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice == 1) {
        if (!registerUser(username)) return 1;
    } else if (choice == 2) {
        if (!loginUser(username)) return 1;
    } else {
        printf("Invalid choice.\n");
        return 1;
    }

    loadInventory(inventory, &count, username);

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Add Item\n2. Display Inventory\n3. Update Quantity\n4. Delete Item\n5. Export to CSV\n6. Save & Exit\nChoice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: addItem(inventory, &count); break;
            case 2: displayInventory(inventory, count); break;
            case 3: updateQuantity(inventory, count); break;
            case 4: deleteItem(inventory, &count); break;
            case 5: exportToCSV(inventory, count, username); break;
            case 6:
                saveInventory(inventory, count, username);
                printf("Goodbye, %s!\n", username);
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}
