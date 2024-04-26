//2020111842 �ݸ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// ���� ����Ʈ�� �������� ����Ű�� ��� ���
Node* head = NULL;

// ���ο� ��带 �����ϴ� �Լ�
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data; //�ش����� �����͸� �־��� �����ͷ� ����
    newNode->next = NULL; //���� ��带 ����Ű�� ������ NULL�� �ʱ�ȭ
    return newNode;
}

// ������������ ���� ����Ʈ�� ��带 �����ϴ� �Լ�
void insert(int data) {
    Node* newNode = createNode(data);

    // ����Ʈ�� ����ְų� ������ ���� ���� ���� ��
    if (head == NULL || head->data >= data) {
        newNode->next = head; //���ο� ��尡 ���ο� head�� ����Ű������
        head = newNode; //���ο� ��尡 ���ο� head�� ��
    }
    else {
        Node* current = head; //current �����͸� ����Ͽ� ���Ḯ��Ʈ Ž��
        while (current->next != NULL && current->next->data < data) {
            current = current->next; //
        }
        newNode->next = current->next; 
        current->next = newNode; 
    } // newNode�� current�� ���� current->next�� �ٽ� newNode�� ����Ű�� ����
}

// ���� ����Ʈ�� ����ϴ� �Լ�
void printList() {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// ���� ����Ʈ���� ��带 �����ϴ� �Լ�
void delete(int key) {
    Node* temp = head;
    Node* prev = NULL;

    // ������ ��带 ã�� ����
    while (temp != NULL && temp->data != key) { //���ϴ� ���� ã��������
        prev = temp; //������ ����� ������带 �˾ƾ� �ؼ� prev�� ������ �Ҵ�
        temp = temp->next; //���� ���� �̵�
    }
    // ������ ��尡 ���� ���
    if (temp == NULL) {
        printf("%d�� ����Ʈ�� ����.\n", key);
        return;
    }
    // ������ ��尡 �� �տ� �ִ� ���
    if (prev == NULL) {
        head = temp->next; //head�� �����ҳ��(temp)�� ���� ���� �����ؼ� ù��° ��� �ǳʶ�
    }
    else {
        prev->next = temp->next; //��������� next�� temp�� �������� �����ؼ� temp �ǳʶ�
    }

    free(temp);
}

int main() {
    FILE* fp = fopen("list3.txt", "r");
    int n,num;
    fscanf(fp, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d ", &num);
        insert(num);
    }
    fclose(fp);

    printf("[�������� ����]\n");
    printList();

    int deleteKey;
    while (1) {
        printf("������ ��� ��ȣ: ");
        scanf("%d", &deleteKey);

        if (deleteKey < 0) {
            printf("����");
            break;
        }
        // �Է¹��� ���ڸ� ���� ����Ʈ���� ����
        delete(deleteKey);
        printList();
    }

    // �������� �Ҵ�� �޸� ����
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    return 0;
}