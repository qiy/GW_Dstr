#include<stdio.h> /* EOF(=^Z��F6),NULL */
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
Status(*VisitFunc)(TElemType); /* �������� */
void InTraverse(SqBiTree T,int e)
{ /* InOrderTraverse()���� */
  if(T[2*e+1]!=Nil) /* ���������� */
    InTraverse(T,2*e+1);
  VisitFunc(T[e]);
  if(T[2*e+2]!=Nil) /* ���������� */
    InTraverse(T,2*e+2);
}
Status InOrderTraverse(SqBiTree T,Status(*Visit)(TElemType))
{ /* ��ʼ����: ����������,Visit�ǶԽ�������Ӧ�ú��� */
  /* �������: �������T,��ÿ�������ú���Visitһ���ҽ�һ�Ρ� */
  /*           һ��Visit()ʧ��,�����ʧ�� */
  VisitFunc=Visit;
  if(!BiTreeEmpty(T)) /* ������ */
    InTraverse(T,0);
  printf("\n");
  return OK;
}
Status visit(TElemType e)
{
  printf("%d ",e);
  return OK;
}
void main()
{
  SqBiTree T;
  InitBiTree(T);
  CreateBiTree(T);
  printf("�������������:\n");
  InOrderTraverse(T,visit);
}
