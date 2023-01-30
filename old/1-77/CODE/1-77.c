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
void InsertSort(SqList *L)
{ /* ��˳���L��ֱ�Ӳ�������*/
  int i,j;
  for(i=2;i<=(*L).length;++i)
    if LT((*L).r[i].key,(*L).r[i-1].key) /* "<",�轫L.r[i]���������ӱ� */
    {
      (*L).r[0]=(*L).r[i]; /* ����Ϊ�ڱ� */
      for(j=i-1;LT((*L).r[0].key,(*L).r[j].key);--j)
 (*L).r[j+1]=(*L).r[j]; /* ��¼���� */
      (*L).r[j+1]=(*L).r[0]; /* ���뵽��ȷλ�� */
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
  InsertSort(&l1);
  printf("ֱ�Ӳ��������:\n");
  print(l1);
}
