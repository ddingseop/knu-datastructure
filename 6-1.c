//2020111842 �ݸ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_COL 1000

typedef struct { 
	int row; //��
	int col; //��
	int value;
}term ;

void fastTranspose(term a[], term b[]) {
	int rowTerms[MAX_COL], startingPos[MAX_COL];
	int i, j, numCols = a[0].col, numTerms = a[0].value; //numTerms�� 0�� �ƴ� ���� ���� ���� ����
	b[0].row = numCols;
	b[0].col = a[0].row;
	b[0].value = numTerms;
	if (numTerms > 0) {
		for (i = 0; i < numCols; i++) {
			rowTerms[i] = 0;  //rowTerms�迭�� �� ���� ���ϴ� ������ ����
		}
		for (i = 1; i <= numTerms; i++) { //ġȯ�ҷ��� �࿭ �ݴ�� �ؾ��ϴϱ� col�� ���ؼ���
			rowTerms[a[i].col]++;  //�� ���� ���ϴ� ������ �������� +
		}
		startingPos[0] = 1;
		for (i = 1; i < numCols; i++) {
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1]; //�� ���� ������ġ+���� ����=���� ���� ������ġ
		}
		for (i = 1; i <= numTerms; i++) {
			j = startingPos[a[i].col]++;
			b[j].row = a[i].col;
			b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}
}

int main() {
	term *a;
	int r, c, v,row,col,value;
	FILE* fp;
	fp = fopen("m1.txt", "r");
	fscanf(fp, "%d %d %d", &r, &c, &v);

	a = (term*)malloc((v + 1) * sizeof(term));
	for (int i = 1; i <= v; i++) {
		fscanf(fp, "%d %d %d", &row, &col, &value);
		a[i].row = row;
		a[i].col = col;
		a[i].value = value;
	}
	a[0].row = r;
	a[0].col = c;
	a[0].value = v;
	int ans = 1;
	printf("Before Transposing\n");
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (a[ans].row == i && a[ans].col == j) { //��ġ�� ������
				printf("%3d", a[ans].value);
				ans++;
			}
			else { //������ �κ��� 0
				printf("%3d", 0);
			}
		}
		printf("\n");
	}
	term* b = (term*)malloc((v + 1) * sizeof(term));
	fastTranspose(a, b);
	printf("\n");
	ans = 1;
	printf("After Transposing\n");
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < r; j++) {
			if (b[ans].row == i && b[ans].col == j) {
				printf("%3d", b[ans].value);
				ans++;
			}
			else {
				printf("%3d", 0);
			}
		}
		printf("\n");
	}
	fclose(fp);
	free(a);
	free(b);
}