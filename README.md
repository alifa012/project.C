# Inventory Management System

## Overview

This project implements an **Inventory Management System** in C. The system enables users to manage items in an inventory, providing features like user registration, login, adding items, updating quantities, deleting items, exporting inventory data to CSV, and saving/loading inventory data.

## Features

### User Management
- **Registration**: New users can register with a username and password.
- **Login**: Registered users can log in using their credentials.

### Inventory Management
- **Add Items**: Add new items to the inventory with details such as name, quantity, and price.
- **Display Inventory**: View all items, along with their quantities and prices, in a tabular format.
- **Update Quantities**: Update the quantity of existing items.
- **Delete Items**: Remove items from the inventory.
- **Export to CSV**: Export inventory data to a CSV file.
- **Save & Load**: Save inventory data to a user-specific file and reload it upon login.

## File Structure

- `main.c`: The main source code file containing the implementation of the Inventory Management System.

## Usage

### Compilation
Compile the program using a C compiler:
```bash
gcc main.c -o inventory_management
```

### Running the Program
Run the compiled program:
```bash
./inventory_management
```

### Workflow
1. **User Registration/Login**: 
   - Choose to either register or log in.
   - User data is stored in a `users.txt` file.

2. **Inventory Operations**:
   - After logging in, you can:
     - Add items to the inventory.
     - View, update, or delete items.
     - Export inventory data to a CSV file.
     - Save and exit, which stores the inventory in a user-specific file.

3. **Data Persistence**:
   - Inventory data is saved in a file named `inventory_<username>.txt`.
   - Data can be reloaded by logging in as the same user.

## Dependencies
- **Standard C Libraries**:
  - `<stdio.h>`: For standard input and output operations.
  - `<stdlib.h>`: For memory management.
  - `<string.h>`: For string manipulation.
  - `<ctype.h>`: For character handling.

## Code Highlights

### Struct Definition
- `Item`: Represents an inventory item with attributes `name`, `quantity`, and `price`.

### Key Functions
- **User Management**:
  - `registerUser`: Registers a new user.
  - `loginUser`: Authenticates an existing user.
- **Inventory Operations**:
  - `addItem`: Adds a new item to the inventory.
  - `displayInventory`: Displays all inventory items.
  - `updateQuantity`: Updates the quantity of an item.
  - `deleteItem`: Deletes an item from the inventory.
  - `saveInventory`: Saves inventory to a file.
  - `loadInventory`: Loads inventory from a file.
  - `exportToCSV`: Exports inventory data to a CSV file.

### Menu
The program offers a menu-driven interface:
1. Add Item
2. Display Inventory
3. Update Quantity
4. Delete Item
5. Export to CSV
6. Save & Exit

## Example Output
```
Welcome to the Inventory Management System
1. Register
2. Login
Choice: 1
Enter a username: user1
Enter a password: pass123
User registered successfully.

--- MENU ---
1. Add Item
2. Display Inventory
3. Update Quantity
4. Delete Item
5. Export to CSV
6. Save & Exit
Choice:
```

## Contributing
If you would like to contribute, feel free to fork this repository, create a new branch, and submit a pull request.

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.
