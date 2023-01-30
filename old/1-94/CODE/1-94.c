#include<limits.h> /* INT_MAX�� */
#include<stdio.h> /* EOF(=^Z��F6),NULL */
#define OK 1
#define ERROR 0
#define N 5 /* ����Ԫ�ظ��� */
typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int Boolean; /* Boolean�ǲ�������,��ֵ��TRUE��FALSE */
typedef int KeyType; /* ��ؼ�����Ϊ���� */
typedef struct /* ����Ԫ������(�Խ̿���ͼ9.1�߿��ɼ�Ϊ��) */
{
  long number; /* ׼��֤�� */
  char name[9]; /* ����(4�����ּ�1����������־) */
  int politics; /* ���� */
  int Chinese; /* ���� */
  int English; /* Ӣ�� */
  int math; /* ��ѧ */
  int physics; /* ���� */
  int chemistry; /* ��ѧ */
  int biology; /* ���� */
  KeyType key; /* �ؼ�������ӦΪKeyType,����ӦΪkey,��bo9-1.c��һ�� */
} ElemType;
ElemType r[N]={{179324,"�η���",85,89,98,100,93,80,47},
               {179325,"�º�",85,86,88,100,92,90,45},
               {179326,"½��",78,75,90,80,95,88,37},
               {179327,"��ƽ",82,80,78,98,84,96,40},
               {179328,"��С��",76,85,94,57,77,69,44}}; /* ȫ�ֱ��� */
#define total key /* �����ܷ�(total)Ϊ�ؼ��� */
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))
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
Status Destroy(SSTable *ST)
{ /* ��ʼ����: ��̬���ұ�ST���ڡ��������: ���ٱ�ST */
  free((*ST).elem);
  (*ST).elem=NULL;
  (*ST).length=0;
  return OK;
}
int Search_Seq(SSTable ST,KeyType key)
{ /* ��˳���ST��˳�������ؼ��ֵ���key������Ԫ�ء����ҵ�������ֵΪ */
  /* ��Ԫ���ڱ��е�λ�ã�����Ϊ0��*/
  int i;
  ST.elem[0].key=key; /* �ڱ� */
  for(i=ST.length;!EQ(ST.elem[i].key,key);--i); /* �Ӻ���ǰ�� */
  return i; /* �Ҳ���ʱ��iΪ0 */
}
int Search_Bin(SSTable ST,KeyType key)
{ /* �������ST���۰������ؼ��ֵ���key������Ԫ�ء����ҵ�������ֵΪ */
  /* ��Ԫ���ڱ��е�λ�ã�����Ϊ0��*/
  int low,high,mid;
  low=1; /* �������ֵ */
  high=ST.length;
  while(low<=high)
  {
    mid=(low+high)/2;
    if EQ(key,ST.elem[mid].key)  /* �ҵ�����Ԫ�� */
      return mid;
    else if LT(key,ST.elem[mid].key)
      high=mid-1; /* ������ǰ��������в��� */
    else
      low=mid+1; /* �����ں��������в��� */
  }
  return 0; /* ˳����в����ڴ���Ԫ�� */
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
void print(ElemType c) /* Traverse()���õĺ��� */
{ printf("%-8ld%-8s%4d%5d%5d%5d%5d%5d%5d%5d\n",c.number,c.name,c.politics,c.Chinese,c.English,c.math,c.physics,c.chemistry,c.biology,c.total);
}
void main()
{
  SSTable st;
  int i,s;
  for(i=0;i<N;i++) /* �����ܷ� */
    r[i].total=r[i].politics+r[i].Chinese+r[i].English+r[i].math+r[i].physics+r[i].chemistry+r[i].biology;
  Creat_Seq(&st,N); /* ��ȫ�����������̬���ұ�st */
  printf("׼��֤��  ����  ���� ���� ���� ��ѧ ���� ��ѧ ���� �ܷ�\n");
  Traverse(st,print); /* ��˳�������̬���ұ�st */
  printf("������������˵��ܷ�: ");
  scanf("%d",&s);
  i=Search_Seq(st,s); /* ˳����� */
  if(i)
    print(*(st.elem+i));
  else
    printf("û�ҵ�\n");
  Destroy(&st);
}
