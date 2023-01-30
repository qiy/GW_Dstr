#include "stdio.h"
#define QueueSize 100 /*�ٶ�Ԥ����Ķ��пռ����Ϊ100��Ԫ��*/  	
typedef int DataType;/*�ٶ�����Ԫ�ص���������Ϊ�ַ�*/  	
typedef struct{
      DataType data[QueueSize];
      int front;/*ͷָ��*/
	  int rear;/*βָ��*/
}SeqQueue;   
/* �ö��п�*/
void Initial(SeqQueue *Q)
{/*��˳������ÿ�*/
      Q->front=Q->rear=0;
} 
/*�ж��п�*/
int IsEmpty(SeqQueue *Q)
{
    return Q->front==Q->rear;
}
/*�ж�����*/
int IsFull(SeqQueue *Q)
{
	return Q->rear==QueueSize-1+Q->front;
}
/*������*/
void Push(SeqQueue *Q,DataType x)
{
    if (IsFull(Q))
	{
		printf("��������"); /*����,�˳�����*/
		exit(1);
	}
    Q->data[Q->rear++]=x;/*���ж�ָ���1��x�����*/
}
/*������*/
DataType Pop(SeqQueue *Q)
{
	if(IsEmpty(Q))
	{
		printf("����Ϊ��"); /*����,�˳�����*/
		exit(1);
	}
	return Q->data[Q->front++];/*���ж�Ԫ�ط��غ󽫶��ж�ָ���1*/
}
/* ȡ���ж�Ԫ��*/
DataType Top(SeqQueue *Q)
{
	if(IsEmpty(Q))
	{
		printf("����Ϊ��"); /*����,�˳�����*/
		exit(1);
	}
	return Q->data[Q->front];
}
void main()
{
	SeqQueue s;
	DataType first,sec;
	Initial(&s);
	Push(&s,'a');
	Push(&s,'b');
	first=Top(&s);
	Pop(&s);
	sec=Top(&s);
	Pop(&s);
}
