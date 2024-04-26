//2020111842 �ݸ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// ���� ���� ����Ʈ ��� ����ü
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// ���� ���� ����Ʈ ����ü
typedef struct DoublyLinkedList {
    Node* header;
} DoublyLinkedList;

// ���� ���� ����Ʈ �ʱ�ȭ �Լ�
void initialize(DoublyLinkedList* dll) { //��� ���
    dll->header = (Node*)malloc(sizeof(Node));
    dll->header->prev = dll->header;
    dll->header->next = dll->header;
}

// ���ĵ� ���·� �� ���� �Լ�
void insert_sorted(DoublyLinkedList* dll, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value; //������ ��

    Node* current = dll->header->next; //�����带 ����Ʈ�� ù��° ����
    while (current != dll->header && current->data < value) { 
        //�����尡 �����尡 �ƴϰ������� ���� ������ Ŀ���� ����
        current = current->next; //�̵�
    }

    new_node->prev = current->prev; //���γ��� ����� prev
    new_node->next = current;
    current->prev->next = new_node;
    current->prev = new_node;
}

// ����Ʈ ��� �Լ�
void print_forward(DoublyLinkedList* dll) {
    Node* current = dll->header->next; //ù��° ���
    while (current != dll->header) {
        printf("[%d]", current->data);
        current = current->next;  //���������� ���
    }
    printf("\n");
}

// ����Ʈ ���� ��� �Լ�
void print_backward(DoublyLinkedList* dll) {
    Node* current = dll->header->prev;  //������ ���
    while (current != dll->header) {
        printf("[%d]", current->data);
        current = current->prev;  //�������� ���
    }
    printf("\n\n");
}

int main() {
    // ���Ͽ��� ���� �о����
    FILE* file = fopen("in.txt", "r");
    int count;
    fscanf(file, "%d", &count);
    int* integers = (int*)malloc(count * sizeof(int));
    for (int i = 0; i < count; ++i) {
        fscanf(file, "%d", &integers[i]);
    }
    fclose(file);

    // ���� ���� ����Ʈ ���� �� ���� ����
    DoublyLinkedList dll;
    initialize(&dll);
    for (int i = 0; i < count; ++i) {
        insert_sorted(&dll, integers[i]);
    }
    free(integers);

    // �ʱ� ����Ʈ ���
    printf("print list:\n");
    print_forward(&dll);
    printf("print Inverse order:\n");
    print_backward(&dll);

    // ����� �Է� �� ó��
    int x;
    while (1) {
        printf("Input number: ");
        if (scanf("%d", &x) != 1) {
            printf("Invalid input. Please enter an integer.\n");
            while (getchar() != '\n'); // �Է� ���� ����
            continue;
        }
        if (x < 0) {
            printf("Quit\n");
            break;
        }
        insert_sorted(&dll, x);
        printf("print list(%d inserted)\n", x);
        print_forward(&dll);
        printf("print inverse order\n");
        print_backward(&dll);
    }
}
