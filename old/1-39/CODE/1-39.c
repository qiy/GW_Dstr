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
linklist  concatenate(linklist list1,linklist list2)
{
	listnode *temp;
    if (list1==NULL)
		return list2;
    else {
        if (list2!=NULL) {
            for ( temp =list1; temp->next; temp = temp->next )
				; /*������list1��ĩβ*/
           	temp->next=list2;/*��list2���ӵ�list1ĩβ*/
        }
	}
    return list1;
}
main()
{
	linklist	list1,list2,list3;
	list1=createlist();
	list2=createlist();
	list3=concatenate(list1,list2);
	do
	{
	   printf("%c",list3->data);
	   list3=list3->next;
    }while(list3!=NULL);
    printf("\n");
}
