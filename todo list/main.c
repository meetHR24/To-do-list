#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a to-do item
struct TodoItem {
    char task[100];
    struct TodoItem* next;
};

// Function to add a new task to the to-do list
void addTask(struct TodoItem** head, const char* task) {
    struct TodoItem* newItem = (struct TodoItem*)malloc(sizeof(struct TodoItem));
    if (!newItem) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strncpy(newItem->task, task, sizeof(newItem->task) - 1);
    newItem->task[sizeof(newItem->task) - 1] = '\0';  // Ensure null-terminated string
    newItem->next = *head;
    *head = newItem;

    printf("Task added: %s\n", newItem->task);
}

// Function to display the to-do list
void displayTasks(struct TodoItem* head) {
    printf("To-Do List:\n");
    while (head != NULL) {
        printf("- %s\n", head->task);
        head = head->next;
    }
    printf("\n");
}

// Function to free the memory allocated for the to-do list
void freeList(struct TodoItem** head) {
    struct TodoItem* current = *head;
    struct TodoItem* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

int main() {
    struct TodoItem* todoList = NULL;
    int choice;
    char task[100];

    do {
        printf("1. Add Task\n");
        printf("2. Display Tasks\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the task: ");
                scanf(" %[^\n]s", task);
                addTask(&todoList, task);
                break;

            case 2:
                displayTasks(todoList);
                break;

            case 3:
                // Free memory before exiting
                freeList(&todoList);
                printf("Exiting program. Memory freed.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 3);

    return 0;
}
