#include<stdio.h> /* EOF(=^Z��F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
/* �������״̬���� */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
/* #define OVERFLOW -2 ��Ϊ��math.h���Ѷ���OVERFLOW��ֵΪ3,��ȥ������ */
typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int Boolean; /* Boolean�ǲ�������,��ֵ��TRUE��FALSE */
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
int LocateElem_CL(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
{ /* ��ʼ���������Ա�L�Ѵ��ڣ�compare()������Ԫ���ж����� */
  /* �������������L�е�1����e�����ϵcompare()������Ԫ�ص�λ�� */
  /*           ������������Ԫ�ز����ڣ��򷵻�ֵΪ0 */
  int i=0;
  LinkList p=L->next->next; /* pָ���һ����� */
  while(p!=L->next)
  {
    i++;
    if(compare(p->data,e)) /* �����ϵ */
      return i;
    p=p->next;
  }
  return 0;
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
Status ListDelete_CL(LinkList *L,int i,ElemType *e) /* �ı�L */
{ /* ɾ��L�ĵ�i��Ԫ��,����e������ֵ */
  LinkList p=(*L)->next,q; /* pָ��ͷ��� */
  int j=0;
  if(i<=0||i>ListLength_CL(*L)) /* ��i��Ԫ�ز����� */
    return ERROR;
  while(j<i-1) /* Ѱ�ҵ�i-1����� */
  {
    p=p->next;
    j++;
  }
  q=p->next; /* qָ���ɾ����� */
  p->next=q->next;
  *e=q->data;
  if(*L==q) /* ɾ�����Ǳ�βԪ�� */
    *L=p;
  free(q); /* �ͷŴ�ɾ����� */
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
Status compare(ElemType c1,ElemType c2)
{
  if(c1==c2)
    return TRUE;
  else
    return FALSE;
}
void visit(ElemType c)
{
  printf("%d ",c);
}
void main()
{
  LinkList L;
  ElemType e;
  int j;
  Status i;
  i=InitList_CL(&L); /* ��ʼ����ѭ������L */
  printf("�����ڵ�ѭ�������в���3,5\n");
  ListInsert_CL(&L,1,3); /* ��L�����β���3,5 */
  ListInsert_CL(&L,2,5);
  j=LocateElem_CL(L,5,compare);
  if(j)
    printf("L�ĵ�%d��Ԫ��Ϊ5��\n",j);
  else
    printf("������ֵΪ5��Ԫ��\n");
  i=ListDelete_CL(&L,2,&e);
  printf("ɾ��L�ĵ�2��Ԫ�أ�\n");
  if(i)
  {
    printf("ɾ����Ԫ��ֵΪ%d,����L�е�����Ԫ������Ϊ��",e);
    ListTraverse_CL(L,visit);
  }
  else
    printf("ɾ�����ɹ���\n");
}
