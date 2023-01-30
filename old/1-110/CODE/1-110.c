#include<limits.h> /* INT_MAX�� */
#include<stdio.h> /* EOF(=^Z��F6),NULL */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
#define MAX_NAME 5 /* �����ַ�������󳤶�+1 */
#define MAX_INFO 20 /* �����Ϣ�ַ�������󳤶�+1 */
typedef int VRType;
typedef char InfoType;
typedef char VertexType[MAX_NAME];
#define INFINITY INT_MAX /* ���������ֵ����� */
#define MAX_VERTEX_NUM 20 /* ��󶥵���� */
typedef enum{DG,DN,AG,AN}GraphKind; /* {����ͼ,������,����ͼ,������} */
typedef struct
{
  VRType adj; /* �����ϵ���͡�����Ȩͼ����1(��)��0(��)��ʾ���ڷ� */
       /* �Դ�Ȩͼ��c��ΪȨֵ���� */
  InfoType *info; /* �û������Ϣ��ָ��(����) */
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct
{
  VertexType vexs[MAX_VERTEX_NUM]; /* �������� */
  AdjMatrix arcs; /* �ڽӾ��� */
  int vexnum,arcnum; /* ͼ�ĵ�ǰ�������ͻ��� */
  GraphKind kind; /* ͼ�������־ */
}MGraph;
typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int ShortPathTable[MAX_VERTEX_NUM];
int LocateVex(MGraph G,VertexType u)
{ /* ��ʼ����:ͼG����,u��G�ж�������ͬ���� */
  /* �������:��G�д��ڶ���u,�򷵻ظö�����ͼ��λ��;���򷵻�-1 */
  int i;
  for(i=0;i<G.vexnum;++i)
    if(strcmp(u,G.vexs[i])==0)
      return i;
  return -1;
}
Status CreateDN(MGraph *G)
{ /* ��������(�ڽӾ���)��ʾ��,����������G */
  int i,j,k,w,IncInfo;
  char s[MAX_INFO],*info;
  VertexType va,vb;
  printf("������������G�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
  scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
  printf("������%d�������ֵ(<%d���ַ�):\n",(*G).vexnum,MAX_NAME);
  for(i=0;i<(*G).vexnum;++i) /* ���춥������ */
    scanf("%s",(*G).vexs[i]);
  for(i=0;i<(*G).vexnum;++i) /* ��ʼ���ڽӾ��� */
    for(j=0;j<(*G).vexnum;++j)
    {
      (*G).arcs[i][j].adj=INFINITY; /* �� */
      (*G).arcs[i][j].info=NULL;
    }
  printf("������%d�����Ļ�β ��ͷ Ȩֵ(�Կո���Ϊ���): \n",(*G).arcnum);
  for(k=0;k<(*G).arcnum;++k)
  {
    scanf("%s%s%d%*c",va,vb,&w);  /* %*c�Ե��س��� */
    i=LocateVex(*G,va);
    j=LocateVex(*G,vb);
    (*G).arcs[i][j].adj=w; /* ������ */
    if(IncInfo)
    {
      printf("������û��������Ϣ(<%d���ַ�): ",MAX_INFO);
      gets(s);
      w=strlen(s);
      if(w)
      {
        info=(char*)malloc((w+1)*sizeof(char));
        strcpy(info,s);
        (*G).arcs[i][j].info=info; /* ���� */
      }
    }
  }
  (*G).kind=DN;
  return OK;
}
void ShortestPath_DIJ(MGraph G,int v0,PathMatrix *P,ShortPathTable *D)
{ /* ��Dijkstra�㷨��������G��v0���㵽���ඥ��v�����·��P[v]����Ȩ���� */
  /* D[v]����P[v][w]ΪTRUE,��w�Ǵ�v0��v��ǰ������·���ϵĶ��㡣 */
  /* final[v]ΪTRUE���ҽ���v��S*/
  int v,w,i,j,min;
  Status final[MAX_VERTEX_NUM];
  for(v=0;v<G.vexnum;++v)
  {
    final[v]=FALSE;
    (*D)[v]=G.arcs[v0][v].adj;
    for(w=0;w<G.vexnum;++w)
      (*P)[v][w]=FALSE; /* ���·�� */
    if((*D)[v]<INFINITY)
    {
      (*P)[v][v0]=TRUE;
      (*P)[v][v]=TRUE;
    }
  }
  (*D)[v0]=0;
  final[v0]=TRUE; /* ��ʼ��,v0��������S�� */
  for(i=1;i<G.vexnum;++i) /* ����G.vexnum-1������ */
  { /* ��ʼ��ѭ��,ÿ�����v0��ĳ��v��������·��,����v��S�� */
    min=INFINITY; /* ��ǰ��֪��v0������������ */
    for(w=0;w<G.vexnum;++w)
      if(!final[w]) /* w������V-S�� */
 if((*D)[w]<min)
 {
   v=w;
   min=(*D)[w];
 } /* w������v0������� */
    final[v]=TRUE; /* ��v0���������v����S�� */
    for(w=0;w<G.vexnum;++w) /* ���µ�ǰ���·�������� */
    {
      if(!final[w]&&min<INFINITY&&G.arcs[v][w].adj<INFINITY&&(min+G.arcs[v][w].adj<(*D)[w]))
      { /* �޸�D[w]��P[w],w��V-S */
        (*D)[w]=min+G.arcs[v][w].adj;
        for(j=0;j<G.vexnum;++j)
          (*P)[w][j]=(*P)[v][j];
        (*P)[w][w]=TRUE;
      }
    }
  }
}
void main()
{
  int i,j,v0=0; /* v0ΪԴ�� */
  MGraph g;
  PathMatrix p;
  ShortPathTable d;
  CreateDN(&g);
  ShortestPath_DIJ(g,v0,&p,&d);
  printf("���·������p[i][j]����:\n");
  for(i=0;i<g.vexnum;++i)
  {
    for(j=0;j<g.vexnum;++j)
      printf("%2d",p[i][j]);
    printf("\n");
  }
  printf("%s������������·������Ϊ��\n",g.vexs[0]);
  for(i=1;i<g.vexnum;++i)
    printf("%s-%s:%d\n",g.vexs[0],g.vexs[i],d[i]);
}
