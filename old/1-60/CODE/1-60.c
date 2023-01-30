#include<stdio.h> /* EOF(=^Z��F6),NULL */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
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
 TElemType Parent(SqBiTree T,TElemType e)
{ /* ��ʼ����: ������T����,e��T��ĳ����� */
  /* �������: ��e��T�ķǸ����,�򷵻�����˫��,���򷵻أ��գ� */
  int i;
  if(T[0]==Nil) /* ���� */
    return Nil;
  for(i=1;i<=MAX_TREE_SIZE-1;i++)
    if(T[i]==e) /* �ҵ�e */
      return T[(i+1)/2-1];
  return Nil; /* û�ҵ�e */
}
TElemType LeftChild(SqBiTree T,TElemType e)
{ /* ��ʼ����: ������T����,e��T��ĳ����� */
  /* �������: ����e�����ӡ���e������,�򷵻أ��գ� */
  int i;
  if(T[0]==Nil) /* ���� */
    return Nil;
  for(i=0;i<=MAX_TREE_SIZE-1;i++)
    if(T[i]==e) /* �ҵ�e */
      return T[i*2+1];
  return Nil; /* û�ҵ�e */
}
TElemType RightChild(SqBiTree T,TElemType e)
{ /* ��ʼ����: ������T����,e��T��ĳ����� */
  /* �������: ����e���Һ��ӡ���e���Һ���,�򷵻أ��գ� */
  int i;
  if(T[0]==Nil) /* ���� */
    return Nil;
  for(i=0;i<=MAX_TREE_SIZE-1;i++)
    if(T[i]==e) /* �ҵ�e */
      return T[i*2+2];
  return Nil; /* û�ҵ�e */
}
TElemType LeftSibling(SqBiTree T,TElemType e)
{ /* ��ʼ����: ������T����,e��T��ĳ����� */
  /* �������: ����e�����ֵܡ���e��T�����ӻ������ֵ�,�򷵻أ��գ� */
  int i;
  if(T[0]==Nil) /* ���� */
    return Nil;
  for(i=1;i<=MAX_TREE_SIZE-1;i++)
    if(T[i]==e&&i%2==0) /* �ҵ�e�������Ϊż��(���Һ���) */
      return T[i-1];
  return Nil; /* û�ҵ�e */
}
TElemType RightSibling(SqBiTree T,TElemType e)
{ /* ��ʼ����: ������T����,e��T��ĳ����� */
  /* �������: ����e�����ֵܡ���e��T���Һ��ӻ������ֵ�,�򷵻أ��գ� */
  int i;
  if(T[0]==Nil) /* ���� */
    return Nil;
  for(i=1;i<=MAX_TREE_SIZE-1;i++)
    if(T[i]==e&&i%2) /* �ҵ�e�������Ϊ����(������) */
      return T[i+1];
  return Nil; /* û�ҵ�e */
}
void main()
{
  TElemType e;
  SqBiTree T;
  InitBiTree(T);
  CreateBiTree(T);
  printf("���������ѯ����ֵ:");
  scanf("%d",&e);
  printf("���%d��˫��Ϊ%d,���Һ��ӷֱ�Ϊ",e,Parent(T,e));
  printf("%d,%d,�����ֱֵܷ�Ϊ",LeftChild(T,e),RightChild(T,e));
  printf("%d,%d\n",LeftSibling(T,e),RightSibling(T,e));
}
