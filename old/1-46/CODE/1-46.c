#include<stdio.h> /* EOF(=^Z��F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int ElemType;
struct LNode
{
  ElemType data;
  struct LNode *next;
};
typedef struct LNode *LinkList; /* ��һ�ֶ���LinkList�ķ��� */
Status InitList_CL(LinkList *L)
{ /* �������������һ���յ����Ա�L */
  *L=(LinkList)malloc(sizeof(struct LNode)); /* ����ͷ���,��ʹLָ���ͷ��� */
  if(!*L) /* �洢����ʧ�� */
    exit(OVERFLOW);
  (*L)->next=*L; /* ָ����ָ��ͷ��� */
  return OK;
}
int ListLength_CL(LinkList L)
{ /* ��ʼ������L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
  int i=0;
  LinkList p=L->next; /* pָ��ͷ��� */
  while(p!=L) /* û����β */
  {
    i++;
    p=p->next;
  }
  return i;
}
Status ListInsert_CL(LinkList *L,int i,ElemType e) /* �ı�L */
{ /* ��L�ĵ�i��λ��֮ǰ����Ԫ��e */
  LinkList p=(*L)->next,s; /* pָ��ͷ��� */
  int j=0;
  if(i<=0||i>ListLength_CL(*L)+1) /* �޷��ڵ�i��Ԫ��֮ǰ���� */
    return ERROR;
  while(j<i-1) /* Ѱ�ҵ�i-1����� */
  {
    p=p->next;
    j++;
  }
  s=(LinkList)malloc(sizeof(struct LNode)); /* �����½�� */
  s->data=e; /* ����L�� */
  s->next=p->next;
  p->next=s;
  if(p==*L) /* �ı�β��� */
    *L=s;
  return OK;
}
Status ListTraverse_CL(LinkList L,void(*vi)(ElemType))
{ /* ��ʼ����:L�Ѵ��ڡ��������:���ζ�L��ÿ������Ԫ�ص��ú���vi()��һ��vi()ʧ��,�����ʧ�� */
  LinkList p=L->next->next;
  while(p!=L->next)
  {
    vi(p->data);
    p=p->next;
  }
  printf("\n");
  return OK;
}
void MergeList_CL(LinkList *La,LinkList Lb)
{
  LinkList p=Lb->next;
  Lb->next=(*La)->next;
  (*La)->next=p->next;
  free(p);
  *La=Lb;
}
void visit(ElemType c)
{
  printf("%d ",c);
}
void main()
{
  int n=5,i;
  LinkList La,Lb;
  InitList_CL(&La);
  for(i=1;i<=n;i++)
    ListInsert_CL(&La,i,i);
  printf("La="); /* �������La������ */
  ListTraverse_CL(La,visit);
  InitList_CL(&Lb);
  for(i=1;i<=n;i++)
    ListInsert_CL(&Lb,1,i*2);
  printf("Lb="); /* �������Lb������ */
  ListTraverse_CL(Lb,visit);
  MergeList_CL(&La,Lb);
  printf("La+Lb="); /* ����ϲ������������� */
  ListTraverse_CL(La,visit);
}
