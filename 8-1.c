//2020111842 �ݸ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
}precedence;

int isp[] = { 0,19,12,12,13,13,13,0 };
int icp[] = { 20,19,12,12,13,13,13,0 };

precedence stack[MAX];
int top = -1;
char expr[MAX];

void push(int* top, precedence item) {
	if (*top >= MAX - 1) {
		return eos;
	}
	stack[++(*top)] = item;
}

precedence pop(int* top) {
	if (*top == -1) {
		return eos;
	}
	return stack[(*top)--];
}

precedence get_token(char* symbol, int* n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(':return lparen;
	case ')':return rparen;
	case '+':return plus;
	case '-':return minus;
	case '*':return times;
	case '/':return divide;
	case '%':return mod;
	case '\0':return eos;
	default: return operand;
	}
}

void printToken(precedence a) {
	switch (a) {
	case lparen:printf("("); 
		break;
	case rparen:printf(")");
		break;
	case plus:printf("+");
		break;
	case minus:printf("-");
		break;
	case times:printf("*");
		break;
	case divide:printf("/");
		break;
	case mod:printf("%%");
		break;
	}
}

void postfix() {
	char symbol;
	precedence token;
	int n = 0;
	int top = 0;
	stack[0] = eos;
	int n_lparen = 0, n_rparen = 0;
	for (token = get_token(&symbol, &n); token != eos; token = get_token(&symbol, &n)) {
		if (token == operand) { //�ǿ����ڸ� �ٷ� ���
			printf("%c", symbol);
		}
		else if (token == lparen) { //'('�ΰ�� ���� ���� ���� ���ֱ�
			n_lparen++;
			push(&top, token);
		}
		else if (token == rparen) {
			n_rparen++;
			while (stack[top] != lparen) {  //�°�ȣ ����������
				printToken(pop(&top));  //���ÿ� �ִ� �����ڵ� ���
			}
			pop(&top);
		}
		else {
			while (isp[stack[top]] >= icp[token]) { //���ÿ� �ִ� ������ �켱������ ����������
				printToken(pop(&top)); //���ÿ��� ������ ���� ���
			}
			push(&top,token); //���ο� �������� �켱������ �� ������ ���ÿ� �־���
		}
		if (n_rparen > n_lparen) {
			break;
		}
	}
	while ((token = pop(&top)) != eos) { //���ÿ� �����ִ� �ֵ� 
		printToken(token);
	}
	printf("\n");
	if (n_lparen != n_rparen) {
		printf("��ȣ����\n");
		
	}
}

int main() {
	FILE* fp;
	fp = fopen("infix.txt", "r");
	while (fscanf(fp, "%s",expr)!=EOF) {
		printf("Infix: %s\n", expr);
		printf("Postfix: ");
		postfix(); 
		printf("\n");
	}
	fclose(fp);
	return 0;
}