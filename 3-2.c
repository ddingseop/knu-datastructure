//2020111842 �ݸ�
#include <stdio.h>
#include <stdlib.h>
int findMax(int arr[], int size) {
	if (size == 1) {
		return arr[0]; //�ϳ��ۿ� ������
	}
	// ���� ��ҿ� ������ ��ҵ� �� �ִ��� ���Ͽ� �ִ��� ����
	int sub = findMax(arr + 1, size - 1);
	if (arr[0] > sub) {
		return arr[0]; //ũ�� �ٲ��ְ�
	}
	else {
		return sub; //������ �״��
	}
}

int main() {
	int num;
	FILE* fp;
	fopen_s(&fp,"in.txt", "r"); //���� �б�
	fscanf_s(fp, "%d", &num);
	int* nums = (int*)malloc(num * sizeof(int)); //�����Ҵ�
	for (int i = 0; i < num; i++) {
		fscanf_s(fp, "%d", &nums[i]);
	}
	printf("���ڸ���Ʈ>>\n");
	for (int i = 0; i < num; i++) {
		printf("%d ", nums[i]);
	}
	printf("\n�ִ밪 : %d",findMax(nums, num));
	free(nums);
	fclose(fp);
	return 0;
}