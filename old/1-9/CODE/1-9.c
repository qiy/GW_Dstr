#include "stdio.h"
#define n 4
int d[n];
void Store(int x, int i, int j)
{/* ��x��ΪD ( i , j ) */
	if (i<0||j<0||i>=n||j>=n)
	{
		printf("������磡");
		exit(1);
	}
	if (i != j && x != 0)
	{
		printf("�ǶԽ�����Ԫ��ֵ����Ϊ��");
		exit(1);
	}
	if (i == j)
		d[i] = x; 	
}
void main()
{
	int i,j;
	int D[n][n] ={{2,0,0,0},{0,1,0,0},{0,0,4,0},{0,0,0,6}};
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			Store(D[i][j],i,j);
	for(i=0;i<n;i++)
	   printf("%d  ",d[i]);
  printf("\n");
}
