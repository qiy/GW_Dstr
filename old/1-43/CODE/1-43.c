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
Status PriorElem_CL(LinkList L,ElemType cur_e,ElemType *pre_e)
{ /* ��ʼ���������Ա�L�Ѵ��� */
  /* �����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ���� */
  /*           �������ʧ�ܣ�pre_e�޶��� */
  LinkList q,p=L->next->next; /* pָ���һ����� */
  q=p->next;
  while(q!=L->next) /* pû����β */
  {
    if(q->data==cur_e)
    {
      *pre_e=p->data;
      return TRUE;
    }
    p=q;
    q=q->next;
  }
  return FALSE;
}
Status NextElem_CL(LinkList L,ElemType cur_e,ElemType *next_e)
{ /* ��ʼ���������Ա�L�Ѵ��� */
  /* �����������cur_e��L������Ԫ��,�Ҳ������һ��,����next_e�������ĺ�̣� */
  /*           �������ʧ�ܣ�next_e�޶��� */
  LinkList p=L->next->next; /* pָ���һ����� */
  while(p!=L) /* pû����β */
  {
    if(p->data==cur_e)
    {
      *next_e=p->next->data;
      return TRUE;
    }
    p=p->next;
  }
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
  printf("��ʼ����ѭ������L i=%d (1:��ʼ���ɹ�)\n",i);
  i=ListEmpty_CL(L);
  printf("L�Ƿ�� i=%d(1:�� 0:��)\n",i);
  ListInsert_CL(&L,1,3); /* ��L�����β���3,5 */
  ListInsert_CL(&L,2,5);
  printf("���β���Ԫ��3��5\n");
  PriorElem_CL(L,5,&e); /* ��Ԫ��5��ǰ�� */
  printf("5ǰ���Ԫ�ص�ֵΪ%d��\n",e);
  NextElem_CL(L,3,&e); /* ��Ԫ��3�ĺ�� */
  printf("3�����Ԫ�ص�ֵΪ%d��\n",e);
}
