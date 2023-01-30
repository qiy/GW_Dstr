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
typedef struct
{
  int level,order; /* ���Ĳ�,�������(��������������) */
}position;
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
 TElemType Value(SqBiTree T,position e)
{ /* ��ʼ����: ������T����,e��T��ĳ�����(��λ��) */
  /* �������: ���ش���λ��e(��,�������)�Ľ���ֵ */
  return T[(int)pow(2,e.level-1)+e.order-2];
}
 void Move(SqBiTree q,int j,SqBiTree T,int i) /* InsertChild()�õ����� */
{ /* �Ѵ�q��j��㿪ʼ��������Ϊ��T��i��㿪ʼ������ */
  if(q[2*j+1]!=Nil) /* q������������ */
    Move(q,(2*j+1),T,(2*i+1)); /* ��q��j������������ΪT��i���������� */
  if(q[2*j+2]!=Nil) /* q������������ */
    Move(q,(2*j+2),T,(2*i+2)); /* ��q��j������������ΪT��i���������� */
  T[i]=q[j]; /* ��q��j�����ΪT��i��� */
  q[j]=Nil; /* ��q��j����ÿ� */
}
 Status InsertChild(SqBiTree T,TElemType p,Status LR,SqBiTree c)
{ /* ��ʼ����: ������T����,p��T��ĳ������ֵ,LRΪ0��1,�ǿն�����c��T */
  /*           ���ཻ��������Ϊ�� */
  /* �������: ����LRΪ0��1,����cΪT��p���������������p����ԭ����� */
  /*           ���������Ϊc�������� */
  int j,k,i=0;
  for(j=0;j<(int)pow(2,BiTreeDepth(T))-1;j++) /* ����p����� */
    if(T[j]==p) /* jΪp����� */
      break;
  k=2*j+1+LR; /* kΪp������Һ��ӵ���� */
  if(T[k]!=Nil) /* pԭ��������Һ��Ӳ��� */
    Move(T,k,T,2*k+2); /* �Ѵ�T��k��㿪ʼ��������Ϊ��k������������ʼ������ */
  Move(c,i,T,k); /* �Ѵ�c��i��㿪ʼ��������Ϊ��T��k��㿪ʼ������ */
  return OK;
}
void Print(SqBiTree T)
{ /* ��㡢������������������ */
  int j,k;
  position p;
  TElemType e;
  for(j=1;j<=BiTreeDepth(T);j++)
  {
    printf("��%d��: ",j);
    for(k=1;k<=pow(2,j-1);k++)
    {
      p.level=j;
      p.order=k;
      e=Value(T,p);
      if(e!=Nil)
        printf("%d:%d ",k,e);
    }
    printf("\n");
  }
}
void main()
{
  int j;
  TElemType e;
  SqBiTree T,s;
  InitBiTree(T);
  CreateBiTree(T);
  printf("����������Ϊ�յ���s:\n");
  CreateBiTree(s);
  printf("��s�嵽��T��,��������T����s��˫�׽�� sΪ��(0)����(1)����: ");
  scanf("%d%d",&e,&j);
  InsertChild(T,e,j,s);
  Print(T);
}
