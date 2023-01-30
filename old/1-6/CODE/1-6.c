#include<stdio.h> /* EOF(=^Z��F6),NULL */
#include<math.h> /* floor(),ceil(),abs() */
#include<stdarg.h>
#define OK 1
#define ERROR 0
#define MAX_ARRAY_DIM 8
typedef int ElemType;
typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef struct
{
  ElemType *base; /* ����Ԫ�ػ�ַ����InitArray���� */
  int dim; /* ����ά�� */
  int *bounds; /* ����ά���ַ����InitArray���� */
  int *constants; /* ����ӳ����������ַ����InitArray���� */
}Array;
/* ˳��洢����Ļ�������*/
Status InitArray(Array *A,int dim,...)
{ /* ��ά��dim�͸�ά���ȺϷ���������Ӧ������A��������OK */
  int elemtotal=1,i; /* elemtotal��Ԫ����ֵ */
  va_list ap;
  if(dim<1||dim>MAX_ARRAY_DIM)
    return ERROR;
  (*A).dim=dim;
  (*A).bounds=(int *)malloc(dim*sizeof(int));
  if(!(*A).bounds)
    exit(OVERFLOW);
  va_start(ap,dim);
  for(i=0;i<dim;++i)
  {
    (*A).bounds[i]=va_arg(ap,int);
    if((*A).bounds[i]<0)
      return UNDERFLOW; /* ��math.h�ж���Ϊ4 */
    elemtotal*=(*A).bounds[i];
  }
  va_end(ap);
  (*A).base=(ElemType *)malloc(elemtotal*sizeof(ElemType));
  if(!(*A).base)
    exit(OVERFLOW);
  (*A).constants=(int *)malloc(dim*sizeof(int));
  if(!(*A).constants)
    exit(OVERFLOW);
  (*A).constants[dim-1]=1;
  for(i=dim-2;i>=0;--i)
    (*A).constants[i]=(*A).bounds[i+1]*(*A).constants[i+1];
  return OK;
}
Status DestroyArray(Array *A)
{ /* ��������A */
  if((*A).base)
  {
    free((*A).base);
    (*A).base=NULL;
  }
  else
    return ERROR;
  if((*A).bounds)
  {
    free((*A).bounds);
    (*A).bounds=NULL;
  }
  else
    return ERROR;
  if((*A).constants)
  {
    free((*A).constants);
    (*A).constants=NULL;
  }
  else
    return ERROR;
  return OK;
}
Status Locate(Array A,va_list ap,int *off) /* Value()��Assign()���ô˺��� */
{ /* ��apָʾ�ĸ��±�ֵ�Ϸ����������Ԫ����A�е���Ե�ַoff */
  int i,ind;
  *off=0;
  for(i=0;i<A.dim;i++)
  {
    ind=va_arg(ap,int);
    if(ind<0||ind>=A.bounds[i])
      return OVERFLOW;
    *off+=A.constants[i]*ind;
  }
  return OK;
}
Status Value(ElemType *e,Array A,...)
{ /* ...����Ϊ��ά���±�ֵ�������±�Ϸ�����e����ֵΪA����Ӧ��Ԫ��ֵ */
  va_list ap;
  Status result;
  int off;
  va_start(ap,A);
  if((result=Locate(A,ap,&off))==OVERFLOW) /* ����Locate() */
    return result;
  *e=*(A.base+off);
  return OK;
}
Status Assign(Array *A,ElemType e,...)
{ /* ...����Ϊ��ά���±�ֵ�������±�Ϸ�����e��ֵ����A��ָ����Ԫ�� */
  va_list ap;
  Status result;
  int off;
  va_start(ap,e);
  if((result=Locate(*A,ap,&off))==OVERFLOW) /* ����Locate() */
    return result;
  *((*A).base+off)=e;
  return OK;
}
void main()
{
  Array A;
  int i,j,k,*p,dim=3,bound1=3,bound2=4,bound3=2; /* a[3][4][2]���� */
  ElemType e,*p1;
  InitArray(&A,dim,bound1,bound2,bound3); /* ����3��4��2��3ά����A */
  p=A.bounds;
  printf("A.bounds=");
  for(i=0;i<dim;i++) /* ˳�����A.bounds */
    printf("%d ",*(p+i));
  p=A.constants;
  printf("\nA.constants=");
  for(i=0;i<dim;i++) /* ˳�����A.constants */
    printf("%d ",*(p+i));
  printf("\n%dҳ%d��%d�о���Ԫ������:\n",bound1,bound2,bound3);
  for(i=0;i<bound1;i++)
  {
    for(j=0;j<bound2;j++)
    {
      for(k=0;k<bound3;k++)
      {
        Assign(&A,i*100+j*10+k,i,j,k); /* ��i*100+j*10+k��ֵ��A[i][j][k] */
        Value(&e,A,i,j,k); /* ��A[i][j][k]��ֵ����e */
        printf("A[%d][%d][%d]=%2d ",i,j,k,e); /* ���A[i][j][k] */
      }
      printf("\n");
    }
    printf("\n");
  }
  p1=A.base;
  printf("A.base=\n");
  for(i=0;i<bound1*bound2*bound3;i++) /* ˳�����A.base */
  {
    printf("%4d",*(p1+i));
    if(i%(bound2*bound3)==bound2*bound3-1)
      printf("\n");
  }
  DestroyArray(&A);
}
