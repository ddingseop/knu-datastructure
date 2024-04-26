//2020111842 �ݸ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// ���� ǥ�� ��� �Լ�
void printBinary(int n) {
    if (n > 1)
        printBinary(n / 2); //2�� �����鼭
    printf("%d", n % 2); //��ͷ� ������ ���ϱ�
}

// '0'�� ���� ��� �Լ�
int countZeros(int n) {
    if (n == 0)
        return 1; // 0�� ��� '0'�� ������ 1
    else if (n == 1)
        return 0; // 1�� ��� '0'�� ������ 0
    else if (n % 2 == 0)
        return countZeros(n / 2) + 1; // ¦���� ���, [N/2]�� '0' ���� + 1
    else
        return countZeros(n / 2); // Ȧ���� ���, [N/2]�� '0' ����
}

int main() {
    int N;
    do {
        printf("Input num: ");
        scanf_s("%d", &N);
        if (N < 0) {
            printf("Exit");  //����ó��
            return 0;
        }
        printf("2��ǥ��: ");
        printBinary(N);

        printf("\n%d�� 0�� %d�� �ִ�.\n", N, countZeros(N));
    } while (1);

    return 0;
}