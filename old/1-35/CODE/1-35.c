#include <stdio.h>
typedef   char  datatype;
typedef	  struct	node{
	datatype	  data;
	struct 	node  *next;
} listnode;
typedef  listnode  *linklist;
listnode  *p;
linklist  createlist(void)
{
      char ch;
      linklist  head;
      listnode  *p;
      head=NULL;/*��ʼ��Ϊ��*/
      ch=getchar( );
      while (ch!='\n'){
           p=(listnode*)malloc(sizeof(listnode));/*����ռ�*/
           p->data=ch;/*������ֵ*/
           p->next=head;/*ָ�����ָ��*/
		   head=p;/*headָ��ָ�����²���Ľ����*/
       	   ch=getchar( );
      }
      return (head);
}
listnode * getnode(linklist head,int i)
{
     int j;
     listnode * p;
     p=head;
	 	 j=0;
     while(p->next && j<i){/*������i�����ǰ�����н��*/
           p=p->next;
           j++;
     }
     if (i==j)
     {
         printf("%c\n",p->data);
         return p;
     }
     else
         return NULL;
}
main()
{
		linklist	list;
		listnode * node;
		int i=0;
		list=createlist();
		node=getnode(list,i);
}
