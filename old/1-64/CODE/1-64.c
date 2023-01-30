#define CHAR /* �ַ��� */
#include<stdio.h> /* EOF(=^Z��F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define STACK_INIT_SIZE 10 /* �洢�ռ��ʼ������ */
#define STACKINCREMENT 2 /* �洢�ռ�������� */
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
typedef BiTree SElemType; /* ��ջԪ��Ϊ��������ָ������ */

typedef struct SqStack
{
  SElemType *base; /* ��ջ����֮ǰ������֮��base��ֵΪNULL */
  SElemType *top; /* ջ��ָ�� */
  int stacksize; /* ��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ */
}SqStack; /* ˳��ջ */
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
Status InitStack(SqStack *S)
{ /* ����һ����ջS */
  (*S).base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
  if(!(*S).base)
    exit(OVERFLOW); /* �洢����ʧ�� */
  (*S).top=(*S).base;
  (*S).stacksize=STACK_INIT_SIZE;
  return OK;
}
Status StackEmpty(SqStack S)
{ /* ��ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE */
  if(S.top==S.base)
    return TRUE;
  else
    return FALSE;
}
Status Push(SqStack *S,SElemType e)
{ /* ����Ԫ��eΪ�µ�ջ��Ԫ�� */
  if((*S).top-(*S).base>=(*S).stacksize) /* ջ����׷�Ӵ洢�ռ� */
  {
    (*S).base=(SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
    if(!(*S).base)
      exit(OVERFLOW); /* �洢����ʧ�� */
    (*S).top=(*S).base+(*S).stacksize;
    (*S).stacksize+=STACKINCREMENT;
  }
  *((*S).top)++=e;
  return OK;
}
Status Pop(SqStack *S,SElemType *e)
{ /* ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR */
  if((*S).top==(*S).base)
    return ERROR;
  *e=*--(*S).top;
  return OK;
}
Status InOrderTraverse1(BiTree T,Status(*Visit)(TElemType))
{ /* ���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����*/
  /* �������������T�ķǵݹ��㷨(����ջ)����ÿ������Ԫ�ص��ú���Visit */
  SqStack S;
  InitStack(&S);
  while(T||!StackEmpty(S))
  {
    if(T)
    { /* ��ָ���ջ,���������� */
      Push(&S,T);
      T=T->lchild;
    }
    else
    { /* ��ָ����ջ,���ʸ����,���������� */
      Pop(&S,&T);
      if(!Visit(T->data))
        return ERROR;
      T=T->rchild;
    }
  }
  printf("\n");
  return OK;
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
  printf("����ǵݹ����������:\n");
  InOrderTraverse1(T,visitT);
}
