#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct Employee  {
    int id;
    char name[100];
    char position[100];
    char salary[100];
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

SingleNode *insertSingleNodeAtEnd(SingleNode *head, Employee employee) {
    SingleNode *newNode = createSingleNode(employee);
    if (head == NULL) {
        head = newNode;
    }
    SingleNode *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return head;
}
void printSingleList(SingleNode *head) {
    if (head == NULL) {
        printf("Danh sach rong\n");
        return;
    }
    SingleNode *current = head;
    while (current != NULL) {
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
    while (current != NULL) {
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
    SingleNode *current = head;
    SingleNode *prev = NULL;
    while (current != NULL && current->employee.id != id) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Khong tim thay id\n");
        return head;
    }
    if (current == head) {
        head = head->next;
        free(current);
        return head;
    }
    prev -> next = current->next;
    free(current);
    return head;
}
void updateEmployeeById(SingleNode *head, int id) {
    char newName[100];
    if (head == NULL) {
        printf("Danh sach rong\n");
        return;
    }
    SingleNode *current = head;
    while (current != NULL && current->employee.id != id) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Khong tim thay id");
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
    getchar();
    printf("Chuc vu moi: ");
    fgets(current->employee.position, sizeof(current->employee.position), stdin);
    current->employee.position[strcspn(current->employee.position, "\n")] = 0;
    printf("Muc luong moi: ");
    scanf("%s", current->employee.salary);
}
SingleNode* findSingleNodeById(SingleNode *head, int id) {
    if (head == NULL) {
        printf("Danh sach rong\n");
        return head;
    }
    SingleNode *current = head;
    while (current != NULL && current->employee.id != id) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Khong tim thay id\n");
        return head;
    }
    return current;
}
DoubleNode *insertDoubleNodeAtEnd(DoubleNode *head, Employee employee) {
    DoubleNode *newNode = createDoubleNode(employee);
    DoubleNode *current = head;
    if (current == NULL) {
        head = newNode;
        return head;
    }
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;

    return head;
}
//Hàm sắp xếp nhân viên theo lương
SingleNode* sortBySalary(SingleNode *head) {
    if (head == NULL || head->next == NULL) return head;

    for (SingleNode *i = head; i != NULL; i = i->next) {
        for (SingleNode *j = head; j->next != NULL; j = j->next) {
            if (j->employee.salary > j->next->employee.salary) {
                Employee temp = j->employee;
                j->employee = j->next->employee;
                j->next->employee = temp;
            }
        }
    }
    return head;
}

//Hàm tìm kiếm nhân viên theo tên
SingleNode* findSingleNodeByName(SingleNode *head, char name[]) {
    if (head == NULL) {
        printf("Danh sach rong\n");
    }
    SingleNode *current = head;
    while (current != NULL && strcasecmp(current->employee.name, name) != 0) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Khong tim thay ten\n");
    }
    return current;
}
int main() {
    int choice;
    SingleNode *SingleHead = NULL;
    DoubleNode *DoubleHead = NULL;
    do {
        printf("======MENU======\n");
        printf("1. Them nhan vien\n");
        printf("2. Hien thi danh sach nhan vien dang lam viec\n");
        printf("3. Xoa nhan vien theo ID\n");
        printf("4. Cap nhap thong tin nhan vien\n");
        printf("5. Danh dau nhan vien da nghi viec\n");
        printf("6. Hien thi danh sach nhan vien da nghi viec\n");
        printf("7. Sap xep nhan vien theo luong\n");
        printf("8. Tim kiem nhan vien theo ten\n");
        printf("9. Thoat chuong trinh\n");
        printf("Nhap lua chon cua ban:");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                Employee newEmployee;
                char name[100];
                newEmployee.id = autoId++;
                fflush(stdin);
                do {
                    printf("Nhap ten nhan vien: ");
                    fgets(name, sizeof(name), stdin);
                    name[strcspn(name, "\n")] = 0;
                    if (!isNameUnique(SingleHead, name)) {
                        printf("Ten bi trung! Vui long nhap lai.\n");
                    }else {
                        strcpy(newEmployee.name, name);
                        break;
                    }
                } while (!isNameUnique(SingleHead, newEmployee.name));
                fflush(stdin);
                printf("Nhap chuc vu: ");
                fgets(newEmployee.position, sizeof(newEmployee.position), stdin);
                newEmployee.position[strcspn(newEmployee.position, "\n")] = 0;
                fflush(stdin);
                printf("Nhap luong: ");
                fgets(newEmployee.salary, sizeof(newEmployee.salary), stdin);
                newEmployee.salary[strcspn(newEmployee.salary, "\n")] = 0;
                SingleHead = insertSingleNodeAtEnd(SingleHead, newEmployee);
                break;
            case 2:
                printSingleList(SingleHead);
                break;
            case 3:
                int deleteId;
                printf("Nhap id nhan vien ban muon xoa: ");
                scanf("%d", &deleteId);
                SingleHead = deleteSingleNodeById(SingleHead, deleteId);
                break;
            case 4:
                int updateId;
                printf("Nhap id nhan vien ban muon cap nhat: ");
                scanf("%d", &updateId);
                updateEmployeeById(SingleHead, updateId);
                break;
            case 5://đánh dấu nhân viên đã nghỉ việc
                int finishId;
                printf("Nhap id khoa hoc cua ban muon danh dau: ");
                scanf("%d", &finishId);

                SingleNode *finishNode = findSingleNodeById(SingleHead, finishId);
                if (finishNode == NULL) {
                    printf("Khong tim thay id\n");
                    break;
                }
                Employee finishEmployee = finishNode->employee;
                DoubleHead = insertDoubleNodeAtEnd(DoubleHead, finishEmployee);
                SingleHead = deleteSingleNodeById(SingleHead, finishId);
                break;
            case 6:
                printDoubleList(DoubleHead);
                break;
            case 7:
                SingleHead = sortBySalary(SingleHead);
                printf("Danh sach da duoc sap xep theo so luong\n");
                printSingleList(SingleHead);
                break;
            case 8:
                char findStr[100];
                printf("Nhap ten nhan vien can tim kiem: ");
                gets(findStr);
                SingleNode *findNode = findSingleNodeByName(SingleHead, findStr);
                if (findNode == NULL) {
                    break;
                }
                printf("Id: %d\n", findNode->employee.id);
                printf("Ten: %s\n", findNode->employee.name);
                printf("Chuc vu: %s\n", findNode->employee.position);
                printf("Muc luong: %s\n", findNode->employee.salary);

                break;
            case 9:
                printf("Cam on ban da su dung chuong trinh\n");
                break;
            default:
                printf("Lua chon khong hop le!Vui long chon lai\n");
                break;
        }
    }while (choice != 9);
    return 0;
}