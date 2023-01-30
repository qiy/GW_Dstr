#include<stdio.h> /* EOF(=^Z��F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
/* �������״̬���� */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
#define N 16 /* ����Ԫ�ظ��� */
typedef struct
{
  int ord;
}Others; /* ��¼���������� */
#define Nil ' ' /* ���������Ϊ�ո�(��̿��鲻ͬ) */
#define MAXKEYLEN 16 /* �ؼ��ֵ���󳤶� */
typedef struct
{
  char ch[MAXKEYLEN]; /* �ؼ��� */
  int num; /* �ؼ��ֳ��� */
}KeysType; /* �ؼ������� */
typedef struct
{
  KeysType key; /* �ؼ��� */
  Others others; /* ��������(�����̶���) */
}Record; /* ��¼���� */
typedef enum{LEAF,BRANCH}NodeKind; /* �������:{Ҷ��,��֧} */
typedef struct DLTNode /* ˫�������� */
{
  char symbol;
  struct DLTNode *next; /* ָ���ֵܽ���ָ�� */
  NodeKind kind;
  union
  {
    Record *infoptr; /* Ҷ�ӽ��ļ�¼ָ�� */
    struct DLTNode *first; /* ��֧���ĺ�����ָ�� */
  }a;
}DLTNode,*DLTree;
Status InitDSTable(DLTree *DT)
{ /* �������: ����һ���յ�˫������DT */
  *DT=NULL;
  return OK;
}
void DestroyDSTable(DLTree *DT)
{ /* ��ʼ����: ˫������DT���ڡ��������: ����˫������DT */
  if(*DT) /* �ǿ��� */
  {
    if((*DT)->kind==BRANCH&&(*DT)->a.first) /* *DT�Ƿ�֧������к��� */
      DestroyDSTable(&(*DT)->a.first); /* ���ٺ������� */
    if((*DT)->next) /* ���ֵ� */
      DestroyDSTable(&(*DT)->next); /* �����ֵ����� */
    free(*DT); /* �ͷŸ���� */
    *DT=NULL; /* ��ָ�븳0 */
  }
}
Record *SearchDLTree(DLTree T,KeysType K)
{ /* �ڷǿ�˫������T�в��ҹؼ��ֵ���K�ļ�¼�������ڣ� */
  /* �򷵻�ָ��ü�¼��ָ�룬���򷵻ؿ�ָ�롣*/
  DLTree p;
  int i;
  if(T)
  {
    p=T; /* ��ʼ�� */
    i=0;
    while(p&&i<K.num)
    {
      while(p&&p->symbol!=K.ch[i]) /* ���ҹؼ��ֵĵ�iλ */
        p=p->next;
      if(p&&i<K.num) /* ׼��������һλ */
        p=p->a.first;
      ++i;
    } /* ���ҽ��� */
    if(!p) /* ���Ҳ��ɹ� */
      return NULL;
    else /* ���ҳɹ� */
      return p->a.infoptr;
  }
  else
    return NULL; /* ���� */
}
void InsertDSTable(DLTree *DT,Record *r)
{ /* ��ʼ����: ˫������DT���ڣ�rΪ�����������Ԫ�ص�ָ�� */
  /* �������: ��DT�в�������ؼ��ֵ���(*r).key.ch������Ԫ�أ� */
  /*           �򰴹ؼ���˳���r��DT�� */
  DLTree p=NULL,q,ap;
  int i=0;
  KeysType K=r->key;
  if(!*DT&&K.num) /* �����ҹؼ��ַ����ǿ� */
  {
    *DT=ap=(DLTree)malloc(sizeof(DLTNode));
    for(;i<K.num;i++) /* �����֧��� */
    {
      if(p)
        p->a.first=ap;
      ap->next=NULL;
      ap->symbol=K.ch[i];
      ap->kind=BRANCH;
      p=ap;
      ap=(DLTree)malloc(sizeof(DLTNode));
    }
    p->a.first=ap; /* ����Ҷ�ӽ�� */
    ap->next=NULL;
    ap->symbol=Nil;
    ap->kind=LEAF;
    ap->a.infoptr=r;
  }
  else /* �ǿ��� */
  {
    p=*DT; /* ָ������ */
    while(p&&i<K.num)
    {
      while(p&&p->symbol<K.ch[i]) /* ���ֵܽ����� */
      {
        q=p;
        p=p->next;
      }
      if(p&&p->symbol==K.ch[i]) /* �ҵ���K.ch[i]����Ľ�� */
      {
        q=p;
        p=p->a.first; /* pָ����K.ch[i+1]�ȽϵĽ�� */
        ++i;
      }
      else /* û�ҵ�,����ؼ��� */
      {
        ap=(DLTree)malloc(sizeof(DLTNode));
        if(q->a.first==p)
          q->a.first=ap; /* �ڳ��ӵ�λ�ò��� */
        else /* q->next==p */
          q->next=ap; /* ���ֵܵ�λ�ò��� */
        ap->next=p;
        ap->symbol=K.ch[i];
        ap->kind=BRANCH;
        p=ap;
        ap=(DLTree)malloc(sizeof(DLTNode));
        i++;
        for(;i<K.num;i++) /* �����֧��� */
        {
          p->a.first=ap;
          ap->next=NULL;
          ap->symbol=K.ch[i];
          ap->kind=BRANCH;
   p=ap;
          ap=(DLTree)malloc(sizeof(DLTNode));
        }
        p->a.first=ap; /* ����Ҷ�ӽ�� */
        ap->next=NULL;
        ap->symbol=Nil;
        ap->kind=LEAF;
        ap->a.infoptr=r;
      }
    }
  }
}
typedef struct
{
  char ch;
  DLTree p;
}SElemType; /* ����ջԪ������ */
#define STACK_INIT_SIZE 10 /* �洢�ռ��ʼ������ */
#define STACKINCREMENT 2 /* �洢�ռ�������� */
typedef struct SqStack
{
  SElemType *base; /* ��ջ����֮ǰ������֮��base��ֵΪNULL */
  SElemType *top; /* ջ��ָ�� */
  int stacksize; /* ��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ */
}SqStack; /* ˳��ջ */
Status InitStack(SqStack *S)
{ /* ����һ����ջS */
  (*S).base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
  if(!(*S).base)
    exit(OVERFLOW); /* �洢����ʧ�� */
  (*S).top=(*S).base;
  (*S).stacksize=STACK_INIT_SIZE;
  return OK;
}
Status StackEmpty(SqStack S)
{ /* ��ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE */
  if(S.top==S.base)
    return TRUE;
  else
    return FALSE;
}
Status Push(SqStack *S,SElemType e)
{ /* ����Ԫ��eΪ�µ�ջ��Ԫ�� */
  if((*S).top-(*S).base>=(*S).stacksize) /* ջ����׷�Ӵ洢�ռ� */
  {
    (*S).base=(SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
    if(!(*S).base)
      exit(OVERFLOW); /* �洢����ʧ�� */
    (*S).top=(*S).base+(*S).stacksize;
    (*S).stacksize+=STACKINCREMENT;
  }
  *((*S).top)++=e;
  return OK;
}
Status Pop(SqStack *S,SElemType *e)
{ /* ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR */
  if((*S).top==(*S).base)
    return ERROR;
  *e=*--(*S).top;
  return OK;
}
void TraverseDSTable(DLTree DT,void(*Vi)(Record))
{ /* ��ʼ����: ˫������DT���ڣ�Vi�ǶԽ�������Ӧ�ú����� */
  /*           ViR�ǶԼ�¼������Ӧ�ú��� */
  /* �������: ���ؼ��ֵ�˳������ؼ��ּ����Ӧ�ļ�¼ */
  SqStack s;
  SElemType e;
  DLTree p;
  int i=0,n=8;
  if(DT)
  {
    InitStack(&s);
    e.p=DT;
    e.ch=DT->symbol;
    Push(&s,e);
    p=DT->a.first;
    while(p->kind==BRANCH) /* ��֧��� */
    {
      e.p=p;
      e.ch=p->symbol;
      Push(&s,e);
      p=p->a.first;
    }
    e.p=p;
    e.ch=p->symbol;
    Push(&s,e);
    Vi(*(p->a.infoptr));
    i++;
    while(!StackEmpty(s))
    {
      Pop(&s,&e);
      p=e.p;
      if(p->next) /* ���ֵܽ�� */
      {
        p=p->next;
        while(p->kind==BRANCH) /* ��֧��� */
        {
          e.p=p;
          e.ch=p->symbol;
          Push(&s,e);
          p=p->a.first;
        }
        e.p=p;
        e.ch=p->symbol;
        Push(&s,e);
        Vi(*(p->a.infoptr));
        i++;
        if(i%n==0)
          printf("\n"); /* ���n��Ԫ�غ��� */
      }
    }
  }
}
void print(Record e)
{
  int i;
  printf("(");
  for(i=0;i<e.key.num;i++)
    printf("%c",e.key.ch[i]);
  printf(",%d)",e.others.ord);
}
void main()
{
  DLTree t;
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
    r[i].key.num=strlen(r[i].key.ch);
    p=SearchDLTree(t,r[i].key);
    if(!p) /* t�в����ڹؼ���Ϊr[i].key���� */
      InsertDSTable(&t,&r[i]);
  }
  printf("���ؼ��ַ�����˳�����˫������:\n");
  TraverseDSTable(t,print);
  printf("\n����������Ҽ�¼�Ĺؼ��ַ���: ");
  scanf("%s",s);
  k.num=strlen(s);
  strcpy(k.ch,s);
  p=SearchDLTree(t,k);
  if(p)
    print(*p);
  else
    printf("û�ҵ�");
  printf("\n");
  DestroyDSTable(&t);
}
