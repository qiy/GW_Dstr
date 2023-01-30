#include<stdio.h> /* EOF(=^Z��F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int ElemType;
/* c2-2.h ���Ա�ĵ�����洢�ṹ */
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
Status ListEmpty_CL(LinkList L)
{ /* ��ʼ���������Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
  if(L->next==L) /* �� */
    return TRUE;
  else
    return FALSE;
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
Status GetElem_CL(LinkList L,int i,ElemType *e)
{ /* ����i��Ԫ�ش���ʱ,��ֵ����e������OK,���򷵻�ERROR */
  int j=1; /* ��ʼ��,jΪ������ */
  LinkList p=L->next->next; /* pָ���һ����� */
  if(i<=0||i>ListLength_CL(L)) /* ��i��Ԫ�ز����� */
    return ERROR;
  while(j<i)
  { /* ˳ָ��������,ֱ��pָ���i��Ԫ�� */
    p=p->next;
    j++;
  }
  *e=p->data; /* ȡ��i��Ԫ�� */
  return OK;
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
  printf("��ʼ����ѭ������L i=%d (1:��ʼ���ɹ�)\n",i);
  i=ListEmpty_CL(L);
  printf("L�Ƿ�� i=%d(1:�� 0:��)\n",i);
  ListInsert_CL(&L,1,3); /* ��L�����β���3,5 */
  ListInsert_CL(&L,2,5);
  i=GetElem_CL(L,1,&e);
  j=ListLength_CL(L);
  printf("L������Ԫ�ظ���=%d,��1��Ԫ�ص�ֵΪ%d��\n",j,e);
  printf("L�е�����Ԫ������Ϊ��");
  ListTraverse_CL(L,visit);
}
