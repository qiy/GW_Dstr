#include "stdio.h"
#define QueueSize 100 /*�ٶ�Ԥ����Ķ��пռ����Ϊ100��Ԫ��*/  
typedef char DataType ; /*�ٶ�����Ԫ�ص���������Ϊ�ַ�*/
typedef struct node{
	DataType data;
	struct node *next;
}QueueNode;
typedef struct{
	QueueNode *front;  /*ͷָ��*/
	QueueNode *rear;
}LinkQueue;
/* �ö��п�*/

void Initial(LinkQueue *Q)
/*��˳������ÿ�*/

{    Q->front=Q->rear=NULL;
} 

/*�ж��п�*/
int IsEmpty(LinkQueue *Q)
{
    return Q->front==NULL&&Q->rear==NULL;
}

/*������*/
void Push(LinkQueue *Q,DataType x)
{
/*��Ԫ��x����������β��*/
	QueueNode *p=(QueueNode *)malloc(sizeof(QueueNode));/*�����½��*/
	p->data=x;
	p->next=NULL;
    if(IsEmpty(Q))
		Q->front=Q->rear=p;  /*��x����ն���*/
	else 
	{ /*x����ǿն��е�β*/
		Q->rear->next=p;     /*p����ԭ��β����*/
		Q->rear=p;           /*��βָ��ָ���µ�β*/
	}
}

/*������*/
DataType Pop(LinkQueue *Q)
{
	DataType x;
	QueueNode *p;
	if(IsEmpty(Q))
	{
		printf("����Ϊ��");/*����*/
		exit(1);
	}
	p=Q->front;                   /*ָ���ͷ���*/
	x=p->data;                    /*�����ͷ��������*/
	Q->front=p->next;             /*����ͷ��������ժ��*/
    if(Q->rear==p)/*ԭ����ֻ��һ����㣬ɾȥ����б�գ���ʱ��ͷָ����Ϊ��*/
		Q->rear=NULL;
	free(p);   /*�ͷű�ɾ��ͷ���*/
	return x;  /*����ԭ��ͷ����*/
}

/* ȡ���ж�Ԫ��*/
DataType Front(LinkQueue *Q)
{
	if(IsEmpty(Q))
	{
		printf("����Ϊ��"); /*����,�˳�����*/
		exit(1);
	}
	return Q->front->data;
}

void main()
{
	LinkQueue s;
	DataType first,sec;
	Initial(&s);
	Push(&s,'a');
	Push(&s,'b');
	first=Front(&s);
	Pop(&s);
	sec=Front(&s);
	Pop(&s);
}
