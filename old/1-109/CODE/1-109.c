#include<stdio.h> /* EOF(=^Z��F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
/* �������״̬���� */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
/* #define OVERFLOW -2 ��Ϊ��math.h���Ѷ���OVERFLOW��ֵΪ3,��ȥ������ */
typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int Boolean; /* Boolean�ǲ�������,��ֵ��TRUE��FALSE */
#define MAX_NAME 5 /* �����ַ�������󳤶�+1 */
typedef int InfoType;
typedef char VertexType[MAX_NAME]; /* �ַ������� */
/* c7-2.h ͼ���ڽӱ�洢��ʾ */
#define MAX_VERTEX_NUM 20
typedef enum{DG,DN,AG,AN}GraphKind; /* {����ͼ,������,����ͼ,������} */
typedef struct ArcNode
{
  int adjvex; /* �û���ָ��Ķ����λ�� */
  struct ArcNode *nextarc; /* ָ����һ������ָ�� */
  InfoType *info; /* ����Ȩֵָ�룩 */
}ArcNode; /* ���� */
typedef struct
{
  VertexType data; /* ������Ϣ */
  ArcNode *firstarc; /* ��һ������ĵ�ַ,ָ���һ�������ö���Ļ���ָ�� */
}VNode,AdjList[MAX_VERTEX_NUM]; /* ͷ��� */
typedef struct
{
  AdjList vertices;
  int vexnum,arcnum; /* ͼ�ĵ�ǰ�������ͻ��� */
  int kind; /* ͼ�������־ */
}ALGraph;
int LocateVex(ALGraph G,VertexType u)
{ /* ��ʼ����: ͼG����,u��G�ж�������ͬ���� */
  /* �������: ��G�д��ڶ���u,�򷵻ظö�����ͼ��λ��;���򷵻�-1 */
  int i;
  for(i=0;i<G.vexnum;++i)
    if(strcmp(u,G.vertices[i].data)==0)
      return i;
  return -1;
}
Status CreateGraph(ALGraph *G)
{ /* �����ڽӱ�洢�ṹ,����û�������Ϣ��ͼG(��һ����������4��ͼ) */
  int i,j,k;
  int w; /* Ȩֵ */
  VertexType va,vb;
  ArcNode *p;
  printf("������ͼ������(����ͼ:0,������:1,����ͼ:2,������:3): ");
  scanf("%d",&(*G).kind);
  printf("������ͼ�Ķ�����,����: ");
  scanf("%d,%d",&(*G).vexnum,&(*G).arcnum);
  printf("������%d�������ֵ(<%d���ַ�):\n",(*G).vexnum,MAX_NAME);
  for(i=0;i<(*G).vexnum;++i) /* ���춥������ */
  {
    scanf("%s",(*G).vertices[i].data);
    (*G).vertices[i].firstarc=NULL;
  }
  if((*G).kind==1||(*G).kind==3) /* �� */
    printf("��˳������ÿ����(��)��Ȩֵ����β�ͻ�ͷ(�Կո���Ϊ���):\n");
  else /* ͼ */
    printf("��˳������ÿ����(��)�Ļ�β�ͻ�ͷ(�Կո���Ϊ���):\n");
  for(k=0;k<(*G).arcnum;++k) /* ����������� */
  {
    if((*G).kind==1||(*G).kind==3) /* �� */
      scanf("%d%s%s",&w,va,vb);
    else /* ͼ */
      scanf("%s%s",va,vb);
    i=LocateVex(*G,va); /* ��β */
    j=LocateVex(*G,vb); /* ��ͷ */
    p=(ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex=j;
    if((*G).kind==1||(*G).kind==3) /* �� */
    {
      p->info=(int *)malloc(sizeof(int));
      *(p->info)=w;
    }
    else
      p->info=NULL; /* ͼ */
    p->nextarc=(*G).vertices[i].firstarc; /* ���ڱ�ͷ */
    (*G).vertices[i].firstarc=p;
    if((*G).kind>=2) /* ����ͼ����,�����ڶ������� */
    {
      p=(ArcNode*)malloc(sizeof(ArcNode));
      p->adjvex=i;
      if((*G).kind==3) /* ������ */
      {
        p->info=(int*)malloc(sizeof(int));
        *(p->info)=w;
      }
      else
        p->info=NULL; /* ����ͼ */
      p->nextarc=(*G).vertices[j].firstarc; /* ���ڱ�ͷ */
      (*G).vertices[j].firstarc=p;
    }
  }
  return OK;
}
VertexType* GetVex(ALGraph G,int v)
{ /* ��ʼ����: ͼG����,v��G��ĳ���������š��������: ����v��ֵ */
  if(v>=G.vexnum||v<0)
    exit(ERROR);
  return &G.vertices[v].data;
}
int FirstAdjVex(ALGraph G,VertexType v)
{ /* ��ʼ����: ͼG����,v��G��ĳ������ */
  /* �������: ����v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ���,�򷵻�-1 */
  ArcNode *p;
  int v1;
  v1=LocateVex(G,v); /* v1Ϊ����v��ͼG�е���� */
  p=G.vertices[v1].firstarc;
  if(p)
    return p->adjvex;
  else
    return -1;
}
int NextAdjVex(ALGraph G,VertexType v,VertexType w)
{ /* ��ʼ����: ͼG����,v��G��ĳ������,w��v���ڽӶ��� */
  /* �������: ����v��(�����w��)��һ���ڽӶ������š� */
  /*           ��w��v�����һ���ڽӵ�,�򷵻�-1 */
  ArcNode *p;
  int v1,w1;
  v1=LocateVex(G,v); /* v1Ϊ����v��ͼG�е���� */
  w1=LocateVex(G,w); /* w1Ϊ����w��ͼG�е���� */
  p=G.vertices[v1].firstarc;
  while(p&&p->adjvex!=w1) /* ָ��p��������ָ���㲻��w */
    p=p->nextarc;
  if(!p||!p->nextarc) /* û�ҵ�w��w�����һ���ڽӵ� */
    return -1;
  else /* p->adjvex==w */
    return p->nextarc->adjvex; /* ����v��(�����w��)��һ���ڽӶ������� */
}
Boolean visited[MAX_VERTEX_NUM]; /* ���ʱ�־����(ȫ����) */
void(*VisitFunc)(char* v); /* ��������(ȫ����) */
void DFS(ALGraph G,int v)
{ /* �ӵ�v����������ݹ��������ȱ���ͼG��*/
  int w;
  VertexType v1,w1;
  strcpy(v1,*GetVex(G,v));
  visited[v]=TRUE; /* ���÷��ʱ�־ΪTRUE(�ѷ���) */
  VisitFunc(G.vertices[v].data); /* ���ʵ�v������ */
  for(w=FirstAdjVex(G,v1);w>=0;w=NextAdjVex(G,v1,strcpy(w1,*GetVex(G,w))))
    if(!visited[w])
      DFS(G,w); /* ��v����δ���ʵ��ڽӵ�w�ݹ����DFS */
}
void DFSTraverse(ALGraph G,void(*Visit)(char*))
{ /* ��ͼG��������ȱ�����*/
  int v;
  VisitFunc=Visit; /* ʹ��ȫ�ֱ���VisitFunc,ʹDFS�����躯��ָ����� */
  for(v=0;v<G.vexnum;v++)
    visited[v]=FALSE; /* ���ʱ�־�����ʼ�� */
  for(v=0;v<G.vexnum;v++)
    if(!visited[v])
      DFS(G,v); /* ����δ���ʵĶ������DFS */
  printf("\n");
}
typedef int QElemType; /* �������� */
typedef struct QNode
{
  QElemType data;
  struct QNode *next;
}QNode,*QueuePtr;
typedef struct
{
  QueuePtr front,rear; /* ��ͷ����βָ�� */
}LinkQueue;
Status InitQueue(LinkQueue *Q)
{ /* ����һ���ն���Q */
  (*Q).front=(*Q).rear=(QueuePtr)malloc(sizeof(QNode));
  if(!(*Q).front)
    exit(OVERFLOW);
  (*Q).front->next=NULL;
  return OK;
}
Status QueueEmpty(LinkQueue Q)
{ /* ��QΪ�ն���,�򷵻�TRUE,���򷵻�FALSE */
  if(Q.front==Q.rear)
    return TRUE;
  else
    return FALSE;
}
Status EnQueue(LinkQueue *Q,QElemType e)
{ /* ����Ԫ��eΪQ���µĶ�βԪ�� */
  QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
  if(!p) /* �洢����ʧ�� */
    exit(OVERFLOW);
  p->data=e;
  p->next=NULL;
  (*Q).rear->next=p;
  (*Q).rear=p;
  return OK;
}
Status DeQueue(LinkQueue *Q,QElemType *e)
{ /* �����в���,ɾ��Q�Ķ�ͷԪ��,��e������ֵ,������OK,���򷵻�ERROR */
  QueuePtr p;
  if((*Q).front==(*Q).rear)
    return ERROR;
  p=(*Q).front->next;
  *e=p->data;
  (*Q).front->next=p->next;
  if((*Q).rear==p)
    (*Q).rear=(*Q).front;
  free(p);
  return OK;
}
void BFSTraverse(ALGraph G,void(*Visit)(char*))
{/*��������ȷǵݹ����ͼG��ʹ�ø�������Q�ͷ��ʱ�־����visited��*/
  int v,u,w;
  VertexType u1,w1;
  LinkQueue Q;
  for(v=0;v<G.vexnum;++v)
    visited[v]=FALSE; /* �ó�ֵ */
  InitQueue(&Q); /* �ÿյĸ�������Q */
  for(v=0;v<G.vexnum;v++) /* �������ͨͼ,ֻv=0�ͱ���ȫͼ */
    if(!visited[v]) /* v��δ���� */
    {
      visited[v]=TRUE;
      Visit(G.vertices[v].data);
      EnQueue(&Q,v); /* v����� */
      while(!QueueEmpty(Q)) /* ���в��� */
      {
        DeQueue(&Q,&u); /* ��ͷԪ�س��Ӳ���Ϊu */
        strcpy(u1,*GetVex(G,u));
        for(w=FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1,strcpy(w1,*GetVex(G,w))))
          if(!visited[w]) /* wΪu����δ���ʵ��ڽӶ��� */
          {
            visited[w]=TRUE;
            Visit(G.vertices[w].data);
            EnQueue(&Q,w); /* w��� */
          }
      }
    }
  printf("\n");
}
void Display(ALGraph G)
{ /* ���ͼ���ڽӾ���G */
  int i;
  ArcNode *p;
  switch(G.kind)
  {
    case DG: printf("����ͼ\n");
             break;
    case DN: printf("������\n");
             break;
    case AG: printf("����ͼ\n");
             break;
    case AN: printf("������\n");
  }
  printf("%d�����㣺\n",G.vexnum);
  for(i=0;i<G.vexnum;++i)
    printf("%s ",G.vertices[i].data);
  printf("\n%d����(��):\n",G.arcnum);
  for(i=0;i<G.vexnum;i++)
  {
    p=G.vertices[i].firstarc;
    while(p)
    {
      if(G.kind<=1) /* ���� */
      {
        printf("%s��%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
        if(G.kind==DN) /* �� */
          printf(":%d ",*(p->info));
      }
      else /* ����(�����������) */
      {
        if(i<p->adjvex)
        {
          printf("%s��%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
          if(G.kind==AN) /* �� */
            printf(":%d ",*(p->info));
        }
      }
      p=p->nextarc;
    }
    printf("\n");
  }
}
int ve[MAX_VERTEX_NUM]; 
void FindInDegree(ALGraph G,int indegree[])
{ /* �󶥵�����*/
  int i;
  ArcNode *p;
  for(i=0;i<G.vexnum;i++)
    indegree[i]=0; /* ����ֵ */
  for(i=0;i<G.vexnum;i++)
  {
    p=G.vertices[i].firstarc;
    while(p)
    {
      indegree[p->adjvex]++;
      p=p->nextarc;
    }
  }
}
typedef int SElemType; /* ջ���� */
#define STACK_INIT_SIZE 10 /* �洢�ռ��ʼ������ */
#define STACKINCREMENT 2 /* �洢�ռ�������� */
typedef struct SqStack
{
  SElemType *base; /* ��ջ����֮ǰ������֮��base��ֵΪNULL */
  SElemType *top; /* ջ��ָ�� */
  int stacksize; /* ��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ */
}SqStack; /* ˳��ջ */
/* bo3-1.c ˳��ջ���洢�ṹ��c3-1.h���壩�Ļ���������9���� */
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
Status TopologicalOrder(ALGraph G,SqStack *T)
  /* (ȫ�ֱ���)��TΪ�������ж���ջ,SΪ����ȶ���ջ����G�޻�·,����ջT */
  /* ����G��һ����������,�Һ���ֵΪOK,����ΪERROR */
  int j,k,count,indegree[MAX_VERTEX_NUM];
  SqStack S;
  ArcNode *p;
  FindInDegree(G,indegree);/*�Ը����������indegree[0..vernum-1] */
  InitStack(&S); /* ��ʼ��ջ */
  for(j=0;j<G.vexnum;++j) /* ������ȶ���ջS */
    if(!indegree[j])
      Push(&S,j); /* ���Ϊ0�߽�ջ */
  InitStack(T); /* ��ʼ���������ж���ջ */
  count=0; /* ������������ */
  for(j=0;j<G.vexnum;++j) /* ��ʼ��ve[]=0 (��Сֵ) */
    ve[j]=0;
  while(!StackEmpty(S))
  { /* ջ���� */
    Pop(&S,&j);
    Push(T,j); /* j�Ŷ�����Tջ������ */
    ++count;
    for(p=G.vertices[j].firstarc;p;p=p->nextarc)
    { /* ��j�Ŷ����ÿ���ڽӵ����ȼ�1 */
      k=p->adjvex;
      if(--indegree[k]==0) /* ����ȼ�Ϊ0,����ջ */
        Push(&S,k);
      if(ve[j]+*(p->info)>ve[k])
        ve[k]=ve[j]+*(p->info);
    }
  }
  if(count<G.vexnum)
  {
    printf("���������л�·\n");
    return ERROR;
  }
  else
    return OK;
}
Status CriticalPath(ALGraph G)
  int vl[MAX_VERTEX_NUM];
  SqStack T;
  int i,j,k,ee,el;
  ArcNode *p;
  char dut,tag;
  if(!TopologicalOrder(G,&T)) /* �������� */
    return ERROR;
  j=ve[0];
  for(i=1;i<G.vexnum;i++) /* j=Max(ve[]) ��ɵ��ֵ */
    if(ve[i]>j)
      j=ve[i];
  for(i=0;i<G.vexnum;i++) /* ��ʼ�������¼�����ٷ���ʱ��(���ֵ) */
    vl[i]=j; /* ��ɵ�����緢��ʱ�� */
  while(!StackEmpty(T)) /* ������������������vlֵ */
    for(Pop(&T,&j),p=G.vertices[j].firstarc;p;p=p->nextarc)
    {
      k=p->adjvex;
      dut=*(p->info); /* dut<j,k> */
      if(vl[k]-dut<vl[j])
        vl[j]=vl[k]-dut;
    }
  printf(" j  k  dut  ee  el  tag\n");
  for(j=0;j<G.vexnum;++j) /* ��ee,el�͹ؼ�� */
    for(p=G.vertices[j].firstarc;p;p=p->nextarc)
    {
      k=p->adjvex;
      dut=*(p->info);
      ee=ve[j];
      el=vl[k]-dut;
      tag=(ee==el)?'*':' ';
      printf("%2d %2d %3d %3d %3d    %c\n",j,k,dut,ee,el,tag); /* ����ؼ�� */
    }
  printf("�ؼ��Ϊ:\n");
  for(j=0;j<G.vexnum;++j) /* ͬ�� */
    for(p=G.vertices[j].firstarc;p;p=p->nextarc)
    {
      k=p->adjvex;
      dut=*(p->info);
      if(ve[j]==vl[k]-dut)
        printf("%s��%s\n",G.vertices[j].data,G.vertices[k].data); /* ����ؼ�� */
    }
  return OK;
}
void main()
{
  ALGraph h;
  printf("��ѡ��������\n");
  CreateGraph(&h);
  Display(h);
  CriticalPath(h);
}
