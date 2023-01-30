#include<stdio.h>
#define N 10
#define T 3
#define LT(a,b) ((a)<(b))
#define MAXSIZE 20 /* һ������ʾ����С˳������󳤶� */
typedef int InfoType; /* ������������������� */
typedef int KeyType; /* ����ؼ�������Ϊ���� */
typedef struct
{
  KeyType key; /* �ؼ����� */
  InfoType otherinfo; /* ������������������������ж��� */
}RedType; /* ��¼���� */

typedef struct
{
  RedType r[MAXSIZE+1]; /* r[0]���û������ڱ���Ԫ */
  int length; /* ˳����� */
}SqList; /* ˳������� */
void ShellInsert(SqList *L,int dk)
{ /* ��˳���L��һ��ϣ���������򡣱��㷨�Ǻ�һ��ֱ�Ӳ���������ȣ� */
  /* ���������޸ģ� */
  /* 1.ǰ���¼λ�õ�������dk,������1; */
  /* 2.r[0]ֻ���ݴ浥Ԫ,�����ڱ�����j<=0ʱ,����λ�����ҵ���*/
  int i,j;
  for(i=dk+1;i<=(*L).length;++i)
    if LT((*L).r[i].key,(*L).r[i-dk].key)
    { /* �轫(*L).r[i]�������������ӱ� */
      (*L).r[0]=(*L).r[i]; /* �ݴ���(*L).r[0] */
      for(j=i-dk;j>0&&LT((*L).r[0].key,(*L).r[j].key);j-=dk)
        (*L).r[j+dk]=(*L).r[j]; /* ��¼���ƣ����Ҳ���λ�� */
      (*L).r[j+dk]=(*L).r[0]; /* ���� */
    }
}
void print(SqList L)
{
  int i;
  for(i=1;i<=L.length;i++)
    printf("%d ",L.r[i].key);
  printf("\n");
}
void print1(SqList L)
{
  int i;
  for(i=1;i<=L.length;i++)
    printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
  printf("\n");
}
void ShellSort(SqList *L,int dlta[],int t)
{ /* ����������dlta[0..t-1]��˳���L��ϣ������*/
  int k;
  for(k=0;k<t;++k)
  {
    ShellInsert(L,dlta[k]); /* һ������Ϊdlta[k]�Ĳ������� */
    printf("��%d��������: ",k+1);
    print(*L);
  }
}
void main()
{
  RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8},{55,9},{4,10}};
  SqList l;
  int i,dt[T]={5,3,1}; /* ������������ */
  for(i=0;i<N;i++)
    l.r[i+1]=d[i];
  l.length=N;
  printf("����ǰ: ");
  print(l);
  ShellSort(&l,dt,T);
  printf("�����: ");
  print1(l);
}
