//2020111842 �ݸ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode {
    int coef;
    int expo;
    struct PolyNode* link;
} PolyNode;

typedef PolyNode* PolyPointer;

PolyPointer createNode(int coef, int expo) {
    PolyPointer node = (PolyPointer)malloc(sizeof(PolyNode));
    node->coef = coef;
    node->expo = expo;
    node->link = NULL;
    return node;
}

void insertNode(PolyPointer* head, PolyPointer node) {
    //���ο� ���� ������ ���׽� ù ��° ���� �������� Ŭ��
    if (*head == NULL || node->expo > (*head)->expo) { 
        node->link = *head;
        *head = node;
        //���ο� ���� ���׽� ù��°�� ����
        return;
    }

    PolyPointer current = *head;
    //���ο� ���� ������ ������ �������� �������� ���� ������
    while (current->link && node->expo < current->link->expo) {
        current = current->link; 
    }
    //���ο� ���� ������ ������ �������� ������ ������
    if (current->link && node->expo == current->link->expo) {
        current->link->coef += node->coef;
        //�̹� �����ϴ� ���� ������ ���� ���� ����� ���ο� ���ǰ�� ������
        free(node);
    }
    else { //���� ������ ������ ���� �������� ������
        node->link = current->link;
        current->link = node;
        //���ο� ���� �������� ���� ������ ����
    }
}

void printPolynomial(PolyPointer poly) {
    while (poly) {
        if (poly->coef != 0) {
            printf("[%d, %d] ", poly->coef, poly->expo);
        }
        poly = poly->link;
    }
    printf("\n");
}

PolyPointer multiplyPolynomials(PolyPointer poly1, PolyPointer poly2) {
    PolyPointer result = NULL;
    PolyPointer term1 = poly1;
    while (term1) {
        PolyPointer term2 = poly2;
        while (term2) {
            int coef = term1->coef * term2->coef;
            int expo = term1->expo + term2->expo;
            PolyPointer productTerm = createNode(coef, expo);
            insertNode(&result, productTerm);
            term2 = term2->link;
        }
        term1 = term1->link;
    }
    return result;
}

void freePolynomial(PolyPointer poly) {
    PolyPointer temp;
    while (poly) {
        temp = poly;
        poly = poly->link;
        free(temp);
    }
}

int main() {
    FILE* fp1 = fopen("poly1.txt", "r");
    FILE* fp2 = fopen("poly2.txt", "r");

    int num, coef, expo;

    fscanf(fp1, "%d", &num);
    PolyPointer poly1 = NULL;
    for (int i = 0; i < num; ++i) {
        fscanf(fp1, "%d %d", &coef, &expo);
        PolyPointer node = createNode(coef, expo);
        insertNode(&poly1, node);
    }

    fscanf(fp2, "%d", &num);
    PolyPointer poly2 = NULL;
    for (int i = 0; i < num; ++i) {
        fscanf(fp2, "%d %d", &coef, &expo);
        PolyPointer node = createNode(coef, expo);
        insertNode(&poly2, node);
    }
    fclose(fp1);
    fclose(fp2);
    
    printf("poly1:\n");
    printPolynomial(poly1);
    printf("poly2:\n");
    printPolynomial(poly2);

    PolyPointer poly3 = multiplyPolynomials(poly1, poly2);
    printf("poly1 * poly2:\n");
    printPolynomial(poly3, "result");

    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(poly3);

    return 0;
}

