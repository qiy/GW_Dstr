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
typedef struct BiTPNode
{
  TElemType data;
  struct BiTPNode *parent,*lchild,*rchild; /* ˫�ס����Һ���ָ�� */
}BiTPNode,*BiPTree;
Status InitBiTree(BiPTree *T)
{ /* �������: ����ն�����T */
  *T=NULL;
  return OK;
}
void DestroyBiTree(BiPTree *T)
{ /* ��ʼ����: ������T���ڡ��������: ���ٶ�����T */
  if(*T) /* �ǿ��� */
  {
    if((*T)->lchild) /* ������ */
      DestroyBiTree(&(*T)->lchild); /* ������������ */
    if((*T)->rchild) /* ���Һ��� */
      DestroyBiTree(&(*T)->rchild); /* �����Һ������� */
    free(*T); /* �ͷŸ���� */
    *T=NULL; /* ��ָ�븳0 */
  }
}
void Create(BiPTree *T) /* CreateBiTree()���� */
{ /* �������������������н���ֵ����Ϊ�ַ��ͻ����ͣ��������ж��壩�� */
  /* �����ȱ˫��ָ������������ʾ�Ķ�����T������Nil��ʾ�գ��ӣ��� */
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
    *T=(BiPTree)malloc(sizeof(BiTPNode));
    if(!*T)
      exit(OVERFLOW);
    (*T)->data=ch; /* ���ɸ���� */
    Create(&(*T)->lchild); /* ���������� */
    Create(&(*T)->rchild); /* ���������� */
  }
}
typedef BiPTree QElemType; /* �����Ԫ��Ϊ��������ָ������ */
 /* c3-2.h �������У������е���ʽ�洢�ṹ */
