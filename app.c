#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Task {
    char *task;
    int completed;
};

struct Task *tasks = NULL;
int len = 0;

void addTask(const char *task) {
    tasks = (struct Task *)realloc(tasks, (len + 1) * sizeof(struct Task));
    tasks[len].task = (char *)malloc(strlen(task) + 1);
    strcpy(tasks[len].task, task);
    tasks[len].completed = 0;
    len++;
    printf("Task added!\n");
}

void listTasks() {
    char status;
    for (int i = 0; i < len; i++) {
        if (tasks[i].completed == 1) {
            status = 'X';
        } else {
            status = ' ';
        }
        printf(" [%c] %d. %s\n",status, i + 1, tasks[i].task);
    }
}

void markCompleted(int index) {
    if (index <= len && index > 0) {
        tasks[index - 1].completed = 1;
        printf("Task marked as completed\n");
    } else {
        printf("Invalid Index\n");
    }
}

void deleteTask(int index) {
    if (index <= len && index > 0) {
        index = index - 1;
        free(tasks[index].task);
        for (int i = index; i < len - 1; i++) {
            tasks[i] = tasks[i + 1];
        }
        len--;
        tasks = (struct Task *)realloc(tasks, len * sizeof(struct Task));
    } else {
        printf("Invalid Index\n");
    }
}

void editTask(int index, const char *task) {
    if (index <= len && index > 0) {
        index = index - 1;
        char *editedTask = (char *)realloc(tasks[index].task, strlen(task) + 1);
        if (editedTask != NULL) {
            tasks[index].task = editedTask;
            strcpy(tasks[index].task, task);
            printf("Task edited!\n");
        } else {
            printf("Memory allocation failed\n");
        }
    } else {
        printf("Invalid Index\n");
    }
}

int main(void) {
    int running = 1;
    char *taskInput = (char *)malloc(100 * sizeof(char));
    int choice;
    int indexInput;

    printf("To-Do\n");
    printf("********************************\n");
    printf("1 = Add Task\n");
    printf("2 = List all tasks\n");
    printf("3 = Mark as completed\n");
    printf("4 = Edit task\n");
    printf("5 = Delete task\n");
    printf("6 = Exit\n");

    while (running) {
        printf("Enter 1-6 -> ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter task: ");
                getchar();
                fgets(taskInput, 100, stdin); 
                taskInput[strcspn(taskInput, "\n")] = '\0';
                addTask(taskInput);
                break;
            case 2:
                listTasks();
                break;
            case 3:
                printf("Enter index: ");
                scanf("%d", &indexInput);
                markCompleted(indexInput);
                break;
            case 4:
                printf("Enter Index: ");
                scanf("%d", &indexInput);
                printf("Edit: ");
                getchar();
                fgets(taskInput, 100, stdin);
                taskInput[strcspn(taskInput, "\n")] = '\0';
                editTask(indexInput, taskInput);
                break;
            case 5:
                printf("Enter Index: ");
                scanf("%d", &indexInput);
                deleteTask(indexInput);
                break;
            case 6:
                running = 0;
                break;
            default:
                printf("Invalid Choice");
                break;
        }
    }

    free(taskInput);
    free(tasks);

    printf("********************************\n");
    return 0;
}

