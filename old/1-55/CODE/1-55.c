#include<stdio.h> /* EOF(=^Z��F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
#if CHAR
typedef char TElemType;
  TElemType Nil=' '; /* ���ַ����Կո��Ϊ�� */
#else
  typedef int TElemType;
  TElemType Nil=0; /* ��������0Ϊ�� */
#endif
#define MAX_TREE_SIZE 100 /* ��������������� */
typedef TElemType SqBiTree[MAX_TREE_SIZE]; /* 0�ŵ�Ԫ�洢����� */
Status InitBiTree(SqBiTree T)
{ /* ����ն�����T����ΪT�ǹ̶����飬����ı䣬�ʲ���Ҫ& */
  int i;
  for(i=0;i<MAX_TREE_SIZE;i++)
    T[i]=Nil; /* ��ֵΪ�� */
  return OK;
}
Status CreateBiTree(SqBiTree T)
{ /* �������������������н���ֵ(�ַ��ͻ�����), ����˳��洢�Ķ�����T */
  int i=0;
#if CHAR
  int l;
  char s[MAX_TREE_SIZE];
  printf("�밴�����������ֵ(�ַ�)���ո��ʾ�ս�㣬�������%d:\n",MAX_TREE_SIZE);
  gets(s); /* �����ַ��� */
  l=strlen(s); /* ���ַ����ĳ��� */
  for(;i<l;i++) /* ���ַ�����ֵ��T */
  {
    T[i]=s[i];
    if(i!=0&&T[(i+1)/2-1]==Nil&&T[i]!=Nil) /* �˽��(����)��˫���Ҳ��Ǹ� */
    {
      printf("������˫�׵ķǸ����%c\n",T[i]);
      exit(ERROR);
    }
  }
  for(i=l;i<MAX_TREE_SIZE;i++) /* ���ո�ֵ��T�ĺ���Ľ�� */
    T[i]=Nil;
#else
  printf("�밴�����������ֵ(����)��0��ʾ�ս�㣬��999�������������%d:\n",MAX_TREE_SIZE);
  while(1)
  {
    scanf("%d",&T[i]);
    if(T[i]==999)
      break;
    if(i!=0&&T[(i+1)/2-1]==Nil&&T[i]!=Nil) /* �˽��(����)��˫���Ҳ��Ǹ� */
    {
      printf("������˫�׵ķǸ����%d\n",T[i]);
      exit(ERROR);
    }
    i++;
  }
  while(i<MAX_TREE_SIZE)
  {
    T[i]=Nil; /* ���ո�ֵ��T�ĺ���Ľ�� */
    i++;
  }
#endif
  return OK;
}
Status BiTreeEmpty(SqBiTree T)
{ /* ��ʼ����: ������T���� */
  /* �������: ��TΪ�ն�����,�򷵻�TRUE,����FALSE */
  if(T[0]==Nil) /* �����Ϊ��,������ */
    return TRUE;
  else
    return FALSE;
}
int BiTreeDepth(SqBiTree T)
{ /* ��ʼ����: ������T���ڡ��������: ����T����� */
  int i,j=-1;
  for(i=MAX_TREE_SIZE-1;i>=0;i--) /* �ҵ����һ����� */
    if(T[i]!=Nil)
      break;
  i++; /* Ϊ�˱��ڼ��� */
  do
    j++;
  while(i>=pow(2,j));
  return j;
}
Status Root(SqBiTree T,TElemType *e)
{ /* ��ʼ����: ������T���� */
  /* �������:  ��T����,��e����T�ĸ�,����OK;���򷵻�ERROR,e�޶��� */
  if(BiTreeEmpty(T)) /* T�� */
    return ERROR;
  else
  {
    *e=T[0];
    return OK;
  }
}
void main()
{
   Status i;
  TElemType e;
  SqBiTree T;
  InitBiTree(T);
  CreateBiTree(T);
  printf("������������,���շ�%d(1:�� 0:��) �������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
  i=Root(T,&e);
  if(i)
    printf("�������ĸ�Ϊ��%d\n",e);
  else
    printf("���գ��޸�\n");
}
