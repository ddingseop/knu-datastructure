//2020111842 �ݸ�
#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int row;
    int col;
    int dir;
} element;

typedef struct {
    int vert;
    int horiz;
} offsets;

offsets move[4] = { {-1,0},{0,1},{1,0},{0,-1} };

int top = -1;
void push(element item, element* stack);
element pop(element* stack);
void stackFull();
element stackEmpty();

void initializeArray(int** arr, int row, int col);
void initializeMark(int** mark, int row, int col);
int** readMaze(FILE* fp, int* row, int* col, int* startrow, int* startcol, int* finishrow, int* finishcol);
void freeArray(int** arr, int row);
void freeMark(int** mark, int row);
void path(int** maze, int** mark, offsets* move, int startrow, int startcol, int finishrow, int finishcol, int mazerow, int mazecol);
int same(element* stack, int row, int col, int top);

int main(void)
{
    FILE* files[4];
    files[0] = fopen("maze1.txt", "r");
    files[1] = fopen("maze2.txt", "r");
    files[2] = fopen("maze3.txt", "r");
    files[3] = fopen("maze4.txt", "r");

    for (int i = 0; i< 4; i++) {
        int row, col, startrow, startcol, finishrow, finishcol;
        int** maze = readMaze(files[i], &row, &col, &startrow, &startcol, &finishrow, &finishcol);
        if (maze == NULL) {
            printf("Failed to read maze %d\n", i + 1);
            continue;
        }

        printf("MAZE%d\n", i + 1);
        for (int i = 1; i <= row ; i++) {
            for (int j = 1; j <= col; j++)
                printf("%d ", maze[i][j]);
            printf("\n");
        }
        int** mark = (int**)malloc(sizeof(int*) * (row + 2));
        initializeMark(mark, row, col);

        path(maze, mark, move, startrow + 1, startcol + 1, finishrow + 1, finishcol + 1, row, col);

        freeArray(maze, row);
        freeMark(mark, row);
        fclose(files[i]);
    }

    return 0;
}

void initializeArray(int** arr, int row, int col) { //�迭 �����Ҵ��Լ�
    for (int i = 0; i < row + 2; i++) {
        arr[i] = (int*)malloc(sizeof(int) * (col + 2));
        for (int j = 0; j < col + 2; j++) {
            if (i == 0 || j == 0 || i == row + 1 || j == col + 1)
                arr[i][j] = 1;
            else
                arr[i][j] = 0;
        }
    }
}
void initializeMark(int** mark, int row, int col) { //�湮�迭 �����Ҵ��Լ�
    for (int i = 0; i < row + 2; i++) {
        mark[i] = (int*)malloc(sizeof(int) * (col + 2));
        for (int j = 0; j < col + 2; j++)
            mark[i][j] = 0;
    }
}
//���Ͽ��� �迭 �о����
int** readMaze(FILE* fp, int* row, int* col, int* startrow, int* startcol, int* finishrow, int* finishcol) {
    if (fp == NULL)
        return NULL;

    fscanf(fp, "%d %d", row, col);
    int** maze = (int**)malloc(sizeof(int*) * (*row + 2));
    initializeArray(maze, *row, *col);

    for (int i = 1; i <= *row; i++) {
        for (int j = 1; j <= *col; j++)
            fscanf(fp, "%d", &maze[i][j]);
    }

    fscanf(fp, "%d %d", startrow, startcol);
    fscanf(fp, "%d %d", finishrow, finishcol);

    return maze;
}

void freeArray(int** arr, int row) {
    for (int i = 0; i < row + 2; i++)
        free(arr[i]);
    free(arr);
}

void freeMark(int** mark, int row) {
    for (int i = 0; i < row + 2; i++)
        free(mark[i]);
    free(mark);
}

void push(element item, element* stack)
{
    if (top >= MAX_STACK_SIZE - 1)
        stackFull();
    stack[++top] = item;
}

element pop(element* stack)
{
    if (top == -1)
        return stackEmpty();
    return stack[top--];
}

void stackFull()
{
    fprintf(stderr, "Stack is full");
    exit(EXIT_FAILURE);
}

element stackEmpty()
{
    fprintf(stderr, "Stack is empty");
    exit(EXIT_FAILURE);
}

void path(int** maze, int** mark, offsets* move, int startrow, int startcol, int finishrow, int finishcol, int mazerow, int mazecol)
{
	int i, row, col, nextrow, nextcol, dir, found = false;
	element position; //������ġ ���� ����
	element stack[MAX_STACK_SIZE]; //���ü���
	top = -1; //���� �������
	mark[startrow][startcol] = 1; //������ �湮ǥ��
	top = 0; //���ÿ� �������� �ϳ� �����
	stack[0].row = startrow; stack[0].col = startcol; stack[0].dir = 0;

	while (top > -1 && !found) //������ ������� �ʰ� �������� ��������
	{
		position = pop(stack); //���ÿ��� ��ġ���� ������
		row = position.row; //row������ ��ġ���� ����
		col = position.col; //col������ ��ġ���� ����
		dir = position.dir; //dir������ ��ġ���� ����

		while (dir < 4 && !found) //�����⿡ ���� �ݺ�
		{
			nextrow = row + move[dir].vert; //������ġ ���(�̵����⿡ ���� ����)
			nextcol = col + move[dir].horiz; //������ġ ���(�̵����⿡ ���� ����)
			if (nextrow == finishrow && nextcol == finishcol) //������ġ�� �������̶��
				found = true; //�ݺ�����
			else if (!maze[nextrow][nextcol] && !mark[nextrow][nextcol]) //0�̶�� �̵��Ҽ� �ִ°Ŵϱ�
			{
				mark[nextrow][nextcol] = 1; //�湮ǥ��
				position.row = row; //������ġ���� ����
				position.col = col; //������ġ���� ����
				position.dir = ++dir; //������������ Ž���ϱ����� ���� ����
				push(position, stack); //�ش���ġ ���ÿ� �߰�
				row = nextrow; //������ġ�� �̵�
				col = nextcol; //������ġ�� �̵�
				dir = 0; //���� �ʱ�ȭ����
			}
			else ++dir; //���� ��ġ�� ���� ���ٸ� �̵����� ����
		}
	}
	if (found)
	{
		printf("The path is : \n");
		for (int i = 1; i <= mazerow; i++)
		{
			for (int j = 1; j <= mazecol; j++)
			{
				if (i == startrow && j == startcol)
					printf("S ");
				else if (i == finishrow && j == finishcol)
					printf("F ");
				else if (same(stack, i, j, top) == 1)
					printf("X ");
				else if (row == i && col == j)
					printf("X ");
				else
					printf("%d ", maze[i][j]);

			}
			printf("\n");
		}

	}
	else {
		printf("No path!\n");
		for (int i = 1; i <= mazerow; i++)
		{
			for (int j = 1; j <= mazecol; j++)
			{
				if (i == startrow && j == startcol)
					printf("S ");
				else if (i == finishrow && j == finishcol)
					printf("F ");
				else if (same(stack, i, j, top) == 1)
					printf("X ");
				else
					printf("%d ", maze[i][j]);

			}
			printf("\n");
		}
	}

}

int same(element* stack, int row, int col, int top)
{
	int num = 0;
	for (int i = 0; i <= top; i++) {
		if (stack[i].row == row && stack[i].col == col)
			num = 1;
	}
	return num;
}

