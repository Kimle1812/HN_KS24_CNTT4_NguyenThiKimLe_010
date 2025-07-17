#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Browser {
    char ulr[100];
    char timestamp[30];
} Browser;

typedef struct Stack {
    Browser* browsers;
    int top;
    int capacity;
}Stack;

typedef struct Queue {
    Browser* browsers;
    int front;
    int rear;
    int capacity;
} Queue;

Stack *createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->browsers = (Browser*)malloc(sizeof(Browser) * stack->capacity);
    return stack;
}

Queue *createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = 0;
    queue->rear = -1;
    queue->capacity = capacity;
    queue->browsers = (Browser*)malloc(sizeof(Browser) * queue->capacity);
    return queue;
}
int isStackFull(Stack* stack) {
    if(stack->top == stack->capacity - 1) {
        return 1;
    }
    return 0;
}

int isQueueFull(Queue* queue) {
    if(queue->rear == queue->capacity - 1) {
        return 1;
    }
    return 0;
}
int isStackEmpty(Stack* stack) {
    if (stack->top == -1) {
        return 1;
    }
    return 0;
}
void push(Stack *stack, Browser browsers) {
    if(isStackFull(stack)) {
        printf("Stack is full\n");
        return;
    }
    stack->browsers[++stack->top] = browsers;
}

void showHistoryBrowser(Queue *queue) {
    if (queue->front > queue->rear) {
        printf("Queue empty\n");
        return;
    }
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("Ulr: %s\n", queue->browsers[i].ulr);
        printf("Timestamp: %s\n", queue->browsers[i].timestamp);
        printf("\n");
    }
}
Browser* pop(Stack *stack) {
    if(isStackEmpty(stack)) {
        printf("Stack is empty\n");
        return NULL;
    }
    Browser* browser = &stack->browsers[stack->top];
    stack->top--;
    return browser;
}

void enqueue(Queue* queue, Browser browser) {
    if(isQueueFull(queue)) {
        printf("Queue is full\n");
        return;
    }
    queue->browsers[++queue->rear] = browser;
}

int main() {
    int choice;
    Stack* backStack = createStack(10);
    Stack* forwardStack = createStack(10);
    Queue* historyBrowsers = createQueue(10);
    do {
        printf("===BROWSER HISTORY===\n");
        printf("1. CALL\n");
        printf("2. BACK\n");
        printf("3. FORWARD\n");
        printf("4. HISTORY\n");
        printf("5. EXIT\n");
        printf("Enter your choice:");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                Browser newBrowser;
                fflush(stdin);
                printf("Enter url: ");
                fgets(newBrowser.ulr, sizeof(newBrowser.ulr), stdin);
                newBrowser.ulr[strcspn(newBrowser.ulr, "\n")] = 0;
                fflush(stdin);
                printf("Enter timestamp: ");
                gets(newBrowser.timestamp);
                push(backStack, newBrowser);
                enqueue(historyBrowsers, newBrowser);
                break;
            case 2:
                Browser* backBrowser;
                backBrowser = pop(backStack);
                if(backBrowser == NULL) {
                    break;
                }
                push(forwardStack, *backBrowser);
                printf("Quay lai so truoc do thanh cong\n");
                break;
            case 3:
                Browser* forwardBrowser = pop(forwardStack);
                if(forwardBrowser == NULL) {
                    break;
                }
                push(backStack, *forwardBrowser);
                enqueue(historyBrowsers, *forwardBrowser);
                break;
            case 4:
                showHistoryBrowser(historyBrowsers);
                break;
            case 5:
                printf("EXIT\n");
                break;
        }
    }while (choice != 5);
    return 0;
}