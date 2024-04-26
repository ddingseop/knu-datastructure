//2020111842 �ݸ�
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct { //����ü ����
    char name[50];
    int score;
    int age;
} Student;

int main() {
    FILE* fp;
    int num_students;

    // ���� ����
    fp = fopen("in.txt", "r");
    if (fp == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return 1;
    }

    // �л� �� �б�
    fscanf(fp, "%d", &num_students);

    // �л� ������ �迭 ���� �Ҵ�
    Student* students = (Student*)malloc(num_students * sizeof(Student));

    // �л� ������ �б�
    for (int i = 0; i < num_students; i++) {
        fscanf(fp, "%s %d %d", students[i].name, &students[i].score, &students[i].age);
    }

    // Ư�� ���� �̻��� ���� �л����� �̸� ���
    int cutoff_score;
    printf("�������� �Է�: ");
    scanf("%d", &cutoff_score);

    printf("%d�� �̻��� �л��� ���:\n", cutoff_score);
    for (int i = 0; i < num_students; i++) {
        if (students[i].score >= cutoff_score) {
            printf("�̸�: %s, ����: %d, ����: %d\n", students[i].name, students[i].score, students[i].age);
        }
    }

    // �޸� ���� �� ���� �ݱ�
    free(students);
    fclose(fp);

    return 0;
}
