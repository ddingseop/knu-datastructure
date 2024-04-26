//2020111842 �ݸ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct { //����ü ����
	int coef;  //���
	int expon; //����
} polynomial;

int avail = 0;
polynomial* terms;

int compare(int A, int B) { //���Լ�
    if (A > B)
        return 1;
    else if (A == B)
        return 0;
    else
        return -1;
}

void attach(int coefficient, int exponent) { 
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}

void padd(int sa, int fa, int sb, int fb, int* sd, int* fd) {
    int coef;
    *sd = avail; //C�� ��ġ
    while (sa <= fa && sb <= fb)
        switch (compare(terms[sa].expon, terms[sb].expon)) {
        case 1:
            attach(terms[sb].coef, terms[sb].expon);
            sb++;
            break;
        case 0:
            coef = terms[sa].coef + terms[sb].coef;
            if (coef)
                attach(coef, terms[sa].expon);
            sb++;
            sa++;
            break;
        case -1:
            attach(terms[sa].coef, terms[sa].expon);
            sa++;
        }
    for (; sa <= fa; sa++) //A���� ����������
        attach(terms[sa].coef, terms[sa].expon);
    for (; sb <= fb; sb++)  //B���� ����������
        attach(terms[sb].coef, terms[sb].expon);
    *fd = avail - 1;  //���곡���� avail�� ��ĭ�� �����Ѽ� ���� avail-1�� ����
}

int main() {
    FILE* iF, * oF;
    int sA, fA, sB, fB, sC, fC;
    int numA, numB, numC;  //���� ����

    iF = fopen("in1.txt", "r");
    fscanf(iF, "%d %d", &numA, &numB);

    terms = (polynomial*)malloc((numA + numB + 1) * 2 *  sizeof(polynomial)); //�����Ҵ�
    avail = numA + numB; // terms���� A�� B�� ä������ numA+numB��°���� C�� ä����
    for (int i = 0; i < numA; i++) {
        fscanf(iF, "%d", &terms[i].coef);
        fscanf(iF, "%d", &terms[i].expon);
    }
    fA = numA - 1;

    for (int i = 0; i < numB; i++) {
        fscanf(iF, "%d", &terms[numA + i].coef);
        fscanf(iF, "%d", &terms[numA + i].expon);
    }
    fB = numA + numB - 1;
    fclose(iF);

    oF = fopen("out1.txt", "w");
    padd(0, fA, numA, fB, &sC, &fC);
    numC = fC - sC + 1;

    if (fC - sC + 1 != 0) {  
        fprintf(oF, "%d ", numC);
        for (int i = sC; i <= fC; i++) {
            fprintf(oF, "%d %d ", terms[i].coef, terms[i].expon);
        }
    }
    else {  //���� ���� 0�� �϶�(�� �Լ� ���� 0�϶�)
        fprintf(oF, "%d ", fC - sC + 1);
        fprintf(oF, "%d", 0);
    }
    fclose(oF);
    free(terms);

    return 0;
}

//padd�Լ�����  *sd = avail; �� �κ��� �ִµ�  avail = numA + numB;�� ����� �Լ� ������ ���⼭ ������