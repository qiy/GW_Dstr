#include "stdio.h"
#define MEMORY_SIZE  100  /* �ڴ��С */
#define MAX_STACKS 10      /* ջ�ĸ�����1*/
typedef char element;
element memory [MEMORY_SIZE];
int top[MAX_STACKS-1];
int boundary[MAX_STACKS];
/* ��ջ��*/
void Initial(int n)
{/*������˳��ջ�ÿ�*/
	int i;
	top [0] = boundary [0] = -1;
	for ( i =1;  i<n;  i ++ )
		top[i]=boundary[i]= (MEMORY_SIZE/n)*i;
	boundary[n]=MEMORY_SIZE-1;
}
/*��ջ*/
void Push(int i, element item)
{
	if (top[i] == boundary[i+1] )
	{
		printf("��%d��ջ������",i);
		exit(1);
	}
	memory[++top[i]] = item;
}
/*��ջ*/
element Pop(int i)
{
	if ( top[i] == boundary[i] )
	{
		printf("��%d��ջ�ѿա�",i);
		exit(1);
	}
	return memory[top[i]--];
}
void main()
{
	int  n=2;      /* ʹ�õ�ջ�ĸ��� */
	element first,sec;
	Initial(n);
	Push(1,'a');
	Push(0,'b');
	sec=Pop(1);
	first=Pop(0);
}

