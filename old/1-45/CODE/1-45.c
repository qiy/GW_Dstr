#include<stdio.h> /* EOF(=^Z��F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
/* �������״̬���� */
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
Status DestroyList_CL(LinkList *L)
{ /* ����������������Ա�L */
  LinkList q,p=(*L)->next; /* pָ��ͷ��� */
  while(p!=*L) /* û����β */
  {
    q=p->next;
    free(p);
    p=q;
  }
  free(*L);
  *L=NULL;
  return OK;
}
Status ClearList_CL(LinkList *L) /* �ı�L */
{ /* ��ʼ���������Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
  LinkList p,q;
  *L=(*L)->next; /* Lָ��ͷ��� */
  p=(*L)->next; /* pָ���һ����� */
  while(p!=*L) /* û����β */
  {
    q=p->next;
    free(p);
    p=q;
  }
  (*L)->next=*L; /* ͷ���ָ����ָ������ */
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
     printf("���L��%d(1: �ɹ�)\n",ClearList_CL(&L));
  printf("���L��L�Ƿ�գ�%d(1:�� 0:��)\n",ListEmpty_CL(L));
  printf("����L��%d(1: �ɹ�)\n",DestroyList_CL(&L));
}
