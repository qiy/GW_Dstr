#include <stdio.h>
#define N	4
typedef   char  datatype;
typedef	  struct	node{
datatype	  data;
struct 	node  *next;
} listnode;
typedef  listnode  *linklist;
listnode  *p;
//��head�ڵ������½ڵ�
linklist  creater()
{
    char  ch;
    linklist  head;
    listnode  *p,*r;
    head=NULL;
	r=NULL;/*rΪβָ��*/
    while((ch=getchar())!='\n'){
        p=(listnode *)malloc(sizeof(listnode));
        p->data=ch;
        if(head==NULL)
            head=p;/*head ָ���һ��������*/
        else
			r->next=p;/*���뵽����β��*/
        r=p;/*rָ�����½�㣬�������*/
     }
     if (r!=NULL)
          r->next=NULL;/*����β�����ĺ��ָ��ָ��Ϊ��*/
     return(head);
 }
main()
{
	linklist newlist=creater();
	do
	{
	   printf("%c",newlist->data);
	   newlist=newlist->next;
    }while(newlist!=NULL);
    printf("\n");
}
