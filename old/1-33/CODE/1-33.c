#include <stdio.h>
#define N	4
typedef   char  datatype;
typedef	  struct	node{
datatype	  data;
struct 	node  *next;
} listnode;
typedef  listnode  *linklist;
listnode  *p;
linklist  createlist(int n)
{
	int i;
    linklist  head;
	listnode *p;
    head=NULL;
    for(i=n;i>0;--i)/*ָ������Ϊn,�������������*/
	{
		p=(listnode*)malloc(sizeof(listnode));
        scanf("%c",&p->data);
        p->next=head;
        head=p;
	}
	return(head);
}
main()
{
	linklist newlist=createlist(N);
	do
	{
	   printf("%c",newlist->data);
	   newlist=newlist->next;
    }while(newlist!=NULL);
    printf("\n");
}
