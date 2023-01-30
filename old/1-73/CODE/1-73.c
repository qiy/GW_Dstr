#define CHAR 1 /* �ַ��� */
#if CHAR
  typedef char TElemType;
  TElemType Nil=' '; /* �ַ����Կո��Ϊ�� */
#else
  typedef int TElemType;
  TElemType Nil=0; /* ������0Ϊ�� */
#endif
#include<stdio.h> /* EOF(=^Z��F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef enum{Link,Thread}PointerTag; /* Link(0):ָ��,Thread(1):���� */
typedef struct BiThrNode
{
  TElemType data;
  struct BiThrNode *lchild,*rchild; /* ���Һ���ָ�� */
  PointerTag LTag,RTag; /* ���ұ�־ */
}BiThrNode,*BiThrTree;
Status CreateBiThrTree(BiThrTree *T)
{ /* ��������������������н���ֵ,�������������T */
  /* 0(����)/�ո�(�ַ���)��ʾ�ս�� */
  TElemType h;
#if CHAR
  scanf("%c",&h);
#else
  scanf("%d",&h);
#endif
  if(h==Nil)
    *T=NULL;
  else
  {
    *T=(BiThrTree)malloc(sizeof(BiThrNode));
    if(!*T)
      exit(OVERFLOW);
    (*T)->data=h; /* ���ɸ����(����) */
    CreateBiThrTree(&(*T)->lchild); /* �ݹ鹹�������� */
    if((*T)->lchild) /* ������ */
      (*T)->LTag=Link;
    CreateBiThrTree(&(*T)->rchild); /* �ݹ鹹�������� */
    if((*T)->rchild) /* ���Һ��� */
      (*T)->RTag=Link;
  }
  return OK;
}
BiThrTree pre; /* ȫ�ֱ���,ʼ��ָ��ոշ��ʹ��Ľ�� */
void InThreading(BiThrTree p)
{ /* �����������������������*/
  if(p)
  {
    InThreading(p->lchild); /* �ݹ������������� */
    if(!p->lchild) /* û������ */
    {
      p->LTag=Thread; /* ǰ������ */
      p->lchild=pre; /* ����ָ��ָ��ǰ�� */
    }
    if(!pre->rchild) /* ǰ��û���Һ��� */
    {
      pre->RTag=Thread; /* ������� */
      pre->rchild=p; /* ǰ���Һ���ָ��ָ����(��ǰ���p) */
    }
    pre=p; /* ����preָ��p��ǰ�� */
    InThreading(p->rchild); /* �ݹ������������� */
  }
}
Status InOrderThreading(BiThrTree *Thrt,BiThrTree T)
{ /* �������������T,����������������,Thrtָ��ͷ��㡣*/
  *Thrt=(BiThrTree)malloc(sizeof(BiThrNode));
  if(!*Thrt)
    exit(OVERFLOW);
  (*Thrt)->LTag=Link; /* ��ͷ��� */
  (*Thrt)->RTag=Thread;
  (*Thrt)->rchild=*Thrt; /* ��ָ���ָ */
  if(!T) /* ���������գ�����ָ���ָ */
    (*Thrt)->lchild=*Thrt;
  else
  {
    (*Thrt)->lchild=T;
    pre=*Thrt;
    InThreading(T); /* ��������������������� */
    pre->rchild=*Thrt;
    pre->RTag=Thread; /* ���һ����������� */
    (*Thrt)->rchild=pre;
  }
  return OK;
}
Status InOrderTraverse_Thr(BiThrTree T,Status(*Visit)(TElemType))
{ /* �����������������T(ͷ���)�ķǵݹ��㷨��*/
  BiThrTree p;
  p=T->lchild; /* pָ������ */
  while(p!=T)
  { /* �������������ʱ,p==T */
    while(p->LTag==Link)
      p=p->lchild;
    if(!Visit(p->data)) /* ������������Ϊ�յĽ�� */
      return ERROR;
    while(p->RTag==Thread&&p->rchild!=T)
    {
      p=p->rchild;
      Visit(p->data); /* ���ʺ�̽�� */
    }
    p=p->rchild;
  }
  return OK;
}
Status vi(TElemType c)
{
#if CHAR
  printf("%c ",c);
#else
  printf("%d ",c);
#endif
  return OK;
}
void main()
{
  BiThrTree H,T;
#if CHAR
  printf("�밴�������������(��:ab�����ո��ʾaΪ�����,bΪ�������Ķ�����)\n");
#else
  printf("�밴�������������(��:1 2 0 0 0��ʾ1Ϊ�����,2Ϊ�������Ķ�����)\n");
#endif
  CreateBiThrTree(&T); /* ��������������� */
  InOrderThreading(&H,T); /* ��������������������������� */
  printf("�������(���)����������:\n");
  InOrderTraverse_Thr(H,vi); /* �������(���)���������� */
  printf("\n");
}
