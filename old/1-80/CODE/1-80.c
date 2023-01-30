#include<limits.h> /* INT_MAX�� */
#include<stdio.h> /* EOF(=^Z��F6),NULL */
#include<stdlib.h> /* atoi() */
#define N 8
#define SIZE 100 /* ��̬�������� */
typedef int KeyType; /* ����ؼ�������Ϊ���� */
typedef int InfoType; /* ������������������� */
typedef struct
{
  KeyType key; /* �ؼ����� */
  InfoType otherinfo; /* ������������������������ж��� */
}RedType; /* ��¼���� */

typedef struct
{
  RedType rc; /* ��¼�� */
  int next; /* ָ���� */
}SLNode; /* �������� */
typedef struct
{
  SLNode r[SIZE]; /* 0�ŵ�ԪΪ��ͷ��� */
  int length; /* ����ǰ���� */
}SLinkListType; /* ��̬�������� */
void TableInsert(SLinkListType *SL,RedType D[],int n)
{ /* ������D����n��Ԫ�صı��������ľ�̬����SL */
  int i,p,q;
  (*SL).r[0].rc.key=INT_MAX; /* ��ͷ����¼�Ĺؼ���ȡ�������(�ǽ�������ı�β) */
  (*SL).r[0].next=0; /* next��Ϊ0��ʾ��β(��Ϊ�ձ���ʼ��) */
  for(i=0;i<n;i++)
  {
    (*SL).r[i+1].rc=D[i]; /* ������D��ֵ������̬����SL */
    q=0;
    p=(*SL).r[0].next;
    while((*SL).r[p].rc.key<=(*SL).r[i+1].rc.key)
    { /* ��̬��������� */
      q=p;
      p=(*SL).r[p].next;
    }
    (*SL).r[i+1].next=p; /* ����ǰ��¼���뾲̬���� */
    (*SL).r[q].next=i+1;
  }
  (*SL).length=n;
}
void Arrange(SLinkListType *SL)
{ /* ���ݾ�̬����SL�и�����ָ��ֵ������¼λ�ã�ʹ��SL�м�¼���ؼ��� */
  /* �ǵݼ�����˳������*/
  int i,p,q;
  SLNode t;
  p=(*SL).r[0].next; /* pָʾ��һ����¼�ĵ�ǰλ�� */
  for(i=1;i<(*SL).length;++i)
  { /* (*SL).r[1..i-1]�м�¼�Ѱ��ؼ�����������,��i����¼��SL�еĵ�ǰλ��Ӧ��С��i */
    while(p<i)
      p=(*SL).r[p].next; /* �ҵ���i����¼������pָʾ����SL�е�ǰλ�� */
    q=(*SL).r[p].next; /* qָʾ��δ�����ı�β */
    if(p!=i)
    {
      t=(*SL).r[p]; /* ������¼��ʹ��i����¼��λ */
      (*SL).r[p]=(*SL).r[i];
      (*SL).r[i]=t;
      (*SL).r[i].next=p; /* ָ�����ߵļ�¼��ʹ���Ժ����whileѭ���һ� */
    }
    p=q; /* pָʾ��δ�����ı�β��Ϊ�ҵ�i+1����¼��׼�� */
  }
}
void Sort(SLinkListType L,int adr[])
{ /* ���adr[1..L.length]��adr[i]Ϊ��̬����L�ĵ�i����С��¼����� */
  int i=1,p=L.r[0].next;
  while(p)
  {
    adr[i++]=p;
    p=L.r[p].next;
  }
}
void print(SLinkListType L)
{
  int i;
  for(i=1;i<=L.length;i++)
    printf("key=%d ord=%d next=%d\n",L.r[i].rc.key,L.r[i].rc.otherinfo,L.r[i].next);
}
void main()
{
  RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
  SLinkListType l1;
  int *adr,i;
  TableInsert(&l1,d,N);
  printf("����ǰ:\n");
  print(l1);
  Arrange(&l1);
  printf("l1�����:\n");
  print(l1);
}
