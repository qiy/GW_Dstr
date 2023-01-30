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
 Status QueueEmpty(LinkQueue Q)
{ /* ��QΪ�ն���,�򷵻�TRUE,���򷵻�FALSE */
  if(Q.front==Q.rear)
    return TRUE;
  else
    return FALSE;
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
TElemType Parent(BiTree T,TElemType e)
{ /* ��ʼ����: ������T����,e��T��ĳ����� */
  /* �������: ��e��T�ķǸ����,�򷵻�����˫��,���򷵻أ��գ� */
  LinkQueue q;
  QElemType a;
  if(T) /* �ǿ��� */
  {
    InitQueue(&q); /* ��ʼ������ */
    EnQueue(&q,T); /* ������� */
    while(!QueueEmpty(q)) /* �Ӳ��� */
    {
      DeQueue(&q,&a); /* ����,����Ԫ�ظ���a */
      if(a->lchild&&a->lchild->data==e||a->rchild&&a->rchild->data==e)
      /* �ҵ�e(��������Һ���) */
        return a->data; /* ����e��˫�׵�ֵ */
      else /* û�ҵ�e,����������Һ���ָ��(����ǿ�) */
      {
        if(a->lchild)
          EnQueue(&q,a->lchild);
        if(a->rchild)
          EnQueue(&q,a->rchild);
      }
    }
  }
  return Nil; /* ���ջ�û�ҵ�e */
}
 BiTree Point(BiTree T,TElemType s)
{ /* ���ض�����T��ָ��Ԫ��ֵΪs�Ľ���ָ�롣��� */
  LinkQueue q;
  QElemType a;
  if(T) /* �ǿ��� */
  {
    InitQueue(&q); /* ��ʼ������ */
    EnQueue(&q,T); /* �������� */
    while(!QueueEmpty(q)) /* �Ӳ��� */
    {
      DeQueue(&q,&a); /* ����,����Ԫ�ظ���a */
      if(a->data==s)
        return a;
      if(a->lchild) /* ������ */
        EnQueue(&q,a->lchild); /* ������� */
      if(a->rchild) /* ���Һ��� */
        EnQueue(&q,a->rchild); /* ����Һ��� */
    }
  }
  return NULL;
}
 TElemType LeftChild(BiTree T,TElemType e)
{ /* ��ʼ����: ������T����,e��T��ĳ����� */
  /* �������: ����e�����ӡ���e������,�򷵻أ��գ� */
  BiTree a;
  if(T) /* �ǿ��� */
  {
    a=Point(T,e); /* a�ǽ��e��ָ�� */
    if(a&&a->lchild) /* T�д��ڽ��e��e�������� */
      return a->lchild->data; /* ����e�����ӵ�ֵ */
  }
  return Nil; /* ����������ؿ� */
}
TElemType RightChild(BiTree T,TElemType e)
{ /* ��ʼ����: ������T����,e��T��ĳ����� */
  /* �������: ����e���Һ��ӡ���e���Һ���,�򷵻أ��գ� */
  BiTree a;
  if(T) /* �ǿ��� */
  {
    a=Point(T,e); /* a�ǽ��e��ָ�� */
    if(a&&a->rchild) /* T�д��ڽ��e��e�����Һ��� */
      return a->rchild->data; /* ����e���Һ��ӵ�ֵ */
  }
  return Nil; /* ����������ؿ� */
}
 TElemType LeftSibling(BiTree T,TElemType e)
{ /* ��ʼ����: ������T����,e��T��ĳ����� */
  /* �������: ����e�����ֵܡ���e��T�����ӻ������ֵ�,�򷵻أ��գ� */
  TElemType a;
  BiTree p;
  if(T) /* �ǿ��� */
  {
    a=Parent(T,e); /* aΪe��˫�� */
    p=Point(T,a); /* pΪָ����a��ָ�� */
    if(p->lchild&&p->rchild&&p->rchild->data==e) /* p�������Һ������Һ�����e */
      return p->lchild->data; /* ����p������(e�����ֵ�) */
  }
  return Nil; /* ���ջ�û�ҵ�e�����ֵ� */
}

TElemType RightSibling(BiTree T,TElemType e)
{ /* ��ʼ����: ������T����,e��T��ĳ����� */
  /* �������: ����e�����ֵܡ���e��T���Һ��ӻ������ֵ�,�򷵻أ��գ� */
  TElemType a;
  BiTree p;
  if(T) /* �ǿ��� */
  {
    a=Parent(T,e); /* aΪe��˫�� */
    p=Point(T,a); /* pΪָ����a��ָ�� */
    if(p->lchild&&p->rchild&&p->lchild->data==e) /* p�������Һ�����������e */
      return p->rchild->data; /* ����p���Һ���(e�����ֵ�) */
  }
  return Nil; /* ���ջ�û�ҵ�e�����ֵ� */
}

void main()
{
  BiTree T;
  TElemType e1,e2;
  InitBiTree(&T);
#ifdef CHAR
  printf("���������������(��:ab�����ո��ʾaΪ�����,bΪ�������Ķ�����)\n");
#endif
#ifdef INT
  printf("���������������(��:1 2 0 0 0��ʾ1Ϊ�����,2Ϊ�������Ķ�����)\n");
#endif
  CreateBiTree(&T);
printf("������Ҫ��ѯ����ֵ��");
 #ifdef CHAR
  scanf("%*c%c%*c",&e2);
#endif
#ifdef INT
  scanf("%d",&e2);
#endif
e1=Parent(T,e2);
if(e1!=Nil)
#ifdef CHAR
    printf("%c��˫����%c\n",e2,e1);
#endif
#ifdef INT
    printf("%d��˫����%d\n",e2,e1);
#endif
  else
#ifdef CHAR
    printf("%cû��˫��\n",e2);
#endif
#ifdef INT
    printf("%dû��˫��\n",e2);
#endif
  e1=LeftChild(T,e2);
  if(e1!=Nil)
#ifdef CHAR
    printf("%c��������%c\n",e2,e1);
#endif
#ifdef INT
    printf("%d��������%d\n",e2,e1);
#endif
  else
#ifdef CHAR
    printf("%cû������\n",e2);
#endif
#ifdef INT
    printf("%dû������\n",e2);
#endif
  e1=RightChild(T,e2);
  if(e1!=Nil)
#ifdef CHAR
    printf("%c���Һ�����%c\n",e2,e1);
#endif
#ifdef INT
    printf("%d���Һ�����%d\n",e2,e1);
#endif
  else
#ifdef CHAR
    printf("%cû���Һ���\n",e2);
#endif
#ifdef INT
    printf("%dû���Һ���\n",e2);
#endif
  e1=LeftSibling(T,e2);
  if(e1!=Nil)
#ifdef CHAR
    printf("%c�����ֵ���%c\n",e2,e1);
#endif
#ifdef INT
    printf("%d�����ֵ���%d\n",e2,e1);
#endif
  else
#ifdef CHAR
    printf("%cû�����ֵ�\n",e2);
#endif
#ifdef INT
    printf("%dû�����ֵ�\n",e2);
#endif
  e1=RightSibling(T,e2);
  if(e1!=Nil)
#ifdef CHAR
    printf("%c�����ֵ���%c\n",e2,e1);
#endif
#ifdef INT
    printf("%d�����ֵ���%d\n",e2,e1);
#endif
  else
#ifdef CHAR
    printf("%cû�����ֵ�\n",e2);
#endif
#ifdef INT
    printf("%dû�����ֵ�\n",e2);
#endif
}
