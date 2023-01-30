#include<stdio.h> /* EOF(=^Z��F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
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
typedef struct
{
  int level,order; /* ���Ĳ�,�������(��������������) */
}position;
/* bo6-1.c ��������˳��洢(�洢�ṹ��c6-1.h����)�Ļ�������(23��) */
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
TElemType Value(SqBiTree T,position e)
{ /* ��ʼ����: ������T����,e��T��ĳ�����(��λ��) */
  /* �������: ���ش���λ��e(��,�������)�Ľ���ֵ */
  return T[(int)pow(2,e.level-1)+e.order-2];
}
Status Assign(SqBiTree T,position e,TElemType value)
{ /* ��ʼ����: ������T����,e��T��ĳ�����(��λ��) */
  /* �������: ������λ��e(��,�������)�Ľ�㸳��ֵvalue */
  int i=(int)pow(2,e.level-1)+e.order-2; /* ���㡢�������תΪ�������� */
  if(value!=Nil&&T[(i+1)/2-1]==Nil) /* ��Ҷ�Ӹ��ǿ�ֵ��˫��Ϊ�� */
    return ERROR;
  else if(value==Nil&&(T[i*2+1]!=Nil||T[i*2+2]!=Nil)) /*  ��˫�׸���ֵ����Ҷ�ӣ����գ� */
    return ERROR;
  T[i]=value;
  return OK;
}
Status(*VisitFunc)(TElemType); /* �������� */
void PreTraverse(SqBiTree T,int e)
{ /* PreOrderTraverse()���� */
  VisitFunc(T[e]);
  if(T[2*e+1]!=Nil) /* ���������� */
    PreTraverse(T,2*e+1);
  if(T[2*e+2]!=Nil) /* ���������� */
    PreTraverse(T,2*e+2);
}
Status PreOrderTraverse(SqBiTree T,Status(*Visit)(TElemType))
{ /* ��ʼ����: ����������,Visit�ǶԽ�������Ӧ�ú��� */
  /* �������: �������T,��ÿ�������ú���Visitһ���ҽ�һ�Ρ� */
  /*           һ��Visit()ʧ��,�����ʧ�� */
  VisitFunc=Visit;
  if(!BiTreeEmpty(T)) /* ������ */
    PreTraverse(T,0);
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
  Status i;
  position p;
  TElemType e;
  SqBiTree T;
  InitBiTree(T);
  CreateBiTree(T);
  printf("��������޸Ľ��Ĳ�� �������: ");
  scanf("%d%d",&p.level,&p.order);
  e=Value(T,p);
  printf("���޸Ľ���ԭֵΪ%d��������ֵ: ",e);
  scanf("%d",&e);
  Assign(T,p,e);
  printf("�������������:\n");
  PreOrderTraverse(T,visit);
}
