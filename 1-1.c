//2020111842 �ݸ�
#include <stdio.h>
// #define _CRT_SECURE_NO_WARNINGS

int main() {
    // FILE* fp = fopen("out.txt", "w"); //���� ������� ����
    FILE* fp;
    fopen_s(&fp, "out.txt", "w");


    int count = 0;
    int sum = 0;
    int min = 100; // �ʱ� �ּҰ��� 100���� ����
    int max = 1;   // �ʱ� �ִ밪�� 1�� ����

    int num;
    printf("Input number:\n");
    // while (fscanf(stdin, "%d", &num) != EOF)
    while (fscanf_s(stdin, "%d", &num) != EOF) { //�Է������Ҷ����� �ޱ�
        if (num < 1 || num > 100) {  //���� ����
            continue;
        }
        count++; //�Է¹޴� ���� �����ֱ�
        sum += num; //�Է¹޴� ���� �� ���ϱ�
        if (num < min) {
            min = num; //�ּҰ�
        }
        if (num > max) {
            max = num; //�ִ밪
        }
    }
    if (count > 0) {
        int average = (int)sum / count;
        fprintf(fp, "MIN: %d MAX: %d, AVG: %d\n", min, max, average);
    }
    fclose(fp); //���ϴݱ�
    return 0;
}