typedef struct QNode
{
  QElemType data;
  struct QNode *next;
}QNode,*QueuePtr;
typedef struct
{
  QueuePtr front,rear; /* ��ͷ����βָ�� */
}LinkQueue;
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
Status CreateBiTree(BiPTree *T)
{ /* �������������������н���ֵ����Ϊ�ַ��ͻ����ͣ��������ж��壩�� */
  /* �������������ʾ�Ķ�����T */
  LinkQueue q;
  QElemType a;
  Create(T); /* ���������(ȱ˫��ָ��) */
  if(*T) /* �ǿ��� */
  {
    (*T)->parent=NULL; /* ������˫��Ϊ���գ� */
    InitQueue(&q); /* ��ʼ������ */
    EnQueue(&q,*T); /* ��ָ����� */
    while(!QueueEmpty(q)) /* �Ӳ��� */
    {
      DeQueue(&q,&a); /* ����,����Ԫ�ظ���a */
      if(a->lchild) /* ������ */
      {
        a->lchild->parent=a; /* �����ӵ�˫��ָ�븳ֵ */
        EnQueue(&q,a->lchild); /* ������� */
      }
      if(a->rchild) /* ���Һ��� */
      {
 a->rchild->parent=a; /* ���Һ��ӵ�˫��ָ�븳ֵ */
        EnQueue(&q,a->rchild); /* �Һ������ */
      }
    }
  }
  return OK;
}
#define ClearBiTree DestroyBiTree
Status BiTreeEmpty(BiPTree T)
{ /* ��ʼ����: ������T���ڡ��������: ��TΪ�ն�����,�򷵻�TRUE,����FALSE */
  if(T)
    return FALSE;
  else
    return TRUE;
}
int BiTreeDepth(BiPTree T)
{ /* ��ʼ����: ������T���ڡ��������: ����T����� */
  int i,j;
  if(!T)
    return 0;
  if(T->lchild)
    i=BiTreeDepth(T->lchild);
  else
    i=0;
  if(T->rchild)
    j=BiTreeDepth(T->rchild);
  else
    j=0;
  return i>j?i+1:j+1;
}
TElemType Root(BiPTree T)
{ /* ��ʼ����: ������T���ڡ��������: ����T�ĸ� */
  if(T)
    return T->data;
  else
    return Nil;
}
TElemType Value(BiPTree p)
{ /* ��ʼ����: ������T���ڣ�pָ��T��ĳ����� */
  /* �������: ����p��ָ����ֵ */
  return p->data;
}
void Assign(BiPTree p,TElemType value)
{ /* ��p��ָ��㸳ֵΪvalue */
  p->data=value;
}
BiPTree Point(BiPTree T,TElemType e)
{ /* ���ض�����T��ָ��Ԫ��ֵΪe�Ľ���ָ�롣�� */
  LinkQueue q;
  QElemType a;
  if(T) /* �ǿ��� */
  {
    InitQueue(&q); /* ��ʼ������ */
    EnQueue(&q,T); /* �������� */
    while(!QueueEmpty(q)) /* �Ӳ��� */
    {
      DeQueue(&q,&a); /* ����,����Ԫ�ظ���a */
      if(a->data==e)
        return a;
      if(a->lchild) /* ������ */
        EnQueue(&q,a->lchild); /* ������� */
      if(a->rchild) /* ���Һ��� */
        EnQueue(&q,a->rchild); /* ����Һ��� */
    }
  }
  return NULL;
}
TElemType Parent(BiPTree T,TElemType e)
{ /* ��ʼ����: ������T����,e��T��ĳ����� */
  /* �������: ��e��T�ķǸ����,�򷵻�����˫��,���򷵻أ��գ� */
  BiPTree a;
  if(T) /* �ǿ��� */
  {
    a=Point(T,e); /* a�ǽ��e��ָ�� */
    if(a&&a!=T) /* T�д��ڽ��e��e�ǷǸ���� */
      return a->parent->data; /* ����e��˫�׵�ֵ */
  }
  return Nil; /* ����������ؿ� */
}
TElemType LeftChild(BiPTree T,TElemType e)
{ /* ��ʼ����: ������T����,e��T��ĳ����� */
  /* �������: ����e�����ӡ���e������,�򷵻أ��գ� */
  BiPTree a;
  if(T) /* �ǿ��� */
  {
    a=Point(T,e); /* a�ǽ��e��ָ�� */
    if(a&&a->lchild) /* T�д��ڽ��e��e�������� */
      return a->lchild->data; /* ����e�����ӵ�ֵ */
  }
  return Nil; /* ����������ؿ� */
}
TElemType RightChild(BiPTree T,TElemType e)
{ /* ��ʼ����: ������T����,e��T��ĳ����� */
  /* �������: ����e���Һ��ӡ���e���Һ���,�򷵻أ��գ� */
  BiPTree a;
  if(T) /* �ǿ��� */
  {
    a=Point(T,e); /* a�ǽ��e��ָ�� */
    if(a&&a->rchild) /* T�д��ڽ��e��e�����Һ��� */
      return a->rchild->data; /* ����e���Һ��ӵ�ֵ */
  }
  return Nil; /* ����������ؿ� */
}
TElemType LeftSibling(BiPTree T,TElemType e)
{ /* ��ʼ����: ������T����,e��T��ĳ����� */
  /* �������: ����e�����ֵܡ���e��T�����ӻ������ֵ�,�򷵻أ��գ� */
  BiPTree a;
  if(T) /* �ǿ��� */
  {
    a=Point(T,e); /* a�ǽ��e��ָ�� */
    if(a&&a!=T&&a->parent->lchild&&a->parent->lchild!=a) /* T�д��ڽ��e��e�������ֵ� */
      return a->parent->lchild->data; /* ����e�����ֵܵ�ֵ */
  }
  return Nil; /* ����������ؿ� */
}
TElemType RightSibling(BiPTree T,TElemType e)
{ /* ��ʼ����: ������T����,e��T��ĳ����� */
  /* �������: ����e�����ֵܡ���e��T���Һ��ӻ������ֵ�,�򷵻أ��գ� */
  BiPTree a;
  if(T) /* �ǿ��� */
  {
    a=Point(T,e); /* a�ǽ��e��ָ�� */
    if(a&&a!=T&&a->parent->rchild&&a->parent->rchild!=a) /* T�д��ڽ��e��e�������ֵ� */
      return a->parent->rchild->data; /* ����e�����ֵܵ�ֵ */
  }
  return Nil; /* ����������ؿ� */
}
Status InsertChild(BiPTree p,int LR,BiPTree c) /* �β�T���� */
{ /* ��ʼ����: ������T����,pָ��T��ĳ�����,LRΪ0��1,�ǿն�����c��T */
  /*           ���ཻ��������Ϊ�� */
  /* �������: ����LRΪ0��1,����cΪT��p��ָ���������������p��ָ��� */
  /*           ��ԭ��������������Ϊc���������� */
  if(p) /* p���� */
  {
    if(LR==0)
    {
      c->rchild=p->lchild;
      if(c->rchild) /* c���Һ���(pԭ������) */
        c->rchild->parent=c;
      p->lchild=c;
      c->parent=p;
    }
    else /* LR==1 */
    {
      c->rchild=p->rchild;
      if(c->rchild) /* c���Һ���(pԭ���Һ���) */
        c->rchild->parent=c;
      p->rchild=c;
      c->parent=p;
    }
    return OK;
  }
  return ERROR; /* p�� */
}
Status DeleteChild(BiPTree p,int LR) /* �β�T���� */
{ /* ��ʼ����: ������T����,pָ��T��ĳ�����,LRΪ0��1 */
  /* �������: ����LRΪ0��1,ɾ��T��p��ָ������������� */
  if(p) /* p���� */
  {
    if(LR==0) /* ɾ�������� */
      ClearBiTree(&p->lchild);
    else /* ɾ�������� */
      ClearBiTree(&p->rchild);
    return OK;
  }
  return ERROR; /* p�� */
}
void PreOrderTraverse(BiPTree T,Status(*Visit)(BiPTree))
{ /* ����ݹ����������T */
  if(T)
  {
    Visit(T); /* �ȷ��ʸ���� */
    PreOrderTraverse(T->lchild,Visit); /* ��������������� */
    PreOrderTraverse(T->rchild,Visit); /* ���������������� */
  }
}
void InOrderTraverse(BiPTree T,Status(*Visit)(BiPTree))
{ /* ����ݹ����������T */
  if(T)
  {
    InOrderTraverse(T->lchild,Visit); /* ������������� */
    Visit(T); /* �ٷ��ʸ���� */
    InOrderTraverse(T->rchild,Visit); /* ���������������� */
  }
}
void PostOrderTraverse(BiPTree T,Status(*Visit)(BiPTree))
{ /* ����ݹ����������T */
  if(T)
  {
    PostOrderTraverse(T->lchild,Visit); /* ������������� */
    PostOrderTraverse(T->rchild,Visit); /* ������������� */
    Visit(T); /* �����ʸ���� */
  }
}
void LevelOrderTraverse(BiPTree T,Status(*Visit)(BiPTree))
{ /* �������������T(���ö���) */
  LinkQueue q;
  QElemType a;
  if(T)
  {
    InitQueue(&q);
    EnQueue(&q,T);
    while(!QueueEmpty(q))
    {
      DeQueue(&q,&a);
      Visit(a);
      if(a->lchild!=NULL)
        EnQueue(&q,a->lchild);
      if(a->rchild!=NULL)
        EnQueue(&q,a->rchild);
    }
  }
}
Status visitT(BiPTree T)
{
  if(T) /* T�ǿ� */
#ifdef CHAR
    printf("%c��",T->data);
  if(T->parent) /* T��˫�� */
  {
    printf("%c",T->parent->data);
#endif
#ifdef INT
    printf("%d��",T->data);
  if(T->parent) /* T��˫�� */
  {
    printf("%d",T->parent->data);
#endif
    if(T->parent->lchild==T)
      printf("������\n");
    else
      printf("���Һ���\n");
  }
  else
    printf("�����\n");
  return OK;
}
void main()
{
  int i;
  BiPTree T,c,q;
  TElemType e1,e2;
  InitBiTree(&T);
  printf("����ն�������,���շ�%d(1:�� 0:��) �������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
  e1=Root(T);
  if(e1!=Nil)
#ifdef CHAR
    printf("�������ĸ�Ϊ: %c\n",e1);
#endif
#ifdef INT
    printf("�������ĸ�Ϊ: %d\n",e1);
#endif
  else
    printf("���գ��޸�\n");
#ifdef CHAR
  printf("�밴�������������(��:ab�����ո��ʾaΪ�����,bΪ�������Ķ�����)\n");
#endif
#ifdef INT
  printf("�밴�������������(��:1 2 0 0 0��ʾ1Ϊ�����,2Ϊ�������Ķ�����)\n");
#endif
  CreateBiTree(&T);
  printf("������������,���շ�%d(1:�� 0:��) �������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
  e1=Root(T);
  if(e1!=Nil)
#ifdef CHAR
    printf("�������ĸ�Ϊ: %c\n",e1);
#endif
#ifdef INT
    printf("�������ĸ�Ϊ: %d\n",e1);
#endif
  else
    printf("���գ��޸�\n");
  printf("����ݹ����������:\n");
  InOrderTraverse(T,visitT);
  printf("����ݹ����������:\n");
  PostOrderTraverse(T,visitT);
  scanf("%*c"); /* �Ե��س��� */
  printf("���س�������:");
  getchar(); /* ��ͣ��� */
  printf("�������������:\n");
  LevelOrderTraverse(T,visitT);
  printf("������һ������ֵ: ");
#ifdef CHAR
  scanf("%c",&e1);
#endif
#ifdef INT
  scanf("%d",&e1);
#endif
  c=Point(T,e1); /* cΪe1��ָ�� */
#ifdef CHAR
  printf("����ֵΪ%c\n",Value(c));
#endif
#ifdef INT
  printf("����ֵΪ%d\n",Value(c));
#endif
  printf("���ı�˽���ֵ����������ֵ: ");
#ifdef CHAR
  scanf("%*c%c%*c",&e2);
#endif
#ifdef INT
  scanf("%d",&e2);
#endif
  Assign(c,e2);
  printf("�������������:\n");
  LevelOrderTraverse(T,visitT);
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
  InitBiTree(&c);
  printf("����һ��������Ϊ�յĶ�����c:\n");
#ifdef CHAR
  printf("���������������(��:ab�����ո��ʾaΪ�����,bΪ�������Ķ�����)\n");
#endif
#ifdef INT
  printf("���������������(��:1 2 0 0 0��ʾ1Ϊ�����,2Ϊ�������Ķ�����)\n");
#endif
  CreateBiTree(&c);
  printf("����ݹ����������c:\n");
  PreOrderTraverse(c,visitT);
  printf("��c�嵽��T��,��������T����c��˫�׽�� cΪ��(0)����(1)����: ");
#ifdef CHAR
  scanf("%*c%c%d",&e1,&i);
#endif
#ifdef INT
  scanf("%d%d",&e1,&i);
#endif
  q=Point(T,e1);
  InsertChild(q,i,c);
  printf("����ݹ����������:\n");
  PreOrderTraverse(T,visitT);
  printf("ɾ������,�������ɾ��������˫�׽��  ��(0)����(1)����: ");
#ifdef CHAR
  scanf("%*c%c%d",&e1,&i);
#endif
#ifdef INT
  scanf("%d%d",&e1,&i);
#endif
  q=Point(T,e1);
  DeleteChild(q,i);
  printf("����ݹ����������:\n");
  PreOrderTraverse(T,visitT);
  DestroyBiTree(&T);
}
