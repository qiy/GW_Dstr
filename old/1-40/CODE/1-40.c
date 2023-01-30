#include "stdio.h"
typedef   char  datatype;
typedef	 struct	node{
	datatype	 data;
	struct 	node  *next;
} stack;
stack *  creat(void)
{
      char ch;
      stack *  head;
      stack *p;
      head=NULL;/*��ʼ��Ϊ��*/
      ch=getchar( );
      while (ch!='\n'){
           p=(stack*)malloc(sizeof(stack));/*����ռ�*/
           p->data=ch;/*������ֵ*/
           p->next=head;/*ָ�����ָ��*/
		   head=p;/*headָ��ָ�����²���Ľ����*/
       	   ch=getchar( );
      }
      return (head);
}
void MakeNull(stack *s)/*ʹջsΪ��*/
{
		stack *p=s;
		while(s!=NULL){
			s=s->next;
			free(p);/*�ͷſռ�*/
			p=s;
		}
}
datatype Top(stack *s)
{
	if(Empty(s))/*sΪ��ջ��ֱ����������ʾ������Ϣ*/
		printf("The stack is empty.");
	else
		return s->data;
}
void Pop(stack *s)
{
		stack *p;
		if(Empty(s)) /*sΪ��ջ��ֱ����������ʾ������Ϣ*/
			printf("The stack is empty.");
		else{
			p=s;
			s=s->next;
			free(p);/*�ͷ�ջ���ռ�*/
		}
}
void Push(stack *s,datatype x)
{
		stack *p;
		p=(stack*)malloc(sizeof(stack));
		p->data=x;
		p->next=s;
		s=p;
}
int Empty(stack *s)
{
	return(s==NULL);
}
void main()
{
	stack*	m_stack=creat();
	char	m_top;
	if(!Empty(m_stack))
	{
		m_top=Top(m_stack);
		Pop(m_stack);
	}
	else
		Push(m_stack,'a');
	MakeNull(m_stack);
}
