#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Employee {
    int id;
    char name[100];
    char position[100];
    char salary[100]; // Lưu lương dưới dạng chuỗi
} Employee;

typedef struct SingleNode {
    Employee employee;
    struct SingleNode* next;
} SingleNode;

typedef struct DoubleNode {
    Employee employee;
    struct DoubleNode* prev;
    struct DoubleNode* next;
} DoubleNode;

int autoId = 1;

int isNameUnique(SingleNode *head, char name[]) {
    SingleNode *current = head;
    while (current) {
        if (strcasecmp(current->employee.name, name) == 0) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

SingleNode* createSingleNode(Employee employee) {
    SingleNode* newNode = (SingleNode*)malloc(sizeof(SingleNode));
    newNode->employee = employee;
    newNode->next = NULL;
    return newNode;
}

DoubleNode* createDoubleNode(Employee employee) {
    DoubleNode* newNode = (DoubleNode*)malloc(sizeof(DoubleNode));
    newNode->employee = employee;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

SingleNode* insertSingleNodeAtEnd(SingleNode *head, Employee employee) {
    SingleNode *newNode = createSingleNode(employee);
    if (head == NULL) return newNode;

    SingleNode *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}

DoubleNode* insertDoubleNodeAtEnd(DoubleNode *head, Employee employee) {
    DoubleNode *newNode = createDoubleNode(employee);
    if (head == NULL) return newNode;

    DoubleNode *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
    return head;
}

void printSingleList(SingleNode *head) {
    if (head == NULL) {
        printf("Danh sach rong\n");
        return;
    }
    SingleNode *current = head;
    while (current) {
        printf("Id: %d\n", current->employee.id);
        printf("Name: %s\n", current->employee.name);
        printf("Position: %s\n", current->employee.position);
        printf("Salary: %s\n", current->employee.salary);
        current = current->next;
    }
}

void printDoubleList(DoubleNode *head) {
    if (head == NULL) {
        printf("Danh sach rong\n");
        return;
    }
    DoubleNode *current = head;
    while (current) {
        printf("Id: %d\n", current->employee.id);
        printf("Name: %s\n", current->employee.name);
        printf("Position: %s\n", current->employee.position);
        printf("Salary: %s\n", current->employee.salary);
        current = current->next;
    }
}

SingleNode* deleteSingleNodeById(SingleNode *head, int id) {
    if (head == NULL) {
        printf("Danh sach trong\n");
        return head;
    }
    SingleNode *current = head, *prev = NULL;
    while (current && current->employee.id != id) {
        prev = current;
        current = current->next;
    }
    if (!current) {
        printf("Khong tim thay id\n");
        return head;
    }
    if (current == head) {
        head = head->next;
    } else {
        prev->next = current->next;
    }
    free(current);
    return head;
}

SingleNode* findSingleNodeById(SingleNode *head, int id) {
    while (head && head->employee.id != id) {
        head = head->next;
    }
    return head;
}

SingleNode* findSingleNodeByName(SingleNode *head, char name[]) {
    while (head && strcasecmp(head->employee.name, name) != 0) {
        head = head->next;
    }
    return head;
}

SingleNode* sortBySalary(SingleNode *head) {
    if (!head || !head->next) return head;
    for (SingleNode *i = head; i != NULL; i = i->next) {
        for (SingleNode *j = head; j->next != NULL; j = j->next) {
            if (atoi(j->employee.salary) > atoi(j->next->employee.salary)) {
                Employee temp = j->employee;
                j->employee = j->next->employee;
                j->next->employee = temp;
            }
        }
    }
    return head;
}

void updateEmployeeById(SingleNode *head, int id) {
    char newName[100];
    SingleNode *current = findSingleNodeById(head, id);
    if (!current) {
        printf("Khong tim thay id\n");
        return;
    }
    printf("Id: %d\n", current->employee.id);
    printf("Ten cu: %s\n", current->employee.name);
    printf("Chuc vu cu: %s\n", current->employee.position);
    printf("Muc luong cu: %s\n", current->employee.salary);

    do {
        printf("Nhap ten moi: ");
        fgets(newName, sizeof(newName), stdin);
        newName[strcspn(newName, "\n")] = 0;
        if (!isNameUnique(head, newName) && strcasecmp(current->employee.name, newName) != 0) {
            printf("Ten bi trung! Vui long nhap lai.\n");
        } else {
            strcpy(current->employee.name, newName);
            break;
        }
    } while (1);

    printf("Chuc vu moi: ");
    fgets(current->employee.position, sizeof(current->employee.position), stdin);
    current->employee.position[strcspn(current->employee.position, "\n")] = 0;

    printf("Muc luong moi: ");
    fgets(current->employee.salary, sizeof(current->employee.salary), stdin);
    current->employee.salary[strcspn(current->employee.salary, "\n")] = 0;
}

int main() {
    int choice;
    SingleNode *SingleHead = NULL;
    DoubleNode *DoubleHead = NULL;

    do {
        printf("\n======MENU======\n");
        printf("1. Them nhan vien\n");
        printf("2. Hien thi danh sach nhan vien dang lam viec\n");
        printf("3. Xoa nhan vien theo ID\n");
        printf("4. Cap nhat thong tin nhan vien\n");
        printf("5. Danh dau nhan vien da nghi viec\n");
        printf("6. Hien thi danh sach nhan vien da nghi viec\n");
        printf("7. Sap xep nhan vien theo luong\n");
        printf("8. Tim kiem nhan vien theo ten\n");
        printf("9. Thoat chuong trinh\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: {
                Employee newEmployee;
                char name[100];
                newEmployee.id = autoId++;

                do {
                    printf("Nhap ten nhan vien: ");
                    fgets(name, sizeof(name), stdin);
                    name[strcspn(name, "\n")] = 0;
                    if (!isNameUnique(SingleHead, name)) {
                        printf("Ten bi trung! Vui long nhap lai.\n");
                    } else {
                        strcpy(newEmployee.name, name);
                        break;
                    }
                } while (1);

                printf("Nhap chuc vu: ");
                fgets(newEmployee.position, sizeof(newEmployee.position), stdin);
                newEmployee.position[strcspn(newEmployee.position, "\n")] = 0;

                printf("Nhap luong: ");
                fgets(newEmployee.salary, sizeof(newEmployee.salary), stdin);
                newEmployee.salary[strcspn(newEmployee.salary, "\n")] = 0;

                SingleHead = insertSingleNodeAtEnd(SingleHead, newEmployee);
                break;
            }
            case 2:
                printSingleList(SingleHead);
                break;
            case 3: {
                int deleteId;
                printf("Nhap id nhan vien muon xoa: ");
                scanf("%d", &deleteId);
                getchar();
                SingleHead = deleteSingleNodeById(SingleHead, deleteId);
                break;
            }
            case 4: {
                int updateId;
                printf("Nhap id nhan vien muon cap nhat: ");
                scanf("%d", &updateId);
                getchar();
                updateEmployeeById(SingleHead, updateId);
                break;
            }
            case 5: {
                int finishId;
                printf("Nhap id nhan vien da nghi viec: ");
                scanf("%d", &finishId);
                getchar();

                SingleNode *finishNode = findSingleNodeById(SingleHead, finishId);
                if (!finishNode) {
                    printf("Khong tim thay id\n");
                    break;
                }
                DoubleHead = insertDoubleNodeAtEnd(DoubleHead, finishNode->employee);
                SingleHead = deleteSingleNodeById(SingleHead, finishId);
                break;
            }
            case 6:
                printDoubleList(DoubleHead);
                break;
            case 7:
                SingleHead = sortBySalary(SingleHead);
                printf("Danh sach da duoc sap xep theo luong.\n");
                printSingleList(SingleHead);
                break;
            case 8:
                break;
            case 9:
                printf("Cam on ban da su dung chuong trinh!\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
                break;
        }
    } while (choice != 9);

    return 0;
}
