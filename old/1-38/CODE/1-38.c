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
void  deletelist(linklist head,int i)
{
int j=0;
    listnode * p,*r;
	p=head;
    while(p&&j<i-1){
		p=p->next;
		++j;
	}
    if(!p->next||j>i-1)
        exit(1);
    r=p->next;
    p->next=r->next;
    free(r) ;
}
main()
{
	linklist	list;
	int i=1;
	list=createlist();
	deletelist(list,i);
	do
	{
	   printf("%c",list->data);
	   list=list->next;
    }while(list!=NULL);
    printf("\n");
}
