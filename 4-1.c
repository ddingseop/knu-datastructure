//2020111842 �ݸ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
	int I, J, K;
	printf("A[I][J][K]...\n");
	printf("Input I:");
	scanf("%d", &I);
	printf("Input J:");
	scanf("%d", &J);
	printf("Input K:");
	scanf("%d", &K);
	//3�����迭 �����Ҵ�
	int*** A;
	A = (int***)malloc(sizeof(**A) * I);
	for (int i = 0; i < I; i++) {
		A[i] = (int**)malloc(sizeof(int*) * J);
		for (int j = 0; j < J; j++) {
			A[i][j] = (int*)malloc(sizeof(int) * K);
		}
	}
	
	//�迭�� ���ְ� ����ϱ�
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < J; j++) {
			for (int k = 0; k < K; k++) {
				A[i][j][k] = i + j + k;
				printf("A[%d][%d][%d]=%d ", i,j,k,A[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}
	//�ݴ������ �����ϱ�
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < J; j++) {
			free(A[i][j]);
		}
		free(A[i]);
	}
	free(A);
	return 0;
}