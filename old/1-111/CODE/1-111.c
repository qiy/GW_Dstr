#define MAX_NAME 5 /* �����ַ�������󳤶�+1 */
#define MAX_INFO 20 /* �����Ϣ�ַ�������󳤶�+1 */
typedef int VRType;
typedef char VertexType[MAX_NAME];
typedef char InfoType;
#include<limits.h> /* INT_MAX�� */
#include<stdio.h> /* EOF(=^Z��F6),NULL */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int Boolean; /* Boolean�ǲ�������,��ֵ��TRUE��FALSE */
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
int LocateVex(MGraph G,VertexType u)
{ /* ��ʼ����:ͼG����,u��G�ж�������ͬ���� */
  /* �������:��G�д��ڶ���u,�򷵻ظö�����ͼ��λ��;���򷵻�-1 */
  int i;
  for(i=0;i<G.vexnum;++i)
    if(strcmp(u,G.vexs[i])==0)
      return i;
  return -1;
}
Status CreateFAG(MGraph *G)
{ /* ��������(�ڽӾ���)��ʾ��,���ļ�����û�������Ϣ������ͼG */
  int i,j,k;
  char filename[13];
  VertexType va,vb;
  FILE *graphlist;
  printf("�����������ļ���(f7-1.dat)��");
  scanf("%s",filename);
  graphlist=fopen(filename,"r");
  fscanf(graphlist,"%d",&(*G).vexnum);
  fscanf(graphlist,"%d",&(*G).arcnum);
  for(i=0;i<(*G).vexnum;++i) /* ���춥������ */
    fscanf(graphlist,"%s",(*G).vexs[i]);
  for(i=0;i<(*G).vexnum;++i) /* ��ʼ���ڽӾ��� */
    for(j=0;j<(*G).vexnum;++j)
    {
      (*G).arcs[i][j].adj=0; /* ͼ */
      (*G).arcs[i][j].info=NULL; /* û�������Ϣ */
    }
  for(k=0;k<(*G).arcnum;++k)
  {
    fscanf(graphlist,"%s%s",va,vb);
    i=LocateVex(*G,va);
    j=LocateVex(*G,vb);
    (*G).arcs[i][j].adj=(*G).arcs[j][i].adj=1; /* ����ͼ */
  }
  fclose(graphlist);
  (*G).kind=AG;
  return OK;
}
Status CreateDG(MGraph *G)
{ /* ��������(�ڽӾ���)��ʾ��,��������ͼG */
  int i,j,k,l,IncInfo;
  char s[MAX_INFO],*info;
  VertexType va,vb;
  printf("����������ͼG�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
  scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
  printf("������%d�������ֵ(<%d���ַ�):\n",(*G).vexnum,MAX_NAME);
  for(i=0;i<(*G).vexnum;++i) /* ���춥������ */
    scanf("%s",(*G).vexs[i]);
  for(i=0;i<(*G).vexnum;++i) /* ��ʼ���ڽӾ��� */
    for(j=0;j<(*G).vexnum;++j)
    {
      (*G).arcs[i][j].adj=0; /* ͼ */
      (*G).arcs[i][j].info=NULL;
    }
  printf("������%d�����Ļ�β ��ͷ(�Կո���Ϊ���): \n",(*G).arcnum);
  for(k=0;k<(*G).arcnum;++k)
  {
    scanf("%s%s%*c",va,vb);  /* %*c�Ե��س��� */
    i=LocateVex(*G,va);
    j=LocateVex(*G,vb);
    (*G).arcs[i][j].adj=1; /* ����ͼ */
    if(IncInfo)
    {
      printf("������û��������Ϣ(<%d���ַ�): ",MAX_INFO);
      gets(s);
      l=strlen(s);
      if(l)
      {
        info=(char*)malloc((l+1)*sizeof(char));
        strcpy(info,s);
        (*G).arcs[i][j].info=info; /* ���� */
      }
    }
  }
  (*G).kind=DG;
  return OK;
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
Status CreateAG(MGraph *G)
{ /* ��������(�ڽӾ���)��ʾ��,��������ͼG */
  int i,j,k,l,IncInfo;
  char s[MAX_INFO],*info;
  VertexType va,vb;
  printf("����������ͼG�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
  scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
  printf("������%d�������ֵ(<%d���ַ�):\n",(*G).vexnum,MAX_NAME);
  for(i=0;i<(*G).vexnum;++i) /* ���춥������ */
    scanf("%s",(*G).vexs[i]);
  for(i=0;i<(*G).vexnum;++i) /* ��ʼ���ڽӾ��� */
    for(j=0;j<(*G).vexnum;++j)
    {
      (*G).arcs[i][j].adj=0; /* ͼ */
      (*G).arcs[i][j].info=NULL;
    }
  printf("������%d���ߵĶ���1 ����2(�Կո���Ϊ���): \n",(*G).arcnum);
  for(k=0;k<(*G).arcnum;++k)
  {
    scanf("%s%s%*c",va,vb); /* %*c�Ե��س��� */
    i=LocateVex(*G,va);
    j=LocateVex(*G,vb);
    (*G).arcs[i][j].adj=(*G).arcs[j][i].adj=1; /* ����ͼ */
    if(IncInfo)
    {
      printf("������ñߵ������Ϣ(<%d���ַ�): ",MAX_INFO);
      gets(s);
      l=strlen(s);
      if(l)
      {
        info=(char*)malloc((l+1)*sizeof(char));
        strcpy(info,s);
        (*G).arcs[i][j].info=(*G).arcs[j][i].info=info; /* ���� */
      }
    }
  }
  (*G).kind=AG;
  return OK;
}
Status CreateAN(MGraph *G)
{ /* ��������(�ڽӾ���)��ʾ��,����������G���㷨7.2 */
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
Status CreateGraph(MGraph *G)
{ /* ��������(�ڽӾ���)��ʾ��,����ͼG��*/
  printf("������ͼG������(����ͼ:0,������:1,����ͼ:2,������:3): ");
  scanf("%d",&(*G).kind);
  switch((*G).kind)
  {
    case DG: return CreateDG(G); /* ��������ͼ */
    case DN: return CreateDN(G); /* ���������� */
    case AG: return CreateAG(G); /* ��������ͼ */
    case AN: return CreateAN(G); /* ���������� */
    default: return ERROR;
  }
}
void DestroyGraph(MGraph *G)
{ /* ��ʼ����: ͼG���ڡ��������: ����ͼG */
  int i,j;
  if((*G).kind<2) /* ���� */
    for(i=0;i<(*G).vexnum;i++) /* �ͷŻ��������Ϣ(����еĻ�) */
    {
      for(j=0;j<(*G).vexnum;j++)
        if((*G).arcs[i][j].adj==1&&(*G).kind==0||(*G).arcs[i][j].adj!=INFINITY&&(*G).kind==1) /* ����ͼ�Ļ�||�������Ļ� */
          if((*G).arcs[i][j].info) /* �������Ϣ */
          {
            free((*G).arcs[i][j].info);
            (*G).arcs[i][j].info=NULL;
          }
    }
  else /* ���� */
    for(i=0;i<(*G).vexnum;i++) /* �ͷűߵ������Ϣ(����еĻ�) */
      for(j=i+1;j<(*G).vexnum;j++)
        if((*G).arcs[i][j].adj==1&&(*G).kind==2||(*G).arcs[i][j].adj!=INFINITY&&(*G).kind==3) /* ����ͼ�ı�||�������ı� */
          if((*G).arcs[i][j].info) /* �������Ϣ */
          {
            free((*G).arcs[i][j].info);
            (*G).arcs[i][j].info=(*G).arcs[j][i].info=NULL;
          }
  (*G).vexnum=0;
  (*G).arcnum=0;
}
VertexType* GetVex(MGraph G,int v)
{ /* ��ʼ����: ͼG���ڣ�v��G��ĳ���������š��������: ����v��ֵ */
  if(v>=G.vexnum||v<0)
    exit(ERROR);
  return &G.vexs[v];
}
Status PutVex(MGraph *G,VertexType v,VertexType value)
{ /* ��ʼ����: ͼG���ڣ�v��G��ĳ�����㡣�������: ��v����ֵvalue */
  int k;
  k=LocateVex(*G,v); /* kΪ����v��ͼG�е���� */
  if(k<0)
    return ERROR;
  strcpy((*G).vexs[k],value);
  return OK;
}
typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int DistancMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
void ShortestPath_FLOYD(MGraph G,PathMatrix *P,DistancMatrix *D)
{ /* ��Floyd�㷨��������G�и��Զ���v��w֮������·��P[v][w]���� */
  /* ��Ȩ����D[v][w]����P[v][w][u]ΪTRUE,��u�Ǵ�v��w��ǰ������ */
  /* ·���ϵĶ��㡣�㷨7.16 */
  int u,v,w,i;
  for(v=0;v<G.vexnum;v++) /* ���Խ��֮���ʼ��֪·�������� */
    for(w=0;w<G.vexnum;w++)
    {
      (*D)[v][w]=G.arcs[v][w].adj;
      for(u=0;u<G.vexnum;u++)
        (*P)[v][w][u]=FALSE;
      if((*D)[v][w]<INFINITY) /* ��v��w��ֱ��·�� */
      {
        (*P)[v][w][v]=TRUE;
        (*P)[v][w][w]=TRUE;
      }
    }
  for(u=0;u<G.vexnum;u++)
    for(v=0;v<G.vexnum;v++)
      for(w=0;w<G.vexnum;w++)
        if((*D)[v][u]+(*D)[u][w]<(*D)[v][w]) /* ��v��u��w��һ��·������ */
        {
          (*D)[v][w]=(*D)[v][u]+(*D)[u][w];
          for(i=0;i<G.vexnum;i++)
            (*P)[v][w][i]=(*P)[v][u][i]||(*P)[u][w][i];
        }
}
void main()
{
  MGraph g;
  int i,j,k,l,m,n;
  PathMatrix p;
  DistancMatrix d;
  CreateDN(&g);
  for(i=0;i<g.vexnum;i++)
    g.arcs[i][i].adj=0; /* ShortestPath_FLOYD()Ҫ��Խ�Ԫ��ֵΪ0 */
  printf("�ڽӾ���:\n");
  for(i=0;i<g.vexnum;i++)
  {
    for(j=0;j<g.vexnum;j++)
      printf("%11d",g.arcs[i][j]);
    printf("\n");
  }
  ShortestPath_FLOYD(g,&p,&d);
  printf("d����:\n");
  for(i=0;i<g.vexnum;i++)
  {
    for(j=0;j<g.vexnum;j++)
      printf("%6d",d[i][j]);
    printf("\n");
  }
  for(i=0;i<g.vexnum;i++)
    for(j=0;j<g.vexnum;j++)
      printf("%s��%s����̾���Ϊ%d\n",g.vexs[i],g.vexs[j],d[i][j]);
  printf("p����:\n");
  l=strlen(g.vexs[0]); /* ���������ַ����ĳ��� */
  for(i=0;i<g.vexnum;i++)
  {
    for(j=0;j<g.vexnum;j++)
    {
      if(i!=j)
      {
        m=0; /* ռλ�ո� */
        for(k=0;k<g.vexnum;k++)
          if(p[i][j][k]==1)
            printf("%s",g.vexs[k]);
          else
            m++;
        for(n=0;n<m*l;n++) /* ���ռλ�ո� */
          printf(" ");
      }
      else
        for(k=0;k<g.vexnum*l;k++) /* ���ռλ�ո� */
          printf(" ");
      printf("   "); /* �������Ԫ��֮��ļ�� */
    }
    printf("\n");
  }
}
