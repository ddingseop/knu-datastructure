//2020111842 �ݸ�
#include <stdio.h>
#include <time.h>
#define MAX_SIZE 1001
#define _CRT_SECURE_NO_WARNINGS
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
void sort(int[], int);

void main(void) {
	int i, n, step = 10;
	int a[MAX_SIZE];
	double duration; //����ð�
	clock_t start;  //�ð� ���� ����
	printf("    n   time\n");
	for (n = 0; n <= 1000; n += step) {
		for (i = 0; i < n; i++) {
			a[i] = n - i; //�迭 �ʱ�ȭ
		}
		start = clock(); //���� ���� �ð� ���
		sort(a, n); //�����ϱ�
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC; //���� ���� �ð� ���, ����ð� ����
		printf("%6d    %f\n", n, duration);
		if (n == 100) {
			step = 100;
		}
	}
}
void sort(int list[], int n) {  //��Ʈ�Լ� ����
	int i, j, min, temp;
	//���� ����
	for (i = 0; i < n - 1; i++) {
		min = i; //�ּҰ� �ʱ�ȭ
		for (j = i + 1; j < n; j++) { //������ ������ ��簪�� ���ؼ�
			if (list[j] < list[min]) { //�ּҰ� ã��
				min = j; //�ּҰ� ����
			}
		}
		SWAP(list[i], list[min], temp);
	}
}
