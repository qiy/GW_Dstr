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
listnode * locatenode(linklist head,char key)
{
    listnode * p=head;
    while( p->next&& p->data!=key)
        p=p->next;
    if(p!=NULL)
        printf("%c\n",p->data);
    return p;
}
main()
{
	linklist	list;
	listnode * node;
	char key='c';
	list=createlist();
	node=locatenode(list,key);
}
