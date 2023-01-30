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
void PostOrderTraverse(BiTree T,Status(*Visit)(TElemType))
{ /* ��ʼ����: ������T����,Visit�ǶԽ�������Ӧ�ú��� */
  /* �������: ����ݹ����T,��ÿ�������ú���Visitһ���ҽ�һ�� */
  if(T) /* T���� */
  {
    PostOrderTraverse(T->lchild,Visit); /* �Ⱥ������������ */
    PostOrderTraverse(T->rchild,Visit); /* �ٺ������������ */
    Visit(T->data); /* �����ʸ���� */
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
  printf("����ݹ����������:\n");
  PostOrderTraverse(T,visitT);
}
