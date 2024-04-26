//2020111842 �ݸ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} element;

void listAddq(element key, element* que, int size);
void cirAddq(element key, element* que, int size);
void listDeleteq(element* que);
void cirDeleteq(element* que, int size);
void queueFull();
void queueEmpty();

int listfront = -1;
int listrear = -1;
int cirfront = 0;
int cirrear = 0;

int main(void)
{
    FILE* fp = fopen("in1.txt", "r");
    int size;
    fscanf(fp, "%d", &size);
    element* cirQue = malloc(sizeof(element) * size);
    element* listQue = malloc(sizeof(element) * size);
    printf("Queue size : %d\n", size);
    char n;
    element val;
    while (fscanf(fp, "%c", &n) != EOF)
    {
        if (n == 'a')
        {
            fscanf(fp, "%d", &val);
            printf("\nadd %d...\n", val);
            printf("[Circular queue] ");
            cirAddq(val, cirQue, size);
            printf("\n");
            printf("[List queue] ");
            listAddq(val, listQue, size);
        }
        else if (n == 'd')
        {
            printf("\nDelete\n");
            printf("[Circular queue] ");
            cirDeleteq(cirQue, size);
            printf("\n");
            printf("[List queue] ");
            listDeleteq(listQue, size);
        }
    }

}

void listAddq(element key, element* que, int size)
{
    if (listrear == size - 1)
    {
        queueFull();
        return;
    }
    else
    {
        que[++listrear] = key;
        for (int i = listfront + 1; i <= listrear; i++)
            printf("%d ", que[i]);
    }
}
void cirAddq(element key, element* que, int size)
{
    cirrear = (cirrear + 1) % size;
    if (cirfront == cirrear) {
        queueFull();
        cirrear -= 1;
        return;
    }

    que[cirrear] = key;
    for (int i = (cirfront + 1) % size; i != (cirrear + 1) % size; i = (i + 1) % size) {
        printf("%d ", que[i]);
    }
}
void listDeleteq(element* que)
{
    if (listfront == listrear) {  //�� ��Ȳ�� �̹� ����ִ� ���
        queueEmpty();
    }
    ++listfront;
    if (listfront == listrear) {  //front + ���ص� �� ���
        queueEmpty();
    }
    else {

        for (int i = listfront + 1; i <= listrear; i++)
            printf("%d ", que[i]);
    }
}
void cirDeleteq(element* que, int size) {
    if (cirfront == cirrear) {   //�� ��Ȳ�� �̹� ����ִ� ���
        queueEmpty();
        return;
    }
    cirfront = (cirfront + 1) % size;
    if (cirfront == cirrear) {   //front + ���ص� �� ���
        queueEmpty();
    }
    else {
        if (cirrear <= 0) {
            cirrear += size;
        }
        for (int i = (cirfront + 1) % size; i != (cirrear + 1) % size; i = (i + 1) % size) {
            //cirfront ���� ��ġ���� �����Ͽ� cirrear ���� ��ġ�� �����ϱ� ������ �ݺ�,
            //i�� ������ġ�� �̵���Ŵ �� %size�� �����ν� �迭�� ������ �������ʰ� ��ȯ���� ����
            printf("%d ", que[i]);
        }
    }
}
void queueFull() {
    printf("Full.");
}
void queueEmpty() {
    printf("Empty.");
}