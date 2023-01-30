#include "stdio.h"
typedef   char  datatype;
typedef	 struct	node{
	datatype	 data;
	struct 	node  *next;
} position;
typedef 	struct queue{
	position 	*front;
	position 	*rear;
}queuetype;
/*ʹ����Ϊ�գ�*/
void MakeNull(queuetype * q)
{
		q->rear=q->front;
		while(q->front!=NULL){
			q->front=q->front->next;
			free(q->rear);/*�ͷſռ�*/
			q->rear=q->front;
		}
		q->front=(position*)malloc(sizeof(position));
		q->front->next=NULL;
		q->rear=q->front;
}
/* ȡ���еĶ�ͷԪ�أ�*/
datatype Front(queuetype *q)
{
		if(Empty(q))
			printf("'The queue is empty!");
		else
			return(q->front->next->data);
}
/*ɾ������ͷԪ�أ�*/
void dequeue(queuetype * q)
{
		position* p;
		if(Empty(q))
			printf("The queue is empty!");
		else{
			p=q->front;
			q->front=q->front->next;
			free(p);
		}
}
/* �ڶ����м�����Ԫ�أ�*/
void Enqueue(datatype x,queuetype * q)
{
		position* p;
		p=(position*)malloc(sizeof(position));
		p->data=x;
		p->next=NULL;
		q->rear->next=p;
		q->rear=p;
}
/*�ж��Ƿ�Ϊ�ն��У�*/
int Empty(queuetype * q)
{
	return (q->front==q->rear);
}
void main()
{
	queuetype *	m_q;
        char	m_top;
        m_q=(queuetype *)malloc(sizeof(queuetype));
        m_q->front=m_q->rear=(position*)malloc(sizeof(position));
        m_q->rear->next=NULL;
	if(!Empty(m_q))
	{
		m_top=Front(m_q);
		dequeue(m_q);
	}
	else
		Enqueue('c',m_q);
	MakeNull(m_q);
}
