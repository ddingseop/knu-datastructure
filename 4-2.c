//2020111842 �ݸ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b;
    //���� �о����
    FILE* fp1 = fopen("in1.txt", "r");
    FILE* fp2 = fopen("in2.txt", "r");

    if (!fp1 || !fp2) {
        printf("no");
        exit(1);
    }
    //�� �о����
    fscanf(fp1, "%d", &a);
    fscanf(fp2, "%d", &b);

    while (!feof(fp1) && !feof(fp2)) {
        if (a > b) { //ù��° ���ϰ��� �� ū���
            fscanf(fp1, "%d", &a); //ù��° ���� ������ �ҷ���
            continue;
        }
        else if (a < b) { //�ι�° ���ϰ��� �� ū���
            fscanf(fp2, "%d", &b); //�ι�° ���� ������ �ҷ���
            continue;
        }
        else { //�� ���ϰ��� �������
            printf("%d ", a);  //����ϰ�
            fscanf(fp1, "%d", &a); //ù��° ���� ������ �ҷ���
            fscanf(fp2, "%d", &b); //�ι�° ���ϵ� ������ �ҷ���
            continue;
        }
    }
    fclose(fp1);
    fclose(fp2);
}