#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------------------------
// Struct for User
typedef struct {
    int id;
    char name[50];
    float balance;
} User;

// -------------------------------
// Function to create a user (using double pointer)
void createUser(User **user, int id, const char *name, float balance) {
    *user = (User *)malloc(sizeof(User));
    (*user)->id = id;
    strncpy((*user)->name, name, sizeof((*user)->name));
    (*user)->balance = balance;
}

// -------------------------------
// Function to print user (by value)
void printUser(User u) {
    printf("User[%d]: %s ($%.2f)\n", u.id, u.name, u.balance);
}

// -------------------------------
// Modify balance using pointer
void updateBalance(User *user, float delta) {
    user->balance += delta;
}

// -------------------------------
// Apply function to all users (function pointer)
void applyToAll(User **users, int count, void (*func)(User *)) {
    for (int i = 0; i < count; i++) {
        func(users[i]);
    }
}

// Example function for applyToAll
void giveBonus(User *u) {
    u->balance += 10.0f;
}

// -------------------------------
// Generic print function using void*
void printRaw(void *data, char type) {
    switch (type) {
        case 'u': {
            User *u = (User *)data;
            printf("[RAW] %s -> $%.2f\n", u->name, u->balance);
            break;
        }
    }
}

// -------------------------------
// Main program
int main() {
    User *users[3];

    createUser(&users[0], 1, "Alice", 120.5f);
    createUser(&users[1], 2, "Bob", 80.0f);
    createUser(&users[2], 3, "Charlie", 95.25f);

    // Print users (by value)
    for (int i = 0; i < 3; i++) {
        printUser(*users[i]);
    }

    // Update Bob's balance (by pointer)
    updateBalance(users[1], 50.0f);
    printUser(*users[1]);

    // Apply bonus to all users (function pointer)
    applyToAll(users, 3, giveBonus);

    // Print again using void pointer
    for (int i = 0; i < 3; i++) {
        printRaw(users[i], 'u');
    }

    // Cleanup
    for (int i = 0; i < 3; i++) {
        free(users[i]);
    }

    return 0;
}

