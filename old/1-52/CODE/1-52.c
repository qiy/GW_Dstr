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
Status ClearList(DuLinkList L) /* ���ı�L */
{ /* ��ʼ������L�Ѵ��ڡ������������L����Ϊ�ձ� */
  DuLinkList q,p=L->next; /* pָ���һ����� */
  while(p!=L) /* pû����ͷ */
  {
    q=p->next;
    free(p);
    p=q;
  }
  L->next=L->prior=L; /* ͷ��������ָ�����ָ������ */
  return OK;
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
Status GetElem(DuLinkList L,int i,ElemType *e)
{ /* ����i��Ԫ�ش���ʱ,��ֵ����e������OK,���򷵻�ERROR */
  int j=1; /* jΪ������ */
  DuLinkList p=L->next; /* pָ���һ����� */
  while(p!=L&&j<i) /* ˳ָ��������,ֱ��pָ���i��Ԫ�ػ�pָ��ͷ��� */
  {
    p=p->next;
    j++;
  }
  if(p==L||j>i) /* ��i��Ԫ�ز����� */
    return ERROR;
  *e=p->data; /* ȡ��i��Ԫ�� */
  return OK;
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
{
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
Status ListEmpty(DuLinkList L)
{ /* ��ʼ���������Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
  if(L->next==L&&L->prior==L)
    return TRUE;
  else
    return FALSE;
}
void vd(ElemType c) /* ListTraverse()���õĺ���(����һ��) */
{
  printf("%d ",c);
}
void main()
{
  DuLinkList L;
  int i,n,j;
  ElemType e;
  InitList(&L);
  printf("��ʼ��������������1��2��3��4��5\n");
  for(i=1;i<=5;i++)
    ListInsert(L,i,i); /* �ڵ�i�����֮ǰ����i */
  n=3;
  j=GetElem(L,n,&e); /* ������ĵ�n��Ԫ�ظ�ֵ��e */
  if(j)
    printf("����ĵ�%d��Ԫ��ֵΪ%d\n",n,e);
  else
    printf("�����ڵ�%d��Ԫ��\n",n);
}
