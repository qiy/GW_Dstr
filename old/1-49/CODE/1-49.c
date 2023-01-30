#include<stdio.h> /* EOF(=^Z��F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int ElemType;
typedef struct DuLNode
{
  ElemType data;
  struct DuLNode *prior,*next;
}DuLNode,*DuLinkList;
 Status InitList(DuLinkList *L)
{ /* �����յ�˫��ѭ������L */
  *L=(DuLinkList)malloc(sizeof(DuLNode));
  if(*L)
  {
    (*L)->next=(*L)->prior=*L;
    return OK;
  }
  else
    return OVERFLOW;
}
int ListLength(DuLinkList L)
{ /* ��ʼ������L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
  int i=0;
  DuLinkList p=L->next; /* pָ���һ����� */
  while(p!=L) /* pû����ͷ */
  {
    i++;
    p=p->next;
  }
  return i;
}
DuLinkList GetElemP(DuLinkList L,int i) /* ��� */
{ /* ��˫������L�з��ص�i��Ԫ�ص�λ��ָ��*/
  int j;
  DuLinkList p=L;
  for(j=1;j<=i;j++)
    p=p->next;
  return p;
}
Status ListInsert(DuLinkList L,int i,ElemType e)
{ /* �ڴ�ͷ����˫��ѭ�����Ա�L�е�i��λ��֮ǰ����Ԫ��e��i�ĺϷ�ֵΪ1��i�ܱ�+1 */
  DuLinkList p,s;
  if(i<1||i>ListLength(L)+1) /* iֵ���Ϸ� */
    return ERROR;
  p=GetElemP(L,i-1); /* ��L��ȷ����i-1��Ԫ�ص�λ��ָ��p */
  if(!p) /* p=NULL,����i-1��Ԫ�ز����� */
    return ERROR;
  s=(DuLinkList)malloc(sizeof(DuLNode));
  if(!s)
    return OVERFLOW;
  s->data=e; /* �ڵ�i-1��Ԫ��֮����� */
  s->prior=p;
  s->next=p->next;
  p->next->prior=s;
  p->next=s;
  return OK;
}
void ListTraverse(DuLinkList L,void(*visit)(ElemType))
{ /* ��˫��ѭ�����Ա�L��ͷ������,�����ÿ������Ԫ�ص��ú���visit() */
  DuLinkList p=L->next; /* pָ��ͷ��� */
  while(p!=L)
  {
    visit(p->data);
    p=p->next;
  }
  printf("\n");
}
Status ListDelete(DuLinkList L,int i,ElemType *e)
{ /* ɾ����ͷ����˫��ѭ�����Ա�L�ĵ�i��Ԫ��,i�ĺϷ�ֵΪ1��i�ܱ�+1 */
  DuLinkList p;
  if(i<1||i>ListLength(L)) /* iֵ���Ϸ� */
    return ERROR;
  p=GetElemP(L,i);  /* ��L��ȷ����i��Ԫ�ص�λ��ָ��p */
  if(!p) /* p=NULL,����i��Ԫ�ز����� */
    return ERROR;
  *e=p->data;
  p->prior->next=p->next;
  p->next->prior=p->prior;
  free(p);
  return OK;
}
void vd(ElemType c) /* ListTraverse()���õĺ���(����һ��) */
{
  printf("%d ",c);
}
void main()
{
  DuLinkList L;
  int i,n=2;
  ElemType e;
  InitList(&L);
  printf("��ʼ��������������1��2��3��4��5\n");
  for(i=1;i<=5;i++)
    ListInsert(L,i,i); /* �ڵ�i�����֮ǰ����i */
  ListDelete(L,n,&e); /* ɾ�����ͷŵ�n����� */
  printf("ɾ����%d����㣬ֵΪ%d��������Ϊ��",n,e);
  ListTraverse(L,vd); /* ������� */
}
