#define CHAR /* �ַ��� */
#include<stdio.h> /* EOF(=^Z��F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
#ifdef CHAR
  typedef char TElemType;
  TElemType Nil=' '; /* �ַ����Կո��Ϊ�� */
#endif
#ifdef INT
  typedef int TElemType;
  TElemType Nil=0; /* ������0Ϊ�� */
#endif
 typedef struct BiTNode
{
  TElemType data;
  struct BiTNode *lchild,*rchild; /* ���Һ���ָ�� */
}BiTNode,*BiTree;
typedef BiTree QElemType; /* �����Ԫ��Ϊ��������ָ������ */
typedef struct QNode
{
  QElemType data;
  struct QNode *next;
}QNode,*QueuePtr;

typedef struct
{
  QueuePtr front,rear; /* ��ͷ����βָ�� */
}LinkQueue;
Status InitBiTree(BiTree *T)
{ /* �������: ����ն�����T */
  *T=NULL;
  return OK;
}
void CreateBiTree(BiTree *T)
{
  TElemType ch;
#ifdef CHAR
  scanf("%c",&ch);
#endif
#ifdef INT
  scanf("%d",&ch);
#endif
  if(ch==Nil) /* �� */
    *T=NULL;
  else
  {
    *T=(BiTree)malloc(sizeof(BiTNode));
    if(!*T)
      exit(OVERFLOW);
    (*T)->data=ch; /* ���ɸ���� */
    CreateBiTree(&(*T)->lchild); /* ���������� */
    CreateBiTree(&(*T)->rchild); /* ���������� */
  }
}
Status InitQueue(LinkQueue *Q)
{ /* ����һ���ն���Q */
  (*Q).front=(*Q).rear=(QueuePtr)malloc(sizeof(QNode));
  if(!(*Q).front)
    exit(OVERFLOW);
  (*Q).front->next=NULL;
  return OK;
}
 Status QueueEmpty(LinkQueue Q)
{ /* ��QΪ�ն���,�򷵻�TRUE,���򷵻�FALSE */
  if(Q.front==Q.rear)
    return TRUE;
  else
    return FALSE;
}
Status EnQueue(LinkQueue *Q,QElemType e)
{ /* ����Ԫ��eΪQ���µĶ�βԪ�� */
  QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
  if(!p) /* �洢����ʧ�� */
    exit(OVERFLOW);
  p->data=e;
  p->next=NULL;
  (*Q).rear->next=p;
  (*Q).rear=p;
  return OK;
}
Status DeQueue(LinkQueue *Q,QElemType *e)
{ /* �����в���,ɾ��Q�Ķ�ͷԪ��,��e������ֵ,������OK,���򷵻�ERROR */
  QueuePtr p;
  if((*Q).front==(*Q).rear)
    return ERROR;
  p=(*Q).front->next;
  *e=p->data;
  (*Q).front->next=p->next;
  if((*Q).rear==p)
    (*Q).rear=(*Q).front;
  free(p);
  return OK;
}

void LevelOrderTraverse(BiTree T,Status(*Visit)(TElemType))
{ /* ��ʼ������������T����,Visit�ǶԽ�������Ӧ�ú��� */
  /* �������������ݹ����T(���ö���),��ÿ�������ú���Visitһ���ҽ�һ�� */
  LinkQueue q;
  QElemType a;
  if(T)
  {
    InitQueue(&q);
    EnQueue(&q,T);
    while(!QueueEmpty(q))
    {
      DeQueue(&q,&a);
      Visit(a->data);
      if(a->lchild!=NULL)
        EnQueue(&q,a->lchild);
      if(a->rchild!=NULL)
        EnQueue(&q,a->rchild);
    }
    printf("\n");
  }
}
 Status visitT(TElemType e)
{
#ifdef CHAR
  printf("%c ",e);
#endif
#ifdef INT
  printf("%d ",e);
#endif
  return OK;
}
void main()
{
  BiTree T;
  InitBiTree(&T);
   #ifdef CHAR
  printf("���������������(��:ab�����ո��ʾaΪ�����,bΪ�������Ķ�����)\n");
#endif
#ifdef INT
  printf("���������������(��:1 2 0 0 0��ʾ1Ϊ�����,2Ϊ�������Ķ�����)\n");
#endif
  CreateBiTree(&T);
  printf("��α���������:\n");
  LevelOrderTraverse(T,visitT);
}
