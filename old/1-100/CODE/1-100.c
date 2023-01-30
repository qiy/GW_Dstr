#include<stdio.h> /* EOF(=^Z��F6),NULL */
#define OK 1
typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
#define N 16 /* ����Ԫ�ظ��� */
#define LENGTH 27 /* ��������+1(��дӢ����ĸ) */
typedef struct
{
  int ord;
}Others; /* ��¼���������� */
#define Nil ' ' /* ���������Ϊ�ո�(��̿��鲻ͬ) */
#define MAXKEYLEN 16 /* �ؼ��ֵ���󳤶ȣ�ͬc9-4.h */
typedef struct
{
  char ch[MAXKEYLEN]; /* �ؼ��� */
  int num; /* �ؼ��ֳ��� */
}KeysType; 
typedef struct
{
  KeysType key; /* �ؼ��� */
  Others others; /* ��������(�����̶���) */
}Record; 
typedef enum{LEAF,BRANCH}NodeKind; 
typedef struct TrieNode /* Trie�������� */
{
  NodeKind kind;
  union
  {
    struct /* Ҷ�ӽ�� */
    {
      KeysType K;
      Record *infoptr;
    }lf;
    struct /* ��֧��� */
    {
      struct TrieNode *ptr[LENGTH]; /* LENGTHΪ��������+1,�����̶��� */
    /*  int num; �� */
    }bh;
  }a;
}TrieNode,*TrieTree;
#define EQ(a,b) (!strcmp((a),(b)))
Status InitDSTable(TrieTree *T)
{ /* �������: ����һ���յ�Trie����T */
  *T=NULL;
  return OK;
}
void DestroyDSTable(TrieTree *T)
{ /* ��ʼ����: Trie��T���ڡ��������: ����Trie��T */
  int i;
  if(*T) /* �ǿ��� */
  {
    for(i=0;i<LENGTH;i++)
      if((*T)->kind==BRANCH&&(*T)->a.bh.ptr[i]) /* ��i����㲻�� */
        if((*T)->a.bh.ptr[i]->kind==BRANCH) /* ������ */
          DestroyDSTable(&(*T)->a.bh.ptr[i]);
        else /* ��Ҷ�� */
        {
          free((*T)->a.bh.ptr[i]);
          (*T)->a.bh.ptr[i]=NULL;
        }
    free(*T); /* �ͷŸ���� */
    *T=NULL; /* ��ָ�븳0 */
  }
}
int ord(char c)
{
  c=toupper(c);
  if(c>='A'&&c<='Z')
    return c-'A'+1; /* Ӣ����ĸ����������ĸ���е���� */
  else
    return 0; /* �����ַ�����0 */
}
Record *SearchTrie(TrieTree T,KeysType K)
{ /* �ڼ���T�в��ҹؼ��ֵ���K�ļ�¼��*/
  TrieTree p;
  int i;
  for(p=T,i=0;p&&p->kind==BRANCH&&i<K.num;p=p->a.bh.ptr[ord(K.ch[i])],++i);
  /* ��K��ÿ���ַ��������,*pΪ��֧���,ord()���ַ�����ĸ������� */
  if(p&&p->kind==LEAF&&p->a.lf.K.num==K.num&&EQ(p->a.lf.K.ch,K.ch)) /* ���ҳɹ� */
    return p->a.lf.infoptr;
  else /* ���Ҳ��ɹ� */
    return NULL;
}
void InsertTrie(TrieTree *T,Record *r)
{ /* ��ʼ����: Trie����T���ڣ�rΪ�����������Ԫ�ص�ָ�� */
  /* �������: ��T�в�������ؼ��ֵ���(*r).key.ch������Ԫ�أ� */
  /*           �򰴹ؼ���˳���r��T�� */
  TrieTree p,q,ap;
  int i=0,j;
  KeysType K1,K=r->key;
  if(!*T) /* ���� */
  {
    *T=(TrieTree)malloc(sizeof(TrieNode));
    (*T)->kind=BRANCH;
    for(i=0;i<LENGTH;i++) /* ָ��������ֵNULL */
      (*T)->a.bh.ptr[i]=NULL;
    p=(*T)->a.bh.ptr[ord(K.ch[0])]=(TrieTree)malloc(sizeof(TrieNode));
    p->kind=LEAF;
    p->a.lf.K=K;
    p->a.lf.infoptr=r;
  }
  else /* �ǿ��� */
  {
    for(p=*T,i=0;p&&p->kind==BRANCH&&i<K.num;++i)
    {
      q=p;
      p=p->a.bh.ptr[ord(K.ch[i])];
    }
    i--;
    if(p&&p->kind==LEAF&&p->a.lf.K.num==K.num&&EQ(p->a.lf.K.ch,K.ch)) /* T�д��ڸùؼ��� */
      return;
    else /* T�в����ڸùؼ���,����֮ */
    {
      if(!p) /* ��֧�� */
      {
        p=q->a.bh.ptr[ord(K.ch[i])]=(TrieTree)malloc(sizeof(TrieNode));
        p->kind=LEAF;
        p->a.lf.K=K;
        p->a.lf.infoptr=r;
      }
      else if(p->kind==LEAF) /* �в���ȫ��ͬ��Ҷ�� */
      {
        K1=p->a.lf.K;
        do
       {
          ap=q->a.bh.ptr[ord(K.ch[i])]=(TrieTree)malloc(sizeof(TrieNode));
          ap->kind=BRANCH;
          for(j=0;j<LENGTH;j++) /* ָ��������ֵNULL */
            ap->a.bh.ptr[j]=NULL;
          q=ap;
          i++;
        }while(ord(K.ch[i])==ord(K1.ch[i]));
        q->a.bh.ptr[ord(K1.ch[i])]=p;
        p=q->a.bh.ptr[ord(K.ch[i])]=(TrieTree)malloc(sizeof(TrieNode));
        p->kind=LEAF;
        p->a.lf.K=K;
        p->a.lf.infoptr=r;
      }
    }
  }
}
void TraverseDSTable(TrieTree T,Status(*Vi)(Record*))
{ /* ��ʼ����: Trie����T���ڣ�Vi�ǶԼ�¼ָ�������Ӧ�ú��� */
  /* �������: ���ؼ��ֵ�˳������ؼ��ּ����Ӧ�ļ�¼ */
  TrieTree p;
  int i;
  if(T)
  {
    for(i=0;i<LENGTH;i++)
    {
      p=T->a.bh.ptr[i];
      if(p&&p->kind==LEAF)
        Vi(p->a.lf.infoptr);
      else if(p&&p->kind==BRANCH)
        TraverseDSTable(p,Vi);
    }
  }
}
Status pr(Record *r)
{
  printf("(%s,%d)",r->key.ch,r->others.ord);
  return OK;
}
void main()
{
  TrieTree t;
  int i;
  char s[MAXKEYLEN+1];
  KeysType k;
  Record *p;
  Record r[N]={{{"CAI"},1},{{"CAO"},2},{{"LI"},3},{{"LAN"},4},
               {{"CHA"},5},{{"CHANG"},6},{{"WEN"},7},{{"CHAO"},8},
               {{"YUN"},9},{{"YANG"},10},{{"LONG"},11},{{"WANG"},12},
               {{"ZHAO"},13},{{"LIU"},14},{{"WU"},15},{{"CHEN"},16}};
  /* ����Ԫ��(�Խ̿���ʽ9-24Ϊ��) */
  InitDSTable(&t);
  for(i=0;i<N;i++)
  {
    r[i].key.num=strlen(r[i].key.ch)+1;
    r[i].key.ch[r[i].key.num]=Nil; /* �ڹؼ��ַ������ӽ����� */
    p=SearchTrie(t,r[i].key);
    if(!p)
      InsertTrie(&t,&r[i]);
  }
  printf("���ؼ��ַ�����˳�����Trie��(����):\n");
  TraverseDSTable(t,pr);
  printf("\n����������Ҽ�¼�Ĺؼ��ַ���: ");
  scanf("%s",s);
  k.num=strlen(s)+1;
  strcpy(k.ch,s);
  k.ch[k.num]=Nil; /* �ڹؼ��ַ������ӽ����� */
  p=SearchTrie(t,k);
  if(p)
    pr(p);
  else
    printf("û�ҵ�");
  printf("\n");
  DestroyDSTable(&t);
}
