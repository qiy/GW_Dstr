#include<stdio.h> /* EOF(=^Z��F6),NULL */
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
#define N 9 /* ����Ԫ�ظ��� */
typedef char KeyType; /* ��ؼ�����Ϊ�ַ��� */
typedef struct /* ����Ԫ������ */
{
  KeyType key;
  int weight;
}ElemType;
ElemType r[N]={{'A',1},{'B',1},{'C',2},{'D',5},{'E',3},
               {'F',4},{'G',4},{'H',3},{'I',5}}; /* ����Ԫ��(�Խ̿�����9-1Ϊ��),ȫ�ֱ��� */
int sw[N+1]; /* �ۼ�Ȩֵ��ȫ�ֱ��� */
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
typedef struct
{
  ElemType *elem; /* ����Ԫ�ش洢�ռ��ַ������ʱ��ʵ�ʳ��ȷ��䣬0�ŵ�Ԫ���� */
  int length; /* ���� */
}SSTable;
Status Creat_Seq(SSTable *ST,int n)
{ /* �������: ����һ����n������Ԫ�صľ�̬˳����ұ�ST(��������ȫ������r) */
  int i;
  (*ST).elem=(ElemType *)calloc(n+1,sizeof(ElemType)); /* ��̬����n������Ԫ�ؿռ�(0�ŵ�Ԫ����) */
  if(!(*ST).elem)
    return ERROR;
  for(i=1;i<=n;i++)
    *((*ST).elem+i)=r[i-1]; /* ��ȫ������r��ֵ���θ���ST */
  (*ST).length=n;
  return OK;
}
void Ascend(SSTable *ST)
{ /* �ؽ���̬���ұ�Ϊ���ؼ��ַǽ������� */
  int i,j,k;
  for(i=1;i<(*ST).length;i++)
  {
    k=i;
    (*ST).elem[0]=(*ST).elem[i]; /* ���Ƚ�ֵ��[0]��Ԫ */
    for(j=i+1;j<=(*ST).length;j++)
      if LT((*ST).elem[j].key,(*ST).elem[0].key)
      {
        k=j;
        (*ST).elem[0]=(*ST).elem[j];
      }
    if(k!=i) /* �и�С��ֵ�򽻻� */
    {
      (*ST).elem[k]=(*ST).elem[i];
      (*ST).elem[i]=(*ST).elem[0];
    }
  }
}
Status Creat_Ord(SSTable *ST,int n)
{ /* �������: ����һ����n������Ԫ�صľ�̬���ؼ��ַǽ�����ұ�ST */
  /* ��������ȫ������r */
  Status f;
  f=Creat_Seq(ST,n);
  if(f)
    Ascend(ST);
  return f;
}
Status Traverse(SSTable ST,void(*Visit)(ElemType))
{ /* ��ʼ����: ��̬���ұ�ST���ڣ�Visit()�Ƕ�Ԫ�ز�����Ӧ�ú��� */
  /* �������: ��˳���ST��ÿ��Ԫ�ص��ú���Visit()һ���ҽ�һ�Ρ� */
  /* һ��Visit()ʧ�ܣ������ʧ�� */
  ElemType *p;
  int i;
  p=++ST.elem; /* pָ���һ��Ԫ�� */
  for(i=1;i<=ST.length;i++)
    Visit(*p++);
  return OK;
}
typedef ElemType TElemType;
typedef struct BiTNode
{
  TElemType data;
  struct BiTNode *lchild,*rchild; /* ���Һ���ָ�� */
}BiTNode,*BiTree;
Status SecondOptimal(BiTree *T, ElemType R[],int sw[],int low,int high)
{ /* �������R[low..high]�����ۼ�Ȩֵ��sw(����sw[0]==0)�ݹ鹹�� */
  /* ���Ų�����T��*/
  int i,j;
  double min,dw;
  i=low;
  min=fabs(sw[high]-sw[low]);
  dw=sw[high]+sw[low-1];
  for(j=low+1;j<=high;++j) /* ѡ����С�ġ�Piֵ */
    if(fabs(dw-sw[j]-sw[j-1])<min)
    {
      i=j;
      min=fabs(dw-sw[j]-sw[j-1]);
    }
  *T=(BiTree)malloc(sizeof(BiTNode));
  if(!*T)
    return ERROR;
  (*T)->data=R[i]; /* ���ɽ�� */
  if(i==low)
    (*T)->lchild=NULL; /* �������� */
  else
    SecondOptimal(&(*T)->lchild,R,sw,low,i-1); /* ���������� */
  if(i==high)
    (*T)->rchild=NULL; /* �������� */
  else
    SecondOptimal(&(*T)->rchild,R,sw,i+1,high); /* ���������� */
  return OK;
}
void FindSW(int sw[],SSTable ST)
{ /* ���������ST�и�����Ԫ�ص�Weight�����ۼ�Ȩֵ��sw */
  int i;
  sw[0]=0;
  for(i=1;i<=ST.length;i++)
    sw[i]=sw[i-1]+ST.elem[i].weight;
}
typedef BiTree SOSTree; /* ���Ų��������ö�������Ĵ洢�ṹ */
Status CreateSOSTree(SOSTree *T,SSTable ST)
{ /* �������ST����һ�ô��Ų�����T��ST������Ԫ�غ���Ȩ��weight��*/
  if(ST.length==0)
    *T=NULL;
  else
  {
    FindSW(sw,ST); /* ���������ST�и�����Ԫ�ص�Weight�����ۼ�Ȩֵ��sw */
    SecondOptimal(T,ST.elem,sw,1,ST.length);
  }
  return OK;
}
Status Search_SOSTree(SOSTree *T,KeyType key)
{ /* �ڴ��Ų�����T�в��ҹؼ��ֵ���key��Ԫ�ء��ҵ��򷵻�OK�����򷵻�FALSE */
  while(*T) /* T�ǿ� */
    if((*T)->data.key==key)
      return OK;
    else if((*T)->data.key>key)
      *T=(*T)->lchild;
    else
      *T=(*T)->rchild;
  return FALSE; /* ˳����в����ڴ���Ԫ�� */
}

void print(ElemType c) /* Traverse()���õĺ��� */
{
  printf("(%c %d) ",c.key,c.weight);
}
void main()
{
  SSTable st;
  SOSTree t;
  Status i;
  KeyType s;
  Creat_Ord(&st,N); /* ��ȫ����������ǽ���̬���ұ�st */
  Traverse(st,print);
  CreateSOSTree(&t,st); /* ���������һ�ô��Ų����� */
  printf("\n����������ҵ��ַ�: ");
  scanf("%c",&s);
  i=Search_SOSTree(&t,s);
  if(i)
    printf("%c��Ȩֵ��%d\n",s,t->data.weight);
  else
    printf("���в����ڴ��ַ�\n");
}
