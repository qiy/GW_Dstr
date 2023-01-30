#include<limits.h> /* INT_MAX�� */
#include<stdio.h> /* EOF(=^Z��F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int VRType;
typedef char InfoType;
#define MAX_NAME 3 /* �����ַ�������󳤶�+1 */
#define MAX_INFO 20 /* �����Ϣ�ַ�������󳤶�+1 */
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
/*ͼ������(�ڽӾ���)�洢(�洢�ṹ��c7-1.h����)�Ļ�������*/
int LocateVex(MGraph G,VertexType u)
{ /* ��ʼ����:ͼG����,u��G�ж�������ͬ���� */
  /* �������:��G�д��ڶ���u,�򷵻ظö�����ͼ��λ��;���򷵻�-1 */
  int i;
  for(i=0;i<G.vexnum;++i)
    if(strcmp(u,G.vexs[i])==0)
      return i;
  return -1;
}
Status CreateAN(MGraph *G)
{ /* ��������(�ڽӾ���)��ʾ��,����������G��*/
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
  printf("������%d���ߵĶ���1 ����2 Ȩֵ(�Կո���Ϊ���): \n",(*G).arcnum);
  for(k=0;k<(*G).arcnum;++k)
  {
    scanf("%s%s%d%*c",va,vb,&w); /* %*c�Ե��س��� */
    i=LocateVex(*G,va);
    j=LocateVex(*G,vb);
    (*G).arcs[i][j].adj=(*G).arcs[j][i].adj=w; /* ���� */
    if(IncInfo)
    {
      printf("������ñߵ������Ϣ(<%d���ַ�): ",MAX_INFO);
      gets(s);
      w=strlen(s);
      if(w)
      {
        info=(char*)malloc((w+1)*sizeof(char));
        strcpy(info,s);
        (*G).arcs[i][j].info=(*G).arcs[j][i].info=info; /* ���� */
      }
    }
  }
  (*G).kind=AN;
  return OK;
}
typedef struct
{ /* ��¼�Ӷ��㼯U��V-U�Ĵ�����С�ıߵĸ������鶨�� */
  VertexType adjvex;
  VRType lowcost;
}minside[MAX_VERTEX_NUM];
int minimum(minside SZ,MGraph G)
{ /* ��closedge.lowcost����С��ֵ */
  int i=0,j,k,min;
  while(!SZ[i].lowcost)
    i++;
  min=SZ[i].lowcost; /* ��һ����Ϊ0��ֵ */
  k=i;
  for(j=i+1;j<G.vexnum;j++)
    if(SZ[j].lowcost>0)
      if(min>SZ[j].lowcost)
      {
        min=SZ[j].lowcost;
        k=j;
      }
  return k;
}
void MiniSpanTree_PRIM(MGraph G,VertexType u)
{ /* ������ķ�㷨�ӵ�u���������������G����С������T,���T�ĸ�����*/
  int i,j,k;
  minside closedge;
  k=LocateVex(G,u);
  for(j=0;j<G.vexnum;++j) /* ���������ʼ�� */
  {
    if(j!=k)
    {
      strcpy(closedge[j].adjvex,u);
      closedge[j].lowcost=G.arcs[k][j].adj;
    }
  }
  closedge[k].lowcost=0; /* ��ʼ,U={u} */
  printf("��С�����������ĸ�����Ϊ:\n");
  for(i=1;i<G.vexnum;++i)
  { /* ѡ������G.vexnum-1������ */
    k=minimum(closedge,G); /* ���T����һ����㣺��K���� */
    printf("(%s-%s)\n",closedge[k].adjvex,G.vexs[k]); /* ����������ı� */
    closedge[k].lowcost=0; /* ��K���㲢��U�� */
    for(j=0;j<G.vexnum;++j)
      if(G.arcs[k][j].adj<closedge[j].lowcost)
      { /* �¶��㲢��U��������ѡ����С�� */
        strcpy(closedge[j].adjvex,G.vexs[k]);
        closedge[j].lowcost=G.arcs[k][j].adj;
      }
  }
}
void main()
{
  MGraph G;
  CreateAN(&G);
  MiniSpanTree_PRIM(G,G.vexs[0]);
}
