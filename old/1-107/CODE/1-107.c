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
#define MAX_NAME 2 /* �����ַ�������󳤶�+1 */
typedef int InfoType;
typedef char VertexType[MAX_NAME]; /* �ַ������� */
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
int count; /* ȫ����count�Է��ʼ��� */
int low[MAX_VERTEX_NUM];
void DFSArticul(ALGraph G,int v0)
{ /* �ӵ�v0���������������ȱ���ͼG�����Ҳ�����ؽڵ㡣*/
  int min,w;
  ArcNode *p;
  visited[v0]=min=++count; /* v0�ǵ�count�����ʵĶ��� */
  for(p=G.vertices[v0].firstarc;p;p=p->nextarc) /* ��v0��ÿ���ڽӶ����� */
  {
    w=p->adjvex; /* wΪv0���ڽӶ��� */
    if(visited[w]==0) /* wδ�����ʣ���v0�ĺ��� */
    {
      DFSArticul(G,w); /* ����ǰ���low[w] */
      if(low[w]<min)
        min=low[w];
      if(low[w]>=visited[v0])
        printf("%d %s\n",v0,G.vertices[v0].data); /* �ؽڵ� */
    }
    else if(visited[w]<min)
      min=visited[w]; /* w�ѷ��ʣ�w��v0���������ϵ����� */
  }
  low[v0]=min;
}
void FindArticul(ALGraph G)
{ /* ��ͨͼG���ڽӱ����洢�ṹ�����Ҳ����G��ȫ���ؽڵ㡣*/
  /* ȫ����count�Է��ʼ����� */
  int i,v;
  ArcNode *p;
  count=1;
  low[0]=visited[0]=1; /* �趨�ڽӱ���0�Ŷ���Ϊ�������ĸ� */
  for(i=1;i<G.vexnum;++i)
    visited[i]=0; /* ���ඥ����δ���� */
  p=G.vertices[0].firstarc;
  v=p->adjvex;
  DFSArticul(G,v); /* �ӵ�v�������������Ȳ��ҹؽڵ� */
  if(count<G.vexnum) /* �������ĸ��������������� */
  {
    printf("%d %s\n",0,G.vertices[0].data); /* ���ǹؽڵ㣬��� */
    while(p->nextarc)
    {
      p=p->nextarc;
      v=p->adjvex;
      if(visited[v]==0)
        DFSArticul(G,v);
    }
  }
}
void main()
{
  int i;
  ALGraph g;
  printf("��ѡ������ͼ\n");
  CreateGraph(&g);
  printf("����ؽڵ㣺\n");
  FindArticul(g);
  printf(" i G.vertices[i].data visited[i] low[i]\n");
  for(i=0;i<g.vexnum;++i)
    printf("%2d %9s %14d %8d\n",i,g.vertices[i].data,visited[i],low[i]);
}
