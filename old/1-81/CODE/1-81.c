#include<limits.h> /* INT_MAX�� */
#include<stdio.h> /* EOF(=^Z��F6),NULL */
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
void Sort(SLinkListType L,int adr[])
{ /* ���adr[1..L.length]��adr[i]Ϊ��̬����L�ĵ�i����С��¼����� */
  int i=1,p=L.r[0].next;
  while(p)
  {
    adr[i++]=p;
    p=L.r[p].next;
  }
}
void Rearrange(SLinkListType *L,int adr[])
{ /* adr������̬����L��������򣬼�L.r[adr[i]]�ǵ�iС�ļ�¼�� */
  int i,j,k;
  for(i=1;i<(*L).length;++i)
    if(adr[i]!=i)
    {
      j=i;
      (*L).r[0]=(*L).r[i]; /* �ݴ��¼(*L).r[i] */
      while(adr[j]!=i)
      { /* ����(*L).r[adr[j]]�ļ�¼��λֱ��adr[j]=iΪֹ */
        k=adr[j];
        (*L).r[j]=(*L).r[k];
        adr[j]=j;
        j=k; /* ��¼����λ */
      }
      (*L).r[j]=(*L).r[0];
      adr[j]=j;
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
  adr=(int*)malloc((l1.length+1)*sizeof(int));
  Sort(l1,adr);
  for(i=1;i<=l1.length;i++)
    printf("adr[%d]=%d ",i,adr[i]);
  printf("\n");
  Rearrange(&l1,adr);
  printf("l1�����:\n");
  print(l1);
}
