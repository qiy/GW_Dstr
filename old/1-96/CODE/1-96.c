#include<stdio.h> /* EOF(=^Z��F6),NULL */
#define TRUE 1
#define FALSE 0
#define OK 1
typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int Boolean; /* Boolean�ǲ�������,��ֵ��TRUE��FALSE */
#define N 10 /* ����Ԫ�ظ��� */
typedef int KeyType; /* ��ؼ�����Ϊ���� */
typedef struct
{
  KeyType key;
  int others;
} ElemType; /* ����Ԫ������ */
typedef ElemType TElemType;
typedef struct BiTNode
{
  TElemType data;
  struct BiTNode *lchild,*rchild; /* ���Һ���ָ�� */
}BiTNode,*BiTree;
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
Status InitDSTable(BiTree *DT) /* ͬbo6-2.c */
{ /* �������: ����һ���յĶ�̬���ұ�DT */
  *DT=NULL;
  return OK;
}
void DestroyDSTable(BiTree *DT) /* ͬbo6-2.c */
{ /* ��ʼ����: ��̬���ұ�DT���ڡ��������: ���ٶ�̬���ұ�DT */
  if(*DT) /* �ǿ��� */
  {
    if((*DT)->lchild) /* ������ */
      DestroyDSTable(&(*DT)->lchild); /* ������������ */
    if((*DT)->rchild) /* ���Һ��� */
      DestroyDSTable(&(*DT)->rchild); /* �����Һ������� */
    free(*DT); /* �ͷŸ���� */
    *DT=NULL; /* ��ָ�븳0 */
  }
}
BiTree SearchBST(BiTree T,KeyType key)
{ /* �ڸ�ָ��T��ָ�����������еݹ�ز���ĳ�ؼ��ֵ���key������Ԫ�أ� */
  /* �����ҳɹ����򷵻�ָ�������Ԫ�ؽ���ָ��,���򷵻ؿ�ָ�롣*/
  if((!T)||EQ(key,T->data.key))
    return T; /* ���ҽ��� */
  else if LT(key,T->data.key) /* ���������м������� */
    return SearchBST(T->lchild,key);
  else
    return SearchBST(T->rchild,key); /* ���������м������� */
}
void SearchBST1(BiTree *T,KeyType key,BiTree f,BiTree *p,Status *flag) 
{ /* �ڸ�ָ��T��ָ�����������еݹ�ز�����ؼ��ֵ���key������Ԫ�أ������� */
  /* �ɹ�����ָ��pָ�������Ԫ�ؽ�㣬������TRUE������ָ��pָ�����·���� */
  /* ���ʵ����һ����㲢����FALSE,ָ��fָ��T��˫�ף����ʼ����ֵΪNULL */
  if(!*T) /* ���Ҳ��ɹ� */
  {
    *p=f;
    *flag=FALSE;
  }
  else if EQ(key,(*T)->data.key) /*  ���ҳɹ� */
  {
    *p=*T;
    *flag=TRUE;
  }
  else if LT(key,(*T)->data.key)
    SearchBST1(&(*T)->lchild,key,*T,p,flag); /* ���������м������� */
  else
    SearchBST1(&(*T)->rchild,key,*T,p,flag); /*  ���������м������� */
}

Status InsertBST(BiTree *T, ElemType e)
{ /* ������������T�в����ڹؼ��ֵ���e.key������Ԫ��ʱ������e������TRUE�� */
  /* ���򷵻�FALSE��*/
  BiTree p,s;
  Status flag;
  SearchBST1(T,e.key,NULL,&p,&flag);
  if(!flag) /* ���Ҳ��ɹ� */
  {
    s=(BiTree)malloc(sizeof(BiTNode));
    s->data=e;
    s->lchild=s->rchild=NULL;
    if(!p)
      *T=s; /* ������*sΪ�µĸ���� */
    else if LT(e.key,p->data.key)
      p->lchild=s; /* ������*sΪ���� */
    else
      p->rchild=s; /* ������*sΪ�Һ��� */
    return TRUE;
  }
  else
    return FALSE; /* �������йؼ�����ͬ�Ľ�㣬���ٲ��� */
}

void Delete(BiTree *p)
{ /* �Ӷ�����������ɾ�����p�����ؽ����������������*/
  BiTree q,s;
  if(!(*p)->rchild) /* ����������ֻ���ؽ���������������ɾ�����Ҷ��Ҳ�ߴ˷�֧�� */
  {
    q=*p;
    *p=(*p)->lchild;
    free(q);
  }
  else if(!(*p)->lchild) /* ֻ���ؽ����������� */
  {
    q=*p;
    *p=(*p)->rchild;
    free(q);
  }
  else /* �������������� */
  {
    q=*p;
    s=(*p)->lchild;
    while(s->rchild) /* ת��Ȼ�����ҵ���ͷ���Ҵ�ɾ����ǰ���� */
    {
      q=s;
      s=s->rchild;
    }
    (*p)->data=s->data; /* sָ��ɾ���ģ�ǰ����������ɾ���ǰ����ֵȡ����ɾ����ֵ�� */
    if(q!=*p)
      q->rchild=s->lchild; /* �ؽ�*q�������� */
    else
      q->lchild=s->lchild; /* �ؽ�*q�������� */
    free(s);
  }
}

Status DeleteBST(BiTree *T,KeyType key)
{ /* ������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ����ɾ��������Ԫ�ؽ�㣬 */
  /* ������TRUE�����򷵻�FALSE��*/
  if(!*T) /* �����ڹؼ��ֵ���key������Ԫ�� */
    return FALSE;
  else
  {
    if EQ(key,(*T)->data.key) /* �ҵ��ؼ��ֵ���key������Ԫ�� */
      Delete(T);
    else if LT(key,(*T)->data.key)
      DeleteBST(&(*T)->lchild,key);
    else
      DeleteBST(&(*T)->rchild,key);
    return TRUE;
  }
}
void TraverseDSTable(BiTree DT,void(*Visit)(ElemType))
{ /* ��ʼ����: ��̬���ұ�DT���ڣ�Visit�ǶԽ�������Ӧ�ú��� */
  /* �������: ���ؼ��ֵ�˳���DT��ÿ�������ú���Visit()һ��������һ�� */
  if(DT)
  {
    TraverseDSTable(DT->lchild,Visit); /* ��������������� */
    Visit(DT->data); /* �ٷ��ʸ���� */
    TraverseDSTable(DT->rchild,Visit); /* ���������������� */
  }
}
void print(ElemType c)
{
  printf("(%d,%d) ",c.key,c.others);
}
void main()
{
  BiTree dt,p;
  int i;
  KeyType j;
  ElemType r[N]={{45,1},{12,2},{53,3},{3,4},{37,5},{24,6},{100,7},{61,8},{90,9},{78,10}}; 
  InitDSTable(&dt); /* ����ձ� */
  for(i=0;i<N;i++)
    InsertBST(&dt,r[i]); /* ���β�������Ԫ�� */
  TraverseDSTable(dt,print);
  printf("\n����������ҵ�ֵ: ");
  scanf("%d",&j);
  p=SearchBST(dt,j);
  if(p)
  {
    printf("���д��ڴ�ֵ��");
    DeleteBST(&dt,j);
    printf("ɾ����ֵ��:\n");
    TraverseDSTable(dt,print);
    printf("\n");
  }
  else
    printf("���в����ڴ�ֵ\n");
  DestroyDSTable(&dt);
}
