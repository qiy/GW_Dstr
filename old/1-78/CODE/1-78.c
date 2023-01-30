#include<stdio.h> /* EOF(=^Z��F6),NULL */
#define N 8
#define MAXSIZE 20 /* һ������ʾ����С˳������󳤶� */
#define LT(a,b) ((a)<(b))
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
 void BInsertSort(SqList *L)
{ /* ��˳���L���۰��������*/
  int i,j,m,low,high;
  for(i=2;i<=(*L).length;++i)
  {
    (*L).r[0]=(*L).r[i]; /* ��L.r[i]�ݴ浽L.r[0] */
    low=1;
    high=i-1;
    while(low<=high)
    { /* ��r[low..high]���۰������������λ�� */
      m=(low+high)/2; /* �۰� */
      if LT((*L).r[0].key,(*L).r[m].key)
        high=m-1; /* ������ڵͰ��� */
      else
        low=m+1; /* ������ڸ߰��� */
    }
    for(j=i-1;j>=high+1;--j)
      (*L).r[j+1]=(*L).r[j]; /* ��¼���� */
    (*L).r[high+1]=(*L).r[0]; /* ���� */
  }
}
void print(SqList L)
{
  int i;
  for(i=1;i<=L.length;i++)
    printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
  printf("\n");
}
void main()
{
  RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
  SqList l1;
  int i;
  for(i=0;i<N;i++) /* ��l1.r��ֵ */
    l1.r[i+1]=d[i];
  l1.length=N;
  printf("����ǰ:\n");
  print(l1);
  BInsertSort(&l1);
  printf("�۰���������:\n");
  print(l1);
}